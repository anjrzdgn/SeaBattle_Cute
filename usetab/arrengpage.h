// #ifndef ARRENGPAGE_H
// #define ARRENGPAGE_H


// // #include "mainwindow.h"
// // #include <QApplication>
// // #include <QDrag>
// // #include <QMimeData>
// // #include <QDataStream>
// // #include <QByteArray>
// // #include <QLabel>
// // #include <QFrame>
// // #include <QPixmap>
// // #include <QPoint>
// // #include <QMouseEvent>
// // #include <QDropEvent>
// // #include <QDebug>
// // #include <QPushButton>
// // #include <QSize>
// // #include <fstream>
// // #include "E:/qt1/usetab/ships.cpp"

// // // class Ship {
// // // public:
// // //     QLabel *label;
// // //     QString st;
// // //     int xpos;
// // //     int ypos;
// // //     int w;
// // //     int h;
// // //     int zcolumn;
// // //     int zrow;

// // //     Ship(QLabel *label, QString pixmap, int x, int y, int width, int height)
// // //         : label(label), xpos(x), ypos(y), w(width), h(height), st("h") {

// // //         zcolumn = (label->x() - 200) / 48;
// // //         zrow = (label->y() - 190) / 48;

// // //         QPixmap f(pixmap);
// // //         label->setPixmap(f);
// // //         label->setGeometry(x, y, width, height);
// // //         label->show();
// // //     }

// // //     void rotate() {
// // //         if (label->x() > 1000)
// // //         {
// // //             if (st == "h") {
// // //                 st = "v";
// // //                 label->setGeometry(label->x(), label->y(), h, w);  // Swap width and height
// // //             } else {
// // //                 st = "h";
// // //                 label->setGeometry(label->x(), label->y(), w, h);  // Swap width and height
// // //             }

// // //             QPixmap pixmap = label->pixmap();
// // //             QTransform transform;
// // //             transform.rotate(90);
// // //             QPixmap transformedPixmap = pixmap.transformed(transform, Qt::SmoothTransformation);
// // //             label->setPixmap(transformedPixmap);
// // //         }
// // //     }
// // // };


// // // extern std::vector<std::pair< Ship*,QLabel*>> ships;

// // class Board{

// // public:

// //     QChar table[10][10];
// //     Board()  {
// //         for (int i = 0; i < 10; i++) {
// //             for (int j = 0; j < 10; j++) {
// //                 table[i][j] = 'E';
// //             }
// //         }
// //     }

// //     void setArray(std::vector<std::pair< Ship*,QLabel*>> sshhips)
// //     {
// //         int size;
// //         std::ofstream outFile("cordShips.txt");
// //         for(auto& sh : sshhips)
// //         {
// //             size = sh.first->w / 60;
// //             qDebug() << (sh.second->x()-200)/48 << " " << size <<" " << (sh.second->y()-183)/48;
// //             qDebug() << sh.second->x() << " " << sh.second->y() << ' ' << sh.first->st;

// //             if(sh.second->x()>= 250*0.8 && sh.second->x() <= 860*0.8 && sh.second->y() >= 220*0.8 && sh.second->y() <= 834*0.8)
// //             {

// //                 if(sh.first->st == "h")
// //                 {
// //                     for(int i = (sh.second->x()-200)/48; i < ((sh.second->x()-200)/48) + size; i++)
// //                     {
// //                         table[(sh.second->y()-183)/48][i] = 'S';

// //                         outFile << (sh.second->y()-183)/48 << "," << i << '\n';
// //                     }
// //                     outFile << '\n';
// //                 }
// //                 if(sh.first->st == "v")
// //                 {
// //                     for(int i = (sh.second->y()-200)/48; i < ((sh.second->y()-200)/48) + size; i++)
// //                     {
// //                         table[i][(sh.second->x()-183)/48] = 'S';

// //                         outFile << i << "," << (sh.second->x()-200)/48 << '\n';
// //                     }
// //                     outFile << '\n';
// //                 }
// //             }
// //         }
// //     }

// // };

// // // void Board::setArray(std::vector<std::pair< Ship*,QLabel*>> sshhips)
// // // {
// // //     int size;
// // //     std::ofstream outFile("cordShips.txt");
// // //     for(auto& sh : sshhips)
// // //     {
// // //         size = sh.first->w / 60;
// // //         qDebug() << (sh.second->x()-200)/48 << " " << size <<" " << (sh.second->y()-183)/48;
// // //         qDebug() << sh.second->x() << " " << sh.second->y() << ' ' << sh.first->st;

// // //         if(sh.second->x()>= 250*0.8 && sh.second->x() <= 860*0.8 && sh.second->y() >= 220*0.8 && sh.second->y() <= 834*0.8)
// // //         {

// // //             if(sh.first->st == "h")
// // //             {
// // //                 for(int i = (sh.second->x()-200)/48; i < ((sh.second->x()-200)/48) + size; i++)
// // //                 {
// // //                     table[(sh.second->y()-183)/48][i] = 'S';

// // //                     outFile << (sh.second->y()-183)/48 << "," << i << '\n';
// // //                 }
// // //                 outFile << '\n';
// // //             }
// // //             if(sh.first->st == "v")
// // //             {
// // //                 for(int i = (sh.second->y()-200)/48; i < ((sh.second->y()-200)/48) + size; i++)
// // //                 {
// // //                     table[i][(sh.second->x()-183)/48] = 'S';

// // //                     outFile << i << "," << (sh.second->x()-200)/48 << '\n';
// // //                 }
// // //                 outFile << '\n';
// // //             }
// // //         }
// // //     }
// // // }

// // // class ClickableLabel : public QLabel {
// // //     Q_OBJECT

// // // public:
// // //     ClickableLabel(QWidget *parent = nullptr) : QLabel(parent) {}

// // // signals:
// // //     void clicked();

// // // protected:
// // //     void mousePressEvent(QMouseEvent *event) override {
// // //         emit clicked();
// // //         QLabel::mousePressEvent(event);
// // //     }
// // // };

// // class DragWidget : public QFrame {
// //     Q_OBJECT

// // public:
// //     QLabel *backgroundLabel1 = new QLabel(this);
// //     QLabel *backgroundLabel = new QLabel(this);
// //     // ClickableLabel *houseIcon1 = new ClickableLabel(this);

// //     Board check_and_fill;

// //     DragWidget(QWidget *parent = nullptr)
// //         : QFrame(parent)
// //     {

// //         QLabel *labelA = new QLabel(this);
// //         Ship* A = new Ship(labelA, "C:/SeaBattle_Cute_private/drg/src/1Xship copy.png", 1010, 230, 60, 60);
// //         ships.push_back(std::make_pair(A,labelA));

// //         QLabel *labelB = new QLabel(this);
// //         Ship* B = new Ship(labelB, "C:/SeaBattle_Cute_private/drg/src/1Xship copy.png", 1106, 230, 60, 60);
// //         ships.push_back(std::make_pair(B,labelB));

// //         QLabel *labelC = new QLabel(this);
// //         Ship* C = new Ship(labelC, "C:/SeaBattle_Cute_private/drg/src/1Xship copy.png", 1202, 230, 60, 60);
// //         ships.push_back(std::make_pair(C,labelC));

// //         QLabel *labelD = new QLabel(this);
// //         Ship* D = new Ship(labelD, "C:/SeaBattle_Cute_private/drg/src/1Xship copy.png", 1298, 230, 60, 60);
// //         ships.push_back(std::make_pair(D,labelD));

// //         QLabel *labelE = new QLabel(this);
// //         Ship* E = new Ship(labelE, "C:/SeaBattle_Cute_private/drg/src/2Xship copy.png", 1010, 326, 120, 60);
// //         ships.push_back(std::make_pair(E,labelE));

// //         QLabel *labelF = new QLabel(this);
// //         Ship* F = new Ship(labelF, "C:/SeaBattle_Cute_private/drg/src/2Xship copy.png", 1154, 326, 120, 60);
// //         ships.push_back(std::make_pair(F,labelF));

// //         QLabel *labelG = new QLabel(this);
// //         Ship* G = new Ship(labelG, "C:/SeaBattle_Cute_private/drg/src/2Xship copy.png", 1298, 326, 120, 60);
// //         ships.push_back(std::make_pair(G,labelG));

// //         QLabel *labelH = new QLabel(this);
// //         Ship* H = new Ship(labelH, "C:/SeaBattle_Cute_private/drg/src/3Xship copy.png", 1010, 422, 180, 60);
// //         ships.push_back(std::make_pair(H,labelH));

// //         QLabel *labelI = new QLabel(this);
// //         Ship* I = new Ship(labelI, "C:/SeaBattle_Cute_private/drg/src/3Xship copy.png", 1202, 422, 180, 60);
// //         ships.push_back(std::make_pair(I,labelI));

// //         QLabel *labelJ = new QLabel(this);
// //         Ship* J = new Ship(labelJ, "C:/SeaBattle_Cute_private/drg/src/4Xship copy.png", 1106, 518, 240, 60);
// //         ships.push_back(std::make_pair(J,labelJ));


// //         QPushButton* restore = new QPushButton(this);
// //         restore->setGeometry(815, 665, 50, 50);
// //         restore->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
// //         restore->setCursor(Qt::PointingHandCursor);
// //         connect(restore, &QPushButton::clicked, this, &DragWidget::restore_all_ship);

// //         QPushButton* rotate = new QPushButton(this);
// //         rotate->setGeometry(910, 665, 50, 50);
// //         rotate->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
// //         rotate->setCursor(Qt::PointingHandCursor);
// //         connect(rotate, &QPushButton::clicked, this, &DragWidget::rotateShips);

// //         QPushButton* next = new QPushButton(this);
// //         next->setGeometry(1210, 665, 170, 50);
// //         next->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
// //         next->setCursor(Qt::PointingHandCursor);
// //         connect(next, &QPushButton::clicked, this, &DragWidget::onNextButtonClicked);

// //         QPixmap images("C:/SeaBattle_Cute_private/src_graphic/made/arrangement page copy.png");
// //         backgroundLabel1->setPixmap(images);
// //         backgroundLabel1->setScaledContents(true);
// //         backgroundLabel1->setGeometry(0, 0, 1536, 864); // Set the geometry of the background label to cover the entire window
// //         backgroundLabel1->lower(); // Send the background label to the back
// //         backgroundLabel1->setAcceptDrops(false); // Set to not accept drag and drop events

// //         setMinimumSize(200, 200);
// //         setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
// //         setAcceptDrops(true);
// //     }

// // public slots:
// //     void onNextButtonClicked() {
// //         Board* br = new Board() ;
// //         br->setArray(ships);
// //         for (int i = 0; i <= 9; i++)
// //         {
// //             for (int j = 0; j <= 9; j++)
// //             {
// //                 qDebug() << br->table[i][j];
// //             }
// //         }
// //         qDebug() << "Next button clicked!";
// //         QApplication::quit();
// //     }

// //     void restore_all_ship()
// //     {
// //         for (int i = 0; i < 10; i++) {
// //             for (int j = 0; j < 10; j++) {
// //                 check_and_fill.table[i][j] = 'E';
// //             }

// //         }
// //         for(auto& pair : ships)
// //         {
// //             pair.second->move(pair.first->xpos, pair.first->ypos);
// //             if (pair.first->st == 'v') pair.first->rotate();
// //         }
// //     }

// //     void rotateShips()
// //     {
// //         for (auto& pair : ships)
// //         {
// //             pair.first->rotate();
// //         }
// //     }

// // protected:
// //     void mousePressEvent(QMouseEvent *event) override
// //     {
// //         QLabel *child = static_cast<QLabel*>(childAt(event->position().toPoint()));
// //         if (!child || child == backgroundLabel1 || child == backgroundLabel) // Ignore the background label
// //             return;

// //         QByteArray itemData;
// //         QDataStream dataStream(&itemData, QIODevice::WriteOnly);
// //         dataStream << child->pos();

// //         QMimeData *mimeData = new QMimeData;
// //         mimeData->setData("application/x-dnditemdata", itemData);

// //         QDrag *drag = new QDrag(this);
// //         drag->setMimeData(mimeData);
// //         drag->setPixmap(child->pixmap());
// //         drag->setHotSpot(event->position().toPoint() - child->pos());

// //         drag->exec();
// //     }

// //     void dragEnterEvent(QDragEnterEvent *event) override
// //     {
// //         QLabel *child = static_cast<QLabel*>(childAt(mapFromGlobal(event->pos())));
// //         if (!child || child == backgroundLabel1 || child == backgroundLabel) // Ignore the background label
// //             return;

// //         Ship* ship = nullptr;
// //         for (auto& pair : ships) {
// //             if (pair.second == child) {
// //                 ship = pair.first;
// //                 break;
// //             }
// //         }

// //         int precolumn = (child->geometry().x() - 200) / 48;
// //         int prerow = ((child->geometry().y() - 190) / 48);
// //         if (prerow != 0)
// //         {
// //             prerow++;
// //         }

// //         int size = ship->st == "h" ? child->width() / 60 : child->height() / 60;

// //         if (prerow < 10 && precolumn < 10)
// //         {
// //             if (ship->st == "h") {
// //                 for (int i = 0; i < size; i++) {
// //                     check_and_fill.table[prerow][precolumn + i] = 'E';
// //                 }
// //                 for (int i = prerow - 1; i <= prerow + 1; i++) {
// //                     for (int j = precolumn - 1; j <= precolumn + size; j++) {
// //                         if (i >= 0 && i < 10 && j >= 0 && j < 10) {
// //                             check_and_fill.table[i][j] = 'E';
// //                         }
// //                     }
// //                 }
// //             } else if (ship->st == "v") {
// //                 for (int i = 0; i < size; i++) {
// //                     check_and_fill.table[prerow + i][precolumn] = 'E';
// //                 }
// //                 for (int i = prerow - 1; i <= prerow + size; i++) {
// //                     for (int j = precolumn - 1; j <= precolumn + 1; j++) {
// //                         if (i >= 0 && i < 10 && j >= 0 && j < 10) {
// //                             check_and_fill.table[i][j] = 'E';
// //                         }
// //                     }
// //                 }
// //             }
// //         }

// //         for (auto& pair : ships)
// //         {
// //             if (pair.second != child)
// //             {
// //                 int column = (pair.second->x() - 200) / 48;
// //                 int row = (pair.second->y() - 190) / 48;
// //                 int ss = pair.first->st == "h" ? pair.second->width() / 60 : pair.second->height() / 60;

// //                 if (column < 10 && row < 10)
// //                 {
// //                     if (pair.first->st == "h") {
// //                         for (int i = 0; i < ss; i++) {
// //                             check_and_fill.table[row][column + i] = 'S';
// //                         }
// //                         for (int i = row - 1; i <= row + 1; i++) {
// //                             for (int j = column - 1; j <= column + ss; j++) {
// //                                 if (i >= 0 && i < 10 && j >= 0 && j < 10 && check_and_fill.table[i][j] != 'S') {
// //                                     check_and_fill.table[i][j] = 'O';
// //                                 }
// //                             }
// //                         }
// //                     } else if (pair.first->st == "v") {
// //                         for (int i = 0; i < ss; i++) {
// //                             check_and_fill.table[row + i][column] = 'S';
// //                         }
// //                         for (int i = row - 1; i <= row + ss; i++) {
// //                             for (int j = column - 1; j <= column + 1; j++) {
// //                                 if (i >= 0 && i < 10 && j >= 0 && j < 10 && check_and_fill.table[i][j] != 'S') {
// //                                     check_and_fill.table[i][j] = 'O';
// //                                 }
// //                             }
// //                         }
// //                     }
// //                 }
// //             }
// //         }

// //         if (event->mimeData()->hasFormat("application/x-dnditemdata"))
// //             event->acceptProposedAction();
// //     }




// //     void dropEvent(QDropEvent *event) override
// //     {
// //         if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
// //             QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
// //             QDataStream dataStream(&itemData, QIODevice::ReadOnly);
// //             QPoint offset;
// //             dataStream >> offset;

// //             QLabel *child = static_cast<QLabel*>(childAt(offset));
// //             if (child) {
// //                 int x = event->position().toPoint().x();
// //                 int y = event->position().toPoint().y();

// //                 if (x >= 250*0.8 && x <= 860*0.8 && y >= 220*0.8 && y <= 834*0.8) {
// //                     int column = (x - 200) / 48;
// //                     int row = (y - 190) / 48;

// //                     int xPos = 200 + column * 48;
// //                     int yPos = 190 - 7 + row * 48;

// //                     QPoint position(xPos, yPos);

// //                     Ship* ship = nullptr;
// //                     for (auto& pair : ships)
// //                     {
// //                         if (pair.second == child)
// //                         {
// //                             ship = pair.first;
// //                             break;
// //                         }
// //                     }

// //                     qDebug() << column << ' ' << row;
// //                     qDebug() << check_and_fill.table[row][column];

// //                     if (ship->w == 240 && column > 6 && ship->st == 'h') {
// //                         child->move(offset);
// //                     }
// //                     else if (ship->w == 180 && column > 7 && ship->st == 'h') {
// //                         child->move(offset);
// //                     }
// //                     else if (ship->w == 120 && column > 8 && ship->st == 'h') {
// //                         child->move(offset);
// //                     }
// //                     else if (ship->w == 240 && row < 3 && ship->st == 'v') {
// //                         child->move(offset);
// //                     }
// //                     else if (ship->w == 180 && row < 2 && ship->st == 'v') {
// //                         child->move(offset);
// //                     }
// //                     else if (ship->w == 120 && row < 1 && ship->st == 'v') {
// //                         child->move(offset);
// //                     }
// //                     else
// //                     {
// //                         int size = ship->w / 60;
// //                         bool possible = true;

// //                         int precolumn = (child->geometry().x() - 200) / 48;
// //                         int prerow = ((child->geometry().y() - 190) / 48);
// //                         if (prerow != 0)
// //                         {
// //                             prerow++;
// //                         }

// //                         // Check if the new position is valid for a horizontal ship
// //                         if (ship->st == 'h') {
// //                             for (int i = 0; i < size; i++) {
// //                                 if (check_and_fill.table[row][column + i] != 'E') {
// //                                     possible = false;
// //                                     break;
// //                                 }
// //                             }
// //                         }
// //                         else if (ship->st == 'v') { // Check if the new position is valid for a vertical ship
// //                             for (int i = 0; i < size; i++) {
// //                                 if (check_and_fill.table[row + i][column] != 'E') {
// //                                     possible = false;
// //                                     break;
// //                                 }
// //                             }
// //                         }


// //                         if (possible)
// //                         {
// //                             if (ship->st == 'v' && size == 2)
// //                             {
// //                                 child->move(xPos, yPos - 10);
// //                             }
// //                             else if (ship->st == 'v' && size == 3)
// //                             {
// //                                 child->move(xPos, yPos - 15);
// //                             }
// //                             else if (ship->st == 'v' && size == 4)
// //                             {
// //                                 child->move(xPos, yPos - 20);
// //                             }
// //                             else
// //                             {
// //                                 child->move(xPos, yPos);
// //                             }


// //                             if (ship->st == 'h') {
// //                                 // Set the ship cells for horizontal ships
// //                                 for (int i = 0; i < size; i++) {
// //                                     check_and_fill.table[row][column + i] = 'S';
// //                                 }
// //                                 // Set the surrounding cells for horizontal ships
// //                                 for (int i = row - 1; i <= row + 1; i++) {
// //                                     for (int j = column - 1; j <= column + size; j++) {
// //                                         if (i >= 0 && i < 10 && j >= 0 && j < 10 && check_and_fill.table[i][j] != 'S') {
// //                                             check_and_fill.table[i][j] = 'O';
// //                                         }
// //                                     }
// //                                 }
// //                             }
// //                             else if (ship->st == 'v') {
// //                                 // Set the ship cells for vertical ships
// //                                 for (int i = 0; i < size; i++) {
// //                                     check_and_fill.table[row + i][column] = 'S';
// //                                 }
// //                                 // Set the surrounding cells for vertical ships
// //                                 for (int i = row - 1; i <= row + size; i++) {
// //                                     for (int j = column - 1; j <= column + 1; j++) {
// //                                         if (i >= 0 && i < 10 && j >= 0 && j < 10 && check_and_fill.table[i][j] != 'S') {
// //                                             check_and_fill.table[i][j] = 'O';
// //                                         }
// //                                     }
// //                                 }
// //                             }
// //                         }
// //                         else
// //                         {
// //                             child->move(offset);
// //                         }


// //                     }

// //                     if (offset.x() == xPos && offset.y() == yPos)
// //                     {
// //                         int size = ship->w / 60;

// //                         for (int i = 0; i < size; i++) {
// //                             check_and_fill.table[row][column + i] = 'S';
// //                         }
// //                         for (int i = row - 1; i <= row + 1; i++) {
// //                             for (int j = column - 1; j <= column + size; j++) {
// //                                 if (i >= 0 && i < 10 && j >= 0 && j < 10 && check_and_fill.table[i][j] != 'S') {
// //                                     check_and_fill.table[i][j] = 'O';
// //                                 }
// //                             }
// //                         }
// //                     }
// //                 }
// //                 else
// //                 {
// //                     child->move(offset);
// //                 }
// //                 child->show();
// //             }

// //             event->acceptProposedAction();
// //         }
// //     }
// // };
// #ifndef DRAGWIDGET_H
// #define DRAGWIDGET_H

// #include <QFrame>
// #include <QLabel>
// #include <QPushButton>
// #include <QDrag>
// #include <QMimeData>
// #include <QMouseEvent>
// #include <QDropEvent>
// #include <vector>
// #include <utility>
// #include "ship.h"
// #include "board.h"

// class ClickableLabel : public QLabel {
//     Q_OBJECT

// public:
//     ClickableLabel(QWidget *parent = nullptr) : QLabel(parent) {}

// signals:
//     void clicked();

// protected:
//     void mousePressEvent(QMouseEvent *event) override {
//         emit clicked();
//         QLabel::mousePressEvent(event);
//     }
// };

// class DragWidget : public QFrame {
//     Q_OBJECT

// public:
//     QLabel *backgroundLabel1;
//     QLabel *backgroundLabel;
//     ClickableLabel *houseIcon1;

//     Board check_and_fill;

//     DragWidget(QWidget *parent = nullptr);

// public slots:
//     void onNextButtonClicked();
//     void restore_all_ship();
//     void rotateShips();

// protected:
//     void mousePressEvent(QMouseEvent *event) override;
//     void dragEnterEvent(QDragEnterEvent *event) override;
//     void dropEvent(QDropEvent *event) override;
// };

// // #endif // DRAGWIDGET_H

// #endif // ARRENGPAGE_H
