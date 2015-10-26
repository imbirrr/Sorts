#include "sortsmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SortsMainWindow w;
    w.show();

    return a.exec();
}
