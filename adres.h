#ifndef ADRES_H
#define ADRES_H

#include <QDialog>

namespace Ui {
class adres;
}

class adres : public QDialog
{
    Q_OBJECT

public:
    explicit adres(QWidget *parent = nullptr);
    ~adres();

private:
    Ui::adres *ui;
};

#endif // ADRES_H
