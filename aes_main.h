#ifndef AES_MAIN_H
#define AES_MAIN_H

#include <QMainWindow>

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
            void

    on_encrypt_clicked();

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

private:
    Ui::AES_main *ui;
};

#endif // AES_MAIN_H
