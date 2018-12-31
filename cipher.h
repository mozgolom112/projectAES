#ifndef CIPHER_H
#define CIPHER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <openssl/engine.h>
#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/aes.h>







#define KEYSIZE 32
#define IVSIZE 32
#define BLOCKSIZE 256
#define SALTSIZE 8








class Cipher : public QObject
{
    Q_OBJECT
public:
    explicit Cipher(QObject *parent = nullptr); /* здесь возможно нужно будет поставить 0**/
    ~Cipher();

    /**
     * @brief encrypt a byte array with AES 256 CBC
     * @param passphrase
     * @param data the byte array to encrypt
     * @return
     */
    QByteArray encryptAES(QByteArray passphrase, QByteArray &data);

    /**
     * @brief Decrypt a byte array with AES 256 CBC
     * @param passphrase
     * @param data the byte array to decrypt
     * @return
     */
    QByteArray decryptAES(QByteArray passphrase, QByteArray &data);


    /**
     * @brief Get a byte array filled with random information
     * @param size The size of the byte array to generate
     * @return
     */
    QByteArray randomBytes(int size);



signals:

public slots:

private:



        /**
        * @brief initalize the OpenSSL lib
        */
        void initalize();

        /**
         * @brief Cleanup after the OpenSSL lib
         */
        void finalize();






};

#endif // CIPHER_H
