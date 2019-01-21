#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "algorithm_aes.h"

#include <QMainWindow>
#include <QActionGroup>
#include <QShortcut>


namespace Ui {
    class main_window;
}
/**
 * @brief The MainWindow class - class with Ui designed to work with the user
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private
    slots:
    /**
     * @brief on_encrypt_clicked - signal processing of the "Encrypt"("Шифрование") button.
     * Encrypts data
     * Use hot key: Ctrl + E
     */
    void on_encrypt_clicked();

    /**
     * @brief on_decrypt_clicked - signal processing of the "Decrypt"("Дешифрование") button.
     * Decrypts data
     * Use hot key: Ctrl + D
     */
    void on_decrypt_clicked();

    /**
     * @brief on_Button_for_copy1_clicked - signal processing of the "Сopy"("Копировать") button.
     * Copies the text entered by the user to the clipboar
     */
    void on_Button_for_copy1_clicked();

    /**
     * @brief on_Button_for_cut1_clicked - signal processing of the "Clear"("Очистить") button.
     * Clears the workspace where the user enters text.
     */
    void on_Button_for_cut1_clicked();

    /**
     * @brief on_Button_for_copy2_clicked - signal processing of the "Сopy"("Копировать") button.
     * Copies the result of the program to the clipboar
     */
    void on_Button_for_copy2_clicked();

    /**
     * @brief on_Button_for_cut1_2_clicked - signal processing of the "Clear"("Очистить") button.
     * Clears the workspace where the result of the program is displayed.
     */
    void on_Button_for_cut1_2_clicked();

    /**
     * @brief on_Load_triggered - signal processing of the menu's button "Upload file"("Загрузить файл").
     * Calls the Path window and uploads text from the file to the workspace for the user's text.
     * Use hot key: Ctrl + L
     */
    void on_Load_triggered();

    /**
     * @brief on_save_text_triggered - signal processing of the menu's button "Save entered text"("Сохранить введенный текст").
     * Calls the Path window and saves the text from the user's workspace to a file in the selected path.
     * Use hot key: Ctrl + T
     */
    void on_save_text_triggered();

    /**
     * @brief on_save_result_triggered - signal processing of the menu's button "Save result"("Сохранить результат").
     * Calls the Path window and save the text from the workspace with the result of the program to the selected file.
     * Use hot key: Ctrl + R
     */
    void on_save_result_triggered();

    /**
     * @brief on_Quit_triggered - signal processing of the menu's button "Quit"("Выход").
     * Exit from the program
     * Use hot key: Ctrl + Q
     */
    void on_Quit_triggered();

    /**
     * @brief on_showPass_clicked - reacts to the radio botton near with workspace for password.
     * Makes the password visible, or vice versa
     * @param checked
     */
    void on_showPass_clicked(bool checked);

    /**
     * @brief on_Set_Algorithm_AES_256_triggered - signal processing of the menu's button "AES 256 (Open SSL)".
     * Removes the previous encryption method and creates an instance of the AES_algorithm class.
     * Sets the mode of operation of the application with the AES algorithm
     */
    void on_Set_Algorithm_AES_256_triggered();

    /**
     * @brief on_Set_Test_Algorithm_triggered - signal processing of the menu's button "Another algoritm".
     * Instructions for creating an algorithm selection button
     */
    void on_Set_Test_Algorithm_triggered();
private:
    Ui::main_window *ui;

    /**
      *@brief Method_of_algorithm - encryption and decryption algorithm.
      *Any class inherited from the interface IAlgorithm.
      */
    IAlgorithm* Method_of_algorithm {nullptr};

    /**
      *@brief Algorithm_group - group of all algorithms available in the menu
      *Visualize the selection of the current algorithm.
      */
    QActionGroup* Algorithm_group {nullptr};

    /**
     * @brief keyCtrlE - object for hot keyCtrl + E.
     * Hot key for botton "Encrypt"("Шифрование")
     */
    QShortcut* keyCtrlE {nullptr};

    /**
     * @brief keyCtrlD - object for hot keyCtrl + D.
     * Hot key for botton "Decrypt"("Дешифрование")
     */
    QShortcut* keyCtrlD {nullptr};

};

#endif // MAIN_WINDOW_H
