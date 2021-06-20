#include "tablewindow.h"
#include "ui_tablewindow.h"

tablewindow::tablewindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tablewindow)
{
    ui->setupUi(this);
}

tablewindow::~tablewindow()
{
    delete ui;
}
