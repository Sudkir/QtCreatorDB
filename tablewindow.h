#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QWidget>

#include <QDialog>


namespace Ui {
class tablewindow;
}

class tablewindow : public QDialog
{
    Q_OBJECT

public:
    explicit tablewindow(QWidget *parent = nullptr);
    ~tablewindow();

private:
    Ui::tablewindow *ui;
};

#endif // TABLEWINDOW_H
