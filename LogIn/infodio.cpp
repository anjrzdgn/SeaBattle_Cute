#include "infodio.h"
#include "ui_infodio.h"

InfoDio::InfoDio(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InfoDio)
{
    ui->setupUi(this);
}

InfoDio::~InfoDio()
{
    delete ui;
}

bool InfoDio::checkEmail(QString email)
{
    QString usernameEmail;
    int countdot = 0;

    //check end have @gmail.com
    QRegularExpression pattern(R"([a-zA-Z0-9._%+-]+@gmail\.com)");

    if(pattern.match(email).hasMatch())
    {
        int andisOfG = email.indexOf("@gmail.com");
        usernameEmail = email.left(andisOfG);

        if(usernameEmail == "")
        {
            ui->label->setText("invalid email");
            return false;
        }


        if ((usernameEmail.at(0).isLetter() && usernameEmail.at(0).isLower()) || (usernameEmail.at(0).isLetter() && usernameEmail.at(0).isUpper()) &&
                                                                                     usernameEmail.at(usernameEmail.size() - 1) != '.' && usernameEmail.at(usernameEmail.size() - 1) != '_')
        {
            for(QChar c : usernameEmail)
            {
                if(c == '.' || c == '_')
                {
                    countdot++;

                    if(countdot == 2)
                    {
                        countdot = 0;
                        ui->label->setText("invalid email");
                        return false;
                    }
                }
                else
                {
                    countdot = 0;
                }
            }
        }
        else
        {
            ui->label->setText("invalid email");
            return false;
        }

    }

    else
    {
        ui->label->setText("invalid email");
        return false;
    }

    return true;
}
bool InfoDio::isValidName(QString name)
{
    QRegularExpression regex("^[A-Za-z]+(-[A-Za-z]+)?$");
    if(regex.match(name).hasMatch())
    {
        return true;
    }
    else
    {
        ui->label->setText("invalid name");
        return false;
    }
}
bool InfoDio::CheckPasswordComplexity(QString password)
{
    bool hasLower = false;
    bool hasUpper = false;
    bool hasDigit = false;
    bool hasSpecialChar = false;

    for (QChar c : password)
    {
        if (c.isLower())
        {
            hasLower = true;
        }
        else if (c.isUpper())
        {
            hasUpper = true;
        }
        else if (c.isDigit())
        {
            hasDigit = true;
        }
        else if (c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&'||  c == '*'||  c == '('||  c == ')' || c == '-'||  c == '+'||  c == '=')
        {
            hasSpecialChar = true;
        }
    }

    return hasLower && hasUpper && hasDigit && hasSpecialChar;
}

bool InfoDio::CheckPass(QString password, QString username)
{
    //check size password
    if(password.size() >= 6 && password.size() <= 20)
    {
        //check special character in pass
        if (CheckPasswordComplexity(password))
        {
            //check repreated character
            for(int i = 0; i < password.size() - 1; i++)
            {
                int countchar = 0;
                if(password[i] == password[i+1])
                {
                    countchar++;
                    if(countchar == 4)
                    {
                        ui->label->setText("weak password");
                        return false;
                    }
                }
                else
                {
                    countchar = 0;
                }
            }

            //check username and password
            QVector<QString> words;
            QString currentWord;
            for (QChar ch : username)
            {
                if (ch.isDigit())
                {
                    currentWord += ch;
                }
                else
                {
                    if (!currentWord.isEmpty())
                    {
                        words.push_back(currentWord);
                        currentWord.clear();
                    }
                }
            }
            if (!currentWord.isEmpty())
            {
                words.push_back(currentWord);
            }
            int sum = 0;
            for (QString word : words)
            {
                if (word.length() > 3 && password.contains(word, Qt::CaseInsensitive))
                {
                    ui->label->setText("weak password");
                    sum = 1;
                    return false;
                }
            }
        }
        else
        {
            ui->label->setText("weak password");
            return false;
        }
    }
    else
    {
        ui->label->setText("weak password");
        return false;
    }
    // ui->label->setText("salam");
    return true;
}

bool InfoDio::CheckUser(QString username)
{
    int countdot = 0;

    //check first and end
    if (((QChar(username.at(0)).unicode() > 64 && QChar(username.at(0)).unicode() <= 90)
         || (QChar(username.at(0)).unicode() >= 97 && QChar(username.at(0)).unicode() <= 122))
        && username[username.size() - 1] != '.' && username[username.size() - 1] != '_')
    {

        //check tow '_' and '.' in username
        for(int i = 0; i < username.size(); i++)
        {

            if(username[i] == '.' || username[i] == '_')
            {
                countdot++;
                if(countdot == 2)
                {
                    ui->label->setText("invalid username format");
                    return false;
                }
            }
            else
            {
                countdot = 0;
            }
        }

    }
    else
    {
        ui->label->setText("invalid username format");
        return false;

    }

    return true;
}


void InfoDio::on_pushButton_clicked()
{
    emit send_username(ui->user->text());
    emit send_pass(ui->pass->text());


    if(ui->user->text()!="" && ui->email->text()!="" && ui->name->text()!="" && ui->pass->text()!="" && ui->name_2->text()!="" ){

        QString username=ui->user->text();
        QString password=ui->pass->text();
        QString name=ui->name->text();
        QString lastname=ui->name_2->text();
        QString email=ui->email->text();
        QString level;


        CheckUser(username);
        CheckPass(password,username);
        checkEmail(email);
        CheckPasswordComplexity(password);
        isValidName(name);
        isValidName(lastname);


        if(CheckUser(username)&& CheckPass(password,username)&& checkEmail(email)&&CheckPasswordComplexity(password)&&isValidName(name)&&isValidName(lastname))
        {
            QSqlDatabase myd = QSqlDatabase::addDatabase("QSQLITE");
            myd.setDatabaseName("E:/qt1/LogIn/LogIn/information.db");


            if(myd.open()){
                qDebug()<<"connected..";
                QSqlQuery qry;
                qry.prepare("INSERT INTO info (name, username, password ,email,lastname,level) VALUES (:name, :username, :password ,:email,:lastname,:level)");
                qry.bindValue(":name", name);
                qry.bindValue(":username", username);
                qry.bindValue(":password", password);
                qry.bindValue(":lastname", lastname);
                qry.bindValue(":email", email);
                qry.bindValue(":level", level);

                if (qry.exec()) {
                    qDebug() << "Data inserted successfully";
                } else {
                    qDebug() << "Error: " << qry.lastError().text();
                }
            } else {
                qDebug()<<"Error: " << myd.lastError().text();
            }


            close();
        }
    }
}





