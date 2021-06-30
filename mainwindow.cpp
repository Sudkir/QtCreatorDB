#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)

: QMainWindow(parent),
  ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //Создать объект БД и инициализировать подключение к базе данных
    db = new DataBase();
    db->connectToDataBase();
    updateView();
    //обработчик кнопок
    connect(ui->addDBBtn, SIGNAL (clicked()), this, SLOT (addDB()));
    connect(ui->addTableBtn, SIGNAL (clicked()), this, SLOT (createTable()));
    connect(ui->addKeybtn, SIGNAL (clicked()), this, SLOT (addKey()));
}

//Инициализируем модель для представления данных с заданием названий колонок и внешний вид таблицы с данными
void MainWindow::updateView()
{

   this->setupModel(TABLE_FILES,
                    QStringList() << QString ("id")
                                  << QString("Имя")
                                  << QString("Расположение")
                                  << QString("Вес"));
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
    ui->tableViewDB->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableViewDB->horizontalHeader()->setStretchLastSection(true);
    // Делаем выборку данных из таблицы
    model->select();
}



//Добавление таблицы и сохранения файла с расширением .sql
bool MainWindow::addFile(QString name,QString insertInfo)
{
    QString filePath=
               QFileDialog::getSaveFileName( this,
                                             tr("Сохранить файл как"),
                                             name,
                                             tr("SQL(*.sql)") );
    QFile file(filePath);
    if(!filePath.isEmpty() && file.open(QIODevice::WriteOnly) )

            {
                QTextStream stream(&file);
                stream << insertInfo;
                file.close();
                QFileInfo fileinfo(file);
                qint64 size=fileinfo.size();
                QSqlQuery query;
              query.prepare("INSERT INTO " TABLE_FILES " ( " TABLE_FILENAME ", "
                                                       TABLE_FILESYSPATH ", "
                                                       TABLE_FILESIZE " ) "
                           "VALUES (:NAME, :PATH, :SIZE )");
              query.bindValue(":NAME",name);
              query.bindValue(":PATH",filePath);
              query.bindValue(":SIZE",size);
              if(!query.exec()){
                  QMessageBox::warning(0, QObject::tr("Ошибка БД!"), query.lastError().text());
                  return false;
              }
              else
              {return false;
              }
            }
}



//Создание таблицы
void MainWindow::createTable()
{
    int rowidx = ui->tableViewDB->selectionModel()->currentIndex().row();

        QString idDB=(model->index(rowidx , 0).data().toString());//id
        ui->uiNameDB->setText(model->index(rowidx , 1).data().toString());//name
        QString nameDB=(model->index(rowidx , 1).data().toString());
        if(nameDB[0]=='D'&&nameDB[1]=='B')
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
            QMessageBox::warning(0, QObject::tr("Ошибка!"),"Выбрана не База Данных."
                                                           "\nВыберите файл, который начинается с \"DB_\"");
        }

}




/* принятие данных из форм и запись их в запрос к бд
 * */
void MainWindow::addKey()
{
    QString nameTbl1;
    QString nameColumn1;
    QString nameTbl2;
    QString nameColumn2;

    nameTbl1=ui->lineTbl1->text();
    nameColumn1=ui->lineColumn1->text();
    nameTbl2=ui->lineTbl2->text();
    nameColumn2=ui->lineTbl2->text();
     //ALTER TABLE table1 ADD FOREING KEY (colum1) REFERENCES table2(column2);
    QString sqlKey = QString ("ALTER TABLE '%1' ADD FOREING KEY ('%2') REFERENCES '%3'('%4);")
            .arg(nameTbl1,  nameColumn1,  nameTbl2,  nameColumn2);
    QString fileName = QString("KEY_"+nameTbl1+"_("+nameColumn1+").sql");

    addFile(fileName,sqlKey);
    updateView();

    ui->lineTbl1->setText("");
    ui->lineColumn1->setText("");
    ui->lineTbl2->setText("");
    ui->lineTbl2->setText("");
}

/* принятие данных из форм и запись их в запрос к бд
 * */
void MainWindow::addDB() {

    QString nameUser;
    QString userPassword;
    QString nameDB;

    nameDB=ui->lineDB->text();
    nameUser=ui->lineUser->text();
    userPassword=ui->linePassword->text();
    //CREATE USER test_user WITH password 'qwerty';
    //CREATE DATABASE test_database OWNER test_user;

    QString sqlDB = QString ("CREATE USER '%1' WITH password '%2'\nCREATE DATABASE '%3' OWNER '%4'")
            .arg(nameUser,userPassword,nameDB,nameUser);
    QString fileName = QString("DB_"+nameDB+"_"+nameUser+".sql");
    addFile(fileName,sqlDB);
    updateView();

    ui->lineDB->setText("");
    ui->lineUser->setText("");
    ui->linePassword->setText("");

}

MainWindow::~MainWindow() {
    db->closeDataBase();

}






