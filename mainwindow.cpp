#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QFileDialog>



MainWindow::MainWindow(QWidget *parent)

: QMainWindow(parent),
  ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //объект БД
    db = new DataBase();
    //инициализировать подключение к базе данных
    db->connectToDataBase();
    updateView();
    //обработчик кнопки
    connect(ui->AddDBBtn, SIGNAL (clicked()), this, SLOT (handleButton()));
    connect(ui->AddTableBtn, SIGNAL (clicked()), this, SLOT (createTable()));
    connect(ui->AddKeybtn, SIGNAL (clicked()), this, SLOT (addKey()));
}


void MainWindow::updateView()
{
    //Инициализируем модель для представления данных с заданием названий колонок
   this->setupModel(TABLE_FILES,
                    QStringList() << QString ("id")
                                  << QString("Имя")
                                  << QString("Расположение")
                                  << QString("Вес"));

   // Инициализируем внешний вид таблицы с данными
   this->createUI();
}



/* Метод для инициализации модеи представления данных
 * */
void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    /* Производим инициализацию модели представления данных
     * с установкой имени таблицы в базе данных, по которому
     * будет производится обращение в таблице
     * */
    model = new QSqlTableModel(this);
    model->setTable(tableName);

    /* Устанавливаем названия колонок в таблице с сортировкой данных
     * */
    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    // Устанавливаем сортировку по возрастанию данных по нулевой колонке
    model->setSort(0,Qt::AscendingOrder);
}

void MainWindow::createUI(){
    ui->tableViewDB->setModel(model);     // Устанавливаем модель на TableView
    ui->tableViewDB->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->tableViewDB->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tableViewDB->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->tableViewDB->resizeColumnsToContents();
    ui->tableViewDB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //размер по содержимому
    ui->tableViewDB->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableViewDB->horizontalHeader()->setStretchLastSection(true);

    model->select(); // Делаем выборку данных из таблицы
}



void MainWindow::createDB( QString nameDB,  QString nameUser,  QString userPassword)
{

    //CREATE USER test_user WITH password 'qwerty';
    //CREATE DATABASE test_database OWNER test_user;

    QString sqlDB = QString ("CREATE USER '%1' WITH password '%2'\nCREATE DATABASE '%3' OWNER '%4'")
                            .arg(nameUser,userPassword,nameDB,nameUser);
    //окно сохранения файла
    QString fileName = QString("DB_"+nameDB+"_"+nameUser+".sql");
    QString fileN=
               QFileDialog::getSaveFileName( this,
                                             tr("Сохранить файл как"),
                                             fileName,
                                             tr("SQL(*.sql)")
                                             );
    qint64 size=0;
    QFile file(fileN);
    if(!fileN.isEmpty() &&file.open(QIODevice::WriteOnly) )

            {
                QTextStream stream(&file);
                stream << sqlDB;
                file.close();
                // Определяем размер файла с помощью метода size()
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
    else
    {
         QMessageBox::warning(0, QObject::tr("Ошибка!"),"Выбран неверный путь.");
    }


}

// обработчик изменение размера окна
void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    //ui->tableViewDB->setSizeIncrement(QSize());
}


void MainWindow::createTable()
{
    int rowidx = ui->tableViewDB->selectionModel()->currentIndex().row();

        QString IDDB=(model->index(rowidx , 0).data().toString());//id
        ui->db_name->setText(model->index(rowidx , 1).data().toString());//name
        QString NameDB=(model->index(rowidx , 1).data().toString());
        if(NameDB[0]=='D'&&NameDB[1]=='B')
        {
            tableW = new tablewindow;
            tableW->exec();
            if(tableW->close())
            {
                updateView();
            }
        }
        else
        {
            QMessageBox::warning(0, QObject::tr("Ошибка!"),"Выбрана не База Данных.\nВыберите файл, который начинается с \"DB_\"");
        }

}

void MainWindow::createKey(QString nameTbl1, QString nameColumn1, QString nameTbl2, QString nameColumn2)
{
    //ALTER TABLE table1 ADD FOREING KEY (colum1) REFERENCES table2(column2);
    QString sqlKey = QString ("ALTER TABLE '%1' ADD FOREING KEY ('%2') REFERENCES '%3'('%4);").arg(nameTbl1,  nameColumn1,  nameTbl2,  nameColumn2);
    QString fileName = QString("KEY_"+nameTbl1+"_("+nameColumn1+").sql");
    QString fileN=
               QFileDialog::getSaveFileName( this,
                                             tr("Сохранить файл как"),
                                             fileName,
                                             tr("SQL(*.sql)")
                                             );
    qint64 size=0;
    QFile file(fileN);
    if(!fileN.isEmpty() &&file.open(QIODevice::WriteOnly) )

            {
                QTextStream stream(&file);
                stream << sqlKey;
                file.close();
                // Определяем размер файла с помощью метода size()
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
    else
    {
         QMessageBox::warning(0, QObject::tr("Ошибка!"),"Выбран неверный путь.");
    }


}

//принятие данных из форм и запись их в запрос к бд
//Инициализируем внешний вид таблицы с данными
//очищает поля для ввода
void MainWindow::addKey()
{
    QString f1,f2,f3,f4;

    f1=ui->lineEdit_4->text();
    f2=ui->lineEdit_5->text();
    f3=ui->lineEdit_6->text();
    f4=ui->lineEdit_7->text();

    createKey(f1,f2,f3,f4);
    updateView();

    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
    ui->lineEdit_7->setText("");
}


void MainWindow::handleButton() {

    QString f1,f2,f3;

    f1=ui->lineEdit->text();
    f2=ui->lineEdit_2->text();
    f3=ui->lineEdit_3->text();

    createDB(f1,f2,f3);  
    updateView();

    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");

}

MainWindow::~MainWindow() {

}






