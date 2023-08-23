#include "adres.h"
#include "ui_adres.h"

adres::adres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adres)
{
    ui->setupUi(this);
}

adres::~adres()
{
    delete ui;
}
