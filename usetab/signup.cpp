#include "signup.h"

// #include "ui_signup.h"

SignUp::SignUp(QWidget *parent) : QMainWindow(parent)
{
    // ui->setupUi(this);

    // Set up the background image
    QLabel *back = new QLabel(this);
    QPixmap backgroundPixmap("E:/qt1/drg/signuppage.png");
    back->setPixmap(backgroundPixmap);
    back->setScaledContents(true);
    back->setGeometry(0, 0, 1536, 864);
    back->lower();
    back->setAcceptDrops(false);

    // Create the input fields
    Username = new QLineEdit(this);
    Username->setGeometry(590, 220, 360, 40);
    Username->setStyleSheet("QLineEdit { background-color: transparent; border: none; }");
    Username->setPalette(getPaletteWithColor(Qt::black));
    Username->setFont(getFontWithFamily("Dubai", 28));

    Password = new QLineEdit(this);
    Password->setGeometry(590, 310, 360, 40);
    Password->setStyleSheet("QLineEdit { background-color: transparent; border: none; }");
    Password->setPalette(getPaletteWithColor(Qt::black));
    Password->setFont(getFontWithFamily("Dubai", 28));
    Password->setEchoMode(QLineEdit::Password);

    FirstName = new QLineEdit(this);
    FirstName->setGeometry(590, 490, 360, 40);
    FirstName->setStyleSheet("QLineEdit { background-color: transparent; border: none; }");
    FirstName->setPalette(getPaletteWithColor(Qt::black));
    FirstName->setFont(getFontWithFamily("Dubai", 28));

    Lastname = new QLineEdit(this);
    Lastname->setGeometry(590, 580, 360, 40);
    Lastname->setStyleSheet("QLineEdit { background-color: transparent; border: none; }");
    Lastname->setPalette(getPaletteWithColor(Qt::black));
    Lastname->setFont(getFontWithFamily("Dubai", 28));

    Email = new QLineEdit(this);
    Email->setGeometry(590, 400, 360, 40);
    Email->setStyleSheet("QLineEdit { background-color: transparent; border: none; }");
    Email->setPalette(getPaletteWithColor(Qt::black));
    Email->setFont(getFontWithFamily("Dubai", 28));

    // Create the register button
    Register = new QPushButton(this);
    Register->setGeometry(685, 680, 165, 50);
    Register->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
    Register->setCursor(Qt::PointingHandCursor);
    connect(Register, &QPushButton::clicked, this, &SignUp::WriteDB);
}

QPalette SignUp::getPaletteWithColor(QColor color)
{
    QPalette palette;
    palette.setColor(QPalette::Text, color);
    return palette;
}

QFont SignUp::getFontWithFamily(const QString &family, int size)
{
    QFont font;
    font.setFamily(family);
    font.setPointSize(size);
    return font;
}


bool SignUp::checkEmail(QString email)
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
            // ui->label->setText("invalid email");
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
                        // ui->label->setText("invalid email");
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
            // ui->label->setText("invalid email");
            return false;
        }

    }

    else
    {
        // ui->label->setText("invalid email");
        return false;
    }

    return true;
}
bool SignUp::isValidName(QString name)
{
    QRegularExpression regex("^[A-Za-z]+(-[A-Za-z]+)?$");
    if(regex.match(name).hasMatch())
    {
        return true;
    }
    else
    {
        // ui->label->setText("invalid name");
        return false;
    }
}
bool SignUp::CheckPasswordComplexity(QString password)
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

bool SignUp::CheckPass(QString password, QString username)
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
                        // ui->label->setText("weak password");
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
                    // ui->label->setText("weak password");
                    sum = 1;
                    return false;
                }
            }
        }
        else
        {
            // ui->label->setText("weak password");
            return false;
        }
    }
    else
    {
        // ui->label->setText("weak password");
        return false;
    }
    // ui->label->setText("salam");
    return true;
}

bool SignUp::CheckUser(QString username)
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
                    // ui->label->setText("invalid username format");
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
        // ui->label->setText("invalid username format");
        return false;

    }

    return true;
}


void SignUp::WriteDB() {


    if(this->Username->text()!="" && this->Email->text()!="" && this->FirstName->text()!="" && this->Password->text()!="" && this->Lastname->text()!="" ){

        QString username=this->Username->text();
        QString password=this->Password->text();
        QString name=this->FirstName->text();
        QString lastname=this->Lastname->text();
        QString email=this->Email->text();
        QString level;


        CheckUser(username);
        CheckPass(password,username);
        checkEmail(email);
        CheckPasswordComplexity(password);
        isValidName(name);
        isValidName(lastname);


        if(CheckUser(username)&& CheckPass(password,username)&& checkEmail(email)&&CheckPasswordComplexity(password)&&isValidName(name)&&isValidName(lastname))
        {
            qDebug()<<"salam";
            QSqlDatabase myd = QSqlDatabase::addDatabase("QSQLITE");
            myd.setDatabaseName("E:/qt1/sql/mydba.db");


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
                    qDebug() << "Error: ";
                }
            } else {
                qDebug()<<"Error: " ;
            }


            this->close();
            emit this->passed();
        }
    }
}

// ... rest of the class implementation ...
