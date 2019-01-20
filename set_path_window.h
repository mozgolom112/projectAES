#ifndef SETPATH_H
#define SETPATH_H

#include <QDialog>

namespace Ui {
    class set_path_window;
}
/**
 * @brief The SetPath class - class with UI, which sets path to files
 */
class SetPath : public QDialog {
    Q_OBJECT

public:
    explicit SetPath(QWidget *parent, const bool isWrite, const bool isResult);

    ~SetPath();

    /**
     * @brief GetPath - returns path to file. Called from MainWindow
     * @return
     */
    QString GetPath();

private
    slots:
    /**
     * @brief on_Choose_clicked - response to the "Select"("Выбрать") button.
     * Does checks, and if the path is selected correctly,
     * saves it to the Path variable
     * and closes the current window.
     */
    void on_Choose_clicked();

    /**
     * @brief on_clear_clicked - "Clear"("Очистить") button response.
     * Clears the workspace to set the path
     */
    void on_clear_clicked();

private:
    Ui::set_path_window *ui;

    /**
    * @brief isWrite_ - bool variable, for understanding whether to write or read,
    * search for the path to the file
    */
    bool isWrite_{false};

    /**
    * @brief isResult_ - bool variable,
    * for understanding whether the result of the program is saved,
    * or the text entered by the user
    */
    bool isResult_{false};


    /**
     * @brief path - variable for path to file
     */
    QString path;

};

#endif // SETPATH_H
