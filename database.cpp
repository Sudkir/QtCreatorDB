#include "database.h"
#include <QMessageBox>
#include <QFileInfo>

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
        this->openDataBase();
}

void DataBase::addFile(QString Name,QString Path,QString File)
{
    QFile file(Path);
    if(!Path.isEmpty() &&file.open(QIODevice::WriteOnly) )

            {
                QTextStream stream(&file);
                stream << File;
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
              query.bindValue(":NAME",Name);
              query.bindValue(":PATH",Path);
              query.bindValue(":SIZE",size);
              // После чего выполняется запросом методом exec()
              if(!query.exec()){
                  QMessageBox::warning(0, QObject::tr("Ошибка БД!"), query.lastError().text());
              }
            }
}


void DataBase::connectToEmptyDataBase()
{
        this->openEmptyDataBase();
}

/* Метод для открытия базы данных
 * */
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    SearchDB = QSqlDatabase::addDatabase("QPSQL");
    SearchDB.setDatabaseName("test");
    SearchDB.setUserName("postgres");
    SearchDB.setHostName("localhost");
    SearchDB.setPassword("12345");
//SearchDB.setHostName("127.0.0.1");
    SearchDB.setPort(5432);
    if(!SearchDB.open())
    {
        QMessageBox::warning(0, QObject::tr("Ошибка БД!"), SearchDB.lastError().text());
    return false;
    }
    else
    {return false;
    }


}

void DataBase::openEmptyDataBase()
{
    EmptyDB = QSqlDatabase::addDatabase("QPSQL");
    EmptyDB.setHostName("localhost");
    EmptyDB.setPort(5432);
    if(!EmptyDB.open())
        QMessageBox::warning(0, QObject::tr("Ошибка БД!"), EmptyDB.lastError().text());
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
   SearchDB.close();
}
void DataBase::closeEmptyDataBase()
{
   EmptyDB.close();
}

/* Метод для создания таблицы в базе данных
 * */
bool DataBase::createTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE_USERS " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            TABLE_DATE      " DATE            NOT NULL,"
                            TABLE_TIME      " TIME            NOT NULL,"
                            TABLE_RANDOM    " INTEGER         NOT NULL,"
                            TABLE_MESSAGE   " VARCHAR(255)    NOT NULL"
                        " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE_USERS;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Метод для вставки записи в базу данных
 * */
bool DataBase::inserIntoTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " TABLE_USERS " ( " TABLE_DATE ", "
                                             TABLE_TIME ", "
                                             TABLE_RANDOM ", "
                                             TABLE_MESSAGE " ) "
                  "VALUES (:Date, :Time, :Random, :Message )");
    query.bindValue(":Date",        data[0].toDate());
    query.bindValue(":Time",        data[1].toTime());
    query.bindValue(":Random",      data[2].toInt());
    query.bindValue(":Message",     data[3].toString());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE_USERS;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
