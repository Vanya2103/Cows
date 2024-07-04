#include "mainwindow.h"
#include "highscore.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try {
        HighScore highscore("highscore1.txt");
        MainWindow w(&highscore);
        w.setWindowTitle("BULLS&COWS");
        w.show();
        return a.exec();
    }
    catch (...) {
        return -1;
    }
}

