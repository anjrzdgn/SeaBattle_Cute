#include "loading.h"

// #include "loadingpage.h"

#include <QPixmap>
#include <QApplication>

LoadingPage::LoadingPage(QWidget *parent) : QFrame(parent) {
    backgroundLabel = new QLabel(this);
    QPixmap backgroundPixmap("E:/qt1/drg/loadinghole.png");
    backgroundLabel->setPixmap(backgroundPixmap);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(0, 0, 1536, 864);
    backgroundLabel->lower();
    backgroundLabel->setAcceptDrops(false);

    bar = new QProgressBar(this);
    bar->setGeometry(605, 655, 393, 15);
    bar->setRange(0, 500); // Set the range of the progress bar

    timer = new QTimer(this);
    bool loadingFinishedEmitted = false; // Flag to track whether the signal has been emitted

    connect(timer, &QTimer::timeout, [this, &loadingFinishedEmitted]() {
        static int progress = 0;
        this->bar->setValue(progress);
        progress += 10;
        if (progress >= 500 &&!loadingFinishedEmitted) {
            // Emit the loadingFinished signal when the progress bar is full
            emit this->loadingFinished();
            loadingFinishedEmitted = true; // Set the flag to true
            // qApp->quit();
            // this->close();
        }
    });
    timer->start(100); // Start the timer with an interval of 100ms
}
