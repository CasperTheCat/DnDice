#include "mainwindow.h"
#include "utilities.h"
#include "dice.h"
#include "dice_functions.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    uAttribMod = 0;
    uMaxHealth = 0;
    uCurrentHealth = 0;
    uExperience = 0;

    // Variables for saving out
    // Rest read from fields
    qsName = "[NAME]";
    uLevel = 1;
    qsRace = "[RACE]";
    qsClass = "[CLASS]";
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





//////////////////////////////////////////////////
/// Overriding Buttons
///
void MainWindow::on_btn_check_ovrrde_str_clicked(bool checked)
{
    uncheck_overrides(Attributes::Strength);
}

void MainWindow::on_btn_check_ovrrde_dex_clicked(bool checked)
{
    uncheck_overrides(Attributes::Dexterity);
}

void MainWindow::on_btn_check_ovrrde_con_clicked(bool checked)
{
    uncheck_overrides(Attributes::Constitution);
}

void MainWindow::on_btn_check_ovrrde_int_clicked(bool checked)
{
    uncheck_overrides(Attributes::Intelligence);
}

void MainWindow::on_btn_check_ovrrde_wis_clicked(bool checked)
{
    uncheck_overrides(Attributes::Wisdom);
}

void MainWindow::on_btn_check_ovrrde_cha_clicked(bool checked)
{
    uncheck_overrides(Attributes::Charisma);
}

void MainWindow::uncheck_overrides(Attributes exclusion)
{
    if(exclusion != Attributes::Strength) ui->btn_check_ovrrde_str->setChecked(false);
    if(exclusion != Attributes::Dexterity) ui->btn_check_ovrrde_dex->setChecked(false);
    if(exclusion != Attributes::Constitution) ui->btn_check_ovrrde_con->setChecked(false);
    if(exclusion != Attributes::Intelligence) ui->btn_check_ovrrde_int->setChecked(false);
    if(exclusion != Attributes::Wisdom) ui->btn_check_ovrrde_wis->setChecked(false);
    if(exclusion != Attributes::Charisma) ui->btn_check_ovrrde_cha->setChecked(false);
}

//////////////////////////////////////////////////
/// Get the state
///
uint8_t MainWindow::get_override_state()
{
    return 0 |
            ui->btn_check_ovrrde_str->isChecked() |
            (ui->btn_check_ovrrde_dex->isChecked() << 1) |
            (ui->btn_check_ovrrde_con->isChecked() << 2) |
            (ui->btn_check_ovrrde_int->isChecked() << 3) |
            (ui->btn_check_ovrrde_wis->isChecked() << 4) |
            (ui->btn_check_ovrrde_cha->isChecked() << 5);
}

int MainWindow::get_stat(uint8_t modifier)
{
    if(modifier == Attributes::Strength) return ui->spin_stat_str->value();
    if(modifier == Attributes::Dexterity) return ui->spin_stat_dex->value();
    if(modifier == Attributes:: Constitution) return ui->spin_stat_con->value();
    if(modifier == Attributes::Intelligence) return ui->spin_stat_int->value();
    if(modifier == Attributes::Wisdom) return ui->spin_stat_wis->value();
    if(modifier == Attributes::Charisma) return ui->spin_stat_cha->value();
    return 0;
}

QString MainWindow::get_modifier_shortname(uint8_t modifier)
{
    if(modifier == Attributes::Strength) return "Str";
    if(modifier == Attributes::Dexterity) return "Dex";
    if(modifier == Attributes::Constitution) return "Con";
    if(modifier == Attributes::Intelligence) return "Int";
    if(modifier == Attributes::Wisdom) return "Wis";
    if(modifier == Attributes::Charisma) return "Cha";
    return "None";
}

void MainWindow::run_check(QCheckBox *skill, Attributes defaultAttribute)
{
    auto rollType = roll;
    QString DBG = "";
    uint8_t attribModifier = get_override_state();
    if(!attribModifier) attribModifier = defaultAttribute;


    // Evalute the check, including Advantage and Disadvantage rolls
    if(ui->btn_rollmod_advntg->isChecked())
    {
        rollType = rollAdvantage;
        DBG = " ++ ";
    }

    if(ui->btn_rollmod_dsadvn->isChecked())
    {
        rollType = rollDisadvantage;
        DBG = " -- ";
    }

    // Modifiers
    uint32_t rawRoll = rollWith(rollType, Dice::d20);
    int32_t mod = (get_stat(attribModifier) - 10) / 2;
    if(skill->isChecked()) mod += ui->spin_stat_pro->value();


    ui->text_dbg_output->append(skill->text() + DBG + " (" + get_modifier_shortname(attribModifier) + ")" + ":\t<"
                                + QString::number(rawRoll) + "> + " + QString::number(mod) + " = " + QString::number(rawRoll + mod));

    // Clear modifiers
    uncheck_overrides(Attributes::None);
    ui->btn_rollmod_dsadvn->setChecked(false);
    ui->btn_rollmod_advntg->setChecked(false);
}

void MainWindow::run_save(QCheckBox *skill, Attributes usedAttribute)
{
    auto rollType = roll;
    QString DBG = "";

    // Evalute the check, including Advantage and Disadvantage rolls
    if(ui->btn_rollmod_advntg->isChecked())
    {
        rollType = rollAdvantage;
        DBG = "+";
    }

    if(ui->btn_rollmod_dsadvn->isChecked())
    {
        rollType = rollDisadvantage;
        DBG = "-";
    }

    // Roll and modify
    uint32_t rawRoll = rollWith(rollType, Dice::d20);
    int32_t mod = (get_stat(usedAttribute) - 10) / 2;
    if(skill->isChecked()) mod += ui->spin_stat_pro->value();

    ui->text_dbg_output->append(skill->text() + DBG + " Saving Throw" + ":\t<"
                                + QString::number(rawRoll) + "> + " + QString::number(mod) + " = " + QString::number(rawRoll + mod));

    // Clear modifiers
    uncheck_overrides(Attributes::None);
    ui->btn_rollmod_dsadvn->setChecked(false);
    ui->btn_rollmod_advntg->setChecked(false);
}





// Advantage, Disadvantage.
// Cannot both be active
void MainWindow::on_btn_rollmod_advntg_clicked()
{
    ui->btn_rollmod_dsadvn->setChecked(false);
}

void MainWindow::on_btn_rollmod_dsadvn_clicked()
{
    ui->btn_rollmod_advntg->setChecked(false);
}

///////////////////////////////////////////////////////
/// Buttons
///

void MainWindow::on_btn_check_acro_clicked()
{
    run_check(ui->skills_acro, Attributes::Dexterity);
}

void MainWindow::on_btn_check_anml_clicked()
{
    run_check(ui->skills_animalHandling, Attributes::Wisdom);
}

void MainWindow::on_btn_check_arcana_clicked()
{
    run_check(ui->skills_arcana, Attributes::Intelligence);
}

void MainWindow::on_btn_check_ath_clicked()
{
    run_check(ui->skills_athletics, Attributes::Strength);
}

void MainWindow::on_btn_check_dec_clicked()
{
    run_check(ui->skills_deception, Attributes::Charisma);
}

void MainWindow::on_btn_check_his_clicked()
{
    run_check(ui->skills_history, Attributes::Intelligence);
}

void MainWindow::on_btn_check_ins_clicked()
{
    run_check(ui->skills_insight, Attributes::Wisdom);
}

void MainWindow::on_btn_check_int_clicked()
{
    run_check(ui->skills_intimidation, Attributes::Charisma);
}

void MainWindow::on_btn_check_inv_clicked()
{
    run_check(ui->skills_investigation, Attributes::Intelligence);
}

void MainWindow::on_btn_check_med_clicked()
{
    run_check(ui->skills_medicine, Attributes::Wisdom);
}

void MainWindow::on_btn_check_nat_clicked()
{
    run_check(ui->skills_nature, Attributes::Intelligence);
}

void MainWindow::on_btn_check_perc_clicked()
{
    run_check(ui->skills_perception, Attributes::Wisdom);
}

void MainWindow::on_btn_check_perf_clicked()
{
    run_check(ui->skills_performance, Attributes::Charisma);
}

void MainWindow::on_btn_check_pers_clicked()
{
    run_check(ui->skills_persuasion, Attributes::Charisma);
}

void MainWindow::on_btn_check_rel_clicked()
{
    run_check(ui->skills_religion, Attributes::Intelligence);
}

void MainWindow::on_btn_check_sle_clicked()
{
    run_check(ui->skills_sleightofhand, Attributes::Dexterity);
}

void MainWindow::on_btn_check_ste_clicked()
{
    run_check(ui->skills_stealth, Attributes::Dexterity);
}

void MainWindow::on_btn_check_sur_clicked()
{
    run_check(ui->skills_survival, Attributes::Wisdom);
}

/////
/// Naming things
///

///
/// \brief MainWindow::update_top_bar
/// \param name
/// \param level
/// \param race
/// \param class_
///
void MainWindow::update_top_bar()
{

    ui->label_top_name->setText(qsName);
    ui->label_top_level_race_class->setText(
                QString::fromStdString(make_nth(uLevel)) + " Level " +
                qsRace + " " +
                qsClass
                );
}

///
/// \brief MainWindow::on_other_update_btn_clicked
///
void MainWindow::on_other_update_btn_clicked()
{
    qsName = ui->other_edit_name->text();
    qsRace = ui->other_edit_race->text();
    qsClass = ui->other_edit_class->text();
    //Update the variables
    update_top_bar();
}

/////
/// Saving Throws
///

void MainWindow::on_btn_save_str_clicked()
{
    run_save(ui->other_save_str, Attributes::Strength);
}

void MainWindow::on_btn_save_dex_clicked()
{
    run_save(ui->other_save_dex, Attributes::Dexterity);
}

void MainWindow::on_btn_save_con_clicked()
{
    run_save(ui->other_save_con, Attributes::Constitution);
}

void MainWindow::on_btn_save_int_clicked()
{
    run_save(ui->other_save_int, Attributes::Intelligence);
}

void MainWindow::on_btn_save_wis_clicked()
{
    run_save(ui->other_save_wis, Attributes::Wisdom);
}

void MainWindow::on_btn_save_cha_clicked()
{
    run_save(ui->other_save_cha, Attributes::Charisma);
}
