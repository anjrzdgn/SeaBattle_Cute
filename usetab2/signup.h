#ifndef SIGNUP_H
#define SIGNUP_H



#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <QFont>
#include <QString>
#include <QVector>
#include <QRegularExpression>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class SignUp : public QMainWindow
{
    Q_OBJECT

public:
    SignUp(QWidget *parent = nullptr);

    QLineEdit *Username;
    QLineEdit *Password;
    QLineEdit *FirstName;
    QLineEdit *Lastname;
    QLineEdit *Email;

    QPushButton *Register;

    QLabel *back;

    bool CheckUser(QString username);
    bool CheckPass(QString password, QString username);
    bool CheckPasswordComplexity(QString password);
    bool isValidName(QString name);
    bool checkEmail(QString email);

public slots:
    void WriteDB();

private:
    QPalette getPaletteWithColor(QColor color);
    QFont getFontWithFamily(const QString &family, int size);
signals:
    void passed();
};


#endif // SIGNUP_H
