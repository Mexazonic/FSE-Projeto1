/*
  Control Intensity of LED using PWM on Raspberry pi
  http://www.electronicwings.com
 */

#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PWM_PIN_RESISTOR 23
#define PWM_PIN_VENTOINHA 24

void configura_gpio() {
    wiringPiSetup();
    pinMode(PWM_PIN_RESISTOR, OUTPUT);
    softPwmCreate(PWM_PIN_RESISTOR, 1, 100);
    pinMode(PWM_PIN_VENTOINHA, OUTPUT);
    softPwmCreate(PWM_PIN_VENTOINHA, 1, 100);
}   

void liga_gpio(int intensidade) {
    if (intensidade > 0)
    {
        softPwmWrite(PWM_PIN_VENTOINHA, 0);
        softPwmWrite(PWM_PIN_RESISTOR, abs(intensidade));
        printf("Intensidade Resistor %d: %d e Ventoinha%d: %d\n", PWM_PIN_RESISTOR, abs(intensidade), PWM_PIN_VENTOINHA, 0);
    }
    else if (intensidade <= -40)
    {
        softPwmWrite(PWM_PIN_RESISTOR, 0);
        softPwmWrite(PWM_PIN_VENTOINHA, abs(intensidade));
                printf("Intensidade Resistor %d: %d e Ventoinha%d: %d\n", PWM_PIN_RESISTOR, abs(intensidade), PWM_PIN_VENTOINHA, 0);

    }
    else
    {
        softPwmWrite(PWM_PIN_VENTOINHA, 0);
        softPwmWrite(PWM_PIN_RESISTOR, 0);
        printf("Intensidade Resistor %d: %d e Ventoinha%d: %d\n", PWM_PIN_RESISTOR, abs(intensidade), PWM_PIN_VENTOINHA, 0);

    }
}

void fecha_gpio() {
    softPwmWrite(PWM_PIN_VENTOINHA, 0);
    usleep(500000);
    softPwmWrite(PWM_PIN_RESISTOR, 0);
    usleep(500000);
}