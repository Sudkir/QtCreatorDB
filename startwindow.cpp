#include "startwindow.h"
#include "ui_startwindow.h"
#include <QCoreApplication>
#include <QLineEdit>
#include <QMessageBox>
#include "database.h"



StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    connect(ui->acceptBtn,SIGNAL(clicked()),this,SLOT(loadMain()));
}

StartWindow::~StartWindow()
{
    delete ui;
}


/* В начале SQL запрос формируется с ключами,
 * которые потом связываются методом bindValue
 * для подстановки данных из QVariantList
 * затем открытие основного рабочего окна
 * */



void StartWindow::loadMain()
{
    QString FNameStr,SNameStr,TelStr;
    FNameStr=ui->lineEdit->text();
    SNameStr=ui->lineEdit_2->text();
    TelStr=ui->lineEdit_3->text();


      QSqlQuery query;
    query.prepare("INSERT INTO " TABLE_USERS " ( " TABLE_FNAME ", "
                                             TABLE_SNAME ", "
                                             TABLE_TEL " ) "
                  "VALUES (:FName, :SName, :Tel )");
    query.bindValue(":FName",        FNameStr);
    query.bindValue(":SName",        SNameStr);
    query.bindValue(":Tel",      TelStr);
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        QMessageBox::warning(0, QObject::tr("Ошибка БД!"), query.lastError().text());
    }

    this->hide();
    mainW = new MainWindow;
    mainW->show();
}

