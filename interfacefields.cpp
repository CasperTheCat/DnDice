#include "mainwindow.h"
sInterfaceFields::sInterfaceFields()
{

    uMaxHealth = 0;
    uCurrentHealth = 0;
    uExperience = 0;
    uLevel = 1;
    qsName = "[NAME]";
    qsRace = "[RACE]";
    qsClass = "[CLASS]";
}

sInterfaceFields::~sInterfaceFields()
{

}

void sInterfaceFields::reserve(quint64 size)
{
    bProficencyArray.reserve(size);
    bExpertiseArray.reserve(size);
}
