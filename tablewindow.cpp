#include "tablewindow.h"

tablewindow::tablewindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tablewindow)
{
    ui->setupUi(this);
    loadingTableView();

    connect(ui->addTableBtn,SIGNAL(clicked()),this,SLOT(addTable()));
    connect(ui->addRowBtn,SIGNAL(clicked()),this,SLOT(addRow()));

}
//добавление пкстой сроки
void tablewindow::addRow()
{
    int lastRow = model->rowCount();
        model->insertRow(lastRow);
}


//Заполнение первых строк по умолчанию
void tablewindow::loadingTableView()
{
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


    model = new QStandardItemModel();

QList<QStandardItem*> lst;

               QStandardItem* item = new QStandardItem(0,0);
               item->setText("ID");
               lst<<item;
               item = new QStandardItem(0,1);
               item->setText("SERIAL PRIMARY KEY");
               lst<<item;
               model->appendRow(lst);

QList<QStandardItem*> list2;

               item = new QStandardItem(0,0);
               item->setText("Name");
               list2<<item;
               item = new QStandardItem(0,1);
               item->setText("CHARACTER VARYING(30)");
               list2<<item;
               model->appendRow(list2);

       model->setHeaderData(0, Qt::Horizontal, tr("Имя"));
           model->setHeaderData(1, Qt::Horizontal, tr("Тип"));
       ui->tableView->setModel(model);

}

//Добавление таблицы и сохранения файла с расширением .sql
void tablewindow::addTable()
{

if(ui->lineName->text()!="")
    {
        QString sqlAddTable = "CREATE TABLE "+ui->lineName->text()+"\n(\n";
        int lastRow = model->rowCount();
        QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->tableView->model());
        for(int i=0;i<lastRow;i++)
        {
            QString colum = model->item(i,0)->text();
            QString colum2 = model->item(i,1)->text();
            sqlAddTable=sqlAddTable+colum+" "+colum2+",\n";
        }
        sqlAddTable.chop(2);
        sqlAddTable=sqlAddTable+"\n);";

        QString fileName = QString("TBL_"+ui->lineName->text()+".sql");
        QString fileN=
                   QFileDialog::getSaveFileName( this,
                                                 tr("Сохранить файл как"),
                                                 fileName,
                                                 tr("SQL(*.sql)"));

        QFile file(fileN);
        if(!fileN.isEmpty() &&file.open(QIODevice::WriteOnly) )

                {
                    QTextStream stream(&file);
                    stream << sqlAddTable;
                    file.close();
                    QFileInfo fileinfo(file);
                    qint64 size=fileinfo.size();
                    QSqlQuery query;
                  query.prepare("INSERT INTO " TABLE_FILES " ( " TABLE_FILENAME ", "
                                                           TABLE_FILESYSPATH ", "
                                                           TABLE_FILESIZE " ) "
                               "VALUES (:NAME, :PATH, :SIZE )");
                  query.bindValue(":NAME",fileName);
                  query.bindValue(":PATH",fileN);
                  query.bindValue(":SIZE",size);
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
}

tablewindow::~tablewindow()
{
    delete ui;
}
