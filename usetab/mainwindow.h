#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTabBar>
#include <QString>




QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTabWidget *tabs;
    QString _bwf;
    QString _ca;

 // declare the slot
public slots:
    void switchToTab3();
    void switchToTab4();
    void switchToTab5();
    void switchToTab6();
    void ChoosReg_to_ligin();
    void ChoosReg_to_signup();

    void get_BWF(QString);
    void get_CA(QString);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
