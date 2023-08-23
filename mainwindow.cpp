#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "structSkobki.h"
#include "menu.h"

#include <QPainter>
#include <QStack>
#include <QScrollArea>
#include <QFile>
#include <QPicture>
#include <QMessageBox>
#include <QFileDialog>

int big_blok1(QString* s)
{
    QString ostatok = *s;
    int i = 0;
    int kol_vo_strok = 1;
    //обрезаю длину строки
    while(ostatok.size() > 12){
        kol_vo_strok++;
        i += 12;
        ostatok.clear();
        (*s).insert(i, "\n");
        for (int j = i; j < (*s).size(); j++){
            ostatok += (*s)[j];
        }
    }
    //увеличиваю высоту блока, исходя из количества получившихся строк
    int plus_y = 0;
    if (kol_vo_strok > 6){
        plus_y += (kol_vo_strok - 6) * 17;
    }
    return plus_y;
}

void ysl1(QPainter* paint, int x, int y, QString str, QString s)
{
    for (int i = str.indexOf("(") + 1; i < str.indexOf(")"); i++){
        s += str[i];
    }
    paint->drawLine(x+50, y-50, x+50, y);
    QRect* r = new QRect();
    r->setCoords(x, y, x + 100, y + 100);
    // рисование ромба
    paint->drawText(*r, Qt::AlignCenter, s);
    QPointF i_points[5] = {
        QPointF(x, y + 50),
        QPointF(x + 50, y),
        QPointF(x + 100, y + 50),
        QPointF(x + 50, y + 100),
        QPointF(x, y + 50)
    };
    paint->drawPolyline(i_points, 5);
    //рисование линий соединения
    paint->drawLine(x, y+50, x-50, y+50);
    paint->drawLine(x-50, y+50, x-50, y+100);
    paint->drawLine(x+100, y+50, x+150, y+50);
    paint->drawLine(x+150, y+50, x+150, y+100);
}

void cikl1(QPainter* paint, int x , int* y, QString s)
{
    paint->drawLine(x+50, (*y)-50, x+50, (*y));
    QRect* r = new QRect();
    int plus_y = 100;
    if (s.size() > 14){
        plus_y += big_blok1(&s);
        r->setCoords(x, (*y)+25, x+100, (*y)+plus_y);
    } else {
        r->setCoords(x, (*y), x+100, (*y)+100);
    }
    //рисование фигуры со срезанными углами
    QPointF c_points[7] = {
        QPointF(x, (*y)+plus_y),
        QPointF(x, (*y)+25),
        QPointF(x+25, (*y)),
        QPointF(x+75, (*y)),
        QPointF(x+100, (*y)+25),
        QPointF(x+100, (*y)+plus_y),
        QPointF(x, (*y)+plus_y)
    };
    paint->drawPolyline(c_points, 7);
    //текст
    paint->drawText(*r, Qt::AlignCenter, s);
    *y += plus_y + 50;
}

void conec_cikl1(QPainter* paint, int x, int *y, QString s)
{
    paint->drawLine(x+50, (*y)-50, x+50, (*y));
    QRect* r = new QRect();
    int plus_y = 0;
    if (s.size() > 14){
        plus_y += big_blok1(&s);
        r->setCoords(x, (*y), x+100, (*y)+75+plus_y);
    } else {
        r->setCoords(x, (*y), x+100, (*y)+100);
    }
    //рисование фигуры со срезанными нижними углами
    QPointF c_points[7] = {
        QPointF(x, (*y)),
        QPointF(x, (*y)+75+plus_y),
        QPointF(x+25, (*y)+100+plus_y),
        QPointF(x+75, (*y)+100+plus_y),
        QPointF(x+100, (*y)+75+plus_y),
        QPointF(x+100, (*y)),
        QPointF(x, (*y))
    };
    paint->drawPolyline(c_points, 7);
    //текст
    paint->drawText(*r, Qt::AlignCenter, s);
    *y += plus_y + 150;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //отображение виджета рисования в главном окне
    canvas* wt = new canvas;
    QSize s_wt;
    s_wt.setWidth(1000);
    if (ui->size_10->isChecked()){
        s_wt.setHeight(1500);
    } else if (ui->size_20->isChecked()){
        s_wt.setHeight(3000);
    } else if (ui->size_50->isChecked()){
        s_wt.setHeight(7500);
    } else if (ui->size_70->isChecked()){
        s_wt.setHeight(11000);
    } else if (ui->size_100->isChecked()){
        s_wt.setHeight(15000);
    }
    wt->setMinimumSize(s_wt);
    ui->scrollArea->setWidget(wt);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setBackgroundRole(QPalette::Light);
}

void canvas::paintEvent(QPaintEvent *)
{
    QFile file("input.txt");
    QStack <Skobki> level;
    QPainter paint(this);
    QStringList strList;
    //запись из файла input.txt программу, которую ввел пользователь
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        QString str="";
        while(!file.atEnd())
        {
            str=file.readLine();
            strList.push_back(str);
        }
        file.close();
    }
    //отрисовка схемы
    int x = 500, y = 0;
    QRect* begin = new QRect();
    begin->setCoords(x-50, y, x+150, y+100);
    y += 150;
    paint.drawRoundedRect(*begin, 20, 20);
    paint.drawText(*begin, Qt::AlignCenter, "Begin");
    bool int_main = false;
    bool else_if = false;
    bool elif = false;
            int s_else = 0;
    for (int i = 0; i < strList.size(); i++){
        QString str = strList[i];
        while (str[0] == " "){
            str.remove(0, 1);
        }
        QString s = "";
        if (str.indexOf("else if") != -1){
            QString temp_str = "";
            for (int i = str.indexOf("else") + 4; i < str.size(); i++){
                temp_str += str[i];
            }
            strList.insert(i+1, temp_str);
            str.truncate(str.indexOf("else") + 4);
            else_if = true;
            s_else++;
        }
        int else_x, else_y;
        bool lvl = level.isEmpty();
        if (!lvl){
            lvl = (level.top().s != "/*");
        }
        if (lvl & int_main){
            if (str.indexOf("/*") != -1){
                level.push({"/*", 100, 100});
                continue;
            } else if (str.indexOf("//") != -1) {
                continue;
            } else if (str.indexOf("if") != -1 && str.indexOf("else") == -1 ){                             //рисование блока условия
                level.push({"if", x+150, y+50});
                ysl1(&paint, x, y, str, s);
                y += 150;
                x -= 100;
            } else if (str.indexOf("while") != -1 || str.indexOf("for") != -1){                             //рисование циклов while и for
                for (int i = str.indexOf("(") + 1; i < str.indexOf(")"); i++){
                    s += str[i];
                }
                QString temp = "while " + s;
                level.push({temp, x, y});
                cikl1(&paint, x, &y, s);
            } else if (str.indexOf("}") != -1 && str.indexOf("{") == -1){
                // обработка закрытия различных блоков
                if (level.top().s == "if"){
                    if (str.indexOf("else") == -1){
                        // рисование линии возвращения к if-у
                        QPointF i_points[4] = {
                            QPointF(x+50, y-50),
                            QPointF(x+50, y+50),
                            QPointF(level.top().x, y+50),
                            QPointF(level.top().x, level.top().y),
                        };
                        paint.drawPolyline(i_points, 4);
                        x += 100;
                        y += 100;
                        level.pop();
                    } else if (str.indexOf("if") == -1) {
                        //рисование линии ложного условия else
                        else_x = x + 50;
                        else_y = y;
                        x = level.top().x - 50;
                        y = level.top().y + 100;
                        level.pop();
                        level.push({"else", else_x, else_y});
                    } else {
                        // рисование блока else if
                        x = level.top().x - 50;
                        y = level.top().y + 100;
                        //level.pop();
                        level.push({"else if", x+150, y+50});
                        ysl1(&paint, x, y, str, s);
                        y += 150;
                        x -= 100;
                    }
                    if (elif && str.indexOf("else") == -1){
                        for (int j = 0; j < s_else; j++){
                            strList.insert(i+1, "}");
                        }
                        s_else = 0;
                        else_if = false;
                    }
                } else if (level.top().s == "else") {
                    //соединение истиной и ложной линий условия
                    if (level.top().y <= y){
                        if (str.indexOf("if") == -1){
                            QPointF e_points[4] = {
                                QPointF(x+50, y-50),
                                QPointF(x+50, y+50),
                                QPointF(level.top().x, y+50),
                                QPointF(level.top().x, level.top().y-50),
                            };
                            paint.drawPolyline(e_points, 4);
                            x = x - 100;
                            y = y + 100;
                            level.pop();
                        }
                    } else {
                        QPointF e_points[4] = {
                            QPointF(level.top().x, level.top().y-50),
                            QPointF(level.top().x, level.top().y),
                            QPointF(x+50, level.top().y),
                            QPointF(x+50, y-50),
                        };
                        paint.drawPolyline(e_points, 4);
                        x = level.top().x + 50;
                        y = level.top().y + 50;
                        level.pop();
                    }
                    if (elif && str.indexOf("else") == -1){
                        for (int j = 0; j < s_else; j++){
                            strList.insert(i+1, "}");
                        }
                        s_else = 0;
                        else_if = false;
                    }
                } else if (level.top().s == "else if") {
                    // закрытие всех else if-ов
                    if (str.indexOf("else") == -1){
                        while (level.top().s == "if" || level.top().s == "else if"){
                            if (level.top().y <= y){
                                    QPointF e_points[4] = {
                                        QPointF(x+50, y-50),
                                        QPointF(x+50, y+50),
                                        QPointF(level.top().x, y+50),
                                        QPointF(level.top().x, level.top().y),
                                    };
                                    paint.drawPolyline(e_points, 4);
                                    x = x - 100;
                                    y = y + 50;
                                    level.pop();
                            } else {
                                QPointF e_points[4] = {
                                    QPointF(level.top().x, level.top().y-50),
                                    QPointF(level.top().x, level.top().y),
                                    QPointF(x+50, level.top().y),
                                    QPointF(x+50, y-50),
                                };
                                paint.drawPolyline(e_points, 4);
                                x = level.top().x + 50;
                                y = level.top().y + 50;
                                level.pop();
                            }
                        }
                    } else {
                        // рисование блока else if
                        x = level.top().x - 50;
                        y = level.top().y + 100;
                        //level.pop();
                        level.push({"else if", x+150, y+50});
                        ysl1(&paint, x, y, str, s);
                        y += 150;
                        x -= 100;
                    }
                } else if (level.top().s.indexOf("while") != -1) {
                    //рисование блока окончания цикла
                    s = "";
                    for (int i = level.top().s.indexOf(" "); i < level.top().s.size(); i++){
                        s += level.top().s[i];
                    }
                    conec_cikl1(&paint, x, &y, s);
                    level.pop();
                } else if (level.top().s.indexOf("main") != -1){
                    level.pop();
                    int_main = false;
                }
            } else if (str.size() > 1 && str.indexOf("{") == -1){                                                                      //рисование блока действия
                s = str;
                int plus_y = big_blok1(&s);
                paint.drawLine(x+50, y-50, x+50, y);
                QRect* r = new QRect();
                r->setCoords(x, y, x+100, y+100+plus_y);
                paint.drawRect(*r);
                paint.drawText(*r, Qt::AlignCenter, s);
                y += 150 + plus_y;
            }
        } else if (str.indexOf("*/") != -1 && !level.isEmpty()){
            level.pop();
        }
        if (str.indexOf("int main") != -1){
            level.push({"main", x, y});
            int_main = true;
        }
        if (else_if) elif = true;
    }
    paint.drawLine(x+50, y, x+50, y-50);
    QRect* end = new QRect();
    end->setCoords(x-50, y, x+150, y+100);
    paint.drawRoundedRect(*end, 20, 20);
    paint.drawText(*end, Qt::AlignCenter, "End");
}

void MainWindow::on_pushButton_2_clicked()
{
    //сохраняет нарисованную блок-схему в my.jpg
    canvas *i = new canvas;
    QSize s_wt;
    s_wt.setWidth(1000);
    if (ui->size_10->isChecked()){
        s_wt.setHeight(1500);
    } else if (ui->size_20->isChecked()){
        s_wt.setHeight(3000);
    } else if (ui->size_50->isChecked()){
        s_wt.setHeight(7500);
    } else if (ui->size_70->isChecked()){
        s_wt.setHeight(11000);
    } else if (ui->size_100->isChecked()){
        s_wt.setHeight(15000);
    } else {
        s_wt.setHeight(1000);
    }
    i->setMinimumSize(s_wt);
    QPixmap p(i->size());
    i->setAutoFillBackground(true);
    QPalette pal = i->palette();
    pal.setColor(QPalette::Window, Qt::white);
    i->setPalette(pal);
    i->render(&p, QPoint(), QRegion(), QWidget::DrawChildren);
    QString pyt_img = QFileDialog::getExistingDirectory(0, "Open Dialog", "");
    if (p.save(pyt_img.append("/my.jpg"))){
        QMessageBox::about(this, "Сохранение", "Изображение схемы my.jpg "
                                 "успешно сохранено в выбранную папку");
    } else {
        QMessageBox::warning(this, "Ошибка", "Что-то пошло не так");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    //запись текста из формы в файл input.txt
    QString s;
    QFile file("input.txt");
    s = ui->plainTextEdit->toPlainText();
    if(file.open(QIODevice::WriteOnly)){
        file.write(s.toUtf8());
        file.close();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    // возвращение в главное меню
    menu m;
    this->close();
    m.setModal(true);
    m.exec();
}

void MainWindow::on_text_clicked()
{
    ui->plainTextEdit->clear();
    QFile file("input.txt");
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        QString str = "";
        str = file.readAll();
        ui->plainTextEdit->setPlainText(str);
        file.close();
    }
}
