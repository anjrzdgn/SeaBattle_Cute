#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTabBar>




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

 // declare the slot
public slots:
    void switchToTab3();
    void switchToTab4();
    void switchToTab5();
    void ChoosReg_to_ligin();
    void ChoosReg_to_signup();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
