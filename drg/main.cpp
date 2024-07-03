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

class DragWidget : public QFrame {
    Q_OBJECT

public:
    QLabel *backgroundLabel1 = new QLabel(this);
    QLabel *backgroundLabel = new QLabel(this);

    DragWidget(QWidget *parent = nullptr)
        : QFrame(parent)
    {

        // setMinimumSize(1900, 1080);
        // setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
        // setAcceptDrops(true);

        // QLabel *backgroundLabel1 = new QLabel(this);
        QPixmap images("E:/qt1/drg/er.png");
        backgroundLabel1->setPixmap(images);
        backgroundLabel1->setScaledContents(true);
        backgroundLabel1->setGeometry(0, 0, 1920, 1080); // Set the geometry of the background label to cover the entire window
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
        // backgroundLabel->setGeometry(width() , 0, width() / 2, height());
        backgroundLabel->setGeometry(30, 50, 700, 700);
        backgroundLabel->setAcceptDrops(false);

        setMinimumSize(200, 200);
        setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
        setAcceptDrops(true);

        setMinimumSize(200, 200);
        setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
        setAcceptDrops(true);

        QLabel *boatIcon = new QLabel(this);
        boatIcon->setPixmap(QPixmap("E:/qt1/drg/1^1ship.png"));
        // boatIcon->move(1000, 10);
        boatIcon->show();
        boatIcon->setAttribute(Qt::WA_DeleteOnClose);
        boatIcon->setGeometry(1000,10, 70, 70);

        QLabel *carIcon = new QLabel(this);
        carIcon->setPixmap(QPixmap("E:/qt1/drg/1^1ship.png"));
        // carIcon->move(1000, 110);
        carIcon->show();
        carIcon->setAttribute(Qt::WA_DeleteOnClose);
        carIcon->setGeometry(1000,110, 70, 70);

        QLabel *houseIcon = new QLabel(this);
        houseIcon->setPixmap(QPixmap("E:/qt1/drg/1^1ship.png"));
        // houseIcon->move(1000, 210);
        houseIcon->show();
        houseIcon->setAttribute(Qt::WA_DeleteOnClose);
        houseIcon->setGeometry(1000,210, 70, 70);


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

                if (x >= 30 && x <= 730 && y >= 50 && y <= 750) {
                    int column = (x - 30) / 70;
                    int row = (y - 50) / 70;

                    int xPos=30+column*70;
                    int yPos=50+row*70;

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
