#include "mainwindow.h"
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QDataStream>
#include <QByteArray>
#include <QLabel>
#include <QPixmap>
#include <QPoint>
#include <QMouseEvent>
#include <QDropEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <iostream>
#include <fstream>
#include <string>
#include <QCoreApplication>
#include <sstream>
#include <vector>
#include <utility>
#include <QtCore/QRandomGenerator>
#include <QEventLoop>
#include <QTimer>
#include <QRandomGenerator>
#include <cstdlib>
#include <ctime>
#include <QSet>
#include <QDateTime>
#include <QDebug>
#include <random>
#include <QGraphicsOpacityEffect>



bool moveMentPerson = true;
bool moveMentBot = false;
bool fallShip = false;
bool fallShipOfBot = true;

static int firstShotOfPlayer[1][2] = {-1 , -1};
int firstShot[1][2];


int countshipperson;
int shootSuccses = 0;
int countShotInShip = 0;
int CountShotSuucsesBot = 0;
int CountShotSuucsesPlayer = 0;
int numberOfShook;
int botx = 0;
int shotFritInShip = 0;
int boty = 0;
int randX;
int randY;

QString direction;
QString exactDirection = "Default";
QString exactDirectionOfPlayer = "Default";
QString lastDirec;
QEventLoop eventLoop;
QChar table[10][10];


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

Ship::Ship(QLabel *label, QString pixmap, int x, int y, int width, int height)
    : label(label), xpos(x), ypos(y), w(width), h(height)
{
    st = "h";
    this->label = label;
    zcolumn = (label->x() - 200) / 48;
    zrow = (label->y() - 190) / 48;

    QPixmap f(pixmap);
    label->setPixmap(f);
    label->setGeometry(x, y, width, height);
    label->show();
}

void Ship::rotate()
{
    st = "v";
    label->setGeometry(label->x(), label->y(), w, h);  // Swap width and height
    QPixmap pixmap = label->pixmap();
    QTransform transform;
    transform.rotate(90);
    QPixmap transformedPixmap = pixmap.transformed(transform, Qt::SmoothTransformation);
    label->setPixmap(transformedPixmap);

}

std::vector<std::pair<Ship*, QLabel*>> ships;

void readFromFile(QChar tableWho[10][10], QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "Failed to open the file for reading." << std::endl;
        return ;
    }

    QTextStream in(&file);
    QVector<QString> map;
    int row = 0;
    int col = 0;

    while (!in.atEnd() && row < 10)
    {
        QString line = in.readLine();
        map.push_back(line);

        int charsToCopy = qMin(line.length(), 10);

        for (col = 0; col < charsToCopy; col++)
        {
            tableWho[row][col] = static_cast<char>(line.at(col).toLatin1());
        }

        for (; col < 10; col++)
        {
            tableWho[row][col] = 'E';
        }

        row++;
    }

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            qDebug() << tableWho[i][j];
        }
    }
}

class GamePage : public QFrame {
    Q_OBJECT

public:
    QChar bottable[10][10];

    int countPersonSucsses;
    int countBot;

    ///cord
    std::vector<std::pair<int, int>> currentShip;



    void setShipOfBot(int x, int y, QString sitution);

    bool CheckShip2XBot(QChar botTable[10][10], int X, int Y, QString DirectionOfPerson);

    bool CheckShip3XBot(QChar botTable[10][10], int X, int Y, QString DirectionOfPerson);

    bool CheckShip4XBot(QChar botTable[10][10], int X, int Y, QString DirectionOfPerson);

    void setWAroundF(int y, int x, int size, QString direc, QChar table[10][10]);

    bool checkSpecislIndex(int x, int y, QChar _table[10][10], int a);

    bool isSurroundedByEmptySpaces(int x, int y, QChar table[10][10]);

    void choseDirection(QChar _table[10][10], int& randX, int& randY);

    bool isShipOneSpace(int x, int y, QChar table[10][10], int a);

    void attackAgain(QChar _table[10][10], int X, int Y);

    void setboard(int xp, int yp, QChar status);

    void simpleAttack(QChar _table[10][10]);



    GamePage(QWidget *parent = nullptr) : QFrame(parent) {

        QLabel *labelA = new QLabel(this);
        Ship* A = new Ship(labelA, "C:/Users/98913/Downloads/1Xship copy.png", 190, 200, 60, 60);
        QLabel *labelB = new QLabel(this);
        Ship* B = new Ship(labelB, "C:/Users/98913/Downloads/1Xship copy.png", 1106, 230, 60, 60);
        QLabel *labelC = new QLabel(this);
        Ship* C = new Ship(labelC,"C:/Users/98913/Downloads/1Xship copy.png", 1202, 230, 60, 60);
        QLabel *labelD = new QLabel(this);
        Ship* D = new Ship(labelD, "C:/Users/98913/Downloads/1Xship copy.png", 1298, 230, 60, 60);
        QLabel *labelE = new QLabel(this);
        Ship* E = new Ship(labelE, "C:/Users/98913/Downloads/2Xship copy.png", 1010, 326, 120, 60);
        QLabel *labelF = new QLabel(this);
        Ship* F = new Ship(labelF,"C:/Users/98913/Downloads/2Xship copy.png", 1154, 326, 120, 60);
        QLabel *labelG = new QLabel(this);
        Ship* G = new Ship(labelG, "C:/Users/98913/Downloads/2Xship copy.png", 1298, 326, 120, 60);
        QLabel *labelH = new QLabel(this);
        Ship* H = new Ship(labelH, "C:/Users/98913/Downloads/3Xship copy.png", 1010, 422, 180, 60);

        QLabel *labelI = new QLabel(this);
        Ship* I = new Ship(labelI, "C:/Users/98913/Downloads/3Xship copy.png", 1202, 422, 180, 60);
        //1202 422
        QLabel *labelJ = new QLabel(this);
        Ship* J = new Ship(labelJ, "C:/Users/98913/Downloads/4Xship copy.png", 250, 468, 240, 60);

//1106 518

        ships.push_back(std::make_pair(A,labelA));
        ships.push_back(std::make_pair(B,labelB));
        ships.push_back(std::make_pair(C,labelC));
        ships.push_back(std::make_pair(D,labelD));
        ships.push_back(std::make_pair(E,labelE));
        ships.push_back(std::make_pair(F,labelF));
        ships.push_back(std::make_pair(G,labelG));
        ships.push_back(std::make_pair(H,labelH));
        ships.push_back(std::make_pair(I,labelI));
        ships.push_back(std::make_pair(J,labelJ));


        QFile file("C:/Users/98913/Desktop/New Text Document (3).txt");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        int i = 0;
        while (!in.atEnd())
        {
            QString situation = in.readLine();
            QString size = in.readLine();
            int X = in.readLine().toInt();
            int Y = in.readLine().toInt();

            ships[i].second->move(X, Y);
            if (situation == "v")
            {
                ships[i].first->rotate();
            }
            i += 1;
        }
        file.close();





        countPersonSucsses = 0;
        countBot = 0;

        layout = new QVBoxLayout(this); // Create a layout

        QLabel *backgroundLabel = new QLabel(this);
        QPixmap backgroundPixmap("F:/botMode/battlepage.png");
        backgroundLabel->setPixmap(backgroundPixmap);
        backgroundLabel->setScaledContents(true);
        backgroundLabel->setGeometry(0, 0, 1536, 864); // Set the geometry to cover the entire window
        backgroundLabel->lower(); // Send the background label to the back
        backgroundLabel->setAcceptDrops(false);


        readFromFile(bottable, "botfile.txt");
        readFromFile(table, "personfile.txt");

        //parseCoordinatesFromFile(ships);

        qDebug() << table[0][0] << table[1][0];

    }

    void mousePressEvent(QMouseEvent *event) override
    {
        if(moveMentPerson == false)
        {
            qDebug() << "salam";
            return;
        }
        printMouseClick(event->pos());
    }

    void printMouseClick(const QPoint &pos);



private:

    QVBoxLayout *layout;

};

GamePage* gamepage;


void GamePage::setShipOfBot(int x, int y, QString sitution)
{

    x = x * 48 + 861;
    y = y * 48 + 190;


    if(sitution == "1")
    {
        QLabel *Ship1xhLable = new QLabel(gamepage);
        QPixmap ship1xPixmap("C:/Users/98913/Downloads/1Xship copy.png");
        Ship1xhLable->setPixmap(ship1xPixmap);
        Ship1xhLable->setScaledContents(true);
        Ship1xhLable->setGeometry(x, y, 48, 48);

        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
        opacityEffect->setOpacity(0.85);

        Ship1xhLable->setGraphicsEffect(opacityEffect);



        Ship1xhLable->lower();
        Ship1xhLable->raise();
        Ship1xhLable->show();
    }

    if(sitution == "2h")
    {
        QLabel *Ship2xhLable = new QLabel(gamepage);
        QPixmap ship2xPixmap("C:/Users/98913/Downloads/2Xship copy (1).png");
        Ship2xhLable->setPixmap(ship2xPixmap);
        Ship2xhLable->setScaledContents(true);
        Ship2xhLable->setGeometry(x, y, 96, 48);

        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
        opacityEffect->setOpacity(0.85);

        Ship2xhLable->setGraphicsEffect(opacityEffect);

        Ship2xhLable->lower();
        Ship2xhLable->raise();
        Ship2xhLable->show();

    }

    else if(sitution == "2v")
    {
        QLabel *Ship2xhLable = new QLabel(gamepage);
        QPixmap ship2xPixmap("C:/Users/98913/Downloads/2VXship copy (1).png");
        Ship2xhLable->setPixmap(ship2xPixmap);
        Ship2xhLable->setScaledContents(true);
        Ship2xhLable->setGeometry(x, y, 48, 96);

        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
        opacityEffect->setOpacity(0.85);

        Ship2xhLable->setGraphicsEffect(opacityEffect);

        Ship2xhLable->lower();
        Ship2xhLable->raise();
        Ship2xhLable->show();
    }

    else if(sitution == "3h")
    {
        QLabel *Ship3xhLable = new QLabel(gamepage);
        QPixmap ship3xPixmap("C:/Users/98913/Downloads/3Xship copy.png");
        Ship3xhLable->setPixmap(ship3xPixmap);
        Ship3xhLable->setScaledContents(true);
        Ship3xhLable->setGeometry(x, y, 144, 48);

        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
        opacityEffect->setOpacity(0.85);

        Ship3xhLable->setGraphicsEffect(opacityEffect);

        Ship3xhLable->lower();
        Ship3xhLable->raise();
        Ship3xhLable->show();
    }

    else if(sitution == "3v")
    {
        QLabel *Ship3xhLable = new QLabel(gamepage);
        QPixmap ship3xPixmap("C:/Users/98913/Downloads/3VXship copy.png");
        Ship3xhLable->setPixmap(ship3xPixmap);
        Ship3xhLable->setScaledContents(true);
        Ship3xhLable->setGeometry(x, y, 48, 144);

        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
        opacityEffect->setOpacity(0.85);

        Ship3xhLable->setGraphicsEffect(opacityEffect);

        Ship3xhLable->lower();
        Ship3xhLable->raise();
        Ship3xhLable->show();
    }

    else if(sitution == "4h")
    {
        QLabel *Ship4xhLable = new QLabel(gamepage);
        QPixmap ship4xPixmap("C:/Users/98913/Downloads/4Xship copy.png");
        Ship4xhLable->setPixmap(ship4xPixmap);
        Ship4xhLable->setScaledContents(true);
        Ship4xhLable->setGeometry(x, y, 192, 48);

        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
        opacityEffect->setOpacity(0.85);

        Ship4xhLable->setGraphicsEffect(opacityEffect);

        Ship4xhLable->lower();
        Ship4xhLable->raise();
        Ship4xhLable->show();

    }

    else if(sitution == "4v")
    {
        QLabel *Ship4xhLable = new QLabel(gamepage);
        QPixmap ship4xPixmap("C:/Users/98913/Downloads/4VXship copy.png");
        Ship4xhLable->setPixmap(ship4xPixmap);
        Ship4xhLable->setScaledContents(true);
        Ship4xhLable->setGeometry(x, y, 48, 192);

        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
        opacityEffect->setOpacity(0.85);

        Ship4xhLable->setGraphicsEffect(opacityEffect);

        Ship4xhLable->lower();
        Ship4xhLable->raise();
        Ship4xhLable->show();
    }
}

bool GamePage::CheckShip2XBot(QChar botTable[10][10], int X, int Y, QString DirectionOfPerson)
{
    qDebug() << "CheckShip2Bot";

    botTable[X][Y] = 'B';

    if(DirectionOfPerson == "horizontal")
    {
        if(botTable[X][Y - 1] == 'B' && Y >= 1 && botTable[X][Y + 1] != 'B')
        {
            if(botTable[X][Y + 1] != 'S' && botTable[X][Y - 2] != 'B')
            {
                if(botTable[X][Y - 2] != 'S')
                {
                    botTable[X][Y] = 'F';
                    botTable[X][Y - 1] = 'F';

                    gamepage->setShipOfBot(Y - 1, X, "2h");

                    return true;
                }
            }
        }

        else if(botTable[X][Y + 1] == 'B' && Y >= 1 && botTable[X][Y - 1] != 'B')
        {
            if(botTable[X][Y - 1] != 'S' && botTable[X][Y + 2] != 'B')
            {
                if(botTable[X][Y + 2] != 'S')
                {
                    botTable[X][Y] = 'F';
                    botTable[X][Y + 1] = 'F';

                    gamepage->setShipOfBot(Y, X, "2h");


                    return true;
                }
            }
        }

        return false;
    }

    else if(DirectionOfPerson == "vertical")
    {
        if(botTable[X - 1][Y] == 'B' && Y >= 1 && botTable[X + 1][Y] != 'B')
        {
            if(botTable[X + 1][Y] != 'S' && botTable[X - 2][Y] != 'B')
            {
                if(botTable[X - 2][Y] != 'S')
                {
                    botTable[X][Y] = 'F';
                    botTable[X - 1][Y] = 'F';

                    gamepage->setShipOfBot(Y, X - 1, "2v");


                    return true;
                }
            }
        }

        else if(botTable[X + 1][Y] == 'B' && Y >= 1 && botTable[X - 1][Y] != 'B')
        {
            if(botTable[X - 1][Y] != 'S' && botTable[X + 2][Y] != 'B')
            {
                if(botTable[X + 2][Y] != 'S')
                {
                    botTable[X][Y] = 'F';
                    botTable[X + 1][Y] = 'F';

                    gamepage->setShipOfBot(Y, X, "2v");

                    return true;
                }
            }
        }
        return false;
    }

}

bool GamePage::CheckShip3XBot(QChar botTable[10][10], int X, int Y, QString DirectionOfPerson)
{
    qDebug() << "CheckShip3Bot";
    countShotInShip = 0;
    botTable[X][Y] = 'B';

    if(DirectionOfPerson == "horizontal")
    {
        if(botTable[X][Y - 1] == 'S' || botTable[X][Y + 1] == 'S') return false;

        if(botTable[X][Y - 1] == 'W' || botTable[X][Y - 1] == 'E')
        {
            for(int j = Y; j <= Y + 3; j++)
            {
                if(botTable[X][j] == 'B')
                {
                    countShotInShip++;
                }
                else if(botTable[X][j] == 'S')
                {
                    return false;
                }
            }

            if(countShotInShip == 3)
            {
                if(botTable[X][Y] == 'B') gamepage->setShipOfBot(Y, X, "3h");

                else gamepage->setShipOfBot(Y + 1, X, "3h");

                return true;
            }
        }

        else if(botTable[X][Y + 1] == 'W' || botTable[X][Y + 1] == 'E')
        {
            for(int j = Y; j >= Y - 3; j--)
            {
                if(botTable[X][j] == 'B')
                {
                    countShotInShip++;
                }
                else if(botTable[X][j] == 'S')
                {
                    return false;
                }
            }
            if(countShotInShip == 3)
            {
                if(botTable[X][Y] == 'B') gamepage->setShipOfBot(Y - 2, X, "3h");

                else gamepage->setShipOfBot(Y - 3, X, "3h");

                return true;
            }

        }

        int c = 0;
        int firstY = 0;
        for(int j = Y - 2; j <= Y + 2; j++)
        {
            if(botTable[X][j] == 'B')
            {

                c++;

                if(c == 1)
                {
                    firstY = j;
                }

                countShotInShip++;
            }
            else if(botTable[X][j] == 'S')
            {
                return false;
            }
        }

        if(countShotInShip == 3)
        {
            gamepage->setShipOfBot(Y, X, "3h");
            return true;
        }

        else return false;

    }

    else if(DirectionOfPerson == "vertical")
    {

        if(botTable[X - 1][Y] == 'S' || botTable[X + 1][Y] == 'S') return false;


        if(botTable[X - 1][Y] == 'W' || botTable[X - 1][Y] == 'E')
        {
            for(int j = X; j <= X + 3; j++)
            {
                if(botTable[j][Y] == 'B')
                {
                    countShotInShip++;
                    qDebug() << "countShotInShip " << countShotInShip;
                }
                else if(botTable[j][Y] == 'S')
                {
                    return false;
                }
            }

            if(countShotInShip == 3)
            {
                if(botTable[X][Y] == 'B')
                {
                    gamepage->setShipOfBot(Y, X, "3v");
                }
                else
                {
                    gamepage->setShipOfBot(Y, X + 1, "3v");
                }

                return true;
            }
        }

        else if(botTable[X + 1][Y] == 'W' || botTable[X + 1][Y] == 'E')
        {
            for(int j = X; j >= X - 3; j--)
            {
                if(botTable[j][Y] == 'B')
                {
                    countShotInShip++;
                }
                else if(botTable[j][Y] == 'S')
                {
                    return false;
                }
            }
            if(countShotInShip == 3)
            {
                if(botTable[X][Y] == 'B')
                {
                    gamepage->setShipOfBot(Y, X - 2, "3v");
                }
                else
                {
                    gamepage->setShipOfBot(Y, X - 1, "3v");
                }
                return true;
            }

        }

        int c = 0;
        int firstb = 0;

        for(int j = X - 2; j <= X + 2; j++)
        {
            if(botTable[j][Y] == 'B')
            {
                c++;
                if(c == 1)
                {
                    firstb = j;
                }
                countShotInShip++;
            }
            else if(botTable[j][Y] == 'S')
            {
                return false;
            }
        }

        if(countShotInShip == 3)
        {

            gamepage->setShipOfBot(Y, firstb, "3v");
            return true;
        }

        else return false;
    }

}

bool GamePage::CheckShip4XBot(QChar botTable[10][10], int X, int Y, QString DirectionOfPerson)
{
    qDebug() << "CheckShip4Bot";
    countShotInShip = 0;
    botTable[X][Y] = 'B';

    if(DirectionOfPerson == "horizontal")
    {
        if(botTable[X][Y + 1] == 'B' && botTable[X][Y + 2] == 'B' && botTable[X][Y + 3] == 'B')
        {
            gamepage->setShipOfBot(Y, X, "4h");
            return true;
        }


        else if(botTable[X][Y - 1] == 'B' && botTable[X][Y - 2] == 'B' && botTable[X][Y - 3] == 'B')
        {
            gamepage->setShipOfBot(Y - 3, X, "4h");
            return true;
        }

        int c = 0;
        int yfirst = 0;
        for(int j = Y - 2; j <= Y + 2; j++)
        {
            if(botTable[X][j] == 'B')
            {
                c++;
                if(c == 1)
                {
                    yfirst = j;
                }
                countShotInShip++;
            }
            else if(botTable[X][j] == 'S')
            {
                return false;
            }
        }

        if(countShotInShip == 4)
        {

            gamepage->setShipOfBot(yfirst, X, "4h");
            return true;
        }

        return false;
    }

    else if(DirectionOfPerson == "vertical")
    {
        if(botTable[X + 1][Y] == 'B' && botTable[X + 2][Y] == 'B' && botTable[X + 3][Y] == 'B')
        {
            gamepage->setShipOfBot(Y, X + 3, "4v");
            return true;

        }

        else if(botTable[X - 1][Y] == 'B' && botTable[X - 2][Y] == 'B' && botTable[X - 3][Y] == 'B')
        {
            gamepage->setShipOfBot(Y, X, "4v");
            return true;
        }



        int c = 0;
        int first = 0;
        for(int i = X - 2; i <= X + 2; i++)
        {
            if(botTable[i][Y] == 'B')
            {
                c++;
                if(c == 1)
                {
                    first = i;
                }
                countShotInShip++;
            }
            else if(botTable[i][Y] == 'S')
            {
                return false;
            }
        }

        if(countShotInShip == 4)
        {
            gamepage->setShipOfBot(Y, first, "4v");
            return true;
        }

        return false;
    }
}

void GamePage::setboard(int xp, int yp, QChar status)
{
    int yPos;
    int xPos;

    qDebug() << xp << yp;

    if(xp > 9 || xp < 0)
    {
        return;
    }
    if(yp > 9 || yp < 0)
        return;

    if(status == 'B')
    {
        qDebug() << "Bomb";

        xPos = yp * 48 + 195;
        yPos = xp * 48 + 188;

        // if(((yPos >= 200 && yPos <= 677) || (yPos >= 860 && yPos <= 1340)) && (xPos >= 188 && xPos <= 670))
        //{
        QLabel *b = new QLabel(gamepage);
        QPixmap pix("F:/botMode/test_mark_cross.png");
        b->setPixmap(pix);
        b->setScaledContents(true);
        b->setGeometry(xPos, yPos, 48, 48);
        b->raise();
        b->show();


        QTimer::singleShot(1000, &eventLoop, &QEventLoop::quit);

        eventLoop.exec();
        //}
    }

    else if(status == 'W')
    {
        if(table[xp][yp] == 'W')
        {
            return;
        }
        table[xp][yp] = 'W';

        qDebug() << "Wrong";

        xPos = yp * 48 + 200;
        yPos = xp * 48 + 190;

        //if(((yPos >= 200 && yPos <= 677) || (yPos >= 860 && yPos <= 1340)) && (xPos >= 188 && xPos <= 670))
        //{

        QLabel *b = new QLabel(gamepage);
        QPixmap pix("F:/botMode/missed missile.png");
        b->setPixmap(pix);
        b->setScaledContents(true);
        b->setGeometry(xPos, yPos, 48, 48);
        b->raise();
        b->show();
        QTimer::singleShot(300, &eventLoop, &QEventLoop::quit);

        eventLoop.exec();
        //}
    }

}

/// x , y left of ship
void GamePage::setWAroundF(int y, int x, int size, QString direc, QChar table[10][10])
{
    CountShotSuucsesBot++;

    if(direc == "horizontal")
    {
        if(y != 0 && y != 9)
        {
            //table[x][y - 1] = 'W';
            setboard(x, y - 1, 'W');

            //table[x][y + size] = 'W';
            setboard(x, y + size, 'W');

        }

        else if(y == 0)
        {
            //table[x][y + size] = 'W';
            setboard(x, y + size, 'W');

        }

        else if(y == 9)
        {
            //table[x][y - 1] = 'W';
            setboard(x, y - 1, 'W');
        }

        if(x != 0)
        {
            for(int i = y - 1; i <= y + size; i++)
            {
                //table[x - 1][i] = 'W';
                setboard(x - 1, i, 'W');
            }
        }

        if(x != 9)
        {
            for(int i = y - 1; i <= y + size; i++)
            {
                //table[x + 1][i] = 'W';
                setboard(x + 1, i, 'W');

            }
        }

    }

    else if(direc == "vertocal")
    {
        if(x != 0 && x != 9)
        {
            //table[x - 1][y] = 'W';
            setboard(x - 1, y, 'W');

            //table[x + size][y] = 'W';
            setboard(x + size, y, 'W');

        }

        else if(x == 0)
        {
            //table[x + size][y] = 'W';
            setboard(x + size, y, 'W');

        }

        else if(x == 9)
        {
            //table[x - 1][y] = 'W';
            setboard(x - 1, y, 'W');
        }

        if(y != 9)
        {
            for(int i = x - 1 ; i <= x + size; i++)
            {
                //table[i][y + 1] = 'W';
                setboard(i, y + 1, 'W');

            }
        }

        if(y != 0)
        {
            for(int i = x - 1; i <= x + size; i++)
            {
                //table[i][y - 1] = 'W';
                setboard(i, y - 1, 'W');

            }
        }
    }
}

void GamePage::attackAgain(QChar _table[10][10], int X, int Y)
{
    qDebug() << X << Y;

    if(_table[X][Y] == 'S')
    {
        _table[X][Y] = 'B';
        setboard(X,Y,'B');
        shootSuccses++;

        if(X == firstShot[0][0])
        {
            direction = "horizontal";

            if(Y - firstShot[0][1] > 0)
            {
                lastDirec = "Right";

                if(exactDirection == "Right")
                {
                    if(Y == 9)
                    {
                        if(_table[X][Y - 2] == 'B' || _table[X][Y - 2] == 'S')
                        {
                            if (_table[X][Y - 3] == 'B' || _table[X][Y - 3] == 'S')
                            {

                                _table[X][Y - 2] = 'F';
                                setboard(X,Y - 2,'B');

                                _table[X][Y - 3] = 'F';
                                setboard(X,Y - 3,'B');

                                _table[X][Y - 1] = 'F';
                                setboard(X,Y - 1,'B');

                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                setWAroundF(Y - 3,X ,4, "horizontal", _table);
                                fallShip = true;
                                return;
                            }

                            else
                            {

                                _table[X][Y - 2] = 'F';
                                setboard(X,Y - 2,'B');

                                _table[X][Y - 1] = 'F';
                                setboard(X,Y -1 ,'B');

                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                fallShip = true;
                                setWAroundF(Y - 2,X ,3, "horizontal", _table);
                                return;
                            }
                        }

                        else if (_table[X][Y - 2] != 'S' || _table[X][Y - 2] != 'B')
                        {
                            _table[X][Y - 1] = 'F';
                            setboard(X,Y - 1,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            fallShip = true;
                            setWAroundF(Y - 1, X, 2, "horizontal", _table);
                            return;
                        }
                    }

                    //table 2 space fall
                    if((_table[X][Y + 1] != 'S' && (_table[X][Y - 2] != 'B')&& Y >= 2)
                        || (Y < 2 && _table[X][Y + 1] != 'S'))
                    {
                        _table[X][Y - 1] = 'F';
                        setboard(X,Y - 1,'B');


                        _table[X][Y] = 'F';
                        setboard(X,Y,'B');

                        setWAroundF(Y - 1, X, 2, "horizontal", _table);
                        fallShip = true;
                        return;
                    }

                    //absoultly have 3 space maby 4 space
                    else if((_table[X][Y + 1] != 'S' && _table[X][Y - 2] == 'B' && Y <= 8) ||
                             (Y == 9 && _table[X][Y - 2] == 'B'))
                    {
                        //have 4 space
                        if(_table[X][Y - 3] == 'B' && Y >= 3)
                        {
                            _table[X][Y - 3] = 'F';
                            setboard(X,Y - 3,'B');

                            _table[X][Y - 2] = 'F';
                            setboard(X,Y - 2,'B');

                            _table[X][Y - 1] = 'F';
                            setboard(X,Y - 1,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            setWAroundF(Y - 3, X, 4, "horizontal", _table);
                            fallShip = true;
                        }

                        //have 3 space
                        else
                        {
                            _table[X][Y - 2] = 'F';
                            setboard(X,Y - 2,'B');

                            _table[X][Y - 1] = 'F';
                            setboard(X,Y - 1,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            setWAroundF(Y - 2, X, 3, "horizontal", _table);
                            fallShip = true;
                        }
                    }

                    //absoultly have 3 space maby 4 space
                    else if(_table[X][Y + 1] == 'S' && Y <= 8)
                    {
                        _table[X][Y + 1] = 'B';
                        setboard(X,Y + 1,'B');

                        if(_table[X][Y - 1] == 'B' && _table[X][Y - 2] == 'B')
                        {
                            _table[X][Y + 1] = 'F';

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            _table[X][Y - 1] = 'F';
                            setboard(X,Y - 1,'B');

                            _table[X][Y - 2] = 'F';
                            setboard(X,Y - 2,'B');

                            fallShip = true;
                            setWAroundF(Y - 2, X, 4, "horizontal", _table);
                            return;
                        }


                        //have 3 space
                        else if( (_table[X][Y + 2] != 'S' && _table[X][Y - 2] != 'B' && Y <= 7 && Y >= 2) ||
                                 (Y == 1 && _table[X][Y + 2] != 'S'))
                        {
                            _table[X][Y + 1] = 'F';
                            setboard(X,Y + 1,'B');

                            _table[X][Y - 1] = 'F';
                            setboard(X,Y - 1,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            setWAroundF(Y - 1, X, 3, "horizontal", _table);
                            fallShip = true;
                        }

                        //havev 4 space
                        else if(_table[X][Y + 2] == 'S' && Y <= 7)
                        {
                            _table[X][Y + 2] = 'F';
                            setboard(X,Y + 2,'B');

                            _table[X][Y + 1] = 'F';
                            setboard(X,Y + 1,'B');

                            _table[X][Y - 1] = 'F';
                            setboard(X,Y - 1,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            setWAroundF(Y - 1, X, 4, "horizontal", _table);
                            fallShip =  true;
                        }

                        else if(_table[X][Y - 3] == 'W' && Y >= 2)
                        {
                            _table[X][Y - 2] = 'F';
                            setboard(X,Y - 2,'B');

                            _table[X][Y - 1] = 'F';
                            setboard(X,Y - 1,'B');

                            _table[X][Y + 1] = 'F';
                            setboard(X,Y+ 1,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            setWAroundF(Y - 2, X, 4, "horizontal", _table);
                            fallShip = true;

                            return;
                        }

                    }
                }

                else if(exactDirection == "Default")
                {
                    if(Y == 9)
                    {
                        if(_table[X][Y - 2] == 'S')
                        {
                            if (_table[X][Y - 3] == 'S')
                            {
                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                _table[X][Y - 1] = 'F';
                                setboard(X,Y - 1,'B');

                                _table[X][Y - 2] = 'F';
                                setboard(X,Y - 2,'B');

                                _table[X][Y - 3] = 'F';
                                setboard(X,Y - 3,'B');

                                ///set f

                                fallShip = true;
                                setWAroundF(Y - 3, X, 4, "horizontal", _table);

                                return;
                            }

                            else
                            {
                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                _table[X][Y - 1] = 'F';
                                setboard(X,Y - 1,'B');

                                _table[X][Y - 2] = 'F';
                                setboard(X,Y - 2,'B');

                                fallShip = true;
                                setWAroundF(Y - 2, X, 3, "horizontal", _table);

                                return;
                            }
                        }
                        else
                        {
                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            _table[X][Y - 1] = 'F';
                            setboard(X,Y - 1,'B');

                            fallShip = true;
                            setWAroundF(Y - 1, X, 2, "horizontal", _table);

                            return;
                        }
                    }

                    //check ship 2 space
                    if((_table[X][Y + 1] != 'S' && _table[X][Y - 2] != 'S' && (Y <= 8 || Y >= 2))

                        || (Y == 1 && _table[X][Y + 1] != 'S')

                        || (Y == 9 && _table[X][Y - 2] != 'S'))
                    {
                        //ship had 2 spaces but now fall
                        _table[X][Y] = 'F';
                        setboard(X,Y,'B');

                        _table[X][Y - 1] = 'F';
                        setboard(X,Y - 1,'B');

                        setWAroundF(Y - 1, X, 2, "horizontal", _table);
                        fallShip = true;

                        ///call function to w arount f

                        return;
                    }

                    //absoultly have 3 space
                    else if((_table[X][Y + 1] == 'S' && _table[X][Y + 2] != 'S' && _table[X][Y - 2] != 'S' && (Y <= 7 || Y >= 2))

                             ||(Y == 1 && _table[X][Y + 1] == 'S' && _table[X][Y + 2] != 'S')

                             || (Y == 9 && _table[X][Y - 2] != 'S'&& _table[X][Y + 1] == 'S'))
                    {

                        _table[X][Y - 1] = 'F';
                        setboard(X,Y - 1,'B');


                        _table[X][Y] = 'F';
                        setboard(X,Y,'B');


                        _table[X][Y + 1] = 'F';
                        setboard(X,Y + 1,'B');

                        setWAroundF(Y - 1, X, 3, "horizontal", _table);

                        fallShip = true;
                        shootSuccses++;
                        return;
                    }


                    //maby ship have 3 or 4 spaces and change direction
                    else if((_table[X][Y + 1] != 'S' && Y <= 8))
                    {
                        if(_table[X][Y + 1] == 'E')
                        {
                            moveMentBot = false;
                        }
                        //_table[X][Y + 1] = 'W';
                        setboard(X,Y + 1,'W');

                        moveMentBot = false;
                        exactDirection = "Left";
                        fallShip = false;

                        return;
                    }

                    else if(Y == 9)
                    {
                        exactDirection = "Left";
                        fallShip = false;
                        return;
                    }

                    //have 4 space
                    else if(_table[X][Y + 1] == 'S' && Y >= 1)
                    {
                        qDebug() << "4";

                        //absoultly have 4 apace
                        if(_table[X][Y + 2] == 'S' && Y <= 7)
                        {
                            _table[X][Y - 1] = 'F';
                            setboard(X,Y - 1,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            _table[X][Y + 2] ='F';
                            setboard(X,Y + 2,'B');

                            _table[X][Y + 1] = 'F';
                            setboard(X,Y + 1,'B');

                            setWAroundF(Y - 1, X, 4, "horizontal", _table);

                            fallShip = true;
                            return ;
                        }

                        //absoultly have 4 spacce but should change direction
                        else if((_table[X][Y + 2] != 'S')  && _table[X][Y - 2] == 'S' && Y <= 7 && Y >= 2)
                        {
                            if(_table[X][Y + 2] == 'E')
                            {
                                moveMentBot = false;
                            }

                            _table[X][Y + 1] = 'B';
                            setboard(X,Y + 1,'B');

                            //_table[X][Y + 2] = 'W';
                            setboard(X,Y + 2,'W');


                            exactDirection = "Left";
                            fallShip = false;
                            shootSuccses++;

                            return;
                        }
                    }
                }
            }

            if(Y - firstShot[0][1] < 0)
            {
                lastDirec = "Left";

                if(exactDirection == "Left")
                {

                    if(Y == 0)
                    {
                        if(_table[X][Y + 2] == 'B')
                        {
                            if(_table[X][Y + 3] == 'B')
                            {
                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                _table[X][Y + 1] = 'F';
                                setboard(X,Y + 1,'B');

                                _table[X][Y + 2] = 'F';
                                setboard(X,Y + 2,'B');

                                _table[X][Y + 3] = 'F';
                                setboard(X,Y + 3,'B');

                                fallShip = true;
                                setWAroundF(Y, X, 4, "horizontal", _table);

                                return;
                            }

                            else
                            {
                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                _table[X][Y + 1] = 'F';
                                setboard(X,Y + 1,'B');

                                _table[X][Y + 2] = 'F';
                                setboard(X,Y + 2,'B');

                                fallShip = true;
                                setWAroundF(Y, X, 3, "horizontal", _table);

                                return;
                            }
                        }

                        else if(_table[X][Y + 2] != 'S')
                        {
                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            _table[X][Y + 1] = 'F';
                            setboard(X,Y + 1,'B');

                            fallShip = true;
                            setWAroundF(Y, X, 2, "horizontal", _table);

                            return;
                        }
                    }

                    //table 2 space fall
                    if((_table[X][Y - 1] != 'S' && _table[X][Y + 2] != 'B' && Y >= 1 && Y <= 7)
                        || (Y == 0 && _table[X][Y + 2] != 'B') || (Y == 8 && _table[X][Y - 1] != 'S'))
                    {
                        _table[X][Y] = 'F';
                        setboard(X,Y,'B');

                        _table[X][Y + 1] = 'F';
                        setboard(X,Y + 1,'B');

                        setWAroundF(Y, X, 2, "horizontal", _table);

                        fallShip = true;
                        return;
                    }




                    //absoultly have 3 space maby 4 space
                    else if(_table[X][Y - 1] != 'S' && _table[X][Y + 2] == 'B' && Y >= 1 && Y <= 7)
                    {
                        //have 4 space
                        if(_table[X][Y + 3] == 'B' && Y <= 6)
                        {
                            _table[X][Y + 3] = 'F';
                            setboard(X,Y + 3,'B');

                            _table[X][Y + 2] = 'F';
                            setboard(X,Y + 2,'B');

                            _table[X][Y + 1] = 'F';
                            setboard(X,Y + 1,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            fallShip = true;
                            setWAroundF(Y, X, 4, "horizontal", _table);

                            return;
                        }

                        //have 3 space
                        else if(Y == 7 || (_table[X][Y + 3] != 'B' && Y <=6))
                        {
                            _table[X][Y + 2] = 'F';
                            setboard(X,Y + 2,'B');

                            _table[X][Y + 1] = 'F';
                            setboard(X,Y + 1,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            fallShip = true;
                            setWAroundF(Y, X, 3, "horizontal", _table);

                            return;
                        }

                    }

                    //absoultly have 3 space maby 4 space
                    else if((_table[X][Y - 1] == 'S' && Y >= 1) || (Y == 0))
                    {
                        if(Y == 0)
                        {
                            if(_table[X][Y + 3] == 'B')
                            {
                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                _table[X][Y + 1] = 'F';
                                setboard(X,Y + 1,'B');

                                _table[X][Y + 2] = 'F';
                                setboard(X,Y + 2,'B');

                                _table[X][Y + 3] = 'F';
                                setboard(X,Y + 3,'B');

                                setWAroundF(Y, X, 4, "horizontal", _table);

                                return;
                            }

                            else if(_table[X][Y + 2] == 'B')
                            {
                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                _table[X][Y + 1] = 'F';
                                setboard(X,Y + 1,'B');

                                _table[X][Y + 2] = 'F';
                                setboard(X,Y + 2,'B');

                                setWAroundF(Y, X, 3, "horizontal", _table);

                                return;
                            }

                        }


                        if(Y >= 1)
                            _table[X][Y - 1] = 'B';

                        //have 3 space
                        if(_table[X][Y - 2] != 'S' && _table[X][Y + 2] != 'B' && Y >= 2 && Y <= 7)
                        {
                            _table[X][Y - 1] = 'F';
                            setboard(X,Y - 1,'B');

                            _table[X][Y + 1] = 'F';
                            setboard(X,Y + 1,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            setWAroundF(Y - 1, X, 3, "horizontal", _table);

                            fallShip = true;
                        }

                        //havev 4 space
                        else if(_table[X][Y - 2] == 'S' && Y >= 2)
                        {
                            _table[X][Y - 2] = 'F';
                            setboard(X,Y - 2,'B');

                            _table[X][Y - 1] = 'F';
                            setboard(X,Y - 1,'B');

                            _table[X][Y + 1] = 'F';
                            setboard(X,Y + 1,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            setWAroundF(Y - 2, X, 4, "horizontal", _table);

                            fallShip =  true;
                        }

                        else if(_table[X][Y + 3] == 'W' && Y <= 6)
                        {
                            _table[X][Y + 2] = 'F';
                            setboard(X,Y + 2,'B');

                            _table[X][Y + 1] = 'F';
                            setboard(X,Y + 1,'B');

                            _table[X][Y - 1] = 'F';
                            setboard(X,Y - 1,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            fallShip = true;
                            setWAroundF(Y - 1, X, 4, "horizontal", _table);

                            return;
                        }
                    }
                }

                else if(exactDirection == "Default")
                {
                    if(Y == 0)
                    {
                        if(_table[X][Y + 2] == 'S')
                        {
                            if(_table[X][Y + 3] == 'S')
                            {
                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                _table[X][Y + 1] = 'F';
                                setboard(X,Y + 1,'B');

                                _table[X][Y + 2] = 'F';
                                setboard(X,Y + 2,'B');

                                _table[X][Y + 3] = 'F';
                                setboard(X,Y + 3,'B');

                                setWAroundF(Y, X, 4, "horizontal", _table);

                                fallShip = true;
                                return;
                            }

                            else if(_table[X][Y + 3] != 'S')
                            {
                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                _table[X][Y + 1] = 'F';
                                setboard(X,Y + 1,'B');

                                _table[X][Y + 2] = 'F';
                                setboard(X,Y + 2,'B');

                                fallShip = true;
                                setWAroundF(Y, X, 3, "horizontal", _table);

                                return;
                            }
                        }

                        else if(_table[X][Y + 2] != 'S')
                        {
                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            _table[X][Y + 1] = 'F';
                            setboard(X,Y + 1,'B');

                            fallShip = true;
                            setWAroundF(Y, X, 2, "horizontal", _table);

                            return;
                        }
                    }

                    //check ship 2 space
                    if(_table[X][Y - 1] != 'S' && _table[X][Y + 2] != 'S' && (Y >= 1 || Y <= 7)
                        || (Y == 0 && _table[X][Y + 2] != 'S') || (Y == 8 && _table[X][Y - 1] != 'S'))
                    {
                        //ship had 2 spaces but now fall
                        _table[X][Y] = 'F';
                        setboard(X,Y,'B');

                        _table[X][Y + 1] = 'F';
                        setboard(X,Y + 1,'B');

                        fallShip = true;
                        setWAroundF(Y, X, 2, "horizontal", _table);

                        //atack again random
                        return;
                    }

                    //absoultly have 3 space
                    else if(_table[X][Y - 1] == 'S' &&  (_table[X][Y - 2] == 'E' || _table[X][Y - 2] == 'W') && (_table[X][Y + 2] == 'E' || _table[X][Y + 2] == 'W') && Y >= 2 && Y <= 7
                             || (Y == 1 && _table[X][Y - 1] == 'S' && (_table[X][Y + 2] == 'E' ||_table[X][Y + 2] == 'W')))
                    {

                        _table[X][Y] = 'F';
                        setboard(X,Y,'B');

                        _table[X][Y - 1] = 'F';
                        setboard(X,Y - 1,'B');

                        _table[X][Y + 1] = 'F';
                        setboard(X,Y + 1,'B');


                        fallShip = true;
                        shootSuccses++;
                        setWAroundF(Y - 1, X, 3, "horizontal", _table);

                        return;
                    }

                    //have 4 space
                    else if(_table[X][Y - 1] == 'S' && Y >= 1)
                    {
                        //absoultly have 4 apace
                        if(_table[X][Y - 2] == 'S' && Y >= 2)
                        {
                            _table[X][Y - 1] = 'F';
                            setboard(X,Y - 1,'B');

                            _table[X][Y - 2] ='F';
                            setboard(X,Y - 2,'B');

                            _table[X][Y + 1] = 'F';
                            setboard(X,Y + 1,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            setWAroundF(Y - 2, X, 4, "horizontal", _table);

                            fallShip = true;
                            return;
                        }

                        //absoultly have 4 spacce but should change direction
                        else if((_table[X][Y - 2] == 'E' || _table[X][Y - 2] == 'W') && _table[X][Y + 2] == 'S' && Y >= 2 && Y <= 7)
                        {
                            /// bad az || azafe shod check shavad
                            if(_table[X][Y - 2] == 'W' || _table[X][Y - 2] == 'E')
                            {
                                if(_table[X][Y + 1] == 'B')
                                {
                                    qDebug() << "dorost";

                                    if(_table[X][Y + 2] == 'S')
                                    {

                                        if(_table[X][Y - 2] == 'E')
                                        {

                                            _table[X][Y] = 'B';
                                            setboard(X,Y,'B');

                                            _table[X][Y - 1] = 'B';
                                            setboard(X,Y - 1,'B');

                                            _table[X][Y + 1] = 'B';
                                            setboard(X,Y + 1,'B');

                                            //_table[X][Y - 2] = 'W';
                                            setboard(X,Y - 2,'W');


                                            fallShip = false;
                                            moveMentBot = false;
                                            moveMentPerson = true;
                                            exactDirection = "Right";
                                            return;
                                        }

                                        qDebug() << "dorost2";

                                        _table[X][Y] = 'F';
                                        setboard(X,Y,'B');

                                        _table[X][Y - 1] = 'F';
                                        setboard(X,Y - 1,'B');

                                        _table[X][Y + 1] = 'F';
                                        setboard(X,Y + 1,'B');


                                        _table[X][Y + 2] = 'F';
                                        setboard(X,Y + 2,'B');

                                        fallShip = true;
                                        setWAroundF(Y - 1, X, 4, "horizontal", _table);

                                        shootSuccses++;
                                        return;
                                    }

                                    else
                                    {
                                        _table[X][Y] = 'F';
                                        setboard(X,Y,'B');

                                        _table[X][Y - 1] = 'F';
                                        setboard(X,Y - 1,'B');

                                        _table[X][Y + 1] = 'F';
                                        setboard(X,Y + 1,'B');

                                        fallShip = true;
                                        setWAroundF(Y - 1, X, 3, "horizontal", _table);

                                        shootSuccses++;
                                        return;
                                    }

                                }

                                else
                                {
                                    _table[X][Y - 1] = 'F';
                                    setboard(X,Y - 1,'B');

                                    _table[X][Y] = 'F';
                                    setboard(X,Y,'B');

                                    fallShip = true;
                                    shootSuccses++;
                                    setWAroundF(Y - 1, X, 2, "horizontal", _table);

                                    return;
                                }
                            }

                            else
                            {
                                moveMentBot = false;
                                _table[X][Y - 1] = 'B';
                                setboard(X,Y - 1,'B');

                                //_table[X][Y - 2] = 'W';
                                setboard(X,Y - 2,'W');

                                exactDirection = "Right";
                                fallShip = false;
                                shootSuccses++;

                                return;
                            }
                        }

                    }

                    //maby ship have 3 or 4 spaces and change direction
                    else if(((_table[X][Y - 1] != 'S' || _table[X][Y - 1] != 'B') && Y >= 1) || (Y == 0))
                    {
                        if(_table[X][Y - 1] == 'E')
                        {
                            moveMentBot = false;
                            setboard(X,Y - 1,'W');

                        }

                        if(Y >= 1)
                        {
                            //  _table[X][Y - 1] = 'W';
                        }
                        exactDirection = "Right";
                        fallShip = false;

                        return;
                    }
                }
            }
        }


        else if(Y == firstShot[0][1])
        {
            direction = "vertocal";

            if(X - firstShot[0][0] > 0)
            {
                lastDirec = "Down";
                if(exactDirection == "Down")
                {
                    if(X == 9)
                    {
                        if(_table[X - 2][Y] == 'B')
                        {
                            if(_table[X - 3][Y] == 'B')
                            {
                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                _table[X - 1][Y] = 'F';
                                setboard(X - 1,Y,'B');

                                _table[X - 2][Y] = 'F';
                                setboard(X - 2,Y,'B');

                                _table[X - 3][Y] = 'F';
                                setboard(X - 3,Y,'B');

                                fallShip = true;
                                setWAroundF(Y, X - 3, 4, "vertocal", _table);

                                return;
                            }

                            else
                            {
                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                _table[X - 1][Y] = 'F';
                                setboard(X - 1,Y,'B');

                                _table[X - 2][Y] = 'F';
                                setboard(X - 2,Y,'B');

                                fallShip = true;
                                setWAroundF(Y, X - 2, 3, "vertocal", _table);

                                return;
                            }
                        }

                        else
                        {
                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            _table[X - 1][Y] = 'F';
                            setboard(X - 1,Y,'B');

                            fallShip = true;
                            setWAroundF(Y, X - 1, 2, "vertocal", _table);

                            return;
                        }
                    }

                    //table 2 space fall
                    if((_table[X + 1][Y] != 'S' && _table[X - 2][Y] != 'B' && X <= 8 && X >= 2)
                        || (X == 1 && _table[X + 1][Y] != 'S') || (X == 9 && _table[X - 2][Y] != 'B'))
                    {
                        _table[X][Y] = 'F';
                        setboard(X,Y,'B');

                        _table[X - 1][Y] = 'F';
                        setboard(X - 1,Y,'B');

                        fallShip = true;
                        setWAroundF(Y, X - 1, 2, "vertocal", _table);

                        return;
                    }

                    //absoultly have 3 space maby 4 space
                    else if(_table[X + 1][Y] != 'S' && _table[X - 2][Y] == 'B' && X >= 2 && X <= 8)
                    {
                        //have 4 space
                        if(_table[X - 3][Y] == 'B' && X >= 3)
                        {
                            _table[X - 3][Y] = 'F';
                            setboard(X - 3,Y,'B');

                            _table[X - 2][Y] = 'F';
                            setboard(X - 2,Y,'B');

                            _table[X - 1][Y] = 'F';
                            setboard(X - 1,Y,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            fallShip = true;
                            setWAroundF(Y, X - 3, 4, "vertocal", _table);

                            return;
                        }

                        //have 3 space
                        else
                        {
                            _table[X - 2][Y] = 'F';
                            setboard(X - 2,Y,'B');

                            _table[X - 1][Y] = 'F';
                            setboard(X - 1,Y,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            fallShip = true;
                            setWAroundF(Y, X - 2, 3, "vertocal", _table);

                            return;
                        }

                    }

                    //absoultly have 3 space maby 4 space
                    else if(_table[X + 1][Y] == 'S' && X >= 1 && X <= 8)
                    {
                        _table[X + 1][Y] = 'B';
                        setboard(X + 1,Y,'B');

                        //have 3 space
                        if((_table[X + 2][Y] != 'S' && _table[X - 2][Y] != 'B' && X <= 8 && X >= 2) ||
                            (X == 1) && _table[X + 2][Y] != 'S')
                        {
                            _table[X + 1][Y] = 'F';
                            setboard(X + 1,Y,'B');

                            _table[X - 1][Y] = 'F';
                            setboard(X - 1,Y,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            fallShip = true;
                            setWAroundF(Y, X - 1, 3, "vertocal", _table);

                            return;
                        }

                        //havev 4 space
                        else if(_table[X + 2][Y] == 'S' && X <= 8)
                        {
                            _table[X + 2][Y] = 'F';
                            setboard(X + 2,Y,'B');

                            _table[X + 1][Y] = 'F';
                            setboard(X + 1,Y,'B');

                            _table[X - 1][Y] = 'F';
                            setboard(X - 1,Y,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            setWAroundF(Y, X - 1, 4, "vertocal", _table);

                            fallShip =  true;
                        }

                        else if(_table[X - 3][Y] == 'W' && _table[X - 2][Y] == 'B' && X >= 3)
                        {
                            _table[X - 2][Y] = 'F';
                            setboard(X - 2,Y,'B');

                            _table[X - 1][Y] = 'F';
                            setboard(X - 1,Y,'B');

                            _table[X + 1][Y] = 'F';
                            setboard(X + 1,Y,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            fallShip = true;
                            setWAroundF(Y, X - 2, 4, "vertocal", _table);

                            return;
                        }
                    }
                }

                else if(exactDirection == "Default")
                {
                    if(X == 9)
                    {
                        if(_table[X - 2][Y] == 'S')
                        {
                            if(_table[X - 3][Y] == 'S')
                            {
                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                _table[X - 1][Y] = 'F';
                                setboard(X - 1,Y,'B');

                                _table[X - 2][Y] = 'F';
                                setboard(X - 2,Y,'B');

                                _table[X - 3][Y] = 'F';
                                setboard(X - 3,Y,'B');

                                fallShip = true;
                                setWAroundF(Y, X - 3, 4, "vertocal", _table);

                                return;
                            }

                            else
                            {
                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                _table[X - 1][Y] = 'F';
                                setboard(X - 1,Y,'B');

                                _table[X - 2][Y] = 'F';
                                setboard(X - 2,Y,'B');

                                fallShip = true;
                                setWAroundF(Y, X - 2, 3, "vertocal", _table);

                                return;
                            }
                        }

                        else
                        {
                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            _table[X - 1][Y] = 'F';
                            setboard(X - 1,Y,'B');

                            fallShip = true;
                            setWAroundF(Y, X - 1, 2, "vertocal", _table);

                            return;
                        }
                    }

                    //check ship 2 space
                    if((_table[X + 1][Y] != 'S' && _table[X - 2][Y] != 'S' && X >= 2 && X <= 8)
                        || ((X == 1) && _table[X + 1][Y] != 'S')
                        ||((X == 9) && (_table[X - 2][Y] != 'B' || _table[X - 2][Y] != 'S')))
                    {
                        //ship had 2 spaces but now fall
                        _table[X][Y] = 'F';
                        setboard(X,Y,'B');

                        _table[X - 1][Y] = 'F';
                        setboard(X - 1,Y,'B');

                        fallShip = true;
                        setWAroundF(Y, X - 1, 2, "vertocal", _table);

                        //atack again random
                        return;
                    }

                    //absoultly have 3 space
                    else if((_table[X + 1][Y] == 'S' && _table[X + 2][Y] != 'S' && _table[X - 2][Y] != 'S' && X <= 7 && X >= 2)
                             || ((X == 8) && _table[X + 1][Y] == 'S' && _table[X - 2][Y] != 'S')
                             || (X == 1 && _table[X + 1][Y] == 'S' && _table[X + 1][Y] != 'S' ) )
                    {
                        _table[X + 1][Y] = 'F';
                        setboard(X + 1,Y,'B');

                        _table[X - 1][Y] = 'F';
                        setboard(X - 1,Y,'B');

                        _table[X][Y] = 'F';
                        setboard(X,Y,'B');

                        fallShip = true;
                        shootSuccses++;
                        setWAroundF(Y, X - 1, 3, "vertocal", _table);

                        return;
                    }

                    //maby ship have 3 or 4 spaces and change direction
                    else if(_table[X + 1][Y] != 'S' && X <= 8)
                    {
                        if(_table[X + 1][Y] == 'E')
                        {
                            moveMentBot = false;
                        }
                        //_table[X + 1][Y] = 'W';

                        setboard(X + 1,Y,'W');
                        exactDirection = "Up";
                        fallShip = false;

                        return;

                    }

                    //have 4 space
                    else if(_table[X + 1][Y] == 'S' && X <= 8)
                    {
                        //absoultly have 4 apace
                        if(_table[X + 2][Y] == 'S')
                        {
                            _table[X + 2][Y] ='F';
                            setboard(X + 2,Y,'B');

                            _table[X + 1][Y] = 'F';
                            setboard(X + 1,Y,'B');

                            _table[X - 1][Y] = 'F';
                            setboard(X - 1,Y,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            fallShip = true;
                            setWAroundF(Y, X - 1, 4, "vertocal", _table);

                            return;
                        }

                        //absoultly have 4 spacce but should change direction
                        else if(_table[X + 2][Y] != 'S' && _table[X - 2][Y] == 'S')
                        {
                            if(_table[X + 2][Y] == 'E')
                            {
                                moveMentBot = false;
                                setboard(X + 2,Y,'W');

                            }
                            _table[X + 1][Y] = 'B';
                            setboard(X + 1,Y,'B');

                            //_table[X + 2][Y] = 'W';

                            exactDirection = "Up";

                            fallShip = false;
                            shootSuccses++;

                            return;
                        }
                    }
                }
            }

            else if(X - firstShot[0][0] < 0)
            {
                lastDirec = "Up";
                if(exactDirection == "Up")
                {
                    if(X == 0)
                    {
                        if(_table[X + 2][Y] == 'B')
                        {
                            if(_table[X + 3][Y] == 'B')
                            {
                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                _table[X + 1][Y] = 'F';
                                setboard(X + 1,Y,'B');

                                _table[X + 2][Y] = 'F';
                                setboard(X + 2,Y,'B');

                                _table[X + 3][Y] = 'F';
                                setboard(X + 3,Y,'B');

                                fallShip = true;
                                setWAroundF(Y, X, 4, "vertocal", _table);

                                return;
                            }

                            else
                            {
                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                _table[X + 1][Y] = 'F';
                                setboard(X + 1,Y,'B');

                                _table[X + 2][Y] = 'F';
                                setboard(X + 2,Y,'B');

                                fallShip = true;
                                setWAroundF(Y, X, 3, "vertocal", _table);

                                return;
                            }
                        }

                        else
                        {
                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            _table[X + 1][Y] = 'F';
                            setboard(X + 1,Y,'B');

                            fallShip = true;
                            setWAroundF(Y, X, 2, "vertocal", _table);

                            return;
                        }
                    }

                    //table 2 space fall
                    if(_table[X - 1][Y] != 'S' && _table[X + 2][Y] != 'B' && X >= 1 && X <= 7
                        ||(X == 8 && _table[X - 1][Y] != 'S'))
                    {
                        _table[X][Y] = 'F';
                        setboard(X,Y,'B');

                        _table[X + 1][Y] = 'F';
                        setboard(X + 1,Y,'B');

                        fallShip = true;
                        setWAroundF(Y, X, 2, "vertocal", _table);

                        return;
                    }

                    //absoultly have 3 space maby 4 space
                    else if(_table[X - 1][Y] != 'S' && _table[X + 2][Y] == 'B' && X >= 1 && X <= 7)
                    {
                        //have 4 space
                        if(_table[X + 3][Y] == 'B' && X <= 6)
                        {
                            _table[X + 3][Y] = 'F';
                            setboard(X + 3,Y,'B');

                            _table[X + 2][Y] = 'F';
                            setboard(X + 2,Y,'B');

                            _table[X + 1][Y] = 'F';
                            setboard(X + 1,Y,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            setWAroundF(Y, X, 4, "vertocal", _table);
                            fallShip = true;

                            return;
                        }

                        //have 3 space
                        else if(_table[X + 2][Y] == 'B' && X <= 7)
                        {
                            _table[X + 2][Y] = 'F';
                            setboard(X + 2,Y,'B');

                            _table[X + 1][Y] = 'F';
                            setboard(X + 1,Y,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            setWAroundF(Y, X, 3, "vertocal", _table);

                            fallShip = true;
                        }

                    }

                    //absoultly have 3 space maby 4 space
                    else if(_table[X - 1][Y] == 'S' && X >= 1)
                    {
                        _table[X - 1][Y] = 'B';
                        setboard(X - 1,Y,'B');

                        //have 3 space
                        if(_table[X - 2][Y] != 'S' && _table[X + 2][Y] != 'B')
                        {
                            _table[X - 1][Y] = 'F';
                            setboard(X - 1,Y,'B');

                            _table[X + 1][Y] = 'F';
                            setboard(X + 1,Y,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            setWAroundF(Y, X - 1, 3, "vertocal", _table);

                            fallShip = true;
                            return;
                        }

                        //havev 4 space
                        else if(_table[X - 2][Y] == 'S')
                        {
                            _table[X - 2][Y] = 'F';
                            setboard(X - 2,Y,'B');

                            _table[X - 1][Y] = 'F';
                            setboard(X - 1,Y,'B');

                            _table[X + 1][Y] = 'F';
                            setboard(X + 1,Y,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            setWAroundF(Y, X - 2, 4, "vertocal", _table);

                            fallShip =  true;
                            return;
                        }

                        else if(_table[X + 3][Y] == 'W')
                        {
                            _table[X + 2][Y] = 'F';
                            setboard(X + 2,Y,'B');

                            _table[X + 1][Y] = 'F';
                            setboard(X + 1,Y,'B');

                            _table[X - 1][Y] = 'F';
                            setboard(X - 1,Y,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            fallShip = true;
                            setWAroundF(Y, X - 1, 4, "vertocal", _table);

                            return;
                        }
                    }

                }

                else if(exactDirection == "Default")
                {
                    if(X == 0)
                    {
                        if(_table[X + 2][Y] == 'B')
                        {
                            if(_table[X + 3][Y] == 'B')
                            {
                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                _table[X + 1][Y] = 'F';
                                setboard(X + 1,Y,'B');

                                _table[X + 2][Y] = 'F';
                                setboard(X + 2,Y,'B');

                                _table[X + 3][Y] = 'F';
                                setboard(X + 3,Y,'B');

                                fallShip = true;
                                setWAroundF(Y, X , 4, "vertocal", _table);

                                return;
                            }

                            else
                            {
                                _table[X][Y] = 'F';
                                setboard(X,Y,'B');

                                _table[X + 1][Y] = 'F';
                                setboard(X + 1,Y,'B');

                                _table[X + 2][Y] = 'F';
                                setboard(X + 2,Y,'B');

                                fallShip = true;
                                setWAroundF(Y, X, 3, "vertocal", _table);

                                return;
                            }
                        }

                        else
                        {
                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            _table[X + 1][Y] = 'F';
                            setboard(X + 1,Y,'B');

                            fallShip = true;
                            setWAroundF(Y, X, 2, "vertocal", _table);

                            return;
                        }
                    }

                    //check ship 2 space
                    if(_table[X - 1][Y] != 'S' && _table[X + 2][Y] != 'S'  && X >= 1 && X <= 7)
                    {
                        //ship had 2 spaces but now fall
                        _table[X][Y] = 'F';
                        setboard(X,Y,'B');

                        _table[X + 1][Y] = 'F';
                        setboard(X + 1,Y,'B');

                        fallShip = true;
                        setWAroundF(Y, X, 2, "vertocal", _table);

                        //atack again random
                        return;
                    }

                    //absoultly have 3 space
                    else if(_table[X - 1][Y] == 'S' && _table[X - 2][Y] != 'S' && _table[X + 2][Y] != 'S' && X >= 2 && X <= 7)
                    {
                        _table[X - 1][Y] = 'F';
                        setboard(X - 1,Y,'B');

                        _table[X + 1][Y] = 'F';
                        setboard(X + 1,Y,'B');

                        _table[X][Y] = 'F';
                        setboard(X,Y,'B');

                        fallShip = true;
                        shootSuccses++;
                        setWAroundF(Y, X - 1, 3, "vertocal", _table);

                        return;
                    }

                    //maby ship have 3 or 4 spaces and change direction
                    else if(_table[X - 1][Y] != 'S' && X >= 1)
                    {
                        if(_table[X - 1][Y] == 'E')
                        {
                            moveMentBot = false;
                            setboard(X - 1,Y,'W');

                        }

                        //_table[X - 1][Y] = 'W';
                        exactDirection = "Down";
                        fallShip = false;

                        return;
                    }

                    //have 4 space
                    else if(_table[X - 1][Y] == 'S' && X >= 1)
                    {
                        //absoultly have 4 apace
                        if(_table[X - 2][Y] == 'S' && X >= 2)
                        {
                            _table[X - 2][Y] ='F';
                            setboard(X - 2,Y,'B');

                            _table[X - 1][Y] = 'F';
                            setboard(X - 1,Y,'B');

                            _table[X + 1][Y] = 'F';
                            setboard(X + 1,Y,'B');

                            _table[X][Y] = 'F';
                            setboard(X,Y,'B');

                            fallShip = true;
                            setWAroundF(Y, X - 2, 4, "vertocal", _table);

                            return;
                        }

                        //absoultly have 4 spacce but should change direction
                        else if(_table[X - 2][Y] != 'S'&& _table[X + 2][Y] == 'S' && X >= 2 && X <= 7)
                        {
                            if(_table[X - 2][Y] == 'E')
                            {
                                moveMentBot = false;
                                setboard(X - 2,Y,'W');
                            }

                            //_table[X - 1][Y] = 'B';
                            setboard(X - 1,Y,'B');

                            //_table[X- 2][Y] = 'W';
                            exactDirection = "Down";
                            fallShip = false;
                            shootSuccses++;

                            return;
                        }
                    }
                }
            }
        }

    }

    else if(_table[X][Y] == 'E')
    {
        moveMentBot = false;
        moveMentPerson = true;

        //_table[X][Y] = 'W';
        setboard(X,Y,'W');

        if(X == firstShot[0][0] && Y - firstShot[0][1] > 0)
        {
            lastDirec = "Right";

            if(Y == 1)
            {
                if(_table[X - 1][0] == 'W')
                {
                    exactDirection = "Down";
                }

                else
                {
                    exactDirection = "Up";
                }

                return;
            }

            if(X == 0)
            {
                if(Y == 1)
                {
                    exactDirection = "Down";
                    return;
                }

                else if(_table[X][Y - 2] == 'W')
                {
                    exactDirection = "Down";
                }

                else
                {
                    exactDirection = "Left";
                }

                return;
            }

            else if(X == 9)
            {
                if(Y == 1)
                {
                    exactDirection = "Up";
                    return;
                }

                if(_table[X][Y - 2] == 'W')
                {
                    exactDirection = "Up";
                }

                else
                {
                    exactDirection = "Left";
                    return;
                }

                return;
            }

            if(_table[X][Y - 2] == 'W')
            {
                if(_table[X - 1][Y - 1] == 'W')
                {
                    if(_table[X + 1][Y - 1] != 'W')
                    {
                        exactDirection = "Down";
                    }
                }

                else
                {
                    exactDirection = "Up";
                }

                return;
            }

            else
            {
                exactDirection = "Left";
            }

            return;
        }


        else if(X == firstShot[0][0] && Y - firstShot[0][1] < 0)
        {
            lastDirec = "Left";

            if(X == 0)
            {
                if(Y == 8)
                {
                    exactDirection = "Down";
                    return;
                }

                if(_table[X][Y + 2] == 'W')
                {
                    exactDirection = "Down";
                    return;

                }

                else
                {
                    exactDirection = "Right";
                    return;

                }

                return;
            }

            else if(X == 9)
            {
                if(Y == 8)
                {
                    exactDirection = "Up";
                }

                if(_table[X][Y + 2] == 'W')
                {
                    exactDirection = "Up";
                }

                else
                {
                    exactDirection = "Right";
                }

                return;
            }

            if(Y == 8)
            {
                if(_table[X - 1][Y + 1] == 'W')
                {
                    exactDirection = "Down";
                }
                else
                {
                    exactDirection = "Up";
                }
                return;
            }



            if(_table[X][Y + 2] == 'W' && Y <= 7)
            {
                if(_table[X - 1][Y + 1] == 'W')
                {
                    exactDirection = "Down";
                }

                else
                {
                    exactDirection = "Up";
                }
            }

            else
            {
                exactDirection = "Right";
            }
            return;
        }


        else if(Y == firstShot[0][1] && X - firstShot[0][0] > 0)
        {
            lastDirec = "Down";

            if(Y == 0)
            {
                if(X == 1)
                {
                    exactDirection = "Right";
                }

                if(_table[X - 2][Y] == 'W')
                {
                    exactDirection = "Right";
                }

                else
                {
                    exactDirection = "Up";
                }

                return;
            }


            else if(Y == 9)
            {
                if(X == 1)
                {
                    exactDirection = "Left";
                }

                if(_table[X - 2][Y] == 'W')
                {
                    exactDirection = "Left";
                }

                else
                {
                    exactDirection = "Up";
                }

                return;
            }


            if(_table[X - 2][Y] == 'W')
            {
                if(_table[X - 1][Y - 1] == 'W')
                {
                    exactDirection = "Right";
                }

                else
                {
                    exactDirection = "Left";
                }
            }

            else
            {
                exactDirection = "Up";
            }

            return;
        }

        else if(Y == firstShot[0][1] && X - firstShot[0][0] < 0)
        {
            lastDirec = "Up";

            if(X == 8)
            {
                if(_table[X + 1][Y - 1] == 'W')
                {
                    exactDirection = "Right";
                }
                else
                {
                    exactDirection = "Left";
                }
                return;
            }

            if(Y == 0)
            {
                if(X == 0)
                {
                    exactDirection = "Right";
                }

                if(_table[X + 1][Y + 1] == 'W')
                {
                    exactDirection = "Down";
                }

                else
                {
                    exactDirection = "Right";
                }
                return;
            }

            else if(Y == 9)
            {

                if(X == 8)
                {

                    exactDirection = "Left";
                }

                if(_table[X + 1][Y - 1] == 'W')
                {
                    exactDirection = "Down";
                }

                else
                {
                    exactDirection = "Left";
                }

                return;
            }


            if(_table[X + 2][Y] == 'W')
            {
                if(_table[X + 1][Y + 1] == 'W')
                {
                    exactDirection = "Left";
                }

                else
                {
                    exactDirection= "Right";
                }
                return;
            }

            else
            {
                exactDirection = "Down";
                return;
            }

        }

        return ;

    }

    else if(_table[X][Y] == 'F')
    {

    }

    else
    {

    }
}

void GamePage::choseDirection(QChar _table[10][10], int& randX, int& randY)
{

    qDebug() << "saaaalaaaam chose direc";
    int n;
    int m;
    while (CountShotSuucsesBot < 10) {
        if (!moveMentBot) {
            moveMentPerson = true;
            return;
        }

        if (!fallShip && shootSuccses != 0 && exactDirection != "Default")
        {
            if (exactDirection == "Left")
            {
                if(lastDirec != "Right") exactDirection = "Default";

                attackAgain(_table, randX, randY - 1);
            }
            else if (exactDirection == "Right")
            {
                if(lastDirec != "Left") exactDirection = "Default";

                attackAgain(_table, randX, randY + 1);
            }
            else if (exactDirection == "Up")
            {
                if(lastDirec != "Down") exactDirection = "Default";

                attackAgain(_table, randX - 1, randY);
            }
            else if (exactDirection == "Down")
            {
                if(lastDirec != "Up") exactDirection = "Default";

                attackAgain(_table, randX + 1, randY);
            }
            else
            {
                qDebug() << "saaaalaaaam12";

                exactDirection = "Default";
            }
        }
        else if (fallShip) {
            shootSuccses = 0;
            fallShip = false;
            exactDirection = "Default";
            return;
        }
        else {

            do{

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> distrx(-1, 1);
                std::uniform_int_distribution<> distry(-1, 1);

                int m = distrx(gen);
                int n = distry(gen);

                ///m = QRandomGenerator::global()->bounded(-1,1);
                ///n = QRandomGenerator::global()->bounded(-1,1);

                botx = randX +  m;
                boty = randY + n;


                qDebug() << botx << boty;


            } while (abs(botx - randX) == abs(boty - randY));

            if(botx < 0 || botx >= 10 || boty < 0 || boty >= 10)
            {
                botx = 0;
                boty = 0;
                continue;
            }

            if(_table[randX][randY - 1] == 'W' &&
                _table[randX][randY + 1] == 'W')
            {
                if(randX == 0)
                {
                    botx = randX + 1;
                    boty = randY;
                }
                else if(_table[randX - 1][randY] != 'W')
                {
                    botx = randX - 1;
                    boty = randY;
                }
                else
                {
                    botx = randX + 1;
                    boty = randY;
                }
            }

            else if(_table[randX - 1][randY] == 'W' &&
                     _table[randX + 1][randY] == 'W')
            {
                if(randY == 9)
                {
                    boty = randY - 1;
                    botx = randX;
                }
                else if(_table[randX][randY + 1] != 'W')
                {
                    boty = randY + 1;
                    botx = randX;
                }
                else
                {
                    boty = randY - 1;
                    botx = randX;
                }
            }


            if (_table[botx][boty] == 'W' || _table[botx][boty] == 'F') {
                continue;
            }

            attackAgain(_table, botx, boty);
        }

        if (!moveMentBot) {
            moveMentPerson = true;
            return;
        }

        if (fallShip) {
            shootSuccses = 0;
            fallShip = false;
            exactDirection = "Default";
            return;
        }
    }

    if(CountShotSuucsesBot == 10)
    {
        qDebug() << "bot win";
    }
}

bool GamePage::checkSpecislIndex(int x, int y, QChar _table[10][10], int a)
{
    if(x == 0 && y == 0)
    {
        if(_table[0][1] != 'S' && _table[1][0] != 'S')
        {
            if (a == 0)
            {
                gamepage->setShipOfBot(y, x, "1");
            }

            _table[0][0] = 'F';
            setboard(0,0,'B');

            //_table[0][1] = 'W';
            setboard(0,1,'W');

            //_table[1][0] = 'W';
            setboard(1,0,'W');

            //_table[1][1] = 'W';
            setboard(1,1,'W');

            return true;
        }
    }

    else if(x == 0 && y == 9)
    {
        if(_table[0][8] != 'S' && _table[1][9] != 'S')
        {
            if (a == 0)
            {
                gamepage->setShipOfBot(y, x, "1");
            }

            _table[0][9] = 'F';
            setboard(0,9,'B');

            //_table[0][8] = 'W';
            setboard(0,8,'W');

            //_table[1][9] = 'W';
            setboard(1,9,'W');

            //_table[1][8] = 'W';
            setboard(1,8,'W');

            return true;
        }
    }

    else if(x == 9 && y == 0)
    {
        if(_table[8][0] != 'S' && _table[9][1] != 'S')
        {
            if (a == 0)
            {
                gamepage->setShipOfBot(y, x, "1");
            }

            _table[9][0] = 'F';
            setboard(9,0,'B');

            _table[9][1] = 'W';
            setboard(9,1,'W');

            _table[8][1] = 'W';
            setboard(8,1,'W');

            _table[8][0] = 'W';
            setboard(8,0,'W');

            return true;
        }
    }

    else if(x == 9 && y == 9)
    {
        if(_table[9][8] != 'S' && _table[8][9] != 'S')
        {
            if (a == 0)
            {
                gamepage->setShipOfBot(y, x, "1");
            }

            _table[9][9] = 'F';
            setboard(9,9,'B');

            _table[9][8] = 'W';
            setboard(9,8,'W');

            _table[8][9] = 'W';
            setboard(8,9,'W');

            _table[8][8] = 'W';
            setboard(8,8,'W');

            return true;
        }
    }

    return false;
}

bool GamePage::isSurroundedByEmptySpaces(int x, int y, QChar table[10][10])
{

    if(x >= 1 && x <= 8 && y >= 1 && y <= 8 && table[x][y + 1] != 'S' && table[x][y - 1] != 'S' && table[x + 1][y] != 'S' && table[x - 1][y] != 'S')
    {
        qDebug() << table[x-1][y];
        return true;
    }

    else if(table[x][y + 1] != 'S' && table[x][y - 1] != 'S' && table[x - 1][y] != 'S' && (x == 9 && y > 0 && y < 9))
    {    qDebug() << "2";
        return true;
    }
    else if(table[x][y + 1] != 'S' && table[x][y - 1] != 'S' && table[x + 1][y] != 'S' && (x == 0 && y > 0 && y < 9))
    {    qDebug() << "3";
        return true;
    }
    else if(table[x + 1][y] != 'S' && table[x - 1][y] != 'S' && table[x][y + 1] != 'S' && (y == 0 && x > 0 && x < 9))
    {    qDebug() << "4";
        return true;
    }

    else if(table[x + 1][y] != 'S' && table[x - 1][y] != 'S' && table[x][y - 1] != 'S' && (y == 9 && x > 0 && x < 9))
        return true;

    else
        return false;
}

bool GamePage::isShipOneSpace(int x, int y, QChar table[10][10], int a)
{
    qDebug() << "salam";
    int s = 0;

    for(int i = x - 1; i <= x + 1; i++)
    {
        if((table[i][y] == 'B' || table[i][y] == 'S') && (i <= 9 && i >= 0))
        {
            s++;
            qDebug() << i << y;
        }
    }

    int t = 0;
    for(int j = y - 1; j <= y + 1; j++)
    {
        if(table[x][j] == 'B' || table[x][j] == 'S' && (j <= 9 && j >= 0))
        {
            t++;
        }
    }
    qDebug() << "s:" << s << "t:" << t;

    if(s > 1 || t > 1) return false;

    gamepage->setShipOfBot(y, x, "1");
    return true;

}

void GamePage::simpleAttack(QChar _table[10][10])
{
    qDebug()<<"aaaaaaaaaa";
    int i = 0;
    int numberx;
    int numbery;

    while (CountShotSuucsesBot < 10)
    {
        numberx = 0;
        numbery = 0;
        qDebug() << numberx << numbery;


        if (!moveMentBot)
        {
            qDebug()<<"bbbbbbbbb";

            return;
        }
        if(exactDirection != "Default")
        {
            qDebug()<<"cccccccc";

            qDebug() << "exactdirection Not Be Default";

            choseDirection(_table, randX, randY);
        }
        if (!moveMentBot)
        {
            qDebug()<<"ddddddddd";

            return;
        }


        numberx = QRandomGenerator::global()->bounded(0,10);
        numbery = QRandomGenerator::global()->bounded(0,10);

        randX = numberx;
        randY = numbery;


        qDebug() << randX << randY;


        if (_table[randX][randY] == 'S')
        {
            qDebug() << randX << randY << "shot";
            setboard(randX, randY, 'B');

            if (checkSpecislIndex(randX, randY, _table, 1))
            {
                CountShotSuucsesBot++;
                fallShip = true;
                continue;
            }

            firstShot[0][0] = randX;
            firstShot[0][1] = randY;

            fallShip = false;

            _table[randX][randY] = 'B';
            shootSuccses++;

            // Check if the ship is surrounded by empty spaces
            if(isSurroundedByEmptySpaces(randX, randY, _table))
            {
                qDebug() << "fall 1 ship";
                _table[randX][randY] = 'F';
                fallShip = true;
                setWAroundF(randY, randX, 1, "horizontal", _table);
                continue;
            }

            else
            {
                choseDirection(_table, randX, randY);
            }

            numberOfShook++;
            if(CountShotSuucsesBot == 10)
            {
                qDebug() << "win";
            }
        }

        else if (_table[randX][randY] == 'E')
        {
            //_table[randX][randY] = 'W';

            setboard(randX, randY, 'W');

            moveMentBot = false;
            moveMentPerson = true;
        }

        else if (_table[randX][randY] == 'W' || _table[randX][randY] == 'F')
        {
            i++;
            if(i == 1)
            {
                numberx = 0;
                numbery = 0;
                randX = 0;
                randY = 0;
                i = 0;
            }
            continue;
        }
    }
    if(CountShotSuucsesBot >= 10)
        qDebug() << "bot win";
}

void GamePage::printMouseClick(const QPoint &pos)
{


    int column = (pos.x() - 865) / 47;
    int row = (pos.y() - 190) / 47;

    int xPos=865 + column * 47;
    int yPos=190 + row * 47;

    if(bottable[row][column] == 'W' || bottable[row][column] == 'F'|| bottable[row][column] == 'B')
    {

    }

    else
    {
        if (bottable[row][column] == 'S')
        {
            if (fallShipOfBot)
            {
                shotFritInShip++;
            }

            if(shotFritInShip == 1)
            {
                if(fallShipOfBot)
                {
                    firstShotOfPlayer[0][0] = row;
                    firstShotOfPlayer[0][1] = column;
                    fallShipOfBot = false;
                }

                else
                {
                    ///direction horizontal
                    if(firstShotOfPlayer[0][0] == row) exactDirectionOfPlayer = "horizontal";

                    ///direction vertical
                    else if(firstShotOfPlayer[0][1] == column) exactDirectionOfPlayer = "vertical";
                }
            }

            QLabel *b = new QLabel(this);
            QPixmap pix("F:/botMode/test_mark_cross.png");
            b->setPixmap(pix);
            b->setScaledContents(true);
            b->setGeometry(xPos, yPos, 48, 48);
            b->raise();
            b->show();

            bottable[row][column] = 'B';


            ///check ship 1 space
            if(gamepage->checkSpecislIndex(row, column, bottable, 0))
            {
                qDebug() << "checkSpecislIndex";
                fallShipOfBot = true;
                CountShotSuucsesPlayer++;
                shotFritInShip = 0;
                exactDirectionOfPlayer = "Default";
                firstShotOfPlayer[0][0] = -1;
                firstShotOfPlayer[0][1] = -1;
            }

            ///check ship 1 space
            else if(gamepage->isShipOneSpace(row, column, bottable, 0))
            {
                qDebug() << "isShipOneSpace";
                fallShipOfBot = true;
                CountShotSuucsesPlayer++;
                shotFritInShip = 0;
                exactDirectionOfPlayer = "Default";
                firstShotOfPlayer[0][0] = -1;
                firstShotOfPlayer[0][1] = -1;
            }

            ///check ship 4 space
            else if(CheckShip4XBot(bottable, row, column, exactDirectionOfPlayer))
            {
                qDebug() << "CheckShip4Bot";
                fallShipOfBot = true;
                CountShotSuucsesPlayer++;
                shotFritInShip = 0;
                exactDirectionOfPlayer = "Default";
                firstShotOfPlayer[0][0] = -1;
                firstShotOfPlayer[0][1] = -1;
            }

            ///check ship 3 space
            else if(CheckShip3XBot(bottable, row, column, exactDirectionOfPlayer))
            {
                qDebug() << "CheckShip3Bot";
                fallShipOfBot = true;
                CountShotSuucsesPlayer++;
                shotFritInShip = 0;
                exactDirectionOfPlayer = "Default";
                firstShotOfPlayer[0][0] = -1;
                firstShotOfPlayer[0][1] = -1;
            }

            ///check ship 2 space
            else if(CheckShip2XBot(bottable, row, column, exactDirectionOfPlayer))
            {
                qDebug() << "CheckShip2Bot";
                fallShipOfBot = true;
                CountShotSuucsesPlayer++;
                shotFritInShip = 0;
                exactDirectionOfPlayer = "Default";
                firstShotOfPlayer[0][0] = -1;
                firstShotOfPlayer[0][1] = -1;
            }

            qDebug() <<  " count " << "  " << CountShotSuucsesPlayer << firstShotOfPlayer[0][0] << firstShotOfPlayer[0][1] << exactDirectionOfPlayer;

            if(CountShotSuucsesPlayer == 10)
            {
                qDebug() << "person win";
            }
        }

        else if (bottable[row][column] == 'E')
        {
            QLabel *b = new QLabel(this);
            QPixmap pix("F:/botMode/missed missile.png");
            b->setPixmap(pix);
            b->setScaledContents(true);
            b->setGeometry(xPos + 4, yPos + 4, 40, 40);
            b->raise();
            b->show();

            moveMentPerson = false;
            moveMentBot = true;

            bottable[row][column] = 'W'; // Corrected

            ///play bot
            simpleAttack(table);
            qDebug() << "ssssssssssssssssssssss";
            moveMentPerson = true;
            moveMentBot = false;
            if(CountShotSuucsesBot == 10)
            {
                qDebug() << "bot win";
            }
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    gamepage = new GamePage;

    gamepage->setGeometry(0,0,1536,864);
    gamepage->show();

    return a.exec();
}

#include <main.moc>
