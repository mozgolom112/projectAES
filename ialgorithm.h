#ifndef IALGORITHM_H
#define IALGORITHM_H

#include <QObject>

class IAlgorithm
{
public:

    virtual ~IAlgorithm(){}

    virtual QByteArray encryptAlgorithm(QByteArray password, QByteArray &data_for_encrypt) = 0;

    virtual QByteArray decryptAlgorithm(QByteArray password, QByteArray &data_for_decrypt) = 0;

};

#endif // IALGORITHM_H
