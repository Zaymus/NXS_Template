#include "main.h"

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#define degToRad(degrees) degrees/180 *M_PI// converts degrees to radians
#define radToDeg(radians) radians/M_PI *180// converts radians to degrees
#define log(a) cout << #a << ": " << a// custom logging define that outputs the name and value of a variable to the console
#define sgn(x) x > 0 ? 1 : -1// returns the sign of a given number

extern void print(void*);
#endif
