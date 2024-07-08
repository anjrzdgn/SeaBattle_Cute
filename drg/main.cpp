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


class Ship {
public:
    QLabel *label;
    QChar st='h';

    Ship(QLabel *label, QString pixmap, int x, int y, int width, int height) {
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

        if (this->label->geometry() == QRect(xp, yp, 140, 70)) {
            // Label is horizontal, rotate to vertical
            label->setGeometry(xp, yp, 70, 140);
        } else if (label->geometry() == QRect(xp, yp, 70, 140)) {
            // Label is vertical, rotate to horizontal
            label->setGeometry(xp, yp, 140, 70);
        }else if (label->geometry() == QRect(xp, yp, 70, 210)) {
            // Label is vertical, rotate to horizontal
            label->setGeometry(xp, yp, 210, 70);
        }else if (label->geometry() == QRect(xp, yp, 210, 70)) {
            // Label is vertical, rotate to horizontal
            label->setGeometry(xp, yp, 70, 210);
        }else if (label->geometry() == QRect(xp, yp, 70, 280)) {
            // Label is vertical, rotate to horizontal
            label->setGeometry(xp, yp, 280, 70);
        }else if (label->geometry() == QRect(xp, yp, 280, 70)) {
            // Label is vertical, rotate to horizontal
            label->setGeometry(xp, yp, 70, 280);
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
    QPixmap getPixmap() { return QPixmap("E:/qt1/drg/1^1ship.png"); }
    int getWidth() { return 70; }
    int getHeight() { return 70; }
    QPoint getPosition() { return position; }
};

class Ship1X2 : public SHIP {
private:
    QPoint position;
public:
    Ship1X2(QPoint pos, int id) : SHIP(id), position(pos) {}
    QPixmap getPixmap() { return QPixmap("E:/qt1/drg/2^1ship.png"); }
    int getWidth() { return 140; }
    int getHeight() { return 70; }
    QPoint getPosition() { return position; }
};

class Ship1X3 : public SHIP {
private:
    QPoint position;
public:
    Ship1X3(QPoint pos, int id) : SHIP(id), position(pos) {}
    QPixmap getPixmap() { return QPixmap("E:/qt1/drg/3^1ship.png"); }
    int getWidth() { return 210; }
    int getHeight() { return 70; }
    QPoint getPosition() { return position; }
};

class Ship1X4 : public SHIP {
private:
    QPoint position;
public:
    Ship1X4(QPoint pos, int id) : SHIP(id), position(pos) {}
    QPixmap getPixmap() { return QPixmap("E:/qt1/drg/4^1ship.png"); }
    int getWidth() { return 280; }
    int getHeight() { return 70; }
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
                int x = position.x() + i * 70;
                int y = position.y() + j * 70;
                int index = (y / 70) * 10 + (x / 70);
                if (x < 70 || x >= 770 || y < 90 || y >= 790) {
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
                int x = position.x() + i * 70;
                int y = position.y() + j * 70;
                int index = (y / 70) * 10 + (x / 70);
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
    std::vector<std::pair<QLabel*, SHIP*>> ships;

    // QLabel *labelh = new QLabel(this);
    // Ship h(labelh, "E:/qt1/drg/3^1ship.png", 300, 300, 210, 70);

    DragWidget(QWidget *parent = nullptr)
        : QFrame(parent)
    {



        // setMinimumSize(1900, 1080);
        // setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
        // setAcceptDrops(true);

        std::vector<SHIP*> ships;



        // ships.push_back(new Ship1X1(QPoint(1000, 210)));
        // ships.push_back(new Ship1X1(QPoint(1090, 210)));
        // ships.push_back(new Ship1X1(QPoint(1180, 210)));
        // ships.push_back(new Ship1X1(QPoint(1270, 210)));

        // ships.push_back(new Ship1X2(QPoint(1000, 310)));
        // ships.push_back(new Ship1X2(QPoint(1150, 310)));
        // ships.push_back(new Ship1X2(QPoint(1300, 310)));

        // ships.push_back(new Ship1X3(QPoint(1000, 410)));
        // ships.push_back(new Ship1X3(QPoint(1230, 410)));

        // ships.push_back(new Ship1X4(QPoint(1000, 510)));

        QLabel *labelA = new QLabel(this);
        Ship A(labelA, "E:/qt1/drg/1^1ship2.png", 1000, 210, 50, 50);
        // ships.push_back(&A);

        QLabel *labelB = new QLabel(this);
        Ship B(labelB, "E:/qt1/drg/1^1ship.png", 1090, 210, 70, 70);
        // ships.push_back(&B);

        QLabel *labelC = new QLabel(this);
        Ship C(labelC, "E:/qt1/drg/1^1ship.png", 1180, 210, 70, 70);
        // ships.push_back(&C);

        QLabel *labelD = new QLabel(this);
        Ship D(labelD, "E:/qt1/drg/1^1ship.png", 1270, 210, 70, 70);
        // ships.push_back(&D);

        QLabel *labelE = new QLabel(this);
        Ship E(labelE, "E:/qt1/drg/2^1ship.png", 1000, 310, 70, 140);
        // ships.push_back(&E);

        QLabel *labelF = new QLabel(this);
        Ship F(labelF, "E:/qt1/drg/2^1ship.png", 1150, 310, 70, 140);
        // ships.push_back(&F);

        QLabel *labelG = new QLabel(this);
        Ship G(labelG, "E:/qt1/drg/2^1ship.png", 1300, 310, 70, 140);
        // ships.push_back(&G);

        QLabel *labelH = new QLabel(this);
        Ship H(labelH, "E:/qt1/drg/3^1ship.png", 1000, 410, 70, 210);
        // ships.push_back(&H);

        QLabel *labelI = new QLabel(this);
        Ship I(labelI, "E:/qt1/drg/3^1ship.png", 1230, 410, 70, 210);
        // ships.push_back(&I);

        QLabel *labelJ = new QLabel(this);
        Ship J(labelJ, "E:/qt1/drg/4^1ship.png", 1000, 510, 70, 280);
        // ships.push_back(&J);




        SHIP* a = new Ship1X1(QPoint(1000, 210),1);
        ships.push_back(a);

        SHIP* b = new Ship1X1(QPoint(1090, 210),2);
        ships.push_back(b);

        SHIP* c = new Ship1X1(QPoint(1180, 210),3);
        ships.push_back(c);

        SHIP* d = new Ship1X1(QPoint(1270, 210),4);
        ships.push_back(d);

        SHIP* e = new Ship1X2(QPoint(1000, 310),5);
        ships.push_back(e);

        SHIP* f = new Ship1X2(QPoint(1150, 310),6);
        ships.push_back(f);

        SHIP* g = new Ship1X2(QPoint(1300, 310),7);
        ships.push_back(g);

        SHIP* h = new Ship1X3(QPoint(1000, 410),8);
        ships.push_back(h);

        SHIP* i = new Ship1X3(QPoint(1230, 410),9);
        ships.push_back(i);

        SHIP* j = new Ship1X4(QPoint(1000, 510),10);
        ships.push_back(j);





        // for (int i = 0; i < ships.size(); i++) {
        //     QLabel *label = new QLabel(this);
        //     label->setPixmap(ships[i]->getPixmap());
        //     label->setGeometry(ships[i]->getPosition().x(), ships[i]->getPosition().y(), ships[i]->getWidth(), ships[i]->getHeight());
        //     label->show();
        //     label->geometry().x();
        //     label->setAttribute(Qt::WA_DeleteOnClose);
        // }

        // QLabel *backgroundLabel1 = new QLabel(this);
        QPixmap images("E:/qt1/drg/er.png");
        backgroundLabel1->setPixmap(images);
        backgroundLabel1->setScaledContents(true);
        backgroundLabel1->setGeometry(0, 0, 1600, 900); // Set the geometry of the background label to cover the entire window
        backgroundLabel1->lower(); // Send the background label to the back
        backgroundLabel1->setAcceptDrops(false); // Set to not accept drag and drop events

        //245 234
        setMinimumSize(200, 200);
        setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
        setAcceptDrops(true);


        QLabel img("E:/qt1/drg/shuff.png");
        img.setGeometry(790,800,80,80);

        /*backgroundLabel1->setPixmap(images);
        backgroundLabel1->setScaledContents(true);
        backgroundLabel1->setGeometry(790, 800, 80, 80); // Set the geometry of the background label to cover the entire window
        backgroundLabel1->lower(); // Send the background label to the back
        backgroundLabel1->setAcceptDrops(false);*/


        QPixmap image("E:/qt1/drg/we.png");
        // QLabel *backgroundLabel = new QLabel(this);
        backgroundLabel->setPixmap(image);
        backgroundLabel->setScaledContents(true);
        backgroundLabel->setAlignment(Qt::AlignRight);
        // backgroundLabel->setGeometry(width(), 0, width() / 2, height());
        backgroundLabel->setGeometry(70, 90, 700, 700);
        backgroundLabel->setAcceptDrops(false);

        setMinimumSize(200, 200);
        setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
        setAcceptDrops(true);

        setMinimumSize(200, 200);
        setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
        setAcceptDrops(true);


        QTransform transform;
        transform.rotate(90); // Rotate by 45 degrees
        houseIcon1->setGeometry(1000,310, 70, 210);

        QPixmap pixmap = houseIcon1->pixmap();
        QPixmap transformedPixmap = pixmap.transformed(transform);
        houseIcon1->setPixmap(transformedPixmap);

        connect(houseIcon1, &ClickableLabel::clicked, this, &DragWidget::rotateHouseIcon);
        // connect(houseIcon, &ClickableLabel::clicked, this, &DragWidget::rotateHouseIcon);

    }

    // protected:
    //     void mousePressEvent(QMouseEvent *event) override
    //     {
    //         QLabel *child = static_cast<QLabel*>(childAt(event->position().to
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

    // void dropEvent(QDropEvent *event) override
    // {
    //     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
    //         QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
    //         QDataStream dataStream(&itemData, QIODevice::ReadOnly);
    //         QPoint offset;
    //         dataStream >> offset;

    //         QLabel *child = static_cast<QLabel*>(childAt(offset));
    //         if (child) {
    //             child->move(event->position().toPoint());
    //             child->show();
    //         }

    //         event->acceptProposedAction();
    //     }
    // }

    // void dropEvent(QDropEvent *event) override
    // {
    //     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
    //         QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
    //         QDataStream dataStream(&itemData, QIODevice::ReadOnly);
    //         QPoint offset;
    //         dataStream >> offset;

    //         QLabel *child = static_cast<QLabel*>(childAt(offset));
    //         if (child) {
    //             int x = event->position().toPoint().x();
    //             int y = event->position().toPoint().y();

    //             if (x >= 70 && x <= 770 && y >= 90 && y <= 790) {
    //                 int column = (x - 70) / 70;
    //                 int row = (y - 90) / 70;

    //                     int xPos=70+column*70;
    //                     int yPos=90+row*70;

    //                     qDebug()<<xPos<<" "<<yPos;

    //                 child->move(xPos, yPos);
    //             } else {
    //                 child->move(offset); // move the label back to its original position
    //             }
    //             child->show();
    //         }

    //         event->acceptProposedAction();
    //     }
    // }

    Board board; // create an instance of the Board class

    // void dropEvent(QDropEvent *event) override
    // {
    //     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
    //         QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
    //         QDataStream dataStream(&itemData, QIODevice::ReadOnly);
    //         QPoint offset;
    //         dataStream >> offset;

    //         QLabel *child = static_cast<QLabel*>(childAt(offset));
    //         if (child) {
    //             int x = event->position().toPoint().x();
    //             int y = event->position().toPoint().y();

    //             if (x >= 70 && x <= 770 && y >= 90 && y <= 790) {
    //                 int column = (x - 70) / 70;
    //                 int row = (y - 90) / 70;

    //                 int xPos=70+column*70;
    //                 int yPos=90+row*70;

    //                 QPoint position(xPos, yPos);

    //                 // Get the SHIP object associated with the QLabel
    //                 SHIP* ship = nullptr;
    //                 for (SHIP* s : ships) {
    //                     if (*s->getPixmap().toImage() == *child->pixmap().toImage()) {
    //                         ship = s;
    //                         break;
    //                     }
    //                 }

    //                 if (ship && !board.isValidPosition(ship, position)) {
    //                     child->move(offset); // move the label back to its original position
    //                     return;
    //                 }

    //                 child->move(xPos, yPos);
    //             } else {
    //                 child->move(offset); // move the label back to its original position
    //             }
    //             child->show();
    //         }

    //         event->acceptProposedAction();
    //     }
    // }



    // void dropEvent(QDropEvent *event) override
    // {
    //     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
    //         QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
    //         QDataStream dataStream(&itemData, QIODevice::ReadOnly);
    //         QPoint offset;
    //         dataStream >> offset;

    //         QLabel *child = static_cast<QLabel*>(childAt(offset));
    //         if (child) {
    //             int x = event->position().toPoint().x();
    //             int y = event->position().toPoint().y();

    //             if (x >= 70 && x <= 770 && y >= 90 && y <= 790) {
    //                 int column = (x - 70) / 70;
    //                 int row = (y - 90) / 70;

    //                 int xPos=70+column*70;
    //                 int yPos=90+row*70;

    //                 QPoint position(xPos, yPos);

    //                 // Get the SHIP object associated with the QLabel
    //                 SHIP* ship = nullptr;
    //                 for (auto& pair : ships) {
    //                     if (pair.first == child) {
    //                         ship = pair.second;
    //                         break;
    //                     }
    //                 }

    //                 if (ship && !board.isValidPosition(ship, position)) {
    //                     child->move(offset); // move the label back to its original position
    //                     return;
    //                 }

    //                 child->move(xPos, yPos);

    //                 if (ship != nullptr) {
    //                     int shipId = ship->getId();
    //                     if (dynamic_cast<Ship1X1*>(ship)) {
    //                         qDebug() << "Ship1X1 with id" << shipId << "dropped";
    //                     } else if (dynamic_cast<Ship1X2*>(ship)) {
    //                         qDebug() << "Ship1X2 with id" << shipId << "dropped";
    //                     } else if (dynamic_cast<Ship1X3*>(ship)) {
    //                         qDebug() << "Ship1X3 with id" << shipId << "dropped";
    //                     } else if (dynamic_cast<Ship1X4*>(ship)) {
    //                         qDebug() << "Ship1X4 with id" << shipId << "dropped";
    //                     } else {
    //                         qDebug() << "not found!";
    //                     }
    //                 } else {
    //                     child->move(offset); // move the label back to its original position
    //                 }
    //                 child->show();

    //                 // Place the ship on the board
    //                 if (ship != nullptr) {
    //                     board.placeShip(ship, position);
    //                 }
    //             } else {
    //                 child->move(offset); // move the label back to its original position
    //             }
    //             child->show();
    //         }

    //         event->acceptProposedAction();
    //     }
    // }







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

                if (x >= 70 && x <= 770 && y >= 90 && y <= 790) {
                    int column = (x - 70) / 70;
                    int row = (y - 90) / 70;

                    int xPos=70+column*70;
                    int yPos=90+row*70;

                    QPoint position(xPos, yPos);

                    // Get the SHIP object associated with the QLabel
                    SHIP* ship = nullptr;
                    for (auto& pair : ships) {
                        if (pair.first == child) {
                            ship = pair.second;
                            break;
                        }
                    }

                    child->move(xPos, yPos);

                    if (ship != nullptr) {
                        if (dynamic_cast<Ship1X1*>(ship)) {
                            qDebug() << "Ship1X1 dropped";
                        } else if (dynamic_cast<Ship1X2*>(ship)) {
                            qDebug() << "Ship1X2 dropped";
                        } else if (dynamic_cast<Ship1X3*>(ship)) {
                            qDebug() << "Ship1X3 dropped";
                        } else if (dynamic_cast<Ship1X4*>(ship)) {
                            qDebug() << "Ship1X4 dropped";
                        }
                    } else {
                        qDebug() << "Unknown ship type";
                    }
                } else {
                    child->move(offset); // move the label back to its original position
                }
                child->show();
            }

            event->acceptProposedAction();
        }
    }
    // void dropEvent(QDropEvent *event) override
    // {
    //     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
    //         QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
    //         QDataStream dataStream(&itemData, QIODevice::ReadOnly);
    //         QPoint offset;
    //         dataStream >> offset;

    //         QLabel *child = static_cast<QLabel*>(childAt(offset));
    //         if (child) {
    //             int x = event->position().toPoint().x();
    //             int y = event->position().toPoint().y();

    //             if (x >= 70 && x <= 770 && y >= 90 && y <= 790) {
    //                 int column = (x - 70) / 70;
    //                 int row = (y - 90) / 70;

    //                 int xPos=70+column*70;
    //                 int yPos=90+row*70;

    //                 QPoint position(xPos, yPos);

    //                 // Get the SHIP object associated with the QLabel
    //                 SHIP* ship = nullptr;
    //                 for (auto& pair : ships) {
    //                     if (pair.first == child) {
    //                         ship = pair.second;
    //                         break;
    //                     }
    //                 }

    //                 if (ship && !board.isValidPosition(ship, position)) {
    //                     child->move(offset); // move the label back to its original position
    //                     return;
    //                 }

    //                 child->move(xPos, yPos);
    //             } else {
    //                 child->move(offset); // move the label back to its original position
    //             }
    //             child->show();
    //         }

    //         event->acceptProposedAction();
    //     }
    // }
public slots:
    void rotateHouseIcon() {

        // if(houseIcon1->geometry()==QRect(1000, 310, 210, 70))
        QTransform transform;
        transform.rotate(90); // Rotate by 90 degrees

        if (houseIcon1->geometry() == QRect(1000, 310, 210, 70)) {
            // Label is horizontal, rotate to vertical
            houseIcon1->setGeometry(1000, 310, 70, 210);
        } else if (houseIcon1->geometry() == QRect(1000, 310, 70, 210)) {
            // Label is vertical, rotate to horizontal
            houseIcon1->setGeometry(1000, 310, 210, 70);
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
    window.setGeometry(0, 0, 1920, 1080); // Set window size

    // QLabel *labelt = new QLabel(&window);
    // Ship t(labelt, "E:/qt1/drg/3^1ship.png", 300, 300, 210, 70);




    // QLabel *backgroundImageLab,el = new QLabel(&window);
    // QPixmap backgroundImage("E:/qt1/drg/pic.png"); // Load your image
    // backgroundImageLabel->setPixmap(backgroundImage);
    // backgroundImageLabel->setScaledContents(true);
    // backgroundImageLabel->setGeometry(0, 0, 1920, 1080); // Set the geometry of the background label to cover the entire window

    window.show();


    return app.exec();
}

#include "main.moc"
