#ifndef UART
#define UART

#include <stdio.h>
#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>        //Used for UART
#include <string.h>
#include "../crc16/crc16.h"

int uart0_filestream;
struct termios options;

int inicia_modbus();
float solicita_modbus(char device_code, char request_code, char subcode);
void envia_modbus(char device_code, char request_code, char subcode, int control_value);
void fecha_modbus();

#endif /* UART_MODBUS_H_ */