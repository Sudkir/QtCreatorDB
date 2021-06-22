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


  /* После чего производим наполнение таблицы базы данных
   * контентом, который будет отображаться в TableView
   *


  for(int i = 0; i < 4; i++){
      QVariantList data;
      int random = qrand(); // Получаем случайные целые числа для вставки а базу данных
      data.append(QDate::currentDate()); // Получаем текущую дату для вставки в БД
      data.append(QTime::currentTime()); // Получаем текущее время для вставки в БД
      // Подготавливаем полученное случайное число для вставки в БД
      data.append(random);
      // Подготавливаем сообщение для вставки в базу данных
      data.append("Получено сообщение от " + QString::number(random));
      // Вставляем данные в БД
      db->inserIntoTable(data);
  }
  */

    ui->setupUi(this);
    //объект БД
    db = new DataBase();
    //инициализировать подключение к базе данных
    db->connectToDataBase();
   //Инициализируем модель для представления данных с заданием названий колонок
  this->setupModel(TABLE_FILES,
                   QStringList() << QString ("id")
                                 << QString("Имя")
                                 << QString("Расположение")
                                 << QString("Вес"));

  // Инициализируем внешний вид таблицы с данными
  this->createUI();
    //обработчик кнопки
    connect(ui->AddDBBtn, SIGNAL (clicked()), this, SLOT (handleButton()));
    connect(ui->AddTableBtn, SIGNAL (clicked()), this, SLOT (createTable()));


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

    QString sqlUser = QString ("CREATE USER '%1' WITH password '%2'").arg(nameUser,userPassword);
    QString sqlDB = QString ("CREATE DATABASE '%1' OWNER '%2'").arg(nameDB,nameUser);

    //if(file.exists()){
    //qDebug() << "Файл существует";
    //}

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
                stream << sqlUser+"\n"+sqlDB;
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

    this->setupModel(TABLE_FILES,
                     QStringList() << QString ("id")
                                   << QString("Имя         ")
                                   << QString("Расположение")
                                   << QString("Вес         ")

               );

    // Инициализируем внешний вид таблицы с данными
    this->createUI();

    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");


}
//изменение размера окна

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
                this->setupModel(TABLE_FILES,
                                 QStringList() << QString ("id")
                                               << QString("Имя         ")
                                               << QString("Расположение")
                                               << QString("Вес         "));
                this->createUI();
            }
        }
        else
        {
            QMessageBox::warning(0, QObject::tr("Ошибка!"),"Выбрана не База Данных.\nВыберите файл, который начинается с \"DB_\"");
        }

}

void MainWindow::handleButton() {
    //принятие данных из форм и запись их в запрос к бд
    QString f1,f2,f3;
    f1=ui->lineEdit->text();
    f2=ui->lineEdit_2->text();
    f3=ui->lineEdit_3->text();
    createDB(f1,f2,f3);
}

MainWindow::~MainWindow() {

}

/*
int rowidx = ui->tblView->selectionModel()->currentIndex().row();
ui->txt1->setText(model->index(rowidx , 0).data().toString());
ui->txt2->setText(model->index(rowidx , 1).data().toString());
ui->txt3->setText(model->index(rowidx , 2).data().toString());
ui->txt4->setText(model->index(rowidx , 3).data().toString());
*/








