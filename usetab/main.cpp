#include "mainwindow.h"

#include <QApplication>
#include <QMediaPlayer>

#include <QMediaPlayer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(0,0,1536,864);
    w.setWindowTitle("Sea Battle V.1 CuteCo");
    w.setWindowIcon(QIcon("E:/qt1/usetab/logo.png"));

    // QMediaPlayer *player = new QMediaPlayer();
    // player->setm
    // QMediaPlaylist *playlist = new QMediaPlaylist();
    // playlist->addMedia(QUrl::fromLocalFile("E:/qt1/usetab/BGMusic.mp3"));
    // playlist->setPlaybackMode(QMediaPlaylist::Loop);
    // player->setPlaylist(playlist);
    // player->play();

    w.show();
    return a.exec();
}
#include "main.moc"
