#include "main_window.h"
#include <QApplication>


int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/img/img/icons.png"));
    MainWindow w;
    w.show();

    return a.exec();
}

