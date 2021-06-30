#include "database.h"


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


/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
   SearchDB.close();
}


