#ifndef COMPANYPAGE_H
#define COMPANYPAGE_H

#include <QFrame>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>

class CompanyPage : public QFrame {
    Q_OBJECT

public:
    CompanyPage(QWidget *parent = nullptr);
    QPushButton *ne;

signals:
    void goToTab3();

};

#endif // COMPANYPAGE_H
