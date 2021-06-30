#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "ui_startwindow.h"
#include "database.h"
#include "mainwindow.h"

#include <QCoreApplication>
#include <QLineEdit>
#include <QMessageBox>
#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void loadMain();
public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
private:
    Ui::StartWindow *ui;
    MainWindow *mainW;
};

#endif // STARTWINDOW_H
