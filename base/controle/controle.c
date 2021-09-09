#include "controle.h"
#define CICLOS_SISTEMA 600
#include <stdio.h>

void controle_sistema(variaveis_sistema *params) {

    int T, P, H;
    double sinal_controle = 0;
	int intensidade;

   	// Chave de seleção
	params->sinal_chave = params->define_controle == 3 ? ((int) solicita_modbus(0x01, 0x23, 0xC3)) : params->sinal_chave;

    int i = CICLOS_SISTEMA;
	while(i--) {

		// Leitura da temperatura externa
		bme280ReadValues(&T, &P, &H);
		T -= 150;
		params->TE = (float)T/100.0;

		// Leitura da temperatura interna
		params->TI = solicita_modbus(0x01, 0x23, 0xC1);

        // Leitura da temperatura de referência
		params->TR = solicita_modbus(0x01, 0x23, 0xC2);

		if (params->TI > 0 && params->TR > 0) {

			// Imprimir valores no LCD
			escreve_lcd(params->TE, params->TI, params->TR);

			if(params->sinal_chave == 1) {
				
                // PID
				pid_atualiza_referencia(params->TR);
				sinal_controle = pid_controle(params->TI);
			} else {
				
                // ON OFF
				on_off_atualiza_histerese(params->TR);
				sinal_controle = on_off(params->TI);
			}
			
			// Intensidade
			intensidade = (int) sinal_controle;

			// Sinal de controle
			envia_modbus(0x01, 0x16, 0xD1, intensidade);

			// GPIO
			liga_gpio(intensidade);

			// CSV
			escreve_CSV(params->TI, params->TE, params->TR, sinal_controle);
		}

        // Executar um ciclo por segundo
		sleep(1);
	}
}
