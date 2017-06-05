#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QBitArray>
#include "expmanager.h"
#include "damagemanager.h"

namespace eSkills {
    enum eSkills
    {
        Acrobatics,
        AnimalHandling,
        Arcana,
        Athletics,
        Deception,
        History,
        Insight,
        Intimidation,
        Investigation,
        Medicine,
        Nature,
        Perception,
        Performance,
        Persuasion,
        Religion,
        Sleight_of_Hand,
        Stealth,
        Survival,

        TOTAL_NUMBER_SKILLS
    };
}

namespace eSaves {
    enum eSaves
    {
        Strength,
        Dexterity,
        Constitution,
        Intelligence,
        Wisdom,
        Charisma,

        TOTAL_NUMBER_SAVES
    };
}

struct sInterfaceFields
{
    QString qsName;
    QString qsRace;
    QString qsClass;

    quint32 uMaxHealth;
    quint32 uCurrentHealth;
    quint32 uExperience;


    QBitArray qbaProfArray;
    QBitArray qbaExpArray;
    QBitArray qbaSaveArray;
    QVector<quint32> qvStats;
    //std::vector<bool> bProficiencyArray;
    //std::vector<bool> bExpertiseArray;

    sInterfaceFields();
    ~sInterfaceFields();
    void reserve(quint64 size);

};


namespace Attributes {
    enum Attributes {
        None = 0,
        Strength = 0b00000001,
        Dexterity = 2,
        Constitution = 4,
        Intelligence = 8,
        Wisdom = 16,
        Charisma = 32
    };
}

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void receive_experience(quint32 level, quint32 tExp, quint32 expSince, quint32 expTo);
    void receive_health_update(quint32 cHealth, quint32 mHealth);

private slots:

    void on_btn_check_acro_clicked();

    void on_btn_check_ovrrde_str_clicked(bool checked);

    void on_btn_check_ovrrde_dex_clicked(bool checked);

    void on_btn_check_ovrrde_con_clicked(bool checked);

    void on_btn_check_ovrrde_int_clicked(bool checked);

    void on_btn_check_ovrrde_wis_clicked(bool checked);

    void on_btn_check_ovrrde_cha_clicked(bool checked);

    void on_btn_check_anml_clicked();

    void on_btn_check_arcana_clicked();

    void on_btn_check_ath_clicked();

    void on_btn_rollmod_advntg_clicked();

    void on_btn_rollmod_dsadvn_clicked();

    void on_btn_check_dec_clicked();

    void on_btn_check_his_clicked();

    void on_btn_check_ins_clicked();

    void on_btn_check_int_clicked();

    void on_btn_check_inv_clicked();

    void on_btn_check_med_clicked();

    void on_btn_check_nat_clicked();

    void on_btn_check_perc_clicked();

    void on_btn_check_perf_clicked();

    void on_btn_check_pers_clicked();

    void on_btn_check_rel_clicked();

    void on_btn_check_sle_clicked();

    void on_btn_check_ste_clicked();

    void on_btn_check_sur_clicked();

    void on_other_update_btn_clicked();

    void on_btn_save_str_clicked();

    void on_btn_save_dex_clicked();

    void on_btn_save_con_clicked();

    void on_btn_save_int_clicked();

    void on_btn_save_wis_clicked();

    void on_btn_save_cha_clicked();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionExp_Manager_triggered();

    void on_actionLoad_triggered();

    void on_actionDamage_Manger_triggered();

private:
    Ui::MainWindow *ui;
    ExpManager *expManagerWindow;
    DamageManager *damManagerWindow;

    // AttributeOverrides
private:
    sInterfaceFields *playerData;
    quint32 uLevel;
    quint32 uExpSince;
    quint32 uExpTo;


    // File save
    bool bNewFile;
    bool bFileDirty;
    QString qsFileName;


private:
    // Uncheck buttons
    void uncheck_overrides(Attributes::Attributes exclusion);

    // Check if any of the buttons are clicked
    uint8_t get_override_state();

    // Get player main stat
    int get_stat(uint8_t modifier);

    // Get modifier names
    QString get_modifier_shortname(uint8_t modifier);

    // Generalised function to save space and iteration time
    void run_check(QCheckBox *skill, QCheckBox *expertise, Attributes::Attributes defaultAttribute);

    // Used by the 6 saving throw callers
    void run_save(QCheckBox *skill, Attributes::Attributes usedAttribute);

    // Used by loader in future
    void update_top_bar();

    // Saving
    void saveFile();
    sInterfaceFields *interfaceToFields();
    void fieldsToInterface(sInterfaceFields * loadData);
    void serialiseAndPackFields();

    // Update UI
    void updateTitle();
};

#endif // MAINWINDOW_H
