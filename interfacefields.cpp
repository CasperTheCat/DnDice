#include "mainwindow.h"
sInterfaceFields::sInterfaceFields()
{

    uMaxHealth = 0;
    uCurrentHealth = 0;
    uExperience = 0;
    qsName = "[NAME]";
    qsRace = "[RACE]";
    qsClass = "[CLASS]";
}

sInterfaceFields::~sInterfaceFields()
{

}

void sInterfaceFields::reserve(quint64 size)
{
    qbaProfArray.resize(eSkills::TOTAL_NUMBER_SKILLS);
    qbaExpArray.resize(eSkills::TOTAL_NUMBER_SKILLS);
    qbaSaveArray.resize(eSaves::TOTAL_NUMBER_SAVES);
    //bProficiencyArray.reserve(size);
    //bExpertiseArray.reserve(size);
}
