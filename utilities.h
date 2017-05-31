#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>



std::string make_nth(uint64_t numeric)
{
    std::string nthList[10] = {"th","st","nd","rd","th","th","th","th","th","th"};
    std::string nth = nthList[numeric % 10];
    if(numeric % 100 > 10 && numeric % 100 < 14) nth = "th";
    return std::to_string(numeric) + nth;
}


#endif // UTILITIES_H
