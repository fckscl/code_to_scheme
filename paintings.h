#ifndef PAINTINGS_H
#define PAINTINGS_H
#include <QPainter>

int big_blok(QString* s);

//рисование if
void ysl(QPainter*, int, int, QString, QString);

//рисование циклов
void cikl(QPainter*, int, int*, QString);

void conec_cikl(QPainter*, int, int*, QString);

#endif // PAINTINGS_H
