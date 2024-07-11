#include "login.h"

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

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("E:/qt1/sql/mydba.db");

    if (db.open()) {
        QSqlQuery qry;
        qry.prepare("SELECT info FROM information WHERE username = :username AND password = :password");
        qry.bindValue(":username", username);
        qry.bindValue(":password", password);

        if (qry.exec()) {
            if (qry.next()) {
                qDebug() << "User found!";
                // Add code to handle successful login here
            } else {
                qDebug() << "User not found!";
                // Add code to handle invalid login here
            }
        } else {
            qDebug() << "Error executing query: " ;
        }
    } else {
        qDebug() << "Error opening database: " ;
    }
}
