#include "aes_main.h"
#include "ui_aes_main.h"
#include "setpath.h"
#include <cipher.h>
#include <QClipboard>
#include <QMessageBox>
#include <QPixmap>
#include <QDir>
#include <QTextStream>

AES_main::AES_main(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::AES_main) {
    ui->setupUi(this);
}

AES_main::~AES_main() {
    delete ui;
}

void AES_main::on_encrypt_clicked() {
    Cipher cWrapper;


    QString textforcipher = ui->setText->toPlainText();
    QString pass = ui->setPass->text();
    if (pass == "") {
        QMessageBox::critical(this, "Error", "Введите пароль");
    } else {
        if (textforcipher == "") {
            QMessageBox::critical(this, "Error", "Введите текст для шифрования");
        } else {
            QString passphrase = pass;
            QByteArray plain = QByteArray::fromStdString(textforcipher.toStdString());

            try {
                QByteArray encrypted = cWrapper.encryptAES(passphrase.toLatin1(), plain);

                ui->takeText->setText(encrypted.toBase64());
                //производим очистку Пароля и текста, с которым мы работали, после работы программы
                ui->setPass->clear();
                ui->setText->clear();
            }
            catch (...) {
                QMessageBox::critical(this, "Error", "Ошибка шифрования");
            }
        }
    }

}

void AES_main::on_decrypt_clicked() {
    Cipher cWrapper;


    if (ui->setText->toPlainText().toStdString() == "") {
        QMessageBox::critical(this, "Error", "Введите текст для дешифрования");
    } else {
        QByteArray encrypted = QByteArray::fromBase64(
                QByteArray::fromStdString(ui->setText->toPlainText().toStdString()));

        QString passphrase = ui->setPass->text();
        if (passphrase == "") {
            QMessageBox::critical(this, "Error", "Введите пароль");
        } else {
            try {


                QByteArray decrypted = cWrapper.decryptAES(passphrase.toLatin1(), encrypted);

                ui->takeText->setText(decrypted);
                //производим очистку Пароля и текста, с которым мы работали, после работы программы
                ui->setPass->clear();
                ui->setText->clear();
            } catch (...) {
                QMessageBox::critical(this, "Error",
                                      "Ошибка дешифрования.\nУбедитесь, что ввели правильный текст для дешифроки и правильный пароль");
            }
        }
    }

}


void AES_main::on_Button_for_copy1_clicked() {
    QApplication::clipboard()->setText(ui->setText->toPlainText());
}

void AES_main::on_Button_for_cut1_clicked() {
    ui->setText->clear();
    ui->setText->setFocus();
}

void AES_main::on_Button_for_copy2_clicked() {
    QApplication::clipboard()->setText(ui->takeText->toPlainText());
}

void AES_main::on_Button_for_cut1_2_clicked() {
    ui->takeText->clear();
}

void AES_main::on_Load_triggered() {
    SetPath window(this, false, false);
    window.setModal(true);
    window.exec();
    QString path = window.GetPath();
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        QString str = stream.readAll();

        ui->setText->setPlainText(str);


    }
    ui->setText->moveCursor(QTextCursor::End);
    file.close();

}

void AES_main::on_save_text_triggered() {
    SetPath window(this, true, false);
    window.setModal(true);
    window.exec();
    QString path = window.GetPath();
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        QString writing = ui->setText->toPlainText();
        QTextStream stream(&file);
        stream << writing;

    } else {
        //на случай важных переговоров
        QMessageBox::warning(this, "Ошибка", "Произошла ошибка. Запись не была создана.");
    }
    file.close();
}

void AES_main::on_save_result_triggered() {
    SetPath window(this, true, true);
    window.setModal(true);
    window.exec();
    QString path = window.GetPath();
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        QString writing = ui->takeText->toPlainText();
        QTextStream stream(&file);
        stream << writing;

    } else {
        //на случай важных переговоров
        QMessageBox::warning(this, "Ошибка", "\nПроизошла ошибка. Запись не была создана.");
    }
    file.close();
}

void AES_main::on_help_triggered() {
    QMessageBox::information(this, "Помощь", "\n8 (800) 100-49-94. Кризисная линия доверия. Круглосуточно");
}

void AES_main::on_Quit_triggered() {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Выход из программы",
                                                              "Вы уверены, что хотите выйти?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {

    } else {
        QApplication::quit();
    }

}


void AES_main::on_showPass_clicked(bool checked) {
    if (checked) {
        ui->setPass->setEchoMode(QLineEdit::EchoMode(0));
    } else {
        ui->setPass->setEchoMode(QLineEdit::EchoMode(2));
    }
}
