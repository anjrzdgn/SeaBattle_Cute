#include "ship.h"

// #include "ship.h"

Ship::Ship(QLabel *label, QString pixmap, int x, int y, int width, int height)
    : label(label), xpos(x), ypos(y), w(width), h(height), st("h") {

    zcolumn = (label->x() - 200) / 48;
    zrow = (label->y() - 190) / 48;

    QPixmap f(pixmap);
    label->setPixmap(f);
    label->setGeometry(x, y, width, height);
    label->show();
}

void Ship::rotate() {
    if (label->x() > 1000) {
        if (st == "h") {
            st = "v";
            label->setGeometry(label->x(), label->y(), h, w);  // Swap width and height
        } else {
            st = "h";
            label->setGeometry(label->x(), label->y(), w, h);  // Swap width and height
        }

        QPixmap pixmap = label->pixmap();
        QTransform transform;
        transform.rotate(90);
        QPixmap transformedPixmap = pixmap.transformed(transform, Qt::SmoothTransformation);
        label->setPixmap(transformedPixmap);
    }
}

