#ifndef __VERMANIC_DICE_FUNCTIONS__
#define __VERMANIC_DICE_FUNCTIONS__

#include <cstdint>

typedef uint32_t(*FNCTN_PTR)();
typedef uint32_t(*FNCTN_PTR_ARG)(FNCTN_PTR);

uint32_t roll(FNCTN_PTR dice);

uint32_t rollWith(FNCTN_PTR_ARG diceFunction, FNCTN_PTR dice);

uint32_t rollMulti(uint32_t rounds, FNCTN_PTR dice);

uint32_t rollMultiWith(uint32_t rounds, FNCTN_PTR_ARG diceFunction, FNCTN_PTR dice);

uint32_t rollAdvantage(FNCTN_PTR dice);

uint32_t rollDisadvantage(FNCTN_PTR dice);

#endif
