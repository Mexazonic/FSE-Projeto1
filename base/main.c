#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <signal.h>

#include "menu/menu.h"
#include "controle/controle.h"

void iniciar_sistema();
void fechar_sistema();

int main() {
	
	variaveis_sistema params;
	
	signal(SIGINT, fechar_sistema);
	iniciar_sistema(&params);
	menu(&params);
	controle_sistema(&params);
	fechar_sistema();

	return 0;
}

void iniciar_sistema(variaveis_sistema *params){

	params->KP = 5.0;
	params->KI = 1.0;
	params->KD = 5.0;
	params->histerese = 4.0;

	inicia_modbus();
	bme280Init(1, 0x76);
	lcd_init();
	pid_configura_constantes(params->KP, params->KI, params->KD);
	on_off_define_histerese(params->histerese);
	configura_gpio();
	CSV();
	
	usleep(1000000);
}

void fechar_sistema() {
	
    fecha_gpio();
	fecha_modbus();
}