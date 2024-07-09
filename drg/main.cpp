#include "mainwindow.h"
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QDataStream>
#include <QByteArray>
#include <QLabel>
#include <QFrame>
#include <QPixmap>
#include <QPoint>
#include <QMouseEvent>
#include <QDropEvent>
#include <QDebug>
#include <QPushButton>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    int screenWidth ;
    int screenHeight;
    QScreen *screen = QApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->geometry();
        screenWidth = screenGeometry.width();
        screenHeight = screenGeometry.height();
        qDebug() << "Screen width:" << screenWidth;
        qDebug() << "Screen height:" << screenHeight;
    } else {
        qDebug() << "No screen found!";
    }


    MainWindow w;
    w.setGeometry(0,0,screenWidth,screenHeight);

    w.show();
    return a.exec();
}
