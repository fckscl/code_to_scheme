#include "from_file.h"
#include "ui_from_file.h"
#include "mainwindow.h"
#include "menu.h"

#include <QFile>
#include <QFileDialog>

from_file::from_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::from_file)
{
    ui->setupUi(this);
}

from_file::~from_file()
{
    delete ui;
}

void from_file::on_pyt_file_clicked()
{
    ui->plainTextEdit->clear();
    QFile kod(QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.cpp *.txt"));
    //чтение кода из файла, который указал пользователь
    if ((kod.exists())&&(kod.open(QIODevice::ReadOnly)))
    {
        ui->plainTextEdit->setPlainText(kod.readAll());
        kod.close();
    }
}

void from_file::on_exit_clicked()
{
    this->close();
}

void from_file::on_menu_clicked()
{
    menu* o = new menu();
    o->show();
    this->close();
}


void from_file::on_zapis_clicked()
{
    QFile temp_file("E:\\AI\\QT\\canvas\\input.txt");
    if(temp_file.open(QIODevice::WriteOnly)){
        temp_file.write(ui->plainTextEdit->toPlainText().toUtf8());
        temp_file.close();
    }
}
