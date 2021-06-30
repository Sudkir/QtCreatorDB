#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database.h"
#include "ui_mainwindow.h"
#include "tablewindow.h"

#include <QMainWindow>
#include <QPushButton>
#include <QSqlTableModel>
#include <QCoreApplication>
#include <QMessageBox>
#include <QFileDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
private slots:
    //функция книпки
    void addDB();
    void createTable();
    void addKey();
private:
Ui::MainWindow  *ui;
    //объекты для взаимодействия с информацией в базе данных
    //и моделью представления таблицы базы данных
    DataBase        *db;
    QFile *files;
    QSqlTableModel  *model;
    tablewindow *tableW;

private:

    void updateView();
    bool addFile(QString Name,QString File);

    //которые формируют модель и внешний вид TableView
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();

};
#endif // MAINWINDOW_H
