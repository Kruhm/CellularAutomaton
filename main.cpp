#include "cabase.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CAbase gameWindow;
    gameWindow.show();

    return a.exec();
}
