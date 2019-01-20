#ifndef SETPATH_H
#define SETPATH_H

#include <QDialog>

namespace Ui {
    class set_path_window;
}

class SetPath : public QDialog {
    Q_OBJECT

public:
    explicit SetPath(QWidget *parent, const bool isWrite, const bool isResult);

    ~SetPath();

    QString GetPath();

private
    slots:

    void on_Choose_clicked();

    void on_clear_clicked();

private:
    Ui::set_path_window *ui;
    bool isWrite_{false};
    bool isResult_{false};
    QString path;

};

#endif // SETPATH_H
