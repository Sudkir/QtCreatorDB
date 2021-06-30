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
#include <QMessageBox>
#include <QFileInfo>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "ExampleDataBase"
#define DATABASE_NAME       "DataBase.db"
//name table in DB
#define TABLE_USERS                   "users"
#define TABLE_FILES                   "files"
//Таблица Пользователь
#define TABLE_FNAME "firstname"
#define TABLE_SNAME "lastname"
#define TABLE_TEL "tel"
//Новая база данных
#define TABLE_DBNAME "dbname"
#define TABLE_USERNAME "username"
#define TABLE_USERPASSWORD "userPassword"
//Значения таблицы
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
    void closeDataBase();
private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    SearchDB;
    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBase();

};

#endif // DATABASE_H
