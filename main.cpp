#include "aes_main.h"
#include "cipher.h"

#include <QApplication>


int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/img/img/icons.png"));
    AES_main w;
    w.show();

    return a.exec();
}

