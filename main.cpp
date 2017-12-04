#include "cabase.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    CAbase w;
    w.show();

    return a.exec();
}
