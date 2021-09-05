#define USE_OLED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include "driver_lcd/func_lcd.h"

// delay between samples in microseconds
#define DELAY 1000000
// Width of the graph (128 - 40)
#define WIDTH 88


int main(int argc, char *argv[])
{
	 //LCD
	
	lcd_init(); // setup LCD
    print_lcd();
	
	return 0;

	}