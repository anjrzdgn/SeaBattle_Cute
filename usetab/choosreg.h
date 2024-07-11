#ifndef CHOOSREG_H
#define CHOOSREG_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>

class ChoosReg : public QFrame {
    Q_OBJECT

public:
    ChoosReg(QWidget *parent = nullptr);

    QPushButton *signin;
    QPushButton *signup;
    QLabel *bg;

signals:
    void gologin();
    void goSignup();

};

#endif // CHOOSREG_H
