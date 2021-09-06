#define USE_OLED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include "driver_lcd/func_lcd.h"
#include "bme/bme280.h"
#include "uart/uart.h"



// delay between samples in microseconds
#define DELAY 1000000
// Width of the graph (128 - 40)
#define WIDTH 88


int main(int argc, char *argv[])
{


	start_uart();
    set_options();
    
    char buffer[20];
    strcpy(buffer, create_buffer(0x01, 0x23, 0xC1));
    writeModbus(buffer);

    sleep(1);

	int ti = readModbus();
    printf("%d\n", ti);

	//LCD
	lcd_init(); // setup LCD
    //print_lcd();
	
	//return 0;

	int T, P, H; 

	// BME para temperatura Externa
	int i = bme280Init(1, 0x76);
	
	if (i != 0)
		return -1; 
	

	printf("BME280 Em execução.\n");
	usleep(1000000); // wait for data to settle for first read

	for (i=0; i<5; i++) // read values twice a second for 1 minute
	{	
		printf("%d:\n", i);
		bme280ReadValues(&T, &P, &H);
		T -= 150; // for some reason, the sensor reports temperatures too high

		writeModbus(create_buffer(0x01, 0x23, 0xC1));
		int TI = readModbus();
		

		writeModbus(create_buffer(0x01, 0x23, 0xC2));
		int TR = readModbus();

		printf("Calibrated temp. = %3.2f C, pres. = %6.2f Pa, hum. = %2.2f%%\n", (float)T/100.0, (float)P/256.0, (float)H/1024.0);
		print_lcd((float)T/100.0, (float) ti/1000.0, 33); // write temperature
		
		printf("TE = %3.2f C, TI = %d, TR = %d\n", (float)T/100.0, TI, TR);
		//print_lcd((float)T/100.0, (float) ti/1000.0, 33); // write temperature
		
		usleep(DELAY);
	}


	}