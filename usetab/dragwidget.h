#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QDropEvent>
#include <vector>
#include <utility>
#include "ship.h"
#include "board.h"

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    ClickableLabel(QWidget *parent = nullptr) : QLabel(parent) {}

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override {
        emit clicked();
        QLabel::mousePressEvent(event);
    }
};

class DragWidget : public QFrame {
    Q_OBJECT

public:
    QLabel *backgroundLabel1;
    QLabel *backgroundLabel;
    ClickableLabel *houseIcon1;

    Board check_and_fill;

    DragWidget(QWidget *parent = nullptr);

public slots:
    void onNextButtonClicked();
    void restore_all_ship();
    void rotateShips();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
signals:
    void ARG();
};

#endif // DRAGWIDGET_H
