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
#include <QSize>
#include <iostream>


class Ship {
public:
    QLabel *label;
    QString st = "h";
    int xpos;
    int ypos;
    int w;
    int h;
    int zcolumn;
    int zrow;
    Ship(QLabel *label, QString pixmap, int x, int y, int width, int height) : xpos(x), ypos(y), h(height) {

        zcolumn = (label->x() - 200) / 48;
        zrow = (label->y() - 190) / 48;
        w = width;
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

std::vector<std::pair< Ship*,QLabel*>> ships;

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



class Board{

public:

    QChar table[10][10];
    Board()  {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                table[i][j] = 'E';
            }
        }
    }

    void setArray(std::vector<std::pair< Ship*,QLabel*>> sshhips);

    void setAroundShip(Ship* sshh);

    void setZeroAroundShip(Ship* sshh);
};
///first function
void Board::setArray(std::vector<std::pair< Ship*,QLabel*>> sshhips)
{
    int size;
    for(auto& sh : sshhips)
    {
        size = sh.first->w / 60;
        qDebug() << (sh.second->x()-200)/48 << " " << size <<" " << (sh.second->y()-183)/48;
        qDebug() << sh.second->x() << " " << sh.second->y() << ' ' << sh.first->st;

        if(sh.second->x()>= 250*0.8 && sh.second->x() <= 860*0.8 && sh.second->y() >= 220*0.8 && sh.second->y() <= 834*0.8)
        {
            if(sh.first->st == "h")
            {
                for(int i = (sh.second->x()-200)/48; i < ((sh.second->x()-200)/48) + size; i++)
                {
                    table[(sh.second->y()-183)/48][i] = 'S';
                }

                ///call setAroundShip Function
                //if(sh.first->zcolumn >= 1 && sh.first->zcolumn + size <= 8)
                //{
                   // setAroundShip(sh.first);
                //}

                // else if(sh.first->zrow == 0 || sh.first->zrow + size == 9)
                // {
                //     setZeroAroundShip(sh.first);
                // }

            }
            // else if(sh.first->st == 'v')
            // {
            //     for(int j = sh.first->zrow; j <= sh.first->zrow + size; j++)
            //     {
            //         table[j][sh.first->zcolumn];
            //     }

            //     ///call setAroundShip Function
            //     //if(sh.first->zrow >= 1 && sh.first->zrow + size <= 8)
            //     //{
            //       //  setAroundShip(sh.first);
            //     //}

            //     // else if(sh.first->zrow == 0 || sh.first->zrow + size == 9)
            //     // {
            //     //     setZeroAroundShip(sh.first);
            //     // }

            // }
        }
    }

}

///second function
// void Board::setAroundShip(Ship* sshh)
// {
//     int y = sshh->zrow;
//     int x = sshh->zcolumn;
//     int size = sshh->w;

//     if(sshh->st == 'h')
//     {
//         if(y != 0 && y != 9)
//         {
//             table[x - 1][y] = 'O';
//             table[x + size][y] = 'O';
//         }

//         else if(y == 0)
//         {
//             table[y][x + size] = 'O';
//         }

//         else if(y == 9)
//         {
//             table[y][x - 1] = 'O';
//         }

//         if(y != 0)
//         {
//             for(int i = x - 1; i <= x + size; i++)
//             {
//                 table[i][y - 1] = 'O';
//             }
//         }

//         if(y != 9)
//         {
//             for(int i = x - 1; i < x + size; i++)
//             {
//                 table[y + 1][i] = 'O';
//             }
//         }

//     }

//     else if(sshh->st == 'v')
//     {
//         if(y != 0 && y != 9)
//         {
//             table[x][y - 1] = 'O';
//             table[x][y + size] = 'O';
//         }

//         else if(x == 0)
//         {
//             table[x + size][y] = 'O';
//         }

//         else if(x == 9)
//         {
//             table[x - 1][y] = 'O';
//         }

//         if(x != 9)
//         {
//             for(int i = y - 1; i <= y + size; i++)
//             {
//                 table[x + 1][i] = 'O';
//             }

//         }
//         else if(x != 0)
//         {
//             for(int i = y - 1; i <= y + size; i++)
//             {
//                 table[x - 1][i] = 'O';
//             }
//         }
//     }

// }

///third Function
// void Board::setZeroAroundShip(Ship* sshh)
// {
//     int y = sshh->zcolumn;
//     int x = sshh->zrow;
//     int size = sshh->w;

//     if(sshh->st == 'h')
//     {
//         if(y != 0 && y != 9)
//         {
//             table[x][y - 1] = 'O';
//             table[x][y + size] = 'O';
//         }

//         else if(y == 0)
//         {
//             table[x][y + size] = 'O';
//         }

//         else if(y == 9)
//         {
//             table[x][y - 1] = 'O';
//         }

//         if(x == 0)
//         {
//             for(int i = y - 1; i <= y + size; i++)
//             {
//                 table[x + 1][i] = 'O';
//             }
//         }

//         else if(x == 9)
//         {
//             for(int i = y - 1; i <= y + size; i++)
//             {
//                 table[x - 1][i] = 'O';
//             }
//         }

//     }

//     else if(sshh->st == 'v')
//     {
//         if(x != 0 && x != 9)
//         {
//             table[x - 1][y] = 'O';
//             table[x + size][y] = 'O';
//         }

//         else if(x == 0)
//         {
//             table[x + size][y] = 'O';
//         }

//         else if(x == 9)
//         {
//             table[x - 1][y] = 'O';
//         }

//         if(y == 0)
//         {
//             for(int i = x - 1; i <= x + size; i++)
//             {
//                 table[i][y + 1] = 'O';
//             }
//         }

//         else if(y == 9)
//         {
//             for(int i = x - 1; i < x + size; i++)
//             {
//                 table[i][y - 1] = 'O';
//             }
//         }
//     }

// }


////Write function for drop
// bool checkPosOfShip(Ship* sshh)
// {
//     int x = sshh->zrow;
//     int y = sshh->zcolumn;

//     if(sshh->st == 'h')
//     {
//         for(int i = y; i < y + size; i++)
//         {
//             if(table[x][i] == 'S' ||table[x][i] == 'O')
//             {
//                 return false;
//             }
//         }
//     }

//     else if(sshh->st == 'v')
//     {
//         for(int i = x; i < x + size; i++)
//         {
//             if(table[i][y] == 'S' || table[i][y] == 'O')
//             {
//                 return false;
//             }
//         }
//     }

//     return true;
// }




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

        QLabel *labelA = new QLabel(this);
        Ship* A = new Ship(labelA, "C:/SeaBattle_Cute_private/drg/src/1Xship copy.png", 1010, 230, 60, 60);
        ships.push_back(std::make_pair(A,labelA));

        QLabel *labelB = new QLabel(this);
        Ship* B = new Ship(labelB, "C:/SeaBattle_Cute_private/drg/src/1Xship copy.png", 1106, 230, 60, 60);
        ships.push_back(std::make_pair(B,labelB));

        QLabel *labelC = new QLabel(this);
        Ship* C = new Ship(labelC, "C:/SeaBattle_Cute_private/drg/src/1Xship copy.png", 1202, 230, 60, 60);
        ships.push_back(std::make_pair(C,labelC));

        QLabel *labelD = new QLabel(this);
        Ship* D = new Ship(labelD, "C:/SeaBattle_Cute_private/drg/src/1Xship copy.png", 1298, 230, 60, 60);
        ships.push_back(std::make_pair(D,labelD));

        QLabel *labelE = new QLabel(this);
        Ship* E = new Ship(labelE, "C:/SeaBattle_Cute_private/drg/src/2Xship copy.png", 1010, 326, 120, 60);
        ships.push_back(std::make_pair(E,labelE));

        QLabel *labelF = new QLabel(this);
        Ship* F = new Ship(labelF, "C:/SeaBattle_Cute_private/drg/src/2Xship copy.png", 1154, 326, 120, 60);
        ships.push_back(std::make_pair(F,labelF));

        QLabel *labelG = new QLabel(this);
        Ship* G = new Ship(labelG, "C:/SeaBattle_Cute_private/drg/src/2Xship copy.png", 1298, 326, 120, 60);
        ships.push_back(std::make_pair(G,labelG));

        QLabel *labelH = new QLabel(this);
        Ship* H = new Ship(labelH, "C:/SeaBattle_Cute_private/drg/src/3Xship copy.png", 1010, 422, 180, 60);
        ships.push_back(std::make_pair(H,labelH));

        QLabel *labelI = new QLabel(this);
        Ship* I = new Ship(labelI, "C:/SeaBattle_Cute_private/drg/src/3Xship copy.png", 1202, 422, 180, 60);
        ships.push_back(std::make_pair(I,labelI));

        QLabel *labelJ = new QLabel(this);
        Ship* J = new Ship(labelJ, "C:/SeaBattle_Cute_private/drg/src/4Xship copy.png", 1010, 518, 240, 60);
        ships.push_back(std::make_pair(J,labelJ));


        QPushButton* restore = new QPushButton(this);
        restore->setGeometry(815, 665, 50, 50);
        restore->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
        restore->setCursor(Qt::PointingHandCursor);
        connect(restore, &QPushButton::clicked, QCoreApplication::quit);

        QPushButton* next = new QPushButton(this);
        next->setGeometry(1070, 665, 180, 50);
        next->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
        next->setCursor(Qt::PointingHandCursor);
        //connect(next, &QPushButton::clicked, QCoreApplication::quit);
        connect(next, &QPushButton::clicked, this, &DragWidget::onNextButtonClicked);

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
        // connect(houseIcon1, &ClickableLabel::clicked, this, &DragWidget::rotateHouseIcon);

    }

public slots:
    void onNextButtonClicked() {
        Board* br = new Board() ;
        br->setArray(ships);
        for (int i = 0; i <= 9; i++)
        {
            for (int j = 0; j <= 9; j++)
            {
                qDebug() << br->table[i][j];
            }
        }
        // Code to execute when the "next" button is clicked
        qDebug() << "Next button clicked!";

        // Example: Close the application
        QApplication::quit();
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
                    for (auto& pair : ships) {
                        if (pair.second == child) {
                            ship = pair.first;
                            break;
                        }
                    }

                    if (ship->w == 240 && column > 6 && ship->st == 'h') {
                        child->move(offset);
                    }
                    else if (ship->w == 180 && column > 7 && ship->st == 'h') {
                        child->move(offset);
                    }
                    else if (ship->w == 120 && column > 8 && ship->st == 'h') {
                        child->move(offset);
                    }
                    else if (ship->w == 240 && row < 3 && ship->st == 'v') {
                        child->move(offset);
                    }
                    else if (ship->w == 180 && row < 2 && ship->st == 'v') {
                        child->move(offset);
                    }
                    else if (ship->w == 120 && row < 1 && ship->st == 'v') {
                        child->move(offset);
                    }
                    else
                    {
                        child->move(xPos, yPos);
                    }




                    if (ship) {

                        qDebug() << "dropped at position" << position << " " << column << " " << row << " " << ship->w << " ";
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
