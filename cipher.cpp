#include "cipher.h"
#include "ialgorithm.h"

#include <QDebug>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/aes.h>



Cipher::Cipher(QObject* parent) : QObject(parent) {
    initalize();
}

Cipher::~Cipher() {
    finalize();
}

QByteArray Cipher::encryptAlgorithm(QByteArray passphrase, QByteArray &data) {
    QByteArray msalt = randomBytes(SALTSIZE);
    int rounds = 1;
    unsigned char key[KEYSIZE];
    unsigned char iv[IVSIZE];

    const unsigned char* salt = reinterpret_cast<const unsigned char*>(msalt.constData());
    const unsigned char* password = reinterpret_cast<const unsigned char*>(passphrase.constData());

    int i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt, password, passphrase.length(), rounds, key, iv);

    if (i != KEYSIZE) {
        qCritical() << "EVP_BytesToKey() error: " << ERR_error_string(ERR_get_error(), nullptr);
        return QByteArray();
    }

    EVP_CIPHER_CTX* en;
    en = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_init(en);

    if (!EVP_EncryptInit_ex(en, EVP_aes_256_cbc(), nullptr, key, iv)) {
        qCritical() << "EVP_EncryptInit_ex() failed " << ERR_error_string(ERR_get_error(), nullptr);
        throw ::std::exception(ERR_error_string(ERR_get_error(), nullptr));
        return QByteArray();
    }

    char *input = data.data();
    int len = data.size();

    int c_len = len + AES_BLOCK_SIZE, f_len = 0;
    unsigned char *ciphertext = reinterpret_cast<unsigned char*>(malloc(c_len));

    if (!EVP_EncryptInit_ex(en, nullptr, nullptr, nullptr, nullptr)) {
        qCritical() << "EVP_EncryptInit_ex() failed " << ERR_error_string(ERR_get_error(), nullptr);
        throw ::std::exception(ERR_error_string(ERR_get_error(), nullptr));
        return QByteArray();
    }

    // May have to repeat this for large files

    if (!EVP_EncryptUpdate(en, ciphertext, &c_len, reinterpret_cast<unsigned char *>(input), len)) {
        qCritical() << "EVP_EncryptUpdate() failed " << ERR_error_string(ERR_get_error(), nullptr);
        throw ::std::exception(ERR_error_string(ERR_get_error(), nullptr));
        return QByteArray();
    }

    if (!EVP_EncryptFinal(en, ciphertext + c_len, &f_len)) {
        qCritical() << "EVP_EncryptFinal_ex() failed " << ERR_error_string(ERR_get_error(), nullptr);
        throw ::std::exception(ERR_error_string(ERR_get_error(), nullptr));
        return QByteArray();
    }

    len = c_len + f_len;
    EVP_CIPHER_CTX_cipher(en);

    //ciphertext

    QByteArray encrypted = QByteArray(reinterpret_cast<char*>(ciphertext), len);
    QByteArray finished;
    finished.append("Salted__");
    finished.append(msalt);
    finished.append(encrypted);

    free(ciphertext);

    return finished;
}

QByteArray Cipher::decryptAlgorithm(QByteArray passphrase, QByteArray &data) {
    QByteArray msalt;
    if (QString(data.mid(0, 8)) == "Salted__") {
        msalt = data.mid(8, 8);
        data = data.mid(16);
    } else {
        qWarning() << "Could not load salt from data!";
        msalt = randomBytes(SALTSIZE);
    }

    int rounds = 1;
    unsigned char key[KEYSIZE];
    unsigned char iv[IVSIZE];
    const unsigned char *salt = reinterpret_cast<const unsigned char*>(msalt.constData());
    const unsigned char *password = reinterpret_cast<const unsigned char*>(passphrase.data());

    int i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt, password, passphrase.length(), rounds, key, iv);

    if (i != KEYSIZE) {
        qCritical() << "EVP_BytesToKey() error: " << ERR_error_string(ERR_get_error(), nullptr);
        throw ::std::exception(ERR_error_string(ERR_get_error(), nullptr));
        return QByteArray();
    }

    EVP_CIPHER_CTX* de;
    de = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_init(de);

    if (!EVP_DecryptInit_ex(de, EVP_aes_256_cbc(), nullptr, key, iv)) {
        qCritical() << "EVP_DecryptInit_ex() failed" << ERR_error_string(ERR_get_error(), nullptr);
        throw ::std::exception(ERR_error_string(ERR_get_error(), nullptr));
        return QByteArray();
    }

    char* input = data.data();
    int len = data.size();

    int p_len = len, f_len = 0;
    unsigned char* plaintext = reinterpret_cast<unsigned char*>(malloc(p_len + AES_BLOCK_SIZE));

    //May have to do this multiple times for large data???
    if (!EVP_DecryptUpdate(de, plaintext, &p_len, reinterpret_cast<unsigned char*>(input), len)) {
        qCritical() << "EVP_DecryptUpdate() failed " << ERR_error_string(ERR_get_error(), nullptr);
        throw ::std::exception(ERR_error_string(ERR_get_error(), nullptr));
        return QByteArray();
    }

    if (!EVP_DecryptFinal_ex(de, plaintext + p_len, &f_len)) {
        qCritical() << "EVP_DecryptFinal_ex() failed " << ERR_error_string(ERR_get_error(), nullptr);
        throw ::std::exception(ERR_error_string(ERR_get_error(), nullptr));
        return QByteArray();
    }

    len = p_len + f_len;

    EVP_CIPHER_CTX_cleanup(de);


    QByteArray decrypted = QByteArray(reinterpret_cast<char*>(plaintext), len);
    free(plaintext);

    return decrypted;
}

QByteArray Cipher::randomBytes(int size) {

    unsigned char* arr = new unsigned char[size];
    RAND_bytes(arr, size);

    QByteArray buffer = QByteArray(reinterpret_cast<char *>(arr), size);
    return buffer;

}


void Cipher::initalize() {
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(nullptr);
}

void Cipher::finalize() {
    EVP_cleanup();
    ERR_free_strings();
}


