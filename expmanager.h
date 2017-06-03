#ifndef EXPMANAGER_H
#define EXPMANAGER_H

#include <QDialog>



namespace Ui {
class ExpManager;
}

class ExpManager : public QDialog
{
    Q_OBJECT

public:
    explicit ExpManager(QWidget *parent = 0, quint32 tExp = 0);
    ~ExpManager();

    void update_experience(quint32 tExp);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_btn_add_exp_clicked();

    void on_btn_set_exp_to_level_clicked();

    void on_rst_button_clicked();

private:
    Ui::ExpManager *ui;

private:
    void set_top_label();
    void recalculate_experience();

public:
    // Experience and level
    quint32 uTotalExperience;

    quint32 uNewLevel;
    quint32 uNewTotalExperience;
    quint32 uNewExperienceSinceLevel;
    quint32 uNewExperienceToLevel;

};

#endif // EXPMANAGER_H
