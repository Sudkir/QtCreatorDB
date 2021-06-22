#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QWidget>
#include <QStandardItem>
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
private slots:
    void addTable();
    void addRow();
private:
    Ui::tablewindow *ui;
    QStandardItemModel  *model;
    void loadTableView();


public:


};

#endif // TABLEWINDOW_H
