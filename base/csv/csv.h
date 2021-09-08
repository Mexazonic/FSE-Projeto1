#ifndef CSV_H_
#define CSV_H_
#include <stdio.h>
#include <time.h>
time_t rawtime;
struct tm *info;
char datetime[80];

void CSV();
void escreve_CSV(float TI, double TE, float TR, double intensidade_pwm);

#endif /* CSV_H_ */