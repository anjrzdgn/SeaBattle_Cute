#include "withfriend.h"
// #include "gamepage.h"
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QCoreApplication>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>

int getRandomNumberStd(int min, int max) {
    srand(time(NULL));
    return rand() % (max - min + 1) + min;
}

bool moveMentPerson = false;

void readFromFile(QChar tableWho[10][10], QString fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Failed to open the file for reading." << std::endl;
        return;
    }

    QTextStream in(&file);
    QVector<QString> map;
    int row = 0;
    int col = 0;

    while (!in.atEnd() && row < 10) {
        QString line = in.readLine();
        map.push_back(line);

        int charsToCopy = qMin(line.length(), 10);

        for (col = 0; col < charsToCopy; col++) {
            tableWho[row][col] = static_cast<char>(line.at(col).toLatin1());
        }

        for (; col < 10; col++) {
            tableWho[row][col] = 'E';
        }

        row++;
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            qDebug() << tableWho[i][j];
        }
    }
}

void parseCoordinatesFromFile(std::vector<std::vector<std::pair<int, int>>>& ships, std::vector<std::pair<int, int>>& currentShip, QString name) {
    QFile file(name);
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

GamePage* gamepage;

GamePage::GamePage(QWidget *parent) : QFrame(parent) {
    countPersonSucsses = 0;
    countBot = 0;

    layout = new QVBoxLayout(this);

    QLabel *backgroundLabel = new QLabel(this);
    QPixmap backgroundPixmap("E:/qt1/drg/battlepage.png");
    backgroundLabel->setPixmap(backgroundPixmap);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(0, 0, 1536, 864);
    // backgroundLabel->lower();
    // backgroundLabel->setAcceptDrops(false);

    readFromFile(table1, "map.txt");
    readFromFile(table2, "map.txt");

    qDebug() << table1[0][0] << table1[1][0];
}

void GamePage::mousePressEvent(QMouseEvent *event) {
    printMouseClick(event->pos());
}

void GamePage::printMouseClick(const QPoint &pos) {
    if (moveMentPerson == false) {
        if (pos.x() <= 665 && pos.x() >= 200 && pos.y() <= 670 && pos.y() >= 190) {
            int column = (pos.x() - 200) / 47;
            int row = (pos.y() - 190) / 47;

            int xPos = 200 - 3 + column * 47;
            int yPos = 190 - 2 + row * 47;

            if (table1[row][column] == 'W' || table1[row][column] == 'F' || table1[row][column] == 'B') {
                // Do nothing
            } else {
                if (table1[row][column] == 'S') {
                    QLabel *b = new QLabel(this);
                    QPixmap pix("E:/qt1/drg/not.png");
                    b->setPixmap(pix);
                    b->setScaledContents(true);
                    b->setGeometry(xPos, yPos, 48, 48);
                    b->raise();
                    b->show();

                    table1[row][column] = 'B';
                }

                if (table1[row][column] == 'E') {
                    QLabel *b = new QLabel(this);
                    QPixmap pix("E:/qt1/drg/missed.png");
                    b->setPixmap(pix);
                    b->setScaledContents(true);
                    b->setGeometry(xPos + 4, yPos + 4, 40, 40);
                    b->raise();
                    b->show();

                    table1[row][column] = 'W';
                    moveMentPerson = true;
                }
            }
        }
    }

    if (moveMentPerson == true) {
        if (pos.x() <= 1340 && pos.x() >= 860 && pos.y() <= 670 && pos.y() >= 190) {
            int column = (pos.x() - 865) / 47;
            int row = (pos.y() - 190) / 47;

            int xPos = 865 - 3 + column * 47;
            int yPos = 190 - 2 + row * 47;

            if (table2[row][column] == 'W' || table2[row][column] == 'F' || table2[row][column] == 'B') {
                // Do nothing
            } else {
                if (table2[row][column] == 'S') {
                    QLabel *b = new QLabel(this);
                    QPixmap pix("E:/qt1/drg/not.png");
                    b->setPixmap(pix);
                    b->setScaledContents(true);
                    b->setGeometry(xPos, yPos, 48, 48);
                    b->raise();
                    b->show();

                    table2[row][column] = 'B';
                }

                if (table2[row][column] == 'E') {
                    QLabel *b = new QLabel(this);
                    QPixmap pix("E:/qt1/drg/missed.png");
                    b->setPixmap(pix);
                    b->setScaledContents(true);
                    b->setGeometry(xPos + 4, yPos + 4, 40, 40);
                    b->raise();
                    b->show();

                    table2[row][column] = 'W';
                    moveMentPerson = false;
                }
            }
        }
    }
}

void setboard(int xp, int yp, QChar status) {
    int yPos;
    int xPos;

    qDebug() << xp << yp;

    if (status == 'B') {
        qDebug() << "Bomb";
        xPos = yp * 48 + 200;
        yPos = xp * 48 + 190;

        QLabel *b = new QLabel(gamepage);
        QPixmap pix("F:/botMode/test_mark_cross.png");
        b->setPixmap(pix);
        b->setScaledContents(true);
        b->setGeometry(xPos, yPos, 48, 48);
        b->raise();
        b->show();
    } else if (status == 'W') {
        qDebug() << "Wrong";

        xPos = yp * 48 + 200;
        yPos = xp * 48 + 190;

        QLabel *b = new QLabel(gamepage);
        QPixmap pix("F:/botMode/missed missile.png");
        b->setPixmap(pix);
        b->setScaledContents(true);
        b->setGeometry(xPos, yPos, 48, 48);
        b->raise();
        b->show();
    }
}

