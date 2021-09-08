#include "on_off.h"

double hysteresis;
double tr;

void on_off_define_histerese(float histerese){
    hysteresis = histerese;
}

void on_off_atualiza_histerese(float referencia){
    tr = referencia;
}

double on_off(float saida_medida){
    
	double intervalo = hysteresis / 2;
	int sinal_de_controle_MAX = 100.0;
	int sinal_de_controle_MIN = -100.0;

	
	if(saida_medida < tr - intervalo) {
		return sinal_de_controle_MAX;
	} else if(saida_medida == (tr + intervalo)) {
		return 0;}
	
	return sinal_de_controle_MIN;
	
}