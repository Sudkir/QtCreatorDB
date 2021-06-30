#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include "ui_tablewindow.h"
#include "database.h"

#include <QWidget>
#include <QStandardItem>
#include <QDialog>
#include <QCoreApplication>
#include <QListView>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QSqlQuery>

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
    void loadingTableView();
};

#endif // TABLEWINDOW_H
