#include "mainwindow.h"


void MainWindow::uncheck_dice(eDiceTypes::eDiceTypes exclusion)
{
    if(exclusion != eDiceTypes::d100) ui->btn_dice_d100->setChecked(false);
    if(exclusion != eDiceTypes::d20) ui->btn_dice_d20->setChecked(false);
    if(exclusion != eDiceTypes::d12) ui->btn_dice_d12->setChecked(false);
    if(exclusion != eDiceTypes::d10) ui->btn_dice_d10->setChecked(false);
    if(exclusion != eDiceTypes::d8) ui->btn_dice_d8->setChecked(false);
    if(exclusion != eDiceTypes::d6) ui->btn_dice_d6->setChecked(false);
    if(exclusion != eDiceTypes::d4) ui->btn_dice_d4->setChecked(false);
    if(exclusion != eDiceTypes::d3) ui->btn_dice_d3->setChecked(false);
    if(exclusion != eDiceTypes::d2) ui->btn_dice_d2->setChecked(false);
}



void MainWindow::on_btn_dice_d100_clicked()
{
    // Uncheck Other Buttons
    uncheck_dice(eDiceTypes::d100);
    edtCurrentDice = eDiceTypes::d100;
    roll_dice();
}

void MainWindow::on_btn_dice_d20_clicked()
{
    uncheck_dice(eDiceTypes::d20);
    edtCurrentDice = eDiceTypes::d20;
    roll_dice();
}

void MainWindow::on_btn_dice_d12_clicked()
{
    uncheck_dice(eDiceTypes::d12);
    edtCurrentDice = eDiceTypes::d12;
    roll_dice();
}

void MainWindow::on_btn_dice_d10_clicked()
{
    uncheck_dice(eDiceTypes::d10);
    edtCurrentDice = eDiceTypes::d10;
    roll_dice();
}

void MainWindow::on_btn_dice_d8_clicked()
{
    uncheck_dice(eDiceTypes::d8);
    edtCurrentDice = eDiceTypes::d8;
    roll_dice();
}

void MainWindow::on_btn_dice_d6_clicked()
{
    uncheck_dice(eDiceTypes::d6);
    edtCurrentDice = eDiceTypes::d6;
    roll_dice();
}

void MainWindow::on_btn_dice_d4_clicked()
{
  uncheck_dice(eDiceTypes::d4);
  edtCurrentDice = eDiceTypes::d4;
  roll_dice();
}

void MainWindow::on_btn_dice_d3_clicked()
{
  uncheck_dice(eDiceTypes::d3);
  edtCurrentDice = eDiceTypes::d3;
  roll_dice();
}

void MainWindow::on_btn_dice_d2_clicked()
{
   uncheck_dice(eDiceTypes::d2);
   edtCurrentDice = eDiceTypes::d2;
   roll_dice();
}





