#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "infodio.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    InfoDio* info=new InfoDio(this);
    info-> show();
    connect(info,SIGNAL(send_username(QString)),this,SLOT(get_user(QString)));
    connect(info,SIGNAL(send_pass(QString)),this,SLOT(get_pass(QString)));

}

void MainWindow::get_user(QString user)
{
    this->Username=user;

}

void MainWindow::get_pass(QString pass)
{
    this->Pass=pass;
}



void MainWindow::on_pushButton_clicked()
{
    // QByteArray hash = QCryptographicHash::hash(ui->lineEdit->text().toUtf8(), QCryptographicHash::Sha256);
    if(Username==(ui->lineEdit->text())&& Pass==(ui->lineEdit_2->text())){
        qDebug()<<"success!"<<Username;
    }else {
        qDebug()<<"failed!"<<Username;
    }
}

