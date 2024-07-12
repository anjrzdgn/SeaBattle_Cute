#include "login.h"
#include <QMessageBox>
#include <QSqlError>

LogIn::LogIn(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(1536, 864); // set fixed size for the window

    backgroundLabel = new QLabel(this);
    QPixmap backgroundPixmap("E:/qt1/drg/signinpage.png");
    backgroundLabel->setPixmap(backgroundPixmap);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(0, 0, 1536, 864);
    backgroundLabel->lower();
    backgroundLabel->setAcceptDrops(false);

    usernameEdit = new QLineEdit(this);
    usernameEdit->setGeometry(590, 300, 360, 40);
    usernameEdit->setStyleSheet("QLineEdit { background-color: transparent; border: none; }");

    QPalette palette = usernameEdit->palette();
    palette.setColor(QPalette::Text, Qt::black);
    usernameEdit->setPalette(palette);

    QFont font = usernameEdit->font();
    font.setPointSize(28);
    font.setFamily("Dubai");
    usernameEdit->setFont(font);

    passwordEdit = new QLineEdit(this);
    passwordEdit->setGeometry(590, 410, 360, 40);
    passwordEdit->setStyleSheet("QLineEdit { background-color: transparent; border: none; }");

    QPalette palete = passwordEdit->palette();
    palete.setColor(QPalette::Text, Qt::black);
    passwordEdit->setPalette(palete);

    QFont font1 = passwordEdit->font();
    font1.setPointSize(28);
    font1.setFamily("Dubai");
    passwordEdit->setFont(font1);
    passwordEdit->setEchoMode(QLineEdit::Password);

    signInButton = new QPushButton(this);
    signInButton->setGeometry(685, 565, 160, 50);
    signInButton->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
    signInButton->setCursor(Qt::PointingHandCursor);

    connect(signInButton, &QPushButton::clicked, this, &LogIn::checkUser);
}

void LogIn::checkUser()
{
    username = usernameEdit->text();
    password = passwordEdit->text();

    QSqlDatabase myd = QSqlDatabase::addDatabase("QSQLITE");
    myd.setDatabaseName("E:/qt1/sql/mydba.db"); // Use forward slashes for Windows paths

    if(myd.open()){
        // qDebug()<<"connected..";

        QSqlQuery qry;
        qry.prepare("SELECT name FROM info WHERE username = :username AND password = :password ");
        qry.bindValue(":username", username);
        qry.bindValue(":password", password);

        if (qry.exec()) {
            if (qry.next()) {
                QString name = qry.value(0).toString();
                qDebug() << "Name: " << name;
                emit this->Enter();
            } else {
                qDebug() << "Invalid username or password";
            }
        } else {
            qDebug() << "Error: " << qry.lastError().text();
        }
    } else {
        qDebug()<<"Error: " << myd.lastError().text();
    }
}
