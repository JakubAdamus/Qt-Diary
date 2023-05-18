#include "mainwindow.h"
#include "program.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Program program;
    MainWindow w(nullptr, &program);

    w.show();
    return a.exec();
}
