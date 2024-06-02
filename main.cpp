#include "mainwindow.h"
#include "Affairwidget.h"
#include "Mydatabase.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AffairWidget w;
    w.show();
    QSqlDatabase database;

    return a.exec();
}
