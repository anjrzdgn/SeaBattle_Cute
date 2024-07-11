#include "choosreg.h"

ChoosReg::ChoosReg(QWidget *parent) : QFrame(parent) {
    bg = new QLabel(this);
    QPixmap backgroundPixmap("E:/qt1/drg/logingpage.png");
    bg->setPixmap(backgroundPixmap);
    bg->setScaledContents(true);
    bg->setGeometry(0, 0, 1536, 864);
    bg->lower();
    bg->setAcceptDrops(false);

    signin = new QPushButton(this);
    signin->setGeometry(405, 300, 255, 260);
    signin->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
    signin->setCursor(Qt::PointingHandCursor);

    signup = new QPushButton(this);
    signup->setGeometry(870, 300, 245, 260);
    signup->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
    signup->setCursor(Qt::PointingHandCursor);

    connect(signin, &QPushButton::clicked, this, &ChoosReg::gologin);
    connect(signup, &QPushButton::clicked, this, &ChoosReg::goSignup);
}

// void ChoosReg::goSignin() {
//     // implement goSignin logic here
// }

// void ChoosReg::goSignup() {
//     // implement goSignup logic here
// }
