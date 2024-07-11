#ifndef BOARD_H
#define BOARD_H

#include <QChar>
#include <QDebug>
#include <vector>
#include <utility>
#include "ship.h"

class Board {

public:
    QChar table[10][10];
    Board();

    void setArray(const std::vector<std::pair<Ship*, QLabel*>> &ssships);

private:
    void setAroundShip(Ship* sshh);
    void setZeroAroundShip(Ship* sshh);
};

#endif // BOARD_H
