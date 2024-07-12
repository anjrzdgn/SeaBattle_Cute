#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include <QString>
#include <QFont>
#include <QGraphicsOpacityEffect>
#include <QVBoxLayout>
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

class armoury_info
{
public:
    int bomb_atomic;
    int bomb_3X3;
    int bomb_4X2;
    int sea_mine;
    int observation;
    int air_defence;
};

int user_oil = 200;
int user_rank = 5;

class arselanPage : public MainWindow
{
    Q_OBJECT

public:
    QLabel *backgroundLabel = new QLabel(this);
    armoury_info arsenal;

    QFont font;
    QFont font_oil;
    QFont font_rank;

    QGraphicsOpacityEffect *opacityEffect1 = new QGraphicsOpacityEffect;
    QGraphicsOpacityEffect *opacityEffect2 = new QGraphicsOpacityEffect;
    QGraphicsOpacityEffect *opacityEffect3 = new QGraphicsOpacityEffect;
    QGraphicsOpacityEffect *opacityEffect4 = new QGraphicsOpacityEffect;
    QGraphicsOpacityEffect *opacityEffect5 = new QGraphicsOpacityEffect;
    QGraphicsOpacityEffect *opacityEffect6 = new QGraphicsOpacityEffect;


    QLabel *remain_oil = new QLabel(this);
    QLabel *rank = new QLabel(this);

    QLabel *defence1 = new QLabel(this);
    QLabel *defence2 = new QLabel(this);
    QLabel *defence3 = new QLabel(this);

    QPushButton* reset = new QPushButton(this);

    QPushButton* bomb_atomic = new QPushButton(this);
    QLabel *bomb_atomic_quantity = new QLabel(bomb_atomic);

    QPushButton* bomb_3X3 = new QPushButton(this);
    QLabel *bomb_3X3_quantity = new QLabel(bomb_3X3);

    QPushButton* bomb_4X2 = new QPushButton(this);
    QLabel *bomb_4X2_quantity = new QLabel(bomb_4X2);

    QPushButton* sea_mine = new QPushButton(this);
    QLabel *sea_mine_quantity = new QLabel(sea_mine);

    QPushButton* observation = new QPushButton(this);
    QLabel *observation_quantity = new QLabel(observation);

    QPushButton* air_defence = new QPushButton(this);
    QLabel *air_defence_quantity = new QLabel(air_defence);

    QPushButton* next = new QPushButton(this);

    arselanPage() : lastClickPosition(0, 0), waitingForClick(false)
    {
        arsenal.bomb_atomic = 0;
        arsenal.bomb_3X3 = 0;
        arsenal.bomb_4X2 = 0;
        arsenal.air_defence = 0;
        arsenal.observation = 0;
        arsenal.sea_mine = 0;

        font.setFamily("Showcard Gothic");
        font.setPointSize(85);
        font_oil.setFamily("Showcard Gothic");
        font_oil.setPointSize(22);
        font_rank.setFamily("Showcard Gothic");
        font_rank.setPointSize(30);

        opacityEffect1->setOpacity(0.7);
        opacityEffect2->setOpacity(0.7);
        opacityEffect3->setOpacity(0.7);
        opacityEffect4->setOpacity(0.7);
        opacityEffect5->setOpacity(0.7);
        opacityEffect6->setOpacity(0.7);

        remain_oil->setGeometry(1120, 82, 160, 160);
        remain_oil->setFont(font_oil);
        remain_oil->setStyleSheet("QLabel { color : black; }");
        remain_oil->setText(QString::number(user_oil));

        rank->setGeometry(775, 80, 160, 160);
        rank->setFont(font_rank);
        rank->setStyleSheet("QLabel { color : black; }");
        rank->setText(QString::number(user_rank));

        QPixmap defence_area_image("C:/SeaBattle_Cute_private/src_graphic/made/airdefence area copy.png");
        defence1->setPixmap(defence_area_image);
        defence1->setGeometry(190, 190, 485, 96);
        defence1->setVisible(false);
        defence2->setPixmap(defence_area_image);
        defence2->setGeometry(190, 330, 485, 96);
        defence2->setVisible(false);
        defence3->setPixmap(defence_area_image);
        defence3->setGeometry(190, 570, 485, 96);
        defence3->setVisible(false);

        // Bomb Atomic
        bomb_atomic->setGeometry(760, 240, 160, 160);
        bomb_atomic->setCursor(Qt::PointingHandCursor);
        bomb_atomic->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
        bomb_atomic_quantity->setGraphicsEffect(opacityEffect1);
        bomb_atomic_quantity->setFont(font);
        bomb_atomic_quantity->setStyleSheet("QLabel { color : green; }");
        bomb_atomic_quantity->setGeometry(45, 20, 100, 100);
        connect(bomb_atomic, &QPushButton::clicked, this, &arselanPage::on_bomb_atomic_Clicked);

        // Bomb 3X3
        bomb_3X3->setGeometry(980, 240, 160, 160);
        bomb_3X3->setCursor(Qt::PointingHandCursor);
        bomb_3X3->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
        bomb_3X3_quantity->setGraphicsEffect(opacityEffect2);
        bomb_3X3_quantity->setFont(font);
        bomb_3X3_quantity->setStyleSheet("QLabel { color : green; }");
        bomb_3X3_quantity->setGeometry(45, 20, 100, 100);
        connect(bomb_3X3, &QPushButton::clicked, this, &arselanPage::on_bomb_3X3_Clicked);

        // Bomb 4X2
        bomb_4X2->setGeometry(1200, 240, 160, 160);
        bomb_4X2->setCursor(Qt::PointingHandCursor);
        bomb_4X2->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
        bomb_4X2_quantity->setGraphicsEffect(opacityEffect3);
        bomb_4X2_quantity->setFont(font);
        bomb_4X2_quantity->setStyleSheet("QLabel { color : green; }");
        bomb_4X2_quantity->setGeometry(45, 20, 100, 100);
        connect(bomb_4X2, &QPushButton::clicked, this, &arselanPage::on_bomb_4X2_Clicked);

        // Sea Mine
        sea_mine->setGeometry(1200, 470, 160, 160);
        sea_mine->setCursor(Qt::PointingHandCursor);
        sea_mine->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
        sea_mine_quantity->setGraphicsEffect(opacityEffect4);
        sea_mine_quantity->setFont(font);
        sea_mine_quantity->setStyleSheet("QLabel { color : green; }");
        sea_mine_quantity->setGeometry(45, 20, 100, 100);
        connect(sea_mine, &QPushButton::clicked, this, &arselanPage::on_sea_mine_Clicked);

        // Observation
        observation->setGeometry(980, 470, 160, 160);
        observation->setCursor(Qt::PointingHandCursor);
        observation->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
        observation_quantity->setGraphicsEffect(opacityEffect5);
        observation_quantity->setFont(font);
        observation_quantity->setStyleSheet("QLabel { color : green; }");
        observation_quantity->setGeometry(45, 20, 100, 100);
        connect(observation, &QPushButton::clicked, this, &arselanPage::on_observation_Clicked);

        // Air Defence
        air_defence->setGeometry(760, 470, 160, 160);
        air_defence->setCursor(Qt::PointingHandCursor);
        air_defence->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
        air_defence_quantity->setGraphicsEffect(opacityEffect6);
        air_defence_quantity->setFont(font);
        air_defence_quantity->setStyleSheet("QLabel { color : green; }");
        air_defence_quantity->setGeometry(45, 20, 100, 100);
        connect(air_defence, &QPushButton::clicked, this, &arselanPage::on_air_defence_Clicked);

        // Next Button
        next->setGeometry(1070, 650, 190, 70);
        next->setCursor(Qt::PointingHandCursor);
        next->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
        connect(next, &QPushButton::clicked, this, &arselanPage::onNextClicked);

        // Reset Button
        reset->setGeometry(815, 664, 50, 50);
        reset->setCursor(Qt::PointingHandCursor);
        reset->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
        connect(reset, &QPushButton::clicked, this, &arselanPage::onResetClicked);

        // Background Image
        QPixmap images("C:/SeaBattle_Cute_private/src_graphic/made/arsenals page copy.png");
        backgroundLabel->setPixmap(images);
        backgroundLabel->setScaledContents(true);
        backgroundLabel->setGeometry(0, 0, 1536, 864);
        backgroundLabel->lower();
    }

public slots:
    void on_bomb_atomic_Clicked()
    {
        if (arsenal.bomb_atomic < 1 && user_rank >= 5 && user_oil >= 100)
        {
            arsenal.bomb_atomic += 1;
            user_oil -= 100;
            bomb_atomic_quantity->setText(QString::number(arsenal.bomb_atomic));
            if (user_oil/100 >= 1)
            {
                remain_oil->move(1120,82);
            }
            else if (user_oil/10 >= 1)
            {
                remain_oil->move(1130,82);
            }
            else if (user_oil >= 1)
            {
                remain_oil->move(1140,82);
            }
            remain_oil->setText(QString::number(user_oil));
        }
    }

    void on_bomb_3X3_Clicked()
    {
        if (arsenal.bomb_3X3 < 3 && user_rank >= 3 && user_oil >= 12)
        {
            arsenal.bomb_3X3 += 1;
            user_oil -= 12;
            bomb_3X3_quantity->setText(QString::number(arsenal.bomb_3X3));
            if (user_oil/100 >= 1)
            {
                remain_oil->move(1120,82);
            }
            else if (user_oil/10 >= 1)
            {
                remain_oil->move(1130,82);
            }
            else if (user_oil >= 1)
            {
                remain_oil->move(1140,82);
            }
            remain_oil->setText(QString::number(user_oil));
        }
    }

    void on_bomb_4X2_Clicked()
    {
        if (arsenal.bomb_4X2 < 3 && user_rank >= 1 && user_oil >= 10)
        {
            arsenal.bomb_4X2 += 1;
            user_oil -= 10;
            bomb_4X2_quantity->setText(QString::number(arsenal.bomb_4X2));
            if (user_oil/100 >= 1)
            {
                remain_oil->move(1120,82);
            }
            else if (user_oil/10 >= 1)
            {
                remain_oil->move(1130,82);
            }
            else if (user_oil >= 1)
            {
                remain_oil->move(1140,82);
            }
            remain_oil->setText(QString::number(user_oil));
        }
    }

    void on_sea_mine_Clicked()
    {
        if (arsenal.sea_mine < 5 && user_rank >= 0 && user_oil >= 5)
        {
            arsenal.sea_mine += 1;
            user_oil -= 5;
            sea_mine_quantity->setText(QString::number(arsenal.sea_mine));
            if (user_oil/100 >= 1)
            {
                remain_oil->move(1120,82);
            }
            else if (user_oil/10 >= 1)
            {
                remain_oil->move(1130,82);
            }
            else if (user_oil >= 1)
            {
                remain_oil->move(1140,82);
            }
            remain_oil->setText(QString::number(user_oil));
        }
    }

    void on_observation_Clicked()
    {
        if (arsenal.observation < 1 && user_rank >= 3 && user_oil >= 15)
        {
            arsenal.observation += 1;
            user_oil -= 15;
            observation_quantity->setText(QString::number(arsenal.observation));
            if (user_oil/100 >= 1)
            {
                remain_oil->move(1120,82);
            }
            else if (user_oil/10 >= 1)
            {
                remain_oil->move(1130,82);
            }
            else if (user_oil >= 1)
            {
                remain_oil->move(1140,82);
            }
            remain_oil->setText(QString::number(user_oil));
        }
    }

    void on_air_defence_Clicked()
    {
        if (arsenal.air_defence < 3 && user_rank >= 2 && user_oil >= 12)
        {
            arsenal.air_defence += 1;

            if (arsenal.air_defence == 1)
            {
                defence1->setVisible(true);
            }
            else if (arsenal.air_defence == 2)
            {
                defence2->setVisible(true);
            }
            else if (arsenal.air_defence == 3)
            {
                defence3->setVisible(true);
            }

            user_oil -= 12;
            air_defence_quantity->setText(QString::number(arsenal.air_defence));
            if (user_oil / 100 >= 1)
            {
                remain_oil->move(1120, 82);
            }
            else if (user_oil / 10 >= 1)
            {
                remain_oil->move(1130, 82);
            }
            else if (user_oil >= 1)
            {
                remain_oil->move(1140, 82);
            }
            remain_oil->setText(QString::number(user_oil));
        }
    }

    void onNextClicked()
    {
        // Your code here for next button functionality
    }

    void onResetClicked()
    {
        user_oil += (arsenal.bomb_atomic * 100) +
                    (arsenal.bomb_3X3 * 12) +
                    (arsenal.bomb_4X2 * 10) +
                    (arsenal.air_defence * 12) +
                    (arsenal.observation * 15) +
                    (arsenal.sea_mine * 5);

        arsenal.bomb_atomic = 0;
        arsenal.bomb_3X3 = 0;
        arsenal.bomb_4X2 = 0;
        arsenal.air_defence = 0;
        arsenal.observation = 0;
        arsenal.sea_mine = 0;

        defence1->setVisible(false);
        defence2->setVisible(false);
        defence3->setVisible(false);

        bomb_atomic_quantity->setText("");
        air_defence_quantity->setText("");
        observation_quantity->setText("");
        sea_mine_quantity->setText("");
        bomb_4X2_quantity->setText("");
        bomb_3X3_quantity->setText("");

        if (user_oil / 100 >= 1)
        {
            remain_oil->move(1120, 82);
        }
        else if (user_oil / 10 >= 1)
        {
            remain_oil->move(1130, 82);
        }
        else if (user_oil >= 1)
        {
            remain_oil->move(1140, 82);
        }
        remain_oil->setText(QString::number(user_oil));
    }

private:
    QPoint lastClickPosition;
    bool waitingForClick;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    arselanPage w;
    w.setGeometry(0, 0, 1536, 864);
    w.show();
    return a.exec();
}

#include "main.moc" // Ensure this is at the end for the Q_OBJECT macro
