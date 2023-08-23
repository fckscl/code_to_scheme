#ifndef FROM_FILEM_H
#define FROM_FILEM_H

#include <QWidget>

namespace Ui {
class From_FileM;
}

class From_FileM : public QWidget
{
    Q_OBJECT

public:
    explicit From_FileM(QWidget *parent = nullptr);
    ~From_FileM();

private slots:
    void on_pyt_file_clicked();

    void on_zapis_clicked();

    void on_menu_clicked();

    void on_pushButton_clicked();

    void on_draw_clicked();

private:
    Ui::From_FileM *ui;
};

class Canvas : public QWidget
{
    Q_OBJECT
public:
    Canvas(QWidget* parent=0):QWidget(parent){}
    ~Canvas(){}
    void paintEvent(QPaintEvent*);

protected:
};

#endif // FROM_FILEM_H
