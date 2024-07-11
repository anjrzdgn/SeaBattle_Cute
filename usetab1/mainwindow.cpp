#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "companypage.h"
#include "login.h"
#include "signup.h"
#include "choosreg.h" // include the ChoosReg header file
#include "choosmode.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tabs = new QTabWidget(this);
    // tabs->setTabBarAutoHide(true);
    tabs->setGeometry(0, 0, 1536, 864);
    // tabs->setTabBarAutoHide(true);
    // tabs->tabBar()->setVisible(false);





    QWidget *tab2 = new QWidget;
    QWidget *tab3 = new QWidget;
    QWidget *tab4 = new QWidget; // new tab
    QWidget *tab5 = new QWidget; // new tab
    QWidget *tab6 = new QWidget; // new tab









    tabs->addTab(tab2, "Tab 2");
    tabs->addTab(tab3, "Tab 3");
    tabs->addTab(tab4, "Tab 4"); // add the new tab
    tabs->addTab(tab5, "Tab 5");
    tabs->addTab(tab6, "Tab 6");

    // Create a LogIn instance and add it to tab3
    // LogIn *logIn = new LogIn;
    ChoosReg *choosReg = new ChoosReg; // Create a ChoosReg instance
    QVBoxLayout *tab3Layout = new QVBoxLayout(tab3);
    tab3Layout->addWidget(choosReg); // Add ChoosReg to tab3


    // Create an instance of CompanyPage and add it to tab2
    CompanyPage *companyPage = new CompanyPage(tab2);
    QVBoxLayout *tab2Layout = new QVBoxLayout(tab2);
    tab2Layout->addWidget(companyPage);

    // Create an instance of Login and add it to tab4
    LogIn *logIn = new LogIn;
    QVBoxLayout *tab4Layout = new QVBoxLayout(tab4);
    tab4Layout->addWidget(logIn);

    // Create an instance of SignUp and add it to tab5
    SignUp *signUp = new SignUp;
    QVBoxLayout *tab5Layout = new QVBoxLayout(tab5);
    tab5Layout->addWidget(signUp);


    choose_play_mode *chooseMode = new choose_play_mode; // Create a choose_play_mode instance
    QVBoxLayout *tab6Layout = new QVBoxLayout(tab6);
    tab6Layout->addWidget(chooseMode); // Add choose_play_mode to tab4

    connect(companyPage, &CompanyPage::goToTab3, this, &MainWindow::switchToTab3);
    connect(choosReg, &ChoosReg::gologin, this, &MainWindow::ChoosReg_to_ligin);
    connect(choosReg, &ChoosReg::goSignup, this, &MainWindow::ChoosReg_to_signup);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// void MainWindow::switchToTab2()
// {
//     tabs->setCurrentIndex(2); // switch to tab 2
// }

void MainWindow::switchToTab3() {
    tabs->setCurrentIndex(1); // switch to tab 3
}

void MainWindow::ChoosReg_to_ligin() {
    tabs->setCurrentIndex(2); // switch to tab 4
}

void MainWindow::ChoosReg_to_signup() {
    tabs->setCurrentIndex(3); // switch to tab 5
}
