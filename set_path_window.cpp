#include "setpath.h"
#include "ui_setpath.h"
#include "aes_main.h"


#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QDate>



SetPath::SetPath(QWidget *parent, const bool isWrite, const bool isResult) :
        QDialog(parent),
        isWrite_(isWrite),
        isResult_(isResult),
        ui(new Ui::SetPath) {
    ui->setupUi(this);

    ui->setpath->setText(QDir::currentPath()); //по умолчанию ставим путь, откуда вызвался exe
    if (isWrite_) {
        QString date = QDateTime::currentDateTime().toString("[dd-MM-yyyy](hh_mm_ss)");
        ui->setpath->insert("/" + date);
        if (isResult_) {
            ui->setpath->insert("output.txt");
        } else {
            ui->setpath->insert("input.txt");
        }
    }
}


SetPath::~SetPath() {
    delete ui;
}

QString SetPath::GetPath() {
    return path;
}

void SetPath::on_Choose_clicked() {
    path = ui->setpath->text().trimmed();
//.trimmed() удаление в начале и в конце пробелов и табуляции
    qDebug() << path;
    if (!path.isEmpty()) {
        if (path.endsWith(".txt")) {
            if (QFile(path).exists()) {
                if (isWrite_) {
                    QMessageBox::StandardButton reply = QMessageBox::question(this, "Запись",
                                                                              "Файл с таким именем существует. Хотите его перезаписать?",
                                                                              QMessageBox::Yes | QMessageBox::No);
                    if (reply == QMessageBox::No) {

                    } else {
                        close();
                    }
                } else {
                    close();
                }
            } else {
                if (!isWrite_) {
                    QMessageBox::information(this, "Ошибка пути",
                                             "Файл по данному пути не найден\nПроверьте, что ввели путь правильно");
                } else {
                    //проверка пути до папки
                    QString dir = path;
                    dir.truncate(path.lastIndexOf('/') + 1);// обрезаем до папки
                    qDebug() << dir;
                    if (QFile(dir).exists()) {
                        close();
                    } else {
                        QMessageBox::information(this, "Ошибка пути", "Путь до папки с файлом не существует");
                    }
                }
            }
        } else {
            if (!path.endsWith("/")) {
                QMessageBox::information(this, "Ошибка пути", "Выбрано не верное расширение");
            } else {
                QMessageBox::information(this, "Ошибка пути",
                                         "Вы прописали путь до папки.\nПропишите путь до конца (до файла)");
            }

        }
    } else {
        QMessageBox::information(this, "Ошибка пути", "Введена пуста строка\nВведите путь");
    }
}

void SetPath::on_clear_clicked() {
    ui->setpath->clear();
    ui->setpath->setFocus();
}
