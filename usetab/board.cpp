#include "board.h"

#include "board.h"
#include <fstream>

Board::Board() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            table[i][j] = 'E';
        }
    }
}

void Board::setArray(const std::vector<std::pair<Ship*, QLabel*>> &sships) {
    int size;
    std::ofstream outFile("cordShips.txt");
    for(auto& sh : sships) {
        size = sh.first->w / 60;
        qDebug() << (sh.second->x()-200)/48 << " " << size <<" " << (sh.second->y()-183)/48;
        qDebug() << sh.second->x() << " " << sh.second->y() << ' ' << sh.first->st;

        if(sh.second->x()>= 250*0.8 && sh.second->x() <= 860*0.8 && sh.second->y() >= 220*0.8 && sh.second->y() <= 834*0.8) {
            if(sh.first->st == "h") {
                for(int i = (sh.second->x()-200)/48; i < ((sh.second->x()-200)/48) + size; i++) {
                    table[(sh.second->y()-183)/48][i] = 'S';
                    outFile << (sh.second->y()-183)/48 << "," << i << '\n';
                }
                outFile << '\n';
            }
            if(sh.first->st == "v") {
                for(int i = (sh.second->y()-200)/48; i < ((sh.second->y()-200)/48) + size; i++) {
                    table[i][(sh.second->x()-183)/48] = 'S';
                    outFile << i << "," << (sh.second->x()-200)/48 << '\n';
                }
                outFile << '\n';
            }
        }
    }
}

