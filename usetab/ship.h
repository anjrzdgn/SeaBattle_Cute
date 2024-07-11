#ifndef SHIP_H
#define SHIP_H

#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QTransform>

class Ship {

public:
    QLabel *label;
    QString st;
    int xpos;
    int ypos;
    int w;
    int h;
    int zcolumn;
    int zrow;

    Ship(QLabel *label, QString pixmap, int x, int y, int width, int height);

    void rotate();
};

#endif // SHIP_H
