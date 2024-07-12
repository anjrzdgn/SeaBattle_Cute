#ifndef CHOOSMODE_H
#define CHOOSMODE_H


#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

class choose_play_mode : public QMainWindow
{
    Q_OBJECT

public:
    choose_play_mode();

    int CA_boarder_X;
    int CA_boarder_Y;
    QString BWF;
    QString CA;

private:
    QLabel *backgroundLabel;
    QLabel *BWF_boarder;
    QLabel *CA_boarder;

private slots:
    void onVSBotClicked();
    void onWithFriendClicked();
    void onWIFIClicked();
    void onADModeClicked();
    void onCLModeClicked();
    void onNextClicked();
signals:
    void send_BWF(QString);
    void send_CA(QString);
    void mode_to_arreng();
};



#endif // CHOOSMODE_H
