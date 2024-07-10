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


bool moveMentPerson = true;
bool moveMentBot = false;
int sizecord = 0;


void readFromFilebot(QChar bottable[10][10])
{
    QFile file("botfile.txt");
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
            bottable[row][col] = static_cast<char>(line.at(col).toLatin1());
        }

        for (; col < 10; col++)
        {
            bottable[row][col] = 'E';
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


        readFromFilebot(bottable);

        parseCoordinatesFromFile(ships, currentShip);

    }

    void mousePressEvent(QMouseEvent *event) override
    {
        printMouseClick(event->pos());
    }

    void printMouseClick(const QPoint &pos);



private:

    QVBoxLayout *layout;

};

void GamePage::printMouseClick(const QPoint &pos)
{
    if(moveMentPerson == false)
    {
        return;
    }
    else
    {
        qDebug() << "afgsfhbndg";
    }
    if(countPersonSucsses == 10)
    {
        ///win
    }


    int column = (pos.x() - 865) / 47;
    int row = (pos.y() - 190) / 47;

    int xPos=865 - 3 + column * 47;
    int yPos=190 - 2 + row * 47;



    if(bottable[row][column] == 'W' || bottable[row][column] == 'F'||bottable[row][column] == 'B')
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

            //acsses to play

            QLabel *b = new QLabel(this);
            QPixmap pix("F:/botMode/missed missile.png");
            b->setPixmap(pix);
            b->setScaledContents(true);
            b->setGeometry(xPos + 4, yPos + 4, 40, 40);
            b->raise();
            b->show();
            qDebug() << "asfasd";

            moveMentPerson = false;
            moveMentBot = true;

            bottable[row][column] = 'W'; // Corrected
        }
    }
}




int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    GamePage gamePage;
    gamePage.setGeometry(0,0,1536,864);
    gamePage.show();

    return a.exec();
}

#include "main.moc"
