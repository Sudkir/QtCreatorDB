#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "ExampleDataBase"
#define DATABASE_NAME       "DataBase.db"
//name table in DB
#define TABLE_USERS                   "users"
#define TABLE_FILES                   "files"
//test db
#define TABLE_DATE              "Date"
#define TABLE_TIME              "Time"
#define TABLE_MESSAGE           "Message"
#define TABLE_RANDOM            "Random"
//table users
#define TABLE_FNAME "firstname"
#define TABLE_SNAME "lastname"
#define TABLE_TEL "tel"
//new DB
#define TABLE_DBNAME "dbname"
#define TABLE_USERNAME "username"
#define TABLE_USERPASSWORD "userPassword"
//table files
#define TABLE_FILENAME "filename"
#define TABLE_FILESYSPATH "filesyspath"
#define TABLE_FILESIZE "filesize"




class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBase();
     void connectToEmptyDataBase();
    bool inserIntoTable(const QVariantList &data);
    void closeEmptyDataBase();
    void closeDataBase();

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    SearchDB;
    QSqlDatabase EmptyDB;

private:
    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBase();

    bool restoreDataBase();
    void openEmptyDataBase();

    bool createTable();
};

#endif // DATABASE_H
