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
    return playerData;
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
    qdsOut << saveData->uLevel;

    bNewFile = false;
    updateTitle();
}
