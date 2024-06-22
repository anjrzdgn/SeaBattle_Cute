#ifndef INFODIO_H
#define INFODIO_H

#include <QDialog>
#include <QString>
#include "vector"
#include <QFile>
#include <QCryptographicHash>
#include <QString>
#include <QVector>
#include <QRegularExpression>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

namespace Ui {
class InfoDio;
}

class InfoDio : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDio(QWidget *parent = nullptr);
    ~InfoDio();
    bool CheckUser(QString username);
    bool CheckPass(QString password, QString username);
    bool CheckPasswordComplexity(QString password);
    bool isValidName(QString name);
    bool checkEmail(QString email);

private:
    Ui::InfoDio *ui;
signals:
    void send_username(QString);
    void send_pass(QString);
private slots:
    void on_pushButton_clicked();
};

#endif // INFODIO_H
