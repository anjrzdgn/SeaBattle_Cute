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
    DragWidget(QWidget *parent = nullptr)
        : QFrame(parent)
    {

        // setMinimumSize(1900, 1080);
        // setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
        // setAcceptDrops(true);



        QPixmap image("E:/qt1/drg/gh.png");
        QLabel *backgroundLabel = new QLabel(this);
        backgroundLabel->setPixmap(image);
        backgroundLabel->setScaledContents(true);
        backgroundLabel->setAlignment(Qt::AlignRight);
        backgroundLabel->setGeometry(width() , 0, width() / 2, height());

        setMinimumSize(200, 200);
        setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
        setAcceptDrops(true);

        setMinimumSize(200, 200);
        setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
        setAcceptDrops(true);

        QLabel *boatIcon = new QLabel(this);
        boatIcon->setPixmap(QPixmap("E:/qt1/drg/pic.png"));
        boatIcon->move(10, 10);
        boatIcon->show();
        boatIcon->setAttribute(Qt::WA_DeleteOnClose);

        QLabel *carIcon = new QLabel(this);
        carIcon->setPixmap(QPixmap("E:/qt1/drg/pic.png"));
        carIcon->move(100, 10);
        carIcon->show();
        carIcon->setAttribute(Qt::WA_DeleteOnClose);

        QLabel *houseIcon = new QLabel(this);
        houseIcon->setPixmap(QPixmap("E:/qt1/drg/pic.png"));
        houseIcon->move(10, 80);
        houseIcon->show();
        houseIcon->setAttribute(Qt::WA_DeleteOnClose);


    }

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        QLabel *child = static_cast<QLabel*>(childAt(event->position().toPoint()));
        if (!child)
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
                // event->position().toPoint();
                int width = this->width();
                int height = this->height();
                int y = event->position().toPoint().y();

                if (x > width / 2 && y < height/2) { // if drop position is in the right half of the widget

                    child->move(event->position().toPoint());
                } else { // if drop position is in the left half of the widget
                    child->move(offset); // move the label back to its original position
                }
                child->show();
            }

            event->acceptProposedAction();
        }
    }

};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    DragWidget window;
    // window.setStyleSheet("background-image:url(E:/qt1/drg/123.png);");
    window.resize(1920,1080);
    window.show();


    return app.exec();
}

#include "main.moc"
