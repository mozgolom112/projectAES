#ifndef AES_H
#define AES_H

#include <QObject>
#include "ialgorithm.h"

#define KEYSIZE 32
#define IVSIZE 32
#define BLOCKSIZE 256
#define SALTSIZE 8

class Cipher : public QObject , public IAlgorithm
{
    Q_OBJECT
public:
    explicit Cipher(QObject* parent = nullptr);
    ~Cipher();

    /**
     * @brief encrypt a byte array with AES 256 CBC
     * @param passphrase
     * @param data the byte array to encrypt
     * @return
     */
    QByteArray encryptAlgorithm(QByteArray password, QByteArray &data);

    /**
     * @brief Decrypt a byte array with AES 256 CBC
     * @param passphrase
     * @param data the byte array to decrypt
     * @return
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
