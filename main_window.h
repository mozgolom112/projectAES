#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QActionGroup>

#include "algorithm_aes.h"

namespace Ui {
    class main_window;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

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
    Ui::main_window *ui;

    IAlgorithm* Method_of_algorithm {nullptr};

    QActionGroup* Algorithm_group {nullptr};
};

#endif // MAIN_WINDOW_H
