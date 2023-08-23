#include "spravka.h"
#include "ui_spravka.h"

spravka::spravka(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::spravka)
{
    ui->setupUi(this);
}

spravka::~spravka()
{
    delete ui;
}

void spravka::on_to_menu_clicked()
{
    this->close();
}

void spravka::on_exit_clicked()
{
    this->close();
}
