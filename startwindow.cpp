#include "startwindow.h"

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

//загрузка основной формы программы
void StartWindow::loadMain()
{
    QString firstName;
    QString lastName;
    QString telephoneNumber;
    firstName=ui->lineFirstName->text();
    lastName=ui->lineLastName->text();
    telephoneNumber=ui->lineTelephoneNumber->text();

      QSqlQuery query;
    query.prepare("INSERT INTO " TABLE_USERS " ( " TABLE_FNAME ", "
                                             TABLE_SNAME ", "
                                             TABLE_TEL " ) "
                  "VALUES (:FName, :SName, :Tel )");
    query.bindValue(":FName",        firstName);
    query.bindValue(":SName",        lastName);
    query.bindValue(":Tel",      telephoneNumber);
    if(!query.exec()){
        QMessageBox::warning(0, QObject::tr("Ошибка БД!"), query.lastError().text());
    }

    this->hide();
    mainW = new MainWindow;
    mainW->show();
}

