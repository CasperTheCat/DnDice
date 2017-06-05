#include "mainwindow.h"
#include "utilities.h"
#include "dice.h"
#include "dice_functions.h"
#include <fstream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bNewFile = true;
    bFileDirty = false;
    qsFileName = "untitled";
    setWindowTitle("DnDice: " + qsFileName);

    uLevel = 1;
    uExpSince = 0;
    uExpTo = 0;



    // Use this to store data from now on!!!
    playerData = new sInterfaceFields();
    expManagerWindow = new ExpManager(this);
    damManagerWindow = new DamageManager(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete playerData;
    delete expManagerWindow;
}

void MainWindow::receive_experience(quint32 level, quint32 tExp, quint32 expSince, quint32 expTo)
{
    // Store tExp data in playerData since it gets saved
    playerData->uExperience = tExp;
    uLevel = level;
    uExpSince = expSince;
    uExpTo = expTo;

    // Update Experience UI
    ui->prog_experience->setMaximum(uExpTo);
    ui->prog_experience->setValue(uExpSince);


    // Calculate prof
    ui->spin_stat_pro->setValue(((uLevel - 1) / 4) + 2);
    update_top_bar();
}

void MainWindow::receive_health_update(quint32 cHealth, quint32 mHealth)
{
    ui->prog_health->setMaximum(mHealth);
    ui->prog_health->setValue(cHealth);


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

void MainWindow::uncheck_overrides(Attributes::Attributes exclusion)
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

void MainWindow::run_check(QCheckBox *skill, QCheckBox *expertise, Attributes::Attributes defaultAttribute)
{
    auto rollType = roll;
    QString qsAddOrDis = "<font>";
    uint8_t attribModifier = get_override_state();
    if(!attribModifier) attribModifier = defaultAttribute;


    // Evalute the check, including Advantage and Disadvantage rolls
    if(ui->btn_rollmod_advntg->isChecked())
    {
        rollType = rollAdvantage;
        qsAddOrDis = "<font color=\"green\">";
    }

    if(ui->btn_rollmod_dsadvn->isChecked())
    {
        rollType = rollDisadvantage;
        qsAddOrDis = "<font color=#c00>";
    }

    // Modifiers
    uint32_t rawRoll = rollWith(rollType, Dice::d20);
    int32_t mod = (get_stat(attribModifier) - 10) / 2;
    if(skill->isChecked()) mod += ui->spin_stat_pro->value();
    if(expertise->isChecked()) mod += ui->spin_stat_pro->value();

    ui->text_dbg_output->append(qsAddOrDis + skill->text() + "</font> <font color=\"grey\">(" + get_modifier_shortname(attribModifier) + ")</font>");
    ui->text_dbg_dice->append(QString::number(rawRoll) + "<font color=\"grey\"> + " + QString::number(mod) + "</font> = \t" + QString::number(rawRoll + mod));

    // Clear modifiers
    uncheck_overrides(Attributes::None);
    ui->btn_rollmod_dsadvn->setChecked(false);
    ui->btn_rollmod_advntg->setChecked(false);
}

void MainWindow::run_save(QCheckBox *skill, Attributes::Attributes usedAttribute)
{
    auto rollType = roll;
    QString qsAddOrDis = "<font>";

    // Evalute the check, including Advantage and Disadvantage rolls
    if(ui->btn_rollmod_advntg->isChecked())
    {
        rollType = rollAdvantage;
        qsAddOrDis = "<font color=\"green\">";
    }

    if(ui->btn_rollmod_dsadvn->isChecked())
    {
        rollType = rollDisadvantage;
        qsAddOrDis = "<font color=#c00>";
    }

    // Roll and modify
    uint32_t rawRoll = rollWith(rollType, Dice::d20);
    int32_t mod = (get_stat(usedAttribute) - 10) / 2;
    if(skill->isChecked()) mod += ui->spin_stat_pro->value();

    ui->text_dbg_output->append(qsAddOrDis + skill->text() + " save</font>");
    ui->text_dbg_dice->append(QString::number(rawRoll) + "<font color=\"grey\"> + " + QString::number(mod) + "</font> = \t" + QString::number(rawRoll + mod));

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
    run_check(ui->skills_acro, ui->expertise_acro , Attributes::Dexterity);
}

void MainWindow::on_btn_check_anml_clicked()
{
    run_check(ui->skills_animalHandling,ui->expertise_animalHandling, Attributes::Wisdom);
}

void MainWindow::on_btn_check_arcana_clicked()
{
    run_check(ui->skills_arcana,ui->expertise_arcana, Attributes::Intelligence);
}

void MainWindow::on_btn_check_ath_clicked()
{
    run_check(ui->skills_athletics,ui->expertise_athletics, Attributes::Strength);
}

void MainWindow::on_btn_check_dec_clicked()
{
    run_check(ui->skills_deception, ui->expertise_deception, Attributes::Charisma);
}

void MainWindow::on_btn_check_his_clicked()
{
    run_check(ui->skills_history,ui->expertise_history, Attributes::Intelligence);
}

void MainWindow::on_btn_check_ins_clicked()
{
    run_check(ui->skills_insight,ui->expertise_insight, Attributes::Wisdom);
}

void MainWindow::on_btn_check_int_clicked()
{
    run_check(ui->skills_intimidation,ui->expertise_intimidation, Attributes::Charisma);
}

void MainWindow::on_btn_check_inv_clicked()
{
    run_check(ui->skills_investigation,ui->expertise_investigation, Attributes::Intelligence);
}

void MainWindow::on_btn_check_med_clicked()
{
    run_check(ui->skills_medicine,ui->expertise_medicine, Attributes::Wisdom);
}

void MainWindow::on_btn_check_nat_clicked()
{
    run_check(ui->skills_nature,ui->expertise_nature, Attributes::Intelligence);
}

void MainWindow::on_btn_check_perc_clicked()
{
    run_check(ui->skills_perception,ui->expertise_perception, Attributes::Wisdom);
}

void MainWindow::on_btn_check_perf_clicked()
{
    run_check(ui->skills_performance,ui->expertise_performance, Attributes::Charisma);
}

void MainWindow::on_btn_check_pers_clicked()
{
    run_check(ui->skills_persuasion,ui->expertise_persuasion, Attributes::Charisma);
}

void MainWindow::on_btn_check_rel_clicked()
{
    run_check(ui->skills_religion,ui->expertise_religion, Attributes::Intelligence);
}

void MainWindow::on_btn_check_sle_clicked()
{
    run_check(ui->skills_sleightofhand,ui->expertise_sleightofhand, Attributes::Dexterity);
}

void MainWindow::on_btn_check_ste_clicked()
{
    run_check(ui->skills_stealth,ui->expertise_stealth, Attributes::Dexterity);
}

void MainWindow::on_btn_check_sur_clicked()
{
    run_check(ui->skills_survival,ui->expertise_survival, Attributes::Wisdom);
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

    ui->label_top_name->setText(playerData->qsName);
    ui->label_top_level_race_class->setText(
                QString::fromStdString(make_nth(uLevel)) + " Level " +
                playerData->qsRace + " " +
                playerData->qsClass
                );
}

///
/// \brief MainWindow::on_other_update_btn_clicked
///
void MainWindow::on_other_update_btn_clicked()
{
    playerData->qsName = ui->other_edit_name->text();
    playerData->qsRace = ui->other_edit_race->text();
    playerData->qsClass = ui->other_edit_class->text();
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


void MainWindow::updateTitle()
{
    setWindowTitle("DnDice: " + qsFileName);
}



void MainWindow::on_actionExp_Manager_triggered()
{

    //expManagerWindow->setWindowFlags(Qt::WindowStaysOnTopHint);
    expManagerWindow->show();
    //this->hide();
}


void MainWindow::on_actionDamage_Manger_triggered()
{
    //QString danger = "QProgressBar {background-color: #1d2126; text-align: center; }\n QProgressBar::chunk {background-color: #abc; } ";
    damManagerWindow->show();
    //ui->prog_health->setStyleSheet(danger);
}
