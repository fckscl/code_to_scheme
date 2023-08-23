#include "menu.h"
#include "ui_menu.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "from_filem.h"

#include <QMessageBox>

menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_2_clicked()
{
    MainWindow *w = new MainWindow();
    this->close();
    w->show();
}

void menu::on_pushButton_clicked()
{
    this->close();
}

void menu::on_spravka_clicked()
{
    QMessageBox::about(this, "Справка", "Версия: 1.0 \n"
                                        "Разработчик: fck.scl\n"
                                        "Почта для связи: dimapugach31102003@gmail.com\n");
}

void menu::on_file_clicked()
{
    From_FileM *f = new From_FileM;
    this->close();
    f->show();
}
