#include "mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

///
/// \brief MainWindow::interfaceToFields
/// Takes all interface fields and puts them in a structure
///
sInterfaceFields *MainWindow::interfaceToFields()
{

    playerData->reserve(eSkills::TOTAL_NUMBER_SKILLS);
    // Pretend we did something!
    {
        playerData->qbaProfArray.setBit(eSkills::Acrobatics, ui->skills_acro->isChecked() );
        playerData->qbaProfArray.setBit(eSkills::AnimalHandling, ui->skills_animalHandling->isChecked() );
        playerData->qbaProfArray.setBit(eSkills::Arcana, ui->skills_arcana->isChecked() );
        playerData->qbaProfArray.setBit(eSkills::Athletics, ui->skills_athletics->isChecked() );
        playerData->qbaProfArray.setBit(eSkills::Deception, ui->skills_deception->isChecked() );

        playerData->qbaProfArray.setBit(eSkills::History, ui->skills_history->isChecked() );
        playerData->qbaProfArray.setBit(eSkills::Insight, ui->skills_insight->isChecked() );
        playerData->qbaProfArray.setBit(eSkills::Intimidation, ui->skills_intimidation->isChecked() );
        playerData->qbaProfArray.setBit(eSkills::Investigation, ui->skills_investigation->isChecked() );

        playerData->qbaProfArray.setBit(eSkills::Medicine, ui->skills_medicine->isChecked() );
        playerData->qbaProfArray.setBit(eSkills::Nature, ui->skills_nature->isChecked() );
        playerData->qbaProfArray.setBit(eSkills::Perception, ui->skills_perception->isChecked() );
        playerData->qbaProfArray.setBit(eSkills::Performance, ui->skills_performance->isChecked() );

        playerData->qbaProfArray.setBit(eSkills::Persuasion, ui->skills_persuasion->isChecked() );
        playerData->qbaProfArray.setBit(eSkills::Religion, ui->skills_religion->isChecked() );
        playerData->qbaProfArray.setBit(eSkills::Sleight_of_Hand, ui->skills_sleightofhand->isChecked() );
        playerData->qbaProfArray.setBit(eSkills::Stealth, ui->skills_stealth->isChecked() );

        playerData->qbaProfArray.setBit(eSkills::Survival, ui->skills_survival->isChecked() );
    }

    {
        playerData->qbaExpArray.setBit(eSkills::Acrobatics, ui->expertise_acro->isChecked() );
        playerData->qbaExpArray.setBit(eSkills::AnimalHandling, ui->expertise_animalHandling->isChecked() );
        playerData->qbaExpArray.setBit(eSkills::Arcana, ui->expertise_arcana->isChecked() );
        playerData->qbaExpArray.setBit(eSkills::Athletics, ui->expertise_athletics->isChecked() );
        playerData->qbaExpArray.setBit(eSkills::Deception, ui->expertise_deception->isChecked() );

        playerData->qbaExpArray.setBit(eSkills::History, ui->expertise_history->isChecked() );
        playerData->qbaExpArray.setBit(eSkills::Insight, ui->expertise_insight->isChecked() );
        playerData->qbaExpArray.setBit(eSkills::Intimidation, ui->expertise_intimidation->isChecked() );
        playerData->qbaExpArray.setBit(eSkills::Investigation, ui->expertise_investigation->isChecked() );

        playerData->qbaExpArray.setBit(eSkills::Medicine, ui->expertise_medicine->isChecked() );
        playerData->qbaExpArray.setBit(eSkills::Nature, ui->expertise_nature->isChecked() );
        playerData->qbaExpArray.setBit(eSkills::Perception, ui->expertise_perception->isChecked() );
        playerData->qbaExpArray.setBit(eSkills::Performance, ui->expertise_performance->isChecked() );

        playerData->qbaExpArray.setBit(eSkills::Persuasion, ui->expertise_persuasion->isChecked() );
        playerData->qbaExpArray.setBit(eSkills::Religion, ui->expertise_religion->isChecked() );
        playerData->qbaExpArray.setBit(eSkills::Sleight_of_Hand, ui->expertise_sleightofhand->isChecked() );
        playerData->qbaExpArray.setBit(eSkills::Stealth, ui->expertise_stealth->isChecked() );

        playerData->qbaExpArray.setBit(eSkills::Survival, ui->expertise_survival->isChecked() );
    }

    {
        playerData->qbaSaveArray.setBit(eSaves::Strength, ui->other_save_str->isChecked());
        playerData->qbaSaveArray.setBit(eSaves::Dexterity, ui->other_save_dex->isChecked());
        playerData->qbaSaveArray.setBit(eSaves::Constitution, ui->other_save_con->isChecked());
        playerData->qbaSaveArray.setBit(eSaves::Intelligence, ui->other_save_int->isChecked());
        playerData->qbaSaveArray.setBit(eSaves::Wisdom, ui->other_save_wis->isChecked());
        playerData->qbaSaveArray.setBit(eSaves::Charisma, ui->other_save_cha->isChecked());
    }

    //
    return playerData;
}

void MainWindow::fieldsToInterface(sInterfaceFields *loadData)
{
    {
        ui->skills_acro->setChecked( loadData->qbaProfArray.at(eSkills::Acrobatics) );
        ui->skills_animalHandling->setChecked( loadData->qbaProfArray.at(eSkills::AnimalHandling) );
        ui->skills_arcana->setChecked( loadData->qbaProfArray.at(eSkills::Arcana) );
        ui->skills_athletics->setChecked( loadData->qbaProfArray.at(eSkills::Athletics) );
        ui->skills_deception->setChecked( loadData->qbaProfArray.at(eSkills::Deception) );

        ui->skills_history->setChecked( loadData->qbaProfArray.at(eSkills::History) );
        ui->skills_insight->setChecked( loadData->qbaProfArray.at(eSkills::Insight) );
        ui->skills_intimidation->setChecked( loadData->qbaProfArray.at(eSkills::Intimidation) );
        ui->skills_investigation->setChecked( loadData->qbaProfArray.at(eSkills::Investigation) );

        ui->skills_medicine->setChecked( loadData->qbaProfArray.at(eSkills::Medicine) );
        ui->skills_nature->setChecked( loadData->qbaProfArray.at(eSkills::Nature) );
        ui->skills_perception->setChecked( loadData->qbaProfArray.at(eSkills::Perception) );
        ui->skills_performance->setChecked( loadData->qbaProfArray.at(eSkills::Performance) );

        ui->skills_persuasion->setChecked( loadData->qbaProfArray.at(eSkills::Persuasion) );
        ui->skills_religion->setChecked( loadData->qbaProfArray.at(eSkills::Religion) );
        ui->skills_sleightofhand->setChecked( loadData->qbaProfArray.at(eSkills::Sleight_of_Hand) );
        ui->skills_stealth->setChecked( loadData->qbaProfArray.at(eSkills::Stealth) );

        ui->skills_survival->setChecked( loadData->qbaProfArray.at(eSkills::Survival) );
    }
    {
        ui->expertise_acro->setChecked( loadData->qbaExpArray.at(eSkills::Acrobatics) );
        ui->expertise_animalHandling->setChecked( loadData->qbaExpArray.at(eSkills::AnimalHandling) );
        ui->expertise_arcana->setChecked( loadData->qbaExpArray.at(eSkills::Arcana) );
        ui->expertise_athletics->setChecked( loadData->qbaExpArray.at(eSkills::Athletics) );
        ui->expertise_deception->setChecked( loadData->qbaExpArray.at(eSkills::Deception) );

        ui->expertise_history->setChecked( loadData->qbaExpArray.at(eSkills::History) );
        ui->expertise_insight->setChecked( loadData->qbaExpArray.at(eSkills::Insight) );
        ui->expertise_intimidation->setChecked( loadData->qbaExpArray.at(eSkills::Intimidation) );
        ui->expertise_investigation->setChecked( loadData->qbaExpArray.at(eSkills::Investigation) );

        ui->expertise_medicine->setChecked( loadData->qbaExpArray.at(eSkills::Medicine) );
        ui->expertise_nature->setChecked( loadData->qbaExpArray.at(eSkills::Nature) );
        ui->expertise_perception->setChecked( loadData->qbaExpArray.at(eSkills::Perception) );
        ui->expertise_performance->setChecked( loadData->qbaExpArray.at(eSkills::Performance) );

        ui->expertise_persuasion->setChecked( loadData->qbaExpArray.at(eSkills::Persuasion) );
        ui->expertise_religion->setChecked( loadData->qbaExpArray.at(eSkills::Religion) );
        ui->expertise_sleightofhand->setChecked( loadData->qbaExpArray.at(eSkills::Sleight_of_Hand) );
        ui->expertise_stealth->setChecked( loadData->qbaExpArray.at(eSkills::Stealth) );

        ui->expertise_survival->setChecked( loadData->qbaExpArray.at(eSkills::Survival) );
    }

    {
        ui->other_save_str->setChecked( loadData->qbaSaveArray.at(eSaves::Strength) );
        ui->other_save_dex->setChecked( loadData->qbaSaveArray.at(eSaves::Dexterity) );
        ui->other_save_con->setChecked( loadData->qbaSaveArray.at(eSaves::Constitution) );
        ui->other_save_int->setChecked( loadData->qbaSaveArray.at(eSaves::Intelligence) );
        ui->other_save_wis->setChecked( loadData->qbaSaveArray.at(eSaves::Wisdom) );
        ui->other_save_cha->setChecked( loadData->qbaSaveArray.at(eSaves::Charisma) );
    }
}

void MainWindow::serialiseAndPackFields()
{

}

///////////////////////////////////////////////
/// Save stats and name to disk
/// \brief MainWindow::on_actionSave_triggered
///
void MainWindow::on_actionSave_triggered()
{
    // Can only fast save if we already have a location to save at
    if(!bNewFile) saveFile();
    else on_actionSave_As_triggered();
}

void MainWindow::on_actionSave_As_triggered()
{
    // Get user input to select file locations
    //QFileDialog::setDefaultSuffix(tr(".dnd"));
    QString qsLocalFile = QFileDialog::getSaveFileName(this, tr("Save Character"), "", tr("Character Sheet (*.dnd);;All Files(*)"));
    if(qsLocalFile.isEmpty()) return;

    // Set filename and go ahead saving
    qsFileName = qsLocalFile;
    saveFile();
}

///
/// \brief MainWindow::saveFile
/// Saves the file based on stored name
///
void MainWindow::saveFile()
{
    // Prep save
    QFile qfFile(qsFileName);
    if(!qfFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("Unable to open file"), qfFile.errorString());
        return;
    }

    // Interface to fields
    sInterfaceFields *saveData = interfaceToFields();


    QDataStream qdsOut(&qfFile);
    qdsOut.setVersion(QDataStream::Qt_5_8); // USE STABLE BUILD ONLY
    qdsOut << saveData->qsName;
    qdsOut << saveData->qsRace;
    qdsOut << saveData->qsClass;
    qdsOut << saveData->uMaxHealth;
    qdsOut << saveData->uCurrentHealth;
    qdsOut << saveData->uExperience;
    qdsOut << saveData->qbaProfArray;
    qdsOut << saveData->qbaExpArray;
    qdsOut << saveData->qbaSaveArray;


    bNewFile = false;
    updateTitle();
}

void MainWindow::on_actionLoad_triggered()
{
    QString qsLocalFile = QFileDialog::getOpenFileName(this, tr("Load Character"), "", tr("Character Sheet (*.dnd);;All Files(*)"));
    if(qsLocalFile.isEmpty()) return;

    // Load
    qsFileName = qsLocalFile;

    {
        QFile qfFile(qsFileName);
        if(!qfFile.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"), qfFile.errorString());
            return;
        }

        QDataStream qdsIn(&qfFile);
        qdsIn >> playerData->qsName;
        qdsIn >> playerData->qsRace;
        qdsIn >> playerData->qsClass;
        qdsIn >> playerData->uMaxHealth;
        qdsIn >> playerData->uCurrentHealth;
        qdsIn >> playerData->uExperience;
        qdsIn >> playerData->qbaProfArray;
        qdsIn >> playerData->qbaExpArray;
        qdsIn >> playerData->qbaSaveArray;

        bNewFile = false;
        updateTitle();
        fieldsToInterface(playerData);
        expManagerWindow->update_experience(playerData->uExperience);
        update_top_bar();

    }
}

