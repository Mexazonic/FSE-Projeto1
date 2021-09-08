 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "csv.h"

void CSV()
{
    FILE *f;
    f = fopen("report_log.csv", "w");
    fprintf(f, "Data_Hora,  TI,  TE,  TR,  Sinal_Controle\n");
    fclose(f);
}

void escreve_CSV(float TI, double TE, float TR, double intensidade_pwm)
{
    FILE *f;
    f = fopen("log.csv", "a");
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(datetime, 80, "%d/%m/%Y %H:%M:%S", info);
    fprintf(f, "%s, %f, %lf, %f, %lf\n", datetime, TI, TE, TR, intensidade_pwm);
    fclose(f);
}