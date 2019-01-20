#ifndef IALGORITHM_H
#define IALGORITHM_H

#include <QObject>

/**
 * @brief The IAlgorithm class - interface for different algorithms
 */
class IAlgorithm
{
public:
    virtual ~IAlgorithm(){}

    /**
     * @brief virtual method for algorithms of encrypting
     * @param password
     * @param data_for_encrypt - data, which should be encrypted
     * @return encrypted data
     */
    virtual QByteArray encryptAlgorithm(QByteArray password, QByteArray &data_for_encrypt) = 0;

    /**
     * @brief virtual method for algorithms of decrypting
     * @param password
     * @param data_for_decrypt - data, which should be decrypted
     * @return decrypted data
     */
    virtual QByteArray decryptAlgorithm(QByteArray password, QByteArray &data_for_decrypt) = 0;

};

#endif // IALGORITHM_H
