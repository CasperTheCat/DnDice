#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dice.h"
#include "dice_functions.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::on_d20Roll_clicked()
{
    ui->d20Label->setText(QString::number(roll(Dice::d20)));
}

void MainWindow::on_d12Roll_clicked()
{
    ui->d12Label->setText(QString::number(roll(Dice::d12)));
    //ui->textBrowser->setText(QString::number(roll(Dice::nd20)));
    ui->textBrowser->append(QString::number(roll(Dice::ad20)));
}*/
