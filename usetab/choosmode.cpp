#include "choosmode.h"

// #include "choose_play_mode.h"

choose_play_mode::choose_play_mode() : QMainWindow()
{
    CA_boarder_X = 843;
    CA_boarder_Y = 535;
    BWF = "W";
    CA = "A";

    backgroundLabel = new QLabel(this);
    BWF_boarder = new QLabel(this);
    CA_boarder = new QLabel(this);

    QPushButton* VS_Bot = new QPushButton(this);
    VS_Bot->setGeometry(1038, 227, 215, 215);
    VS_Bot->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
    VS_Bot->setCursor(Qt::PointingHandCursor);
    connect(VS_Bot, &QPushButton::clicked, this, &choose_play_mode::onVSBotClicked);

    QPushButton* with_friend = new QPushButton(this);
    with_friend->setGeometry(660, 227, 215, 215);
    with_friend->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
    with_friend->setCursor(Qt::PointingHandCursor);
    connect(with_friend, &QPushButton::clicked, this, &choose_play_mode::onWithFriendClicked);

    QPushButton* WIFI = new QPushButton(this);
    WIFI->setGeometry(290, 227, 215, 215);
    WIFI->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
    WIFI->setCursor(Qt::PointingHandCursor);
    connect(WIFI, &QPushButton::clicked, this, &choose_play_mode::onWIFIClicked);

    QPushButton* AD_mode = new QPushButton(this);
    AD_mode->setGeometry(860, 551, 390, 60);
    AD_mode->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
    AD_mode->setCursor(Qt::PointingHandCursor);
    connect(AD_mode, &QPushButton::clicked, this, &choose_play_mode::onADModeClicked);

    QPushButton* CL_mode = new QPushButton(this);
    CL_mode->setGeometry(298, 551, 390, 60);
    CL_mode->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
    CL_mode->setCursor(Qt::PointingHandCursor);
    connect(CL_mode, &QPushButton::clicked, this, &choose_play_mode::onCLModeClicked);

    QPushButton* next = new QPushButton(this);
    next->setGeometry(670, 660, 190, 70);
    next->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
    next->setCursor(Qt::PointingHandCursor);
    connect(next, &QPushButton::clicked, this, &choose_play_mode::onNextClicked);

    QPixmap images("E:/qt1/drg/playModepage.png");
    backgroundLabel->setPixmap(images);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(0, 0, 1536, 864); // Set the geometry of the background label to cover the entire window
    backgroundLabel->lower(); // Send the background label to the back

    QPixmap BWF_image("E:/qt1/drg/selectionboarder2.png");
    BWF_boarder->setPixmap(BWF_image);
    BWF_boarder->setScaledContents(true);
    BWF_boarder->setGeometry(270, 215, 245, 245); // Set the geometry of the background label to cover the entire window

    QPixmap CA_image("E:/qt1/drg/selectionboarder1.png");
    CA_boarder->setPixmap(CA_image);
    CA_boarder->setScaledContents(true);
    CA_boarder->setGeometry(840, 535, 420, 95); // Set the geometry of the background label to cover the entire window
}

void choose_play_mode::onVSBotClicked()
{
    BWF_boarder->move(1013, 215);
    BWF ="B";
}

void choose_play_mode::onWithFriendClicked()
{
    BWF_boarder->move(639, 215);
    BWF = "F";
}

void choose_play_mode::onWIFIClicked()
{
    BWF_boarder->move(270, 215);
    BWF = "W";
}

void choose_play_mode::onADModeClicked()
{
    CA_boarder->move(840, 535);
    CA = "A";
}

void choose_play_mode::onCLModeClicked()
{
    CA_boarder->move(277, 535);
    CA = "C";
}

void choose_play_mode::onNextClicked()
{
}
