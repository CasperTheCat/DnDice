#include "damagemanager.h"
#include "ui_damagemanager.h"
#include <iostream>
#include "mainwindow.h"

DamageManager::DamageManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DamageManager)
{
    ui->setupUi(this);

    uMaxHealth = 0;
    uBonusHealth = 0;
    uTempHealth = 0;

    uNewMaxHealth = 1;
    uDamage = 0;
    uHealing = 0;
    uNewDamage = 0;
    uNewHealing = 0;
    uNewBonusHealth = 0;
    uNewTempHealth = 0;

    recalculate_health();
}

DamageManager::~DamageManager()
{
    delete ui;
}

void DamageManager::update_health(quint32 maxHealth, quint32 bonusHealth, quint32 tempHealth, quint32 damage, quint32 heal)
{
    uMaxHealth = maxHealth;
    uBonusHealth = bonusHealth;
    uTempHealth = tempHealth;
    uDamage = damage;
    uHealing = heal;

    on_rst_button_clicked();
}

void DamageManager::refresh()
{
    on_rst_button_clicked();
}

void DamageManager::on_buttonBox_accepted()
{


    // Update Parent!!
    uMaxHealth = uNewMaxHealth + uNewBonusHealth + uNewTempHealth;
    static_cast<MainWindow *>(parentWidget())->receive_health_update(uMaxHealth + uNewHealing - uNewDamage, uMaxHealth);

    // Keep up to the changes
    uMaxHealth = uNewMaxHealth;
    uBonusHealth = uNewBonusHealth;
    uTempHealth = uNewTempHealth;
    uDamage = uNewDamage;
    uHealing = uNewHealing;
    std::cout << uNewDamage << std::endl;
    //this->hide();
    //parentWidget()->show();
}

void DamageManager::on_buttonBox_rejected()
{
    on_rst_button_clicked();
    this->hide();
    parentWidget()->show();
}

// RESET
void DamageManager::on_rst_button_clicked()
{
    uNewMaxHealth = uMaxHealth;
    uNewDamage = uDamage;
    uNewHealing = uHealing;
    uNewBonusHealth = uBonusHealth;
    uNewTempHealth = uTempHealth;
    //uNewTotalMaxHealth
    recalculate_health();
}

///
/// APPLY BUTTON IS NEEDED
///

void DamageManager::on_btn_set_raw_health_clicked()
{
    uNewMaxHealth = ui->spin_raw_health->value();
    recalculate_health();
}

void DamageManager::on_btn_set_bonus_health_clicked()
{
    uNewBonusHealth = ui->spin_bonus_health->value();
    recalculate_health();
}

void DamageManager::on_btn_set_temp_health_clicked()
{
    uNewTempHealth = ui->spin_temp_health->value();
    recalculate_health();
}



void DamageManager::on_btn_add_damage_clicked()
{
    quint32 dam = ui->spin_damage->value();
    if(uNewTempHealth > 0)
    {
        // We have temporary HP, remove it
        uNewTempHealth = (dam < uNewTempHealth) ? uNewTempHealth - dam: 0;
    }
    else
    {
        quint32 temp = (uNewMaxHealth + uNewBonusHealth + uNewTempHealth + uNewHealing);
        if(uNewDamage + dam > temp)
        {
            dam = temp - uNewDamage;
        }
        uNewDamage += dam;
    }

    recalculate_health();
}

void DamageManager::on_btn_add_heal_clicked()
{
    quint32 hea = ui->spin_heal->value();

    if(uNewDamage < (uNewHealing + hea))
    {
        hea = uNewDamage - uNewHealing;
    }

    uNewHealing += hea;
    recalculate_health();
}

void DamageManager::recalculate_health()
{
    quint32 uNewTotalMaxHealth = uNewMaxHealth + uNewBonusHealth + uNewTempHealth;
    ui->label_raw_log->setText(QString::number(uNewMaxHealth));
    ui->label_bonus_log->setText(QString::number(uNewBonusHealth));
    ui->label_temp_log->setText(QString::number(uNewTempHealth));
    ui->label_current_value->setText(QString::number(uNewTotalMaxHealth + uNewHealing - uNewDamage));
    static_cast<MainWindow *>(parentWidget())->receive_health_update(uNewTotalMaxHealth + uNewHealing - uNewDamage, uNewTotalMaxHealth);
    on_buttonBox_accepted();
}
