#ifndef CONTROLE_H_
#define CONTROLE_H_

#include "../uart/uart.h"
#include "../bme/bme280.h"
#include "../driver_lcd/lcd.h"
#include "../PID/pid.h"
#include "../gpio/gpio.h"
#include "../on_off/on_off.h"
#include "../csv/csv.h"

typedef struct  {
    float histerese;
    int define_controle, sinal_chave, define_temperatura_referencia;
    double KP, KI, KD;
    float TI, TR, TE;
    
} variaveis_sistema;

void controle_sistema(variaveis_sistema *params);

#endif /* CONTROLE_H_ */