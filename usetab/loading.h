#ifndef LOADING_H
#define LOADING_H

#include <QFrame>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>

class LoadingPage : public QFrame {
    Q_OBJECT

public:
    LoadingPage(QWidget *parent = nullptr);

private:
    QLabel *backgroundLabel;
    QProgressBar *bar;
    QTimer *timer;

signals:
    void loadingFinished();
};

#endif // LOADING_H
