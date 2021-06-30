#include "mainwindow.h"
#include "startwindow.h"
#include "tablewindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;
    StartWindow s;
    tablewindow t;
        s.show();
    return a.exec();
}
