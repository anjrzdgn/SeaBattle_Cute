#include <QApplication>
#include <QDrag>
#include <utility>
#include <QMimeData>
#include <QDataStream>
#include <QByteArray>
#include <QLabel>
#include <QFrame>
#include <QPixmap>
#include <QPoint>
#include <QMouseEvent>
#include <QDropEvent>
#include <QPushButton>>
#include <QDebug>
#include <QSize>


class Ship {
public:
    QLabel *label;
    QChar st='h';
    int xpos;
    int ypos;
    int w;
    int h;

    Ship(QLabel *label, QString pixmap, int x, int y, int width, int height) : xpos(x), ypos(y), w(width), h(height) {
        QPixmap f(pixmap);
        label->setPixmap(f);
        label->setGeometry(x, y, width, height);
        label->show();
    }

    void show() {
        label->show();
    }

    void getGeo() {
        label->geometry();
    }

    void rotate(){

        QTransform transform;
        if(this->st == 'h'){
            this->st = 'v';
            transform.rotate(90); // Rotate by 90 degrees
        } else if(this->st == 'v'){
            this->st = 'h';
            transform.rotate(270); // Rotate by 270 degrees
        }

        QRect rect = label->geometry();
        int xp = rect.x();
        int yp = rect.y();
        int width = rect.width();
        int height = rect.height();

        if (this->label->geometry() == QRect(xp, yp, 120, 60)) {
            // Label is horizontal, rotate to vertical
            label->setGeometry(xp, yp, 60, 120);
        } else if (label->geometry() == QRect(xp, yp, 60, 120)) {
            // Label is vertical, rotate to horizontal
            label->setGeometry(xp, yp, 120, 60);
        }else if (label->geometry() == QRect(xp, yp, 60, 180)) {
            // Label is vertical, rotate to horizontal
            label->setGeometry(xp, yp, 210, 60);
        }else if (label->geometry() == QRect(xp, yp, 180, 60)) {
            // Label is vertical, rotate to horizontal
            label->setGeometry(xp, yp, 60, 180);
        }else if (label->geometry() == QRect(xp, yp, 60, 240)) {
            // Label is vertical, rotate to horizontal
            label->setGeometry(xp, yp, 240, 60);
        }else if (label->geometry() == QRect(xp, yp, 240, 60)) {
            // Label is vertical, rotate to horizontal
            label->setGeometry(xp, yp, 60, 240);
        }

        QPixmap pixmap = label->pixmap();
        QPixmap transformedPixmap = pixmap.transformed(transform);
        label->setPixmap(transformedPixmap);

    }
};
class SHIP {
public:
    SHIP(int id) : id(id) {} // Add an id constructor parameter
    virtual QPixmap getPixmap() = 0;
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual QPoint getPosition() = 0; // new function
    virtual int getId() { return id; } // Add an id getter function
    virtual ~SHIP() {} // Add this line

private:
    int id; // Add an id member variable
};

class Ship1X1 : public SHIP {
private:
    QPoint position;
public:
    Ship1X1(QPoint pos, int id) : SHIP(id), position(pos) {}
    QPixmap getPixmap() { return QPixmap("C:/SeaBattle_Cute_private/src/1Xship copy.png"); }
    int getWidth() { return 50; }
    int getHeight() { return 50; }
    QPoint getPosition() { return position; }
};

class Ship1X2 : public SHIP {
private:
    QPoint position;
public:
    Ship1X2(QPoint pos, int id) : SHIP(id), position(pos) {}
    QPixmap getPixmap() { return QPixmap("C:/SeaBattle_Cute_private/src/2Xship copy.png"); }
    int getWidth() { return 100; }
    int getHeight() { return 50; }
    QPoint getPosition() { return position; }
};

class Ship1X3 : public SHIP {
private:
    QPoint position;
public:
    Ship1X3(QPoint pos, int id) : SHIP(id), position(pos) {}
    QPixmap getPixmap() { return QPixmap("C:/SeaBattle_Cute_private/src/3Xship copy.png"); }
    int getWidth() { return 150; }
    int getHeight() { return 50; }
    QPoint getPosition() { return position; }
};

class Ship1X4 : public SHIP {
private:
    QPoint position;
public:
    Ship1X4(QPoint pos, int id) : SHIP(id), position(pos) {}
    QPixmap getPixmap() { return QPixmap("C:/SeaBattle_Cute_private/src/4Xship copy.png"); }
    int getWidth() { return 200; }
    int getHeight() { return 50; }
    QPoint getPosition() { return position; }
};


class Board {
public:
    bool positions[100]; // array of 100 positions, initialized to false (empty)

    Board() {
        for (int i = 0; i < 100; i++) {
            positions[i] = false;
        }
    }

    bool isValidPosition(SHIP* ship, QPoint position) {
        int width = ship->getWidth();
        int height = ship->getHeight();

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                int x = position.x() + i * 50;
                int y = position.y() + j * 50;
                int index = (y / 50) * 10 + (x / 50);
                if (x < 50 || x >= 550 || y < 90 || y >= 790) {
                    return false; // out of bounds
                }
                if (positions[index]) {
                    return false; // position is not empty
                }
            }
        }
        return true; // position is valid
    }

    void placeShip(SHIP* ship, QPoint position) {
        int width = ship->getWidth();
        int height = ship->getHeight();

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                int x = position.x() + i * 50;
                int y = position.y() + j * 50;
                int index = (y / 50) * 10 + (x / 50);
                positions[index] = true;
            }
        }
    }

};

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    ClickableLabel(QWidget *parent = nullptr) : QLabel(parent) {}

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override {
        emit clicked();
        QLabel::mousePressEvent(event);
    }
};

class DragWidget : public QFrame {
    Q_OBJECT

public:
    QLabel *backgroundLabel1 = new QLabel(this);
    QLabel *backgroundLabel = new QLabel(this);
    ClickableLabel *houseIcon1 = new ClickableLabel(this);
    std::vector<std::pair< Ship*,QLabel*>> ships;

    DragWidget(QWidget *parent = nullptr)
        : QFrame(parent)
    {

        QLabel *labelA = new QLabel(this);
        Ship A(labelA, "C:/SeaBattle_Cute_private/drg/src/1Xship copy.png", 1010, 230, 60, 60);
        ships.push_back(std::make_pair(&A,labelA));

        QLabel *labelB = new QLabel(this);
        Ship B(labelB, "C:/SeaBattle_Cute_private/drg/src/1Xship copy.png", 1106, 230, 60, 60);
        ships.push_back(std::make_pair(&B,labelB));

        QLabel *labelC = new QLabel(this);
        Ship C(labelC, "C:/SeaBattle_Cute_private/drg/src/1Xship copy.png", 1202, 230, 60, 60);
        ships.push_back(std::make_pair(&C,labelC));

        QLabel *labelD = new QLabel(this);
        Ship D(labelD, "C:/SeaBattle_Cute_private/drg/src/1Xship copy.png", 1298, 230, 60, 60);
        ships.push_back(std::make_pair(&D,labelD));

        QLabel *labelE = new QLabel(this);
        Ship E(labelE, "C:/SeaBattle_Cute_private/drg/src/2Xship copy.png", 1010, 326, 120, 60);
        ships.push_back(std::make_pair(&E,labelE));

        QLabel *labelF = new QLabel(this);
        Ship F(labelF, "C:/SeaBattle_Cute_private/drg/src/2Xship copy.png", 1154, 326, 120, 60);
        ships.push_back(std::make_pair(&F,labelF));

        QLabel *labelG = new QLabel(this);
        Ship G(labelG, "C:/SeaBattle_Cute_private/drg/src/2Xship copy.png", 1298, 326, 120, 60);
        ships.push_back(std::make_pair(&G,labelG));

        QLabel *labelH = new QLabel(this);
        Ship H(labelH, "C:/SeaBattle_Cute_private/drg/src/3Xship copy.png", 1010, 422, 180, 60);
        ships.push_back(std::make_pair(&H,labelH));

        QLabel *labelI = new QLabel(this);
        Ship I(labelI, "C:/SeaBattle_Cute_private/drg/src/3Xship copy.png", 1202, 422, 180, 60);
        ships.push_back(std::make_pair(&I,labelI));

        QLabel *labelJ = new QLabel(this);
        Ship J(labelJ, "C:/SeaBattle_Cute_private/drg/src/4Xship copy.png", 1010, 518, 240, 60);
        ships.push_back(std::make_pair(&J,labelJ));


        QPushButton* restore = new QPushButton(this);
        restore->setGeometry(815, 665, 50, 50);
        restore->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
        restore->setCursor(Qt::PointingHandCursor);
        connect(restore, &QPushButton::clicked, QCoreApplication::quit);

        QPushButton* next = new QPushButton(this);
        next->setGeometry(1070, 665, 180, 50);
        next->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
        next->setCursor(Qt::PointingHandCursor);
        connect(next, &QPushButton::clicked, QCoreApplication::quit);

        QPixmap images("C:/SeaBattle_Cute_private/src_graphic/made/arrangement page copy.png");
        backgroundLabel1->setPixmap(images);
        backgroundLabel1->setScaledContents(true);
        backgroundLabel1->setGeometry(0, 0, 1536, 864); // Set the geometry of the background label to cover the entire window
        backgroundLabel1->lower(); // Send the background label to the back
        backgroundLabel1->setAcceptDrops(false); // Set to not accept drag and drop events

        setMinimumSize(200, 200);
        setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
        setAcceptDrops(true);

        QTransform transform;
        transform.rotate(90); // Rotate by 45 degrees
        houseIcon1->setGeometry(1000,310, 50, 210);

        QPixmap pixmap = houseIcon1->pixmap();
        QPixmap transformedPixmap = pixmap.transformed(transform);
        houseIcon1->setPixmap(transformedPixmap);

        connect(houseIcon1, &ClickableLabel::clicked, this, &DragWidget::rotateHouseIcon);
        // connect(houseIcon, &ClickableLabel::clicked, this, &DragWidget::rotateHouseIcon);

    }


protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        QLabel *child = static_cast<QLabel*>(childAt(event->position().toPoint()));
        if (!child || child == backgroundLabel1 || child == backgroundLabel) // Ignore the background label
            return;

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << child->pos();

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(child->pixmap());
        drag->setHotSpot(event->position().toPoint() - child->pos());

        drag->exec();
    }

    void dragEnterEvent(QDragEnterEvent *event) override
    {
        QLabel *child = static_cast<QLabel*>(childAt(mapFromGlobal(event->pos())));
        if (!child || child == backgroundLabel1|| child == backgroundLabel) // Ignore the background label
            return;

        if (event->mimeData()->hasFormat("application/x-dnditemdata"))
            event->acceptProposedAction();
    }


    Board board; // create an instance of the Board class


    void dropEvent(QDropEvent *event) override
    {
        if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
            QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
            QDataStream dataStream(&itemData, QIODevice::ReadOnly);
            QPoint offset;
            dataStream >> offset;

            QLabel *child = static_cast<QLabel*>(childAt(offset));
            if (child) {
                int x = event->position().toPoint().x();
                int y = event->position().toPoint().y();

                if (x >= 260*0.8 && x <= 860*0.8 && y >= 230*0.8 && y <= 834*0.8) {
                    int column = (x - 200) / 48;
                    int row = (y - 190) / 48;

                    int xPos = 200  + column * 48;
                    int yPos = 190 - 7 + row * 48;

                    QPoint position(xPos, yPos);

                    Ship* ship = nullptr;
                    // int ws;
                    for (auto& pair : ships) {
                        if (pair.second == child) {
                            ship = pair.first;
                            // size = pair.first->label->size();
                            // ws = size.width();
                            break;
                        }
                    }

                    // if (ws == 32765 && column > 6) {
                    //     child->move(offset);
                    // }
                    // else if (ws == 0 && column > 7) {
                    //     child->move(offset);
                    // }
                    // else if (ws == 718 && column > 8) {
                    //     child->move(offset);
                    // }
                    // else
                    // {
                        child->move(xPos, yPos);
                    // }


                    if (ship) {

                            qDebug() << "dropped at position" << position << " " << column << " " << row ; //<< " " << ws;
                    } else {
                        qDebug() << "Unknown label";
                    }
                } else {
                    child->move(offset); // move the label back to its original position
                }
                child->show();
            }

            event->acceptProposedAction();
        }
    }

public slots:
    void rotateHouseIcon() {

        QTransform transform;
        transform.rotate(90); // Rotate by 90 degrees

        if (houseIcon1->geometry() == QRect(1000, 310, 210, 50)) {
            // Label is horizontal, rotate to vertical
            houseIcon1->setGeometry(1000, 310, 50, 210);
        } else if (houseIcon1->geometry() == QRect(1000, 310, 50, 210)) {
            // Label is vertical, rotate to horizontal
            houseIcon1->setGeometry(1000, 310, 210, 50);
        }

        QPixmap pixmap = houseIcon1->pixmap();
        QPixmap transformedPixmap = pixmap.transformed(transform);
        houseIcon1->setPixmap(transformedPixmap);
    }
};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DragWidget window;
    window.setGeometry(0, 0, 1536, 864); // Set window size

    window.show();


    return app.exec();
}

#include "main.moc"
