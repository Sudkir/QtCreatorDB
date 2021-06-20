#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QSqlTableModel>
#include "database.h"
#include "tablewindow.h"


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
    void handleButton();
    void createTable();
private:
Ui::MainWindow  *ui;
    //объекты для взаимодействия с информацией в базе данных
    //и моделью представления таблицы базы данных
    DataBase        *db;
    DataBase        *dbEmpty;
    QSqlTableModel  *model;
    tablewindow *tableW;//переменная окна table

QPushButton *m_button;
private:
    //которые формируют модель и внешний вид TableView
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
    void createDB( QString nameDB, QString nameUser, QString userPassword);


protected:
    // изменение размера компонентов в след за окном
    virtual void resizeEvent(QResizeEvent *);

};
#endif // MAINWINDOW_H
