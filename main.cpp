#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Obliczanie wartości i współczynników wielomianu interpolacyjnego Lagrange'a oraz wartości wielomianu algorytmem Neville'a");
    w.show();
    return a.exec();
}
