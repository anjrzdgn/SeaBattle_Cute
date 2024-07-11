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
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFrame>
#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QVector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <QCoreApplication>
#include <sstream>
#include <vector>
#include <utility>
#include <QtCore/QRandomGenerator>

bool moveMentPerson = true;
bool moveMentBot = false;
int sizecord = 0;
int countshipperson;
int shootSuccses = 0;
bool fallShip = false;
int firstShot[1][2];
int count = 0;
int numberOfShook;
QString direction;
QString exactDirection = "Default";
QString lastDirec;


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
}

void parseCoordinatesFromFile(std::vector<std::vector<std::pair<int, int>>>& ships, std::vector<std::pair<int, int>>& currentShip) {
    QFile file("fuckkkk.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    QTextStream in(&file);
    QString line;

    while (!in.atEnd()) {
        line = in.readLine();
        if (line.isEmpty()) {
            ships.push_back(currentShip);
            currentShip.clear();
        } else {
            std::stringstream ss(line.toStdString());
            int x, y;
            char comma;

            while (ss >> x >> comma >> y) {
                currentShip.push_back(std::make_pair(x, y));
            }
        }
    }

    if (!currentShip.empty()) {
        ships.push_back(currentShip);
    }

    file.close();
}


class GamePage : public QFrame {
    Q_OBJECT

public:
    QChar bottable[10][10];
    QChar table[10][10];

    int countPersonSucsses;
    int countBot;

    ///cord
    std::vector<std::vector<std::pair<int, int>>> ships;
    std::vector<std::pair<int, int>> currentShip;

    GamePage(QWidget *parent = nullptr) : QFrame(parent) {

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

        parseCoordinatesFromFile(ships, currentShip);

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

void setboard(int xp, int yp, QChar status)
{
    int yPos;
    int xPos;

    if(status == 'B')
    {
        xPos = xp * 48 + 200;
        yPos = yp * 48 + 190;

        QLabel *b = new QLabel(gamepage);
        QPixmap pix("F:/botMode/test_mark_cross.png");
        b->setPixmap(pix);
        b->setScaledContents(true);
        b->setGeometry(xPos, yPos, 48, 48);
        b->raise();
        b->show();
    }

    else if(status == 'W')
    {

    }

}

/// x , y left of ship
void setWAroundF(int y, int x, int size, QString direc, QChar table[10][10])
{

    if(direc == "horizontal")
    {
        if(y != 0 && y != 9)
        {
            table[x][y - 1] = 'W';
            table[x][y + size] = 'W';
        }

        else if(y == 0)
        {
            table[x][y + size] = 'W';
        }

        else if(y == 9)
        {
            table[x][y - 1] = 'W';
        }

        if(x != 0)
        {
            for(int i = y - 1; i <= y + size; i++)
            {
                table[x - 1][i] = 'W';
            }
        }

        if(x != 9)
        {
            for(int i = y - 1; i <= y + size; i++)
            {
                table[x + 1][i] = 'W';
            }
        }

    }

    else if(direc == "vertocal")
    {
        if(x != 0 && x != 9)
        {
            table[x - 1][y] = 'W';
            table[x + size][y] = 'W';
        }

        else if(x == 0)
        {
            table[x + size][y] = 'W';
        }

        else if(x == 9)
        {
            table[x - 1][y] = 'W';
        }

        if(y != 9)
        {
            for(int i = x - 1 ; i <= x + size; i++)
            {
                table[i][y + 1] = 'W';
            }

        }

        else if(y != 0)
        {
            for(int i = x - 1; i <= x + size; i++)
            {
                table[i][y - 1] = 'W';
            }
        }
    }

}

void attackAgain(QChar _table[10][10], int X, int Y)
{
    if(_table[X][Y] == 'S')
    {
        _table[X][Y] = 'B';
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
                        if(_table[X][Y - 2] == 'B')
                        {
                            if (_table[X][Y - 3] == 'B')
                            {
                                _table[X][Y] = 'F';
                                _table[X][Y - 1] = 'F';
                                _table[X][Y - 2] = 'F';
                                _table[X][Y - 3] = 'F';
                                setWAroundF(Y - 3,X ,4, "horizontal", _table);
                                fallShip = true;
                                return;
                            }

                            else
                            {
                                _table[X][Y] = 'F';
                                _table[X][Y - 1] = 'F';
                                _table[X][Y - 2] = 'F';
                                fallShip = true;
                                setWAroundF(Y - 2,X ,3, "horizontal", _table);
                                return;
                            }
                        }

                        else
                        {
                            _table[X][Y] = 'F';
                            _table[X][Y - 1] = 'F';
                            fallShip = true;
                            setWAroundF(Y - 1, X, 2, "horizontal", _table);
                            return;
                        }
                    }

                    //table 2 space fall
                    if((_table[X][Y + 1] != 'S' && (_table[X][Y - 2] != 'B')&& Y >= 2)
                        || (Y < 2 && _table[X][Y + 1] != 'S'))
                    {
                        _table[X][Y] = 'F';
                        _table[X][Y - 1] = 'F';

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
                            _table[X][Y - 2] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y - 3, X, 4, "horizontal", _table);
                            fallShip = true;
                        }

                        //have 3 space
                        else
                        {
                            _table[X][Y - 2] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y - 2, X, 3, "horizontal", _table);
                            fallShip = true;
                        }
                    }

                    //absoultly have 3 space maby 4 space
                    else if(_table[X][Y + 1] == 'S' && Y <= 8)
                    {
                        _table[X][Y + 1] = 'B';

                        if(_table[X][Y - 1] == 'B' && _table[X][Y - 2] == 'B')
                        {
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y - 2] = 'F';
                            fallShip = true;
                            setWAroundF(Y - 2, X, 4, "horizontal", _table);
                            return;
                        }

                        //have 3 space
                        if( (_table[X][Y + 2] != 'S' && _table[X][Y - 2] != 'B' && Y <= 7 && Y >= 2) ||
                            (Y == 1 && _table[X][Y + 2] != 'S'))
                        {
                            _table[X][Y + 1] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y - 1, X, 3, "horizontal", _table);
                            fallShip = true;
                        }

                        //havev 4 space
                        else if(_table[X][Y + 2] == 'S' && Y <= 7)
                        {
                            _table[X][Y + 2] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y - 1, X, 4, "horizontal", _table);
                            fallShip =  true;
                        }

                        else if(_table[X][Y - 3] == 'W' && Y >= 2)
                        {
                            _table[X][Y - 2] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
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
                                _table[X][Y - 1] = 'F';
                                _table[X][Y - 2] = 'F';
                                _table[X][Y - 3] = 'F';
                                fallShip = true;
                                setWAroundF(Y - 3, X, 4, "horizontal", _table);

                                return;
                            }

                            else
                            {
                                _table[X][Y] = 'F';
                                _table[X][Y - 1] = 'F';
                                _table[X][Y - 2] = 'F';
                                fallShip = true;
                                setWAroundF(Y - 2, X, 3, "horizontal", _table);

                                return;
                            }
                        }
                        else
                        {
                            _table[X][Y] = 'F';
                            _table[X][Y - 1] = 'F';
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
                        _table[X][Y - 1] = 'F';
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
                        _table[X][Y + 1] = 'F';
                        _table[X][Y - 1] = 'F';
                        _table[X][Y] = 'F';
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
                        _table[X][Y + 1] = 'W';
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
                        //absoultly have 4 apace
                        if(_table[X][Y + 2] == 'S' && Y <= 7)
                        {
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            _table[X][Y + 2] ='F';
                            _table[X][Y + 1] = 'F';
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
                            _table[X][Y + 2] = 'W';
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
                                _table[X][Y + 1] = 'F';
                                _table[X][Y + 2] = 'F';
                                _table[X][Y + 3] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X, 4, "horizontal", _table);

                                return;
                            }

                            else
                            {
                                _table[X][Y] = 'F';
                                _table[X][Y + 1] = 'F';
                                _table[X][Y + 2] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X, 3, "horizontal", _table);

                                return;
                            }
                        }

                        else
                        {
                            _table[X][Y] = 'F';
                            _table[X][Y + 1] = 'F';
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
                        _table[X][Y + 1] = 'F';
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
                            _table[X][Y + 2] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X, 4, "horizontal", _table);

                            return;
                        }

                        //have 3 space
                        else if(Y == 7 || (_table[X][Y + 3] != 'B' && Y <=6))
                        {
                            _table[X][Y + 2] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
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
                                _table[X][Y + 1] = 'F';
                                _table[X][Y + 2] = 'F';
                                _table[X][Y + 3] = 'F';
                                setWAroundF(Y, X, 4, "horizontal", _table);

                                return;
                            }

                            else if(_table[X][Y + 2] == 'B')
                            {
                                _table[X][Y] = 'F';
                                _table[X][Y + 1] = 'F';
                                _table[X][Y + 2] = 'F';
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
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y - 1, X, 3, "horizontal", _table);

                            fallShip = true;
                        }

                        //havev 4 space
                        else if(_table[X][Y - 2] == 'S' && Y >= 2)
                        {
                            _table[X][Y - 2] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y - 2, X, 4, "horizontal", _table);

                            fallShip =  true;
                        }

                        else if(_table[X][Y + 3] == 'W' && Y <= 6)
                        {
                            _table[X][Y + 2] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
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
                                _table[X][Y + 1] = 'F';
                                _table[X][Y + 2] = 'F';
                                _table[X][Y + 3] = 'F';
                                setWAroundF(Y, X, 4, "horizontal", _table);

                                fallShip = true;
                                return;
                            }

                            else if(_table[X][Y + 3] != 'S')
                            {
                                _table[X][Y] = 'F';
                                _table[X][Y + 1] = 'F';
                                _table[X][Y + 2] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X, 3, "horizontal", _table);

                                return;
                            }
                        }

                        else if(_table[X][Y + 2] != 'S')
                        {
                            _table[X][Y] = 'F';
                            _table[X][Y + 1] = 'F';
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
                        _table[X][Y + 1] = 'F';
                        fallShip = true;
                        setWAroundF(Y, X, 2, "horizontal", _table);

                        //atack again random
                        return;
                    }

                    //absoultly have 3 space
                    else if(_table[X][Y - 1] == 'S' &&  (_table[X][Y - 2] == 'E' || _table[X][Y - 2] == 'W') && (_table[X][Y + 2] == 'E' || _table[X][Y + 2] == 'W') && Y >= 2 && Y <= 7
                             || (Y == 1 && _table[X][Y - 1] == 'S' && (_table[X][Y + 2] == 'E' ||_table[X][Y + 2] == 'W')))
                    {
                        _table[X][Y - 1] = 'F';
                        _table[X][Y + 1] = 'F';
                        _table[X][Y] = 'F';
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
                            _table[X][Y - 2] ='F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y - 2, X, 4, "horizontal", _table);

                            fallShip = true;
                            return;
                        }

                        //absoultly have 4 spacce but should change direction
                        else if((_table[X][Y - 2] == 'E' || _table[X][Y - 2] == 'W') && _table[X][Y + 2] == 'S' && Y >= 2 && Y <= 7)
                        {
                            if(_table[X][Y - 2] == 'W')
                            {
                                if(_table[X][Y + 1] == 'S')
                                {
                                    if(_table[X][Y + 2] == 'S')
                                    {
                                        _table[X][Y] = 'F';
                                        _table[X][Y - 1] = 'F';
                                        _table[X][Y + 1] = 'F';
                                        _table[X][Y + 2] = 'F';
                                        fallShip = true;
                                        setWAroundF(Y - 1, X, 4, "horizontal", _table);

                                        shootSuccses++;
                                        return;
                                    }

                                    else
                                    {
                                        _table[X][Y] = 'F';
                                        _table[X][Y - 1] = 'F';
                                        _table[X][Y + 1] = 'F';
                                        fallShip = true;
                                        setWAroundF(Y - 1, X, 3, "horizontal", _table);

                                        shootSuccses++;
                                        return;
                                    }

                                }

                                else
                                {
                                    _table[X][Y - 1] = 'F';
                                    _table[X][Y] = 'F';
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
                                _table[X][Y - 2] = 'W';
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
                        }

                        if(Y >= 1)
                        {
                            _table[X][Y - 1] = 'W';
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
                                _table[X - 1][Y] = 'F';
                                _table[X - 2][Y] = 'F';
                                _table[X - 3][Y] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X - 3, 4, "vertocal", _table);

                                return;
                            }

                            else
                            {
                                _table[X][Y] = 'F';
                                _table[X - 1][Y] = 'F';
                                _table[X - 2][Y] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X - 2, 3, "vertocal", _table);

                                return;
                            }
                        }

                        else
                        {
                            _table[X][Y] = 'F';
                            _table[X - 1][Y] = 'F';
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
                        _table[X - 1][Y] = 'F';
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
                            _table[X - 2][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X - 3, 4, "vertocal", _table);

                            return;
                        }

                        //have 3 space
                        else
                        {
                            _table[X - 2][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X - 2, 3, "vertocal", _table);

                            return;
                        }

                    }

                    //absoultly have 3 space maby 4 space
                    else if(_table[X + 1][Y] == 'S' && X >= 1 && X <= 8)
                    {
                        _table[X + 1][Y] = 'B';

                        //have 3 space
                        if((_table[X + 2][Y] != 'S' && _table[X - 2][Y] != 'B' && X <= 8 && X >= 2) ||
                            (X == 1) && _table[X + 2][Y] != 'S')
                        {
                            _table[X + 1][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X - 1, 3, "vertocal", _table);

                            return;
                        }

                        //havev 4 space
                        else if(_table[X + 2][Y] == 'S' && X <= 8)
                        {
                            _table[X + 2][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y, X - 1, 4, "vertocal", _table);

                            fallShip =  true;
                        }

                        else if(_table[X - 3][Y] == 'W' && _table[X - 2][Y] == 'B' && X >= 3)
                        {
                            _table[X - 2][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
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
                                _table[X - 1][Y] = 'F';
                                _table[X - 2][Y] = 'F';
                                _table[X - 3][Y] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X - 3, 4, "vertocal", _table);

                                return;
                            }

                            else
                            {
                                _table[X][Y] = 'F';
                                _table[X - 1][Y] = 'F';
                                _table[X - 2][Y] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X - 2, 3, "vertocal", _table);

                                return;
                            }
                        }

                        else
                        {
                            _table[X][Y] = 'F';
                            _table[X - 1][Y] = 'F';
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
                        _table[X - 1][Y] = 'F';
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
                        _table[X - 1][Y] = 'F';
                        _table[X][Y] = 'F';
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
                        _table[X + 1][Y] = 'W';
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
                            _table[X + 1][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
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
                            }
                            _table[X + 1][Y] = 'B';
                            _table[X + 2][Y] = 'W';
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
                                _table[X + 1][Y] = 'F';
                                _table[X + 2][Y] = 'F';
                                _table[X + 3][Y] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X, 4, "vertocal", _table);

                                return;
                            }

                            else
                            {
                                _table[X][Y] = 'F';
                                _table[X + 1][Y] = 'F';
                                _table[X + 2][Y] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X, 3, "vertocal", _table);

                                return;
                            }
                        }

                        else
                        {
                            _table[X][Y] = 'F';
                            _table[X + 1][Y] = 'F';
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
                        _table[X + 1][Y] = 'F';
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
                            _table[X + 2][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y, X, 4, "vertocal", _table);
                            fallShip = true;

                            return;
                        }

                        //have 3 space
                        else if(_table[X + 2][Y] == 'B' && X <= 7)
                        {
                            _table[X + 2][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y, X, 3, "vertocal", _table);

                            fallShip = true;
                        }

                    }

                    //absoultly have 3 space maby 4 space
                    else if(_table[X - 1][Y] == 'S' && X >= 1)
                    {
                        _table[X - 1][Y] = 'B';

                        //have 3 space
                        if(_table[X - 2][Y] != 'S' && _table[X + 2][Y] != 'B')
                        {
                            _table[X - 1][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y, X - 1, 3, "vertocal", _table);

                            fallShip = true;
                            return;
                        }

                        //havev 4 space
                        else if(_table[X - 2][Y] == 'S')
                        {
                            _table[X - 2][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y, X - 2, 4, "vertocal", _table);

                            fallShip =  true;
                            return;
                        }

                        else if(_table[X + 3][Y] == 'W')
                        {
                            _table[X + 2][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
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
                                _table[X + 1][Y] = 'F';
                                _table[X + 2][Y] = 'F';
                                _table[X + 3][Y] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X , 4, "vertocal", _table);

                                return;
                            }

                            else
                            {
                                _table[X][Y] = 'F';
                                _table[X + 1][Y] = 'F';
                                _table[X + 2][Y] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X, 3, "vertocal", _table);

                                return;
                            }
                        }

                        else
                        {
                            _table[X][Y] = 'F';
                            _table[X + 1][Y] = 'F';
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
                        _table[X + 1][Y] = 'F';
                        fallShip = true;
                        setWAroundF(Y, X, 2, "vertocal", _table);

                        //atack again random
                        return;
                    }

                    //absoultly have 3 space
                    else if(_table[X - 1][Y] == 'S' && _table[X - 2][Y] != 'S' && _table[X + 2][Y] != 'S' && X >= 2 && X <= 7)
                    {
                        _table[X - 1][Y] = 'F';
                        _table[X + 1][Y] = 'F';
                        _table[X][Y] = 'F';
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
                        }

                        _table[X - 1][Y] = 'W';
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
                            _table[X - 1][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
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
                            }

                            _table[X - 1][Y] = 'B';
                            _table[X- 2][Y] = 'W';
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
        _table[X][Y] = 'W';



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

}

void choseDirection(QChar _table[10][10], int randX, int randY)
{

    int x = 0;
    int y = 0;
    int z = 0;

    while(count < 10)
    {
        if(moveMentBot == false)
        {
            ///return;
            continue;
        }


        if(fallShip == false && shootSuccses != 0 && exactDirection != "Default")
        {
            z = 1;
            if(exactDirection == "Left")
            {
                if(_table[randX][randY - 1] == 'W')
                {
                    exactDirection = "Default";
                    continue;
                }

                if(lastDirec == "Up" || lastDirec == "Down")
                {
                    exactDirection = "Default";
                }

                attackAgain(_table, randX,randY - 1);
            }

            else if(exactDirection == "Right")
            {
                if(_table[randX][randY + 1] == 'W')
                {
                    exactDirection = "Default";
                    continue;
                }


                if(lastDirec == "Up" || lastDirec == "Down")
                {
                    exactDirection = "Default";
                }
                attackAgain(_table, randX,randY + 1);
            }

            else if(exactDirection == "Up")
            {
                if(_table[randX - 1][randY] == 'W')
                {
                    exactDirection = "Default";
                    continue;
                }



                if(lastDirec == "Left" || lastDirec == "Right")
                {
                    exactDirection = "Default";
                }
                attackAgain(_table, randX - 1,randY);
            }

            else if(exactDirection == "Down")
            {

                if(_table[randX + 1][randY] == 'W')
                {
                    exactDirection = "Default";
                    continue;
                }

                if(lastDirec == "Left" || lastDirec == "Right")
                {
                    exactDirection = "Default";
                }
                attackAgain(_table, randX + 1, randY);
            }
        }

        if(fallShip == true)
        {
            shootSuccses = 0;
            fallShip = false;
            exactDirection = "Default";
            count++;
            return;
        }

        if(fallShip == false && z != 1)
        {

            do {

                x = QRandomGenerator::global()->bounded(-1, 1);
                y = QRandomGenerator::global()->bounded(-1, 1);
            } while (abs(x) == abs(y));

            x = x + randX;
            y = y + randY;

            if(_table[randX][randY - 1] == 'W'
                && _table[randX][randY + 1] == 'W')
            {
                if(randX == 0)
                {
                    x = randX + 1;
                }
                else if(_table[randX - 1][randY] != 'W')
                {
                    x = randX - 1;
                }
                else
                {
                    x = randX + 1;
                }
            }

            else if(_table[randX - 1][randY] == 'W' && _table[randX + 1][randY] == 'W')
            {
                if(randY == 9)
                {
                    y = randY - 1;
                }
                else if(_table[randX][randY + 1] != 'W')
                {
                    y = randY + 1;
                }
                else
                {
                    y = randY - 1;
                }
            }

            if(x < 0 || x > 9 || y < 0 || y > 9)
            {
                continue;
            }



            if(_table[x][y] == 'W' || _table[x][y] == 'F')
            {
                continue;
            }


            attackAgain(_table, x, y);
        }

        if(moveMentBot == false)
        {
            continue;
        }

        if(fallShip == true)
        {
            shootSuccses = 0;
            fallShip = false;
            exactDirection = "Default";
            count++;
            return;
        }
    }
}

bool checkSpecislIndex(int x, int y, QChar _table[10][10])
{
    if(x == 0 && y == 0)
    {
        if(_table[0][1] != 'S' && _table[1][0] != 'S')
        {
            _table[0][0] = 'F';
            _table[0][1] = 'W';
            _table[1][0] = 'W';
            _table[1][1] = 'W';
            return true;
        }
    }

    else if(x == 0 && y == 9)
    {
        if(_table[0][8] != 'S' && _table[1][9] != 'S')
        {
            _table[0][9] = 'F';
            _table[0][8] = 'F';
            _table[1][9] = 'F';
            _table[1][8] = 'F';
            return true;
        }
    }

    else if(x == 9 && y == 0)
    {
        if(_table[8][0] != 'S' && _table[9][1] != 'S')
        {
            _table[9][0] = 'F';
            _table[9][1] = 'F';
            _table[8][1] = 'F';
            _table[8][0] = 'F';

            return true;
        }
    }

    else if(x == 9 && y == 9)
    {
        if(_table[9][8] != 'S' && _table[8][9] != 'S')
        {
            _table[9][9] = 'F';
            _table[9][8] = 'F';
            _table[8][9] = 'F';
            _table[8][8] = 'F';
            return true;
        }
    }

    return false;
}

bool isSurroundedByEmptySpaces(int x, int y, QChar table[10][10])
{
    return (table[x][y + 1] != 'S' && table[x][y - 1] != 'S' &&
            table[x + 1][y] != 'S' && table[x - 1][y] != 'S' &&
            x >= 1 && x <= 8 && y >= 1 && y <= 8);
}

void simpleAttack(QChar _table[10][10])
{
    qDebug() << "salam" << _table[9][0] << "salam";

    int randX;
    int randY;

    while (countshipperson < 10)
    {
        if (!moveMentBot)
        {
            return;
        }
        if(exactDirection != "Default")
        {
            //choseDirection(_table, randX, randY);
        }
        if (!moveMentBot)
        {
            return;
        }
        randX = QRandomGenerator::global()->bounded(0, 9);
        randY = QRandomGenerator::global()->bounded(0, 9);

        qDebug() << randX << randY;

        if (_table[randX][randY] == 'S')
        {
            moveMentBot = true;
            if (checkSpecislIndex(randX, randY, _table))
            {
                countshipperson++;
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
                _table[randX][randY] = 'F';
                fallShip = true;
                countshipperson++;
                ///setWAroundF(randY, randX, 1, "horizontal", _table);
                continue;
            }
            else
            {
                setboard(randX, randY, 'B');
                ///choseDirection(_table, randX, randY);
            }

            numberOfShook++;
        }
        else if (_table[randX][randY] == 'E')
        {
            _table[randX][randY] = 'W';
            setboard(randX, randY, 'B');

            moveMentBot = false;
        }
        else if (_table[randX][randY] == 'W' || _table[randX][randY] == 'F')
        {
            continue;
        }
    }
}



void GamePage::printMouseClick(const QPoint &pos)
{

    if(countPersonSucsses == 10)
    {
        ///win
    }


    int column = (pos.x() - 865) / 47;
    int row = (pos.y() - 190) / 47;

    int xPos=865 - 3 + column * 47;
    int yPos=190 - 2 + row * 47;

    if(bottable[row][column] == 'W' || bottable[row][column] == 'F'|| bottable[row][column] == 'B')
    {

    }

    else
    {
        if (bottable[row][column] == 'S')
        {
            sizecord++;

            QLabel *b = new QLabel(this);
            QPixmap pix("F:/botMode/test_mark_cross.png");
            b->setPixmap(pix);
            b->setScaledContents(true);
            b->setGeometry(xPos, yPos, 48, 48);
            b->raise();
            b->show();

            bottable[row][column] = 'B';

            for (int i = 0; i < ships.size(); i++)
            {
                for (auto &coord : ships[i])
                {
                    if (bottable[coord.first][coord.second] == 'B')
                    {

                        qDebug() << sizecord;
                        sizecord++;

                        if (ships[i].size() == sizecord)
                        {

                            for (const auto &coord : ships[i])
                            {
                                qDebug() << coord.first << coord.second;

                                bottable[coord.first][coord.second] = 'F';
                                ///check h or v
                                /// size ship
                                /// find pixel
                                /// fix photo on this
                            }
                            sizecord = 0;
                        }
                        else
                        {
                            // sizecord = 0;
                        }
                    }
                    else
                    {
                        //sizecord = 0;

                    }
                }
            }
        }

        if (bottable[row][column] == 'E')
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
            ///
            qDebug() << table[0][0];
            simpleAttack(table);
            qDebug() << "asfasd";

        }
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    gamepage = new GamePage;

    // GamePage gamePage;

    gamepage->setGeometry(0,0,1536,864);

    gamepage->show();

    return a.exec();
}

#include "main.moc"
