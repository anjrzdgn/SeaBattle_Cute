#include "mainwindow.h"
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QDataStream>
#include <QByteArray>
#include <QLabel>
#include <QFrame>
#include <QPixmap>
#include <QPoint>
#include <QMouseEvent>
#include <QDropEvent>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFrame>
#include <QProgressBar>
#include <QTimer>

class CompanyPage : public QFrame {
    Q_OBJECT

public:
    CompanyPage(QWidget *parent = nullptr) : QFrame(parent) {
        QLabel *backgroundLabel = new QLabel(this);
        QPixmap backgroundPixmap("E:/qt1/drg/companylogo.png");
        backgroundLabel->setPixmap(backgroundPixmap);
        backgroundLabel->setScaledContents(true);
        backgroundLabel->setGeometry(0, 0, 1536, 864);
        backgroundLabel->lower();
        backgroundLabel->setAcceptDrops(false);
    }
};

class LoadingPage : public QFrame {
    Q_OBJECT

public:
    LoadingPage(QWidget *parent = nullptr) : QFrame(parent) {
        QLabel *backgroundLabel = new QLabel(this);
        QPixmap backgroundPixmap("E:/qt1/drg/loadinghole.png");
        backgroundLabel->setPixmap(backgroundPixmap);
        backgroundLabel->setScaledContents(true);
        backgroundLabel->setGeometry(0, 0, 1536, 864);
        backgroundLabel->lower();
        backgroundLabel->setAcceptDrops(false);

        QProgressBar *bar = new QProgressBar(this);
        bar->setGeometry(605, 655, 393, 15);
        bar->setRange(0, 1000); // Set the range of the progress bar

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, [bar]() {
            static int progress = 0;
            bar->setValue(progress);
            progress += 10;
            if (progress >= 1000) {
                // Close the window when the progress bar is full
                qApp->quit();
            }
        });
        timer->start(100); // Start the timer with an interval of 100ms
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    CompanyPage companypage;
    companypage.setGeometry(QRect(0, 0, 1536, 864));
    companypage.show();

    // _sleep(4000);

    LoadingPage loadingpage;
        loadingpage.setGeometry(QRect(0, 0, 1536, 864));
        loadingpage.show();


    // QTimer::singleShot(4000, [&]() {
    //     // Hide the CompanyPage and show the LoadingPage
    //     companypage.hide();

    //     LoadingPage loadingpage;
    //     loadingpage.setGeometry(QRect(0, 0, 1536, 864));
    //     loadingpage.show();

    //     QTimer::singleShot(10000, [&]() {
    //         // Close the window after 10 seconds
    //         qApp->quit();
    //     });
    // });

    return a.exec();
}

#include "main.moc"
