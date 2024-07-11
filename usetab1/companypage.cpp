#include "companypage.h"

#include "companypage.h"

// #include "companypage.h"

CompanyPage::CompanyPage(QWidget *parent) : QFrame(parent) {
    QLabel *backgroundLabel = new QLabel(this);
    QPixmap backgroundPixmap("E:/qt1/drg/companylogo.png");
    backgroundLabel->setPixmap(backgroundPixmap);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(0, 0, 1536, 864);
    backgroundLabel->lower();
    backgroundLabel->setAcceptDrops(false);

    ne = new QPushButton(this);
    ne->setGeometry(0, 0, 1536, 864);
    ne->setStyleSheet("QPushButton { background-color: transparent; border: none; }");

    connect(ne, &QPushButton::clicked, this, &CompanyPage::goToTab3);
}




