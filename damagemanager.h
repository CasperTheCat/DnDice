#ifndef DAMAGEMANAGER_H
#define DAMAGEMANAGER_H

#include <QDialog>

namespace Ui {
class DamageManager;
}

class DamageManager : public QDialog
{
    Q_OBJECT

public:
    explicit DamageManager(QWidget *parent = 0);
    ~DamageManager();
    void update_health(quint32 maxHealth, quint32 bonusHealth, quint32 tempHealth, quint32 damage, quint32 heal);
    void refresh();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_rst_button_clicked();

    void on_btn_set_raw_health_clicked();

    void on_btn_set_bonus_health_clicked();

    void on_btn_set_temp_health_clicked();

    void on_btn_add_damage_clicked();

    void on_btn_add_heal_clicked();

private:
    Ui::DamageManager *ui;
    void recalculate_health();

public:
    quint32 uMaxHealth;
    quint32 uBonusHealth;
    quint32 uTempHealth;
    quint32 uDamage;
    quint32 uHealing;

private:
    quint32 uNewMaxHealth;
    quint32 uNewDamage;
    quint32 uNewHealing;
    quint32 uNewBonusHealth;
    quint32 uNewTempHealth;
};

#endif // DAMAGEMANAGER_H
