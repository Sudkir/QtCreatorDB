#include "tablewindow.h"
#include "ui_tablewindow.h"
#include <QStandardItem>
#include <QCoreApplication>
#include <QListView>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QSqlQuery>
#include <database.h>


//void setupModel ();


tablewindow::tablewindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tablewindow)
{
    ui->setupUi(this);
    loadTableView();
    //




    connect(ui->addTableBtn,SIGNAL(clicked()),this,SLOT(addTable()));
    connect(ui->addRowBtn,SIGNAL(clicked()),this,SLOT(addRow()));

}
void tablewindow::addRow()
{
    int lastRow = model->rowCount();
        model->insertRow(lastRow);
}

void tablewindow::loadTableView()
{
    model = new QStandardItemModel();


    /*
CREATE TABLE customers
(
    Id SERIAL PRIMARY KEY,
    FirstName CHARACTER VARYING(30),
    LastName CHARACTER VARYING(30),
    Email CHARACTER VARYING(30),
    Age INTEGER
);
*/

QList<QStandardItem*> lst;

               QStandardItem* item = new QStandardItem(0,0);
               item->setText("ID");
               lst<<item;
               item = new QStandardItem(0,1);
               item->setText("SERIAL PRIMARY KEY");
               lst<<item;
               model->appendRow(lst);

QList<QStandardItem*> lstr;

               item = new QStandardItem(0,0);
               item->setText("Name");
               lstr<<item;
               item = new QStandardItem(0,1);
               item->setText("CHARACTER VARYING(30)");
               lstr<<item;
               model->appendRow(lstr);

       model->setHeaderData(0, Qt::Horizontal, tr("Имя"));
           model->setHeaderData(1, Qt::Horizontal, tr("Тип"));
       ui->tableView->setModel(model);

}

void tablewindow::addTable()
{

if(ui->lineName->text()!="")
    {
        QString sqlAddTable = "CREATE TABLE "+ui->lineName->text()+"\n(\n";
        int lastRow = model->rowCount();
        QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->tableView->model());
        for(int i=0;i<lastRow;i++)
        {
            QString Colum0 = model->item(i,0)->text();
            QString Colum1 = model->item(i,1)->text();
            sqlAddTable=sqlAddTable+Colum0+" "+Colum1+",\n";
        }
        sqlAddTable.chop(2);
        sqlAddTable=sqlAddTable+"\n);";

        QString fileName = QString("TBL_"+ui->lineName->text()+".sql");
        QString fileN=
                   QFileDialog::getSaveFileName( this,
                                                 tr("Сохранить файл как"),
                                                 fileName,
                                                 tr("SQL(*.sql)")
                                                 );

        QFile file(fileN);
        if(!fileN.isEmpty() &&file.open(QIODevice::WriteOnly) )

                {
                    QTextStream stream(&file);
                    stream << sqlAddTable;
                    file.close();

                    // Определяем размер файла с помощью метода size()
                    qint64 size=0;
                    QFileInfo fileinfo(file);
                    size = fileinfo.size();

                    //запрос на добавление в таблицу
                    QSqlQuery query;
                  query.prepare("INSERT INTO " TABLE_FILES " ( " TABLE_FILENAME ", "
                                                           TABLE_FILESYSPATH ", "
                                                           TABLE_FILESIZE " ) "
                               "VALUES (:NAME, :PATH, :SIZE )");
                  query.bindValue(":NAME",fileName);
                  query.bindValue(":PATH",fileN);
                  query.bindValue(":SIZE",size);
                  // После чего выполняется запросом методом exec()
                  if(!query.exec()){
                      QMessageBox::warning(0, QObject::tr("Ошибка БД!"), query.lastError().text());
                  }
        }


        this->hide();
    }
else
    {
        QMessageBox::warning(0, QObject::tr("Ошибка!"),"Введите название таблицы");
    }





        // Разрешаем выделение строк
        //ui->listView->setSelectionBehavior(QAbstractItemView::SelectRows);
        // Устанавливаем режим выделения лишь одно строки в таблице
        //ui->listView->setSelectionMode(QAbstractItemView::SingleSelection);
        //ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);



        /*

добавиить цикл считывания всего тэбл виев
добавить окно сохранения
авто бодгон размеров
кнопка добавления количесва строк
поле для названия таблицы

       for(int row = 0;row<2;row++)
       {
           QList<QStandardItem*> lst;
           for(int column = 0;column<2;column++)
           {
               QStandardItem* item = new QStandardItem(row,column);
               item->setText("");
               lst<<item;
           }

           model->appendRow(lst);
       }
       mode

*/
}

tablewindow::~tablewindow()
{
    delete ui;
}
