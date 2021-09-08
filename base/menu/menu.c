#include "menu.h"
#include <stdio.h>

int define_controle;
int define_temperatura_referencia;
float temp_reference;
float histerese;
double KP, KI, KD;

void menu(variaveis_sistema *params) {
    printf("\n**************************\n");
    printf("****Controle Temperatura****\n");
    printf("\n**************************\n");
    

    printf("\n**************************\n");
    printf("****Controle****\n");
    printf("1 - On_Off\n");
    printf("2 - PID\n");
    printf("3 - Chave seletora\n");
     printf("\n**************************\n\n");
    printf("\nSelecione uma opcao: ");
    
    scanf("%d", &define_controle);
    params->define_controle = define_controle;

    switch(define_controle) {
        case 1:
            params->sinal_chave = 0;
            printf("Digite a histerese:");
            scanf("%f", &histerese);
            params->histerese = histerese;
            printf("\n");
            break;
        case 2:
            params->sinal_chave = 1;
            printf("Digite o KP:");
            scanf("%lf", &KP);
            params->KP = KP;
            
            printf("\n");
            printf("Digite o KI:");
            scanf("%lf", &KI);
            params->KI = KI;

            printf("\n");
            printf("Digite o KD:");
            scanf("%lf", &KD);
            params->KD = KD;

            printf("\n");
            break;
            
        default:
            printf("\nOpção inválida. Constantes padrões serão usadas.\n\n");
            
    }

    printf("\n**************************\n");
    printf("****Temperatura****\n");
    printf("\n1 - Potenciometro\n");
    printf("2 - Definir temperatura pelo teclado \n");
    printf("\n**************************\n\n");
    printf("\nSelecione uma opcao: ");
    
    scanf("%d", &define_temperatura_referencia);
    params->define_temperatura_referencia = define_temperatura_referencia;

    switch(define_temperatura_referencia) {
        case 2:
            printf("\nDigite a Temp. de referencia:");
            scanf("%f", &temp_reference);
            params->TR = temp_reference;
            printf("\n");
            break;
        default:
            printf("\nOpção inválida. Constantes padrões serão usadas.\n\n");
    }    
}

