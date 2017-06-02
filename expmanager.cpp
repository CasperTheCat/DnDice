#include "expmanager.h"
#include "ui_expmanager.h"

ExpManager::ExpManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpManager)
{
    ui->setupUi(this);
}

ExpManager::~ExpManager()
{
    delete ui;
}

void ExpManager::on_buttonBox_accepted()
{
    this->hide();
    parentWidget()->show();
}
