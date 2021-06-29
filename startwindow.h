#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <mainwindow.h>
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
    MainWindow *mainW;//переменная окна main
};

#endif // STARTWINDOW_H
