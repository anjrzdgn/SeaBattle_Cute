#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>

class LogIn : public QMainWindow
{
    Q_OBJECT

public:
    LogIn(QWidget *parent = nullptr);

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *signInButton;
    QLabel *backgroundLabel;
    QString username, password;

private slots:
    void checkUser();
signals:
    void Enter();

};

#endif // LOGIN_H
