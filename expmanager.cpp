#include "expmanager.h"
#include "ui_expmanager.h"
#include "mainwindow.h"

quint32 aExpForLevel[20] = {
    0,              // 1
    300,            // 2
    900,            // 3
    2700,           // 4
    6500,
    14000,
    23000,
    34000,
    48000,
    64000,          // 10
    85000,
    100000,
    120000,
    140000,
    165000,
    195000,         // 16
    225000,
    265000,
    305000,
    355000
};

ExpManager::ExpManager(QWidget *parent,quint32 tExp) :
    QDialog(parent),
    ui(new Ui::ExpManager)
{
    ui->setupUi(this);

    uTotalExperience = tExp;

    uNewExperienceSinceLevel = 0;
    uNewLevel = 1;
    uNewTotalExperience = 0;

    recalculate_experience();
}

ExpManager::~ExpManager()
{
    delete ui;
}

void ExpManager::update_experience(quint32 tExp)
{
    uTotalExperience = tExp;
    uNewTotalExperience = uTotalExperience;
    recalculate_experience();

    static_cast<MainWindow *>(parentWidget())->receive_experience(uNewLevel,uNewTotalExperience,uNewExperienceSinceLevel,uNewExperienceToLevel);
}

void ExpManager::on_buttonBox_accepted()
{
    // Pass Updates to Parents
    static_cast<MainWindow *>(parentWidget())->receive_experience(uNewLevel,uNewTotalExperience,uNewExperienceSinceLevel,uNewExperienceToLevel);
    uTotalExperience = uNewTotalExperience;
    this->hide();
    parentWidget()->show();
}

void ExpManager::on_buttonBox_rejected()
{
    // we need to revert the changes
    on_rst_button_clicked();
    this->hide();
    parentWidget()->show();
}

void ExpManager::on_btn_add_exp_clicked()
{
    // Just add things
    uNewTotalExperience += ui->spin_add_exp->value();
    recalculate_experience();
}

void ExpManager::on_btn_set_exp_to_level_clicked()
{
    // Lookup experience needed for the level
    qint32 iValue = ui->spin_level->value();
    uNewTotalExperience = aExpForLevel[iValue - 1];
    recalculate_experience();
}

void ExpManager::set_top_label()
{
    ui->label_title_total_exp->setText(QString::number(uNewTotalExperience));
    ui->label_title_level_num->setText(QString::number(uNewLevel));
    ui->label_title_since_level_exp->setText(QString::number(uNewExperienceSinceLevel));
}

void ExpManager::recalculate_experience()
{
    for(uint32_t i = 0; i < 21; ++i)
    {
        uNewLevel = i;
        if(i > 19 || uNewTotalExperience < aExpForLevel[i])
        {
            break;
        }
    }


    uNewExperienceSinceLevel = uNewTotalExperience - aExpForLevel[uNewLevel - 1];
    if(uNewLevel < 20)
        uNewExperienceToLevel = aExpForLevel[uNewLevel] - uNewTotalExperience;
    else
        uNewExperienceToLevel = 0;


    set_top_label();
}

void ExpManager::on_rst_button_clicked()
{
    uNewTotalExperience = uTotalExperience;
    recalculate_experience();
}
