#ifndef FROM_FILE_H
#define FROM_FILE_H

#include <QDialog>

namespace Ui {
class from_file;
}

class from_file : public QDialog
{
    Q_OBJECT

public:
    explicit from_file(QWidget *parent = nullptr);
    ~from_file();

private slots:
    void on_pyt_file_clicked();

    void on_exit_clicked();

    void on_menu_clicked();

    void on_zapis_clicked();

private:
    Ui::from_file *ui;
};

#endif // FROM_FILE_H
