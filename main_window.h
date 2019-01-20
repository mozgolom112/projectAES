#ifndef AES_MAIN_H
#define AES_MAIN_H

#include <QMainWindow>
#include <QActionGroup>

#include "cipher.h"

namespace Ui {
    class AES_main;
}

class AES_main : public QMainWindow {
    Q_OBJECT

public:
    explicit AES_main(QWidget *parent = nullptr);

    ~AES_main();

private
    slots:
    void on_encrypt_clicked();

    void on_decrypt_clicked();

    void on_Button_for_copy1_clicked();

    void on_Button_for_cut1_clicked();

    void on_Button_for_copy2_clicked();

    void on_Button_for_cut1_2_clicked();

    void on_Load_triggered();

    void on_save_text_triggered();

    void on_save_result_triggered();

    void on_Quit_triggered();

    void on_showPass_clicked(bool checked);

    void on_Set_Algorithm_AES_256_triggered();

    void on_Set_Test_Algorithm_triggered();

private:
    Ui::AES_main *ui;

    IAlgorithm* Method_of_algorithm {nullptr};

    QActionGroup* Algorithm_group {nullptr};
};

#endif // AES_MAIN_H
