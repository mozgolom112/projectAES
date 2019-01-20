#include "aes_main.h"
#include "ui_aes_main.h"
#include "setpath.h"
#include "cipher.h"

#include <QClipboard>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>



AES_main::AES_main(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::AES_main) {
    ui->setupUi(this);
    //Дефолтный метод стоит AES шифрование
    Method_of_algorithm = new Cipher(nullptr);


    //группа алгоритмов
    QActionGroup* group  = new QActionGroup(this);

    //Делаем их Checkable
    ui->Set_Algorithm_AES_256->setCheckable(true);
    ui->Set_Test_Algorithm->setCheckable(true);

    //Добавляем их в группу алгоритмов
    ui->Set_Algorithm_AES_256->setActionGroup(group);
    ui->Set_Test_Algorithm->setActionGroup(group);

    //Для демонстрации закомментируйте нижние две строчки
    ui->Set_Test_Algorithm->setDisabled(true);
    ui->Set_Test_Algorithm->setVisible(false);

    //Ставим уникальность галочки
    group->setExclusive(true);
}

AES_main::~AES_main() {
    delete Method_of_algorithm;
    delete ui;
}

void AES_main::on_encrypt_clicked() {


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
                QByteArray encrypted = Method_of_algorithm->encryptAlgorithm(passphrase.toLatin1(), plain);

                ui->takeText->setText(encrypted.toBase64());
                //производим очистку текста, с которым мы работали, после работы программы
                ui->setText->clear();
            }
            catch (...) {
                QMessageBox::critical(this, "Error", "Ошибка шифрования");
            }
        }
    }

}

void AES_main::on_decrypt_clicked() {


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


                QByteArray decrypted = Method_of_algorithm->decryptAlgorithm(passphrase.toLatin1(), encrypted);

                ui->takeText->setText(decrypted);
                //производим очистку текста, с которым мы работали, после работы программы
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

//Выбор алгоритма

void AES_main::on_Set_Algorithm_AES_256_triggered()
{
    if (!(ui->Set_Algorithm_AES_256->isChecked())){ //проверка, если он уже выбран

    delete Method_of_algorithm;

    Method_of_algorithm = new Cipher(nullptr);
    }
}



void AES_main::on_Set_Test_Algorithm_triggered()
{
    //Инструкция по созданию кнопки для нового алгоритма
    /*
    if (!(ui->Set_Test_Algorithm->isChecked())){    //проверка, если Ваш алгоритм уже выбран

    delete Method_of_algorithm;                      //удаляем предыдущий алгоритм

    Method_of_algorithm = new Test_algorithm(nullptr);  //создаете экземпляр нового алгоритма, который должен быть унаследован от IAlgorithm
    }
    */
}
