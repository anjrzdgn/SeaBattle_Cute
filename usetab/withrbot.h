// #ifndef WITHRBOT_H
// #define WITHRBOT_H


// #include <QApplication>
// #include <QFrame>
// #include <QVBoxLayout>
// #include <QLabel>
// #include <QPixmap>
// #include <QMouseEvent>
// #include <QFile>
// #include <QString>
// #include <QTextStream>
// #include <QVector>
// #include <QEventLoop>
// #include <QTimer>
// #include <QRandomGenerator>
// #include <QDateTime>
// #include <vector>
// #include <utility>
// #include <iostream>
// #include <sstream>

// // Global Variables
// bool moveMentPerson = true;
// bool moveMentBot = false;
// int sizecord = 0;
// int countshipperson = 0;
// int shootSuccses = 0;
// bool fallShip = false;
// int firstShot[1][2] = {0};
// int count = 0;
// int x = 0;
// int y = 0;
// int randX = 0;
// int randY = 0;
// int numberOfShook = 0;
// QEventLoop eventLoop;

// // Forward Declarations
// void readFromFile(QChar tableWho[10][10], QString fileName);
// void parseCoordinatesFromFile(std::vector<std::vector<std::pair<int, int>>>& ships, std::vector<std::pair<int, int>>& currentShip);
// void setboard(int xp, int yp, QChar status);
// bool isSurroundedByEmptySpaces(int x, int y, QChar table[10][10]);
// bool checkSpecislIndex(int x, int y, QChar _table[10][10]);
// void simpleAttack(QChar _table[10][10]);

// class GameBot : public QFrame {
//     Q_OBJECT

// public:
//     QChar bottable[10][10];
//     QChar table[10][10];
//     int countPersonSucsses;
//     int countBot;
//     std::vector<std::vector<std::pair<int, int>>> ships;
//     std::vector<std::pair<int, int>> currentShip;

//     GameBot(QWidget *parent = nullptr);

// protected:
//     void mousePressEvent(QMouseEvent *event) override;

// private:
//     QVBoxLayout *layout;
//     void printMouseClick(const QPoint &pos);
// };

// GameBot* gamebot = nullptr;

// void readFromFile(QChar tableWho[10][10], QString fileName) {
//     QFile file(fileName);
//     if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         std::cerr << "Failed to open the file for reading." << std::endl;
//         return;
//     }

//     QTextStream in(&file);
//     QVector<QString> map;
//     int row = 0;
//     int col = 0;

//     while (!in.atEnd() && row < 10) {
//         QString line = in.readLine();
//         map.push_back(line);

//         int charsToCopy = qMin(line.length(), 10);

//         for (col = 0; col < charsToCopy; col++) {
//             tableWho[row][col] = static_cast<char>(line.at(col).toLatin1());
//         }

//         for (; col < 10; col++) {
//             tableWho[row][col] = 'E';
//         }

//         row++;
//     }

//     for (int i = 0; i < 10; i++) {
//         for (int j = 0; j < 10; j++) {
//             qDebug() << tableWho[i][j];
//         }
//     }
// }

// void parseCoordinatesFromFile(std::vector<std::vector<std::pair<int, int>>>& ships, std::vector<std::pair<int, int>>& currentShip) {
//     QFile file("coordinates.txt");
//     if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         std::cerr << "Error opening file!" << std::endl;
//         return;
//     }

//     QTextStream in(&file);
//     QString line;

//     while (!in.atEnd()) {
//         line = in.readLine();
//         if (line.isEmpty()) {
//             ships.push_back(currentShip);
//             currentShip.clear();
//         } else {
//             std::stringstream ss(line.toStdString());
//             int x, y;
//             char comma;

//             while (ss >> x >> comma >> y) {
//                 currentShip.push_back(std::make_pair(x, y));
//             }
//         }
//     }

//     if (!currentShip.empty()) {
//         ships.push_back(currentShip);
//     }

//     file.close();
// }

// GameBot::GameBot(QWidget *parent) : QFrame(parent) {
//     countPersonSucsses = 0;
//     countBot = 0;

//     layout = new QVBoxLayout(this);

//     QLabel *backgroundLabel = new QLabel(this);
//     QPixmap backgroundPixmap("F:/botMode/battlepage.png");
//     backgroundLabel->setPixmap(backgroundPixmap);
//     backgroundLabel->setScaledContents(true);
//     backgroundLabel->setGeometry(0, 0, 1536, 864);
//     backgroundLabel->lower();
//     backgroundLabel->setAcceptDrops(false);

//     readFromFile(bottable, "botfile.txt");
//     readFromFile(table, "botfile.txt");
// }

// void GameBot::mousePressEvent(QMouseEvent *event) {
//     qDebug() << "salamaaaaam1";
//     if (!moveMentPerson) {
//         qDebug() << "salam";
//         return;
//     }
//     printMouseClick(event->pos());
// }

// void GameBot::printMouseClick(const QPoint &pos) {
//     if (countPersonSucsses == 10) {
//         // win
//     }

//     int column = (pos.x() - 865) / 47;
//     int row = (pos.y() - 190) / 47;

//     int xPos = 865 - 3 + column * 47;
//     int yPos = 190 - 2 + row * 47;

//     if (bottable[row][column] == 'W' || bottable[row][column] == 'F' || bottable[row][column] == 'B') {
//         // Do nothing
//     } else {
//         if (bottable[row][column] == 'S') {
//             countPersonSucsses++;
//             if (countPersonSucsses == 10) {
//                 // win
//             }

//             sizecord++;

//             QLabel *b = new QLabel(this);
//             QPixmap pix("F:/botMode/test_mark_cross.png");
//             b->setPixmap(pix);
//             b->setScaledContents(true);
//             b->setGeometry(xPos, yPos, 48, 48);
//             b->raise();
//             b->show();

//             bottable[row][column] = 'B';

//             for (int i = 0; i < ships.size(); i++) {
//                 for (auto &coord : ships[i]) {
//                     if (bottable[coord.first][coord.second] == 'B') {
//                         qDebug() << sizecord;
//                         sizecord++;

//                         if (ships[i].size() == sizecord) {
//                             for (const auto &coord : ships[i]) {
//                                 qDebug() << coord.first << coord.second;
//                                 bottable[coord.first][coord.second] = 'F';
//                             }
//                             sizecord = 0;
//                         }
//                     }
//                 }
//             }
//         }

//         if (bottable[row][column] == 'E') {
//             QLabel *b = new QLabel(this);
//             QPixmap pix("F:/botMode/missed missile.png");
//             b->setPixmap(pix);
//             b->setScaledContents(true);
//             b->setGeometry(xPos + 4, yPos + 4, 40, 40);
//             b->raise();
//             b->show();

//             moveMentPerson = false;
//             moveMentBot = true;

//             bottable[row][column] = 'W';

//             simpleAttack(table);
//             moveMentPerson = true;
//             moveMentBot = false;
//         }
//     }
// }

// void setboard(int xp, int yp, QChar status) {
//     int yPos;
//     int xPos;

//     qDebug() << xp << yp;

//     if (status == 'B') {
//         qDebug() << "Bomb";
//         xPos = yp * 48 + 200;
//         yPos = xp * 48 + 190;

//         QLabel *b = new QLabel(gamebot);
//         QPixmap pix("F:/botMode/test_mark_cross.png");
//         b->setPixmap(pix);
//         b->setScaledContents(true);
//         b->setGeometry(xPos, yPos, 48, 48);
//         b->raise();
//         b->show();

//         QTimer::singleShot(1000, &eventLoop, &QEventLoop::quit);

//         eventLoop.exec();
//     } else if (status == 'W') {
//         qDebug() << "Wrong";

//         xPos = yp * 48 + 200;
//         yPos = xp * 48 + 190;

//         QLabel *b = new QLabel(gamebot);
//         QPixmap pix("F:/botMode/missed missile.png");
//         b->setPixmap(pix);
//         b->setScaledContents(true);
//         b->setGeometry(xPos, yPos, 48, 48);
//         b->raise();
//         b->show();
//         QTimer::singleShot(500, &eventLoop, &QEventLoop::quit);

//         eventLoop.exec();
//     }
// }

// bool isSurroundedByEmptySpaces(int x, int y, QChar table[10][10]) {
//     return (table[x][y + 1] != 'S' && table[x][y - 1] != 'S' &&
//             table[x + 1][y] != 'S' && table[x - 1][y] != 'S' &&
//             x >= 1 && x <= 8 && y >= 1 && y <= 8);
// }

// bool checkSpecislIndex(int x, int y, QChar _table[10][10]) {
//     if (x == 0 && y == 0) {
//         if (_table[0][1] != 'S' && _table[1][0] != 'S') {
//             _table[0][0] = 'F';
//             setboard(0, 0, 'B');

//             _table[0][1] = 'W';
//             setboard(0, 1, 'W');

//             _table[1][0] = 'W';
//             setboard(1, 0, 'W');

//             _table[1][1] = 'W';
//             setboard(1, 1, 'W');

//             return true;
//         }
//     } else if (x == 0 && y == 9) {
//         if (_table[0][8] != 'S' && _table[1][9] != 'S') {
//             _table[0][9] = 'F';
//             setboard(0, 9, 'B');

//             _table[0][8] = 'W';
//             setboard(0, 8, 'W');

//             _table[1][9] = 'W';
//             setboard(1, 9, 'W');

//             _table[1][8] = 'W';
//             setboard(1, 8, 'W');

//             return true;
//         }
//     } else if (x == 9 && y == 0) {
//         if (_table[8][0] != 'S' && _table[9][1] != 'S') {
//             _table[9][0] = 'F';
//             setboard(9, 0, 'B');

//             _table[9][1] = 'W';
//             setboard(9, 1, 'W');

//             _table[8][1] = 'W';
//             setboard(8, 1, 'W');

//             _table[8][0] = 'W';
//             setboard(8, 0, 'W');

//             return true;
//         }
//     } else if (x == 9 && y == 9) {
//         if (_table[9][8] != 'S' && _table[8][9] != 'S') {
//             _table[9][9] = 'F';
//             setboard(9, 9, 'B');

//             _table[9][8] = 'W';
//             setboard(9, 8, 'W');

//             _table[8][9] = 'W';
//             setboard(8, 9, 'W');

//             _table[8][8] = 'W';
//             setboard(8, 8, 'W');

//             return true;
//         }
//     }

//     return false;
// }

// void simpleAttack(QChar _table[10][10]) {
//     while (countshipperson < 10) {
//         if (!moveMentBot) {
//             return;
//         }

//         int numberx = QRandomGenerator::global()->bounded(0, 100);
//         int numbery = QRandomGenerator::global()->bounded(0, 100);

//         int currentSecondx = QDateTime::currentDateTime().time().second();
//         int currentSecondy = QDateTime::currentDateTime().time().second();

//         randX = (currentSecondx * numberx) % 10;
//         randY = (currentSecondy * numbery) % 10;

//         qDebug() << randX << randY;

//         if (_table[randX][randY] == 'S') {
//             setboard(randX, randY, 'B');

//             if (checkSpecislIndex(randX, randY, _table)) {
//                 countshipperson++;
//                 fallShip = true;
//                 continue;
//             }

//             firstShot[0][0] = randX;
//             firstShot[0][1] = randY;

//             fallShip = false;

//             _table[randX][randY] = 'B';
//             shootSuccses++;

//             if (isSurroundedByEmptySpaces(randX, randY, _table)) {
//                 _table[randX][randY] = 'F';
//                 setboard(randX, randY, 'B');
//                 fallShip = true;
//                 countshipperson++;
//                 continue;
//             }

//             numberOfShook++;
//             if (count == 10) {
//                 // win
//             }
//         } else if (_table[randX][randY] == 'E') {
//             _table[randX][randY] = 'W';
//             setboard(randX, randY, 'W');

//             moveMentBot = false;
//             moveMentPerson = true;
//         }
//     }
// }



// #endif // WITHRBOT_H
