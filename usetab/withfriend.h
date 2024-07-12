#ifndef WITHFRIEND_H
#define WITHFRIEND_H

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
#include <QEventLoop>
#include <QTimer>
#include <QRandomGenerator>
#include <cstdlib>
#include <ctime>
#include <QSet>
#include <QDebug>
#include <QDateTime>

int getRandomNumberStd(int min, int max);

void readFromFile(QChar tableWho[10][10], QString fileName);
void parseCoordinatesFromFile(std::vector<std::vector<std::pair<int, int>>>& ships, std::vector<std::pair<int, int>>& currentShip, QString name);

class GamePage : public QFrame {
    Q_OBJECT

public:
    QChar table1[10][10];
    QChar table2[10][10];

    int countPersonSucsses;
    int countBot;

    std::vector<std::vector<std::pair<int, int>>> ships1;
    std::vector<std::pair<int, int>> currentShip1;

    std::vector<std::vector<std::pair<int, int>>> ships2;
    std::vector<std::pair<int, int>> currentShip2;

    GamePage(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QVBoxLayout *layout;

    void printMouseClick(const QPoint &pos);
};

void setboard(int xp, int yp, QChar status);


#endif // WITHFRIEND_H
