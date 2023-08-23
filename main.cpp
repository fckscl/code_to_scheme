#include "mainwindow.h"
#include "menu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    /*QStringList paths(QApplication::libraryPaths());
        paths.append(".");
        QApplication::setLibraryPaths(paths);*/
    QApplication a(argc, argv);
    menu w;
    w.show();
    return a.exec();
}
