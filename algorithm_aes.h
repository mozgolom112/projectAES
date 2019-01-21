#ifndef AES_H
#define AES_H

#include <QObject>
#include "ialgorithm.h"

#define KEYSIZE 32
#define IVSIZE 32
#define BLOCKSIZE 256
#define SALTSIZE 8


/**
 * @brief The AES_algorithm class - realized class, which use AES_256 algorithm for (de\en)crypt.
 * Powered by OpenSSl
 */
class AES_algorithm : public QObject , public IAlgorithm
{
    Q_OBJECT
public:
    explicit AES_algorithm(QObject* parent = nullptr);
    ~AES_algorithm();

    /**
     * @brief Encrypt a byte array with AES 256 CBC
     * @param password, which use to for randomies bytes
     * @param data - data, which should be encrypted
     * @return encrypted data
     */
    QByteArray encryptAlgorithm(QByteArray password, QByteArray &data);

    /**
     * @brief Decrypt a byte array with AES 256 CBC
     * @param password which use to for randomies bytes
     * @param data - data to decrypt
     * @return decrypted data
     */
    QByteArray decryptAlgorithm(QByteArray password, QByteArray &data);

signals:

public slots:

private:
        /**
         * @brief Get a byte array filled with random information
         * @param size The size of the byte array to generate
         * @return
         */
        QByteArray randomBytes(int size);

        /**
        * @brief initalize the OpenSSL lib
        */
        void initalize();

        /**
         * @brief Cleanup after the OpenSSL lib
         */
        void finalize();


};

#endif // AES_H
