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


class SHIP {
public:
    virtual QPixmap getPixmap() = 0;
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual QPoint getPosition() = 0; // new function
};

class Ship1X1 : public SHIP {
private:
    QPoint position;
public:
    Ship1X1(QPoint pos) : position(pos) {}
    QPixmap getPixmap() { return QPixmap("E:/qt1/drg/1^1ship.png"); }
    int getWidth() { return 70; }
    int getHeight() { return 70; }
    QPoint getPosition() { return position; }
};

class Ship1X2 : public SHIP {
private:
    QPoint position;
public:
    Ship1X2(QPoint pos) : position(pos) {}
    QPixmap getPixmap() { return QPixmap("E:/qt1/drg/2^1ship.png"); }
    int getWidth() { return 140; }
    int getHeight() { return 70; }
    QPoint getPosition() { return position; }
};

class Ship1X3 : public SHIP {
private:
    QPoint position;
public:
    Ship1X3(QPoint pos) : position(pos) {}
    QPixmap getPixmap() { return QPixmap("E:/qt1/drg/3^1ship.png"); }
    int getWidth() { return 210; }
    int getHeight() { return 70; }
    QPoint getPosition() { return position; }
};

class Ship1X4 : public SHIP {
private:
    QPoint position;
public:
    Ship1X4(QPoint pos) : position(pos) {}
    QPixmap getPixmap() { return QPixmap("E:/qt1/drg/4^1ship.png"); }
    int getWidth() { return 280; }
    int getHeight() { return 70; }
    QPoint getPosition() { return position; }
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

    DragWidget(QWidget *parent = nullptr)
        : QFrame(parent)
    {



        // setMinimumSize(1900, 1080);
        // setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
        // setAcceptDrops(true);

        std::vector<SHIP*> ships;

        ships.push_back(new Ship1X1(QPoint(1000, 210)));
        ships.push_back(new Ship1X1(QPoint(1090, 210)));
        ships.push_back(new Ship1X1(QPoint(1180, 210)));
        ships.push_back(new Ship1X1(QPoint(1270, 210)));

        ships.push_back(new Ship1X2(QPoint(1000, 310)));
        ships.push_back(new Ship1X2(QPoint(1150, 310)));
        ships.push_back(new Ship1X2(QPoint(1300, 310)));

        ships.push_back(new Ship1X3(QPoint(1000, 410)));
        ships.push_back(new Ship1X3(QPoint(1230, 410)));

        ships.push_back(new Ship1X4(QPoint(1000, 510)));





        for (int i = 0; i < ships.size(); i++) {
            QLabel *label = new QLabel(this);
            label->setPixmap(ships[i]->getPixmap());
            label->setGeometry(ships[i]->getPosition().x(), ships[i]->getPosition().y(), ships[i]->getWidth(), ships[i]->getHeight());
            label->show();
            label->setAttribute(Qt::WA_DeleteOnClose);
        }

        // QLabel *backgroundLabel1 = new QLabel(this);
        QPixmap images("E:/qt1/drg/er.png");
        backgroundLabel1->setPixmap(images);
        backgroundLabel1->setScaledContents(true);
        backgroundLabel1->setGeometry(0, 0, 1600, 900); // Set the geometry of the background label to cover the entire window
        backgroundLabel1->lower(); // Send the background label to the back
        backgroundLabel1->setAcceptDrops(false); // Set to not accept drag and drop events


        setMinimumSize(200, 200);
        setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
        setAcceptDrops(true);



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

        // QLabel *Ship11 = new QLabel(this);
        // Ship11->setPixmap(QPixmap("E:/qt1/drg/1^1ship.png"));
        // // Ship11->move(1000, 10);
        // Ship11->show();
        // Ship11->setAttribute(Qt::WA_DeleteOnClose);
        // Ship11->setGeometry(1000,210, 70, 70);


        // QLabel *Ship12 = new QLabel(this);
        // Ship12->setPixmap(QPixmap("E:/qt1/drg/1^1ship.png"));
        // // Ship12->move(1000, 10);
        // Ship12->show();
        // Ship12->setAttribute(Qt::WA_DeleteOnClose);
        // Ship12->setGeometry(1090,210, 70, 70);

        // QLabel *Ship13 = new QLabel(this);
        // Ship13->setPixmap(QPixmap("E:/qt1/drg/1^1ship.png"));
        // // Ship13->move(1000, 10);
        // Ship13->show();
        // Ship13->setAttribute(Qt::WA_DeleteOnClose);
        // Ship13->setGeometry(1180,210, 70, 70);

        // QLabel *Ship14 = new QLabel(this);
        // Ship14->setPixmap(QPixmap("E:/qt1/drg/1^1ship.png"));
        // // Ship14->move(1000, 10);
        // Ship14->show();
        // Ship14->setAttribute(Qt::WA_DeleteOnClose);
        // Ship14->setGeometry(1270,210, 70, 70);

        // QLabel *Ship21 = new QLabel(this);
        // Ship21->setPixmap(QPixmap("E:/qt1/drg/2^1ship.png"));
        // // Ship21->move(1000, 110);
        // Ship21->show();
        // Ship21->setAttribute(Qt::WA_DeleteOnClose);
        // Ship21->setGeometry(1000,310, 140, 70);

        // QLabel *Ship22 = new QLabel(this);
        // Ship22->setPixmap(QPixmap("E:/qt1/drg/2^1ship.png"));
        // // Ship21->move(1000, 110);
        // Ship22->show();
        // Ship22->setAttribute(Qt::WA_DeleteOnClose);
        // Ship22->setGeometry(1150,310, 140, 70);

        // QLabel *Ship23 = new QLabel(this);
        // Ship23->setPixmap(QPixmap("E:/qt1/drg/2^1ship.png"));
        // // Ship21->move(1000, 110);
        // Ship23->show();
        // Ship23->setAttribute(Qt::WA_DeleteOnClose);
        // Ship23->setGeometry(1300,310, 140, 70);

        // QLabel *Ship31 = new QLabel(this);
        // Ship31->setPixmap(QPixmap("E:/qt1/drg/3^1ship.png"));
        // // Ship31->move(1000, 210);
        // Ship31->show();
        // Ship31->setAttribute(Qt::WA_DeleteOnClose);
        // Ship31->setGeometry(1000,410, 210, 70);

        // QLabel *Ship32 = new QLabel(this);
        // Ship32->setPixmap(QPixmap("E:/qt1/drg/3^1ship.png"));
        // // Ship31->move(1000, 210);
        // Ship32->show();
        // Ship32->setAttribute(Qt::WA_DeleteOnClose);
        // Ship32->setGeometry(1230,410, 210, 70);

        // QLabel *Ship41 = new QLabel(this);
        // Ship41->setPixmap(QPixmap("E:/qt1/drg/4^1ship.png"));
        // // houseIcon->move(1000, 210);
        // Ship41->show();
        // Ship41->setAttribute(Qt::WA_DeleteOnClose);
        // Ship41->setGeometry(1000,510, 280, 70);


        // // QLabel *houseIcon1 = new QLabel(this);
        // houseIcon1->setPixmap(QPixmap("E:/qt1/drg/3^1ship.png"));
        // // houseIcon->move(1000, 210);
        // houseIcon1->show();
        // houseIcon1->setAttribute(Qt::WA_DeleteOnClose);
        // houseIcon1->setGeometry(1000,310, 210, 70);

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

                    qDebug()<<xPos<<" "<<yPos;

                    child->move(xPos, yPos);
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
    //             // event->position().toPoint();
    //             int width = this->width();
    //             int height = this->height();
    //             int y = event->position().toPoint().y();

    //             //(30, 50, 700, 700);
    //             // 30*(width/1920)<x<730*(width/1920)  &&& 10*(height/1080)<y<710*(height/1080)

    //             if (x < (width / 2) && y > height/2) { // if drop position is in the right half of the widget

    //                 child->move(event->position().toPoint());
    //             } else { // if drop position is in the left half of the widget
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

// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);

//     QWidget mainWindow;


//     DragWidget window;
//     // window.setStyleSheet("background-image:url(E:/qt1/drg/123.png);");

//     window.setGeometry(100, 100, 800, 600); // Set window size

//     QLabel backgroundImageLabel(&window);
//     QPixmap backgroundImage("E:/qt1/drg/re.png"); // Load your image

//     backgroundImageLabel.setPixmap(backgroundImage);



//     // window.resize(1920,1080);
//     window.show();


//     return app.exec();
// }


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DragWidget window;
    window.setGeometry(0, 0, 1920, 1080); // Set window size

    // QLabel *backgroundImageLabel = new QLabel(&window);
    // QPixmap backgroundImage("E:/qt1/drg/pic.png"); // Load your image
    // backgroundImageLabel->setPixmap(backgroundImage);
    // backgroundImageLabel->setScaledContents(true);
    // backgroundImageLabel->setGeometry(0, 0, 1920, 1080); // Set the geometry of the background label to cover the entire window

    window.show();

    return app.exec();
}

#include "main.moc"
