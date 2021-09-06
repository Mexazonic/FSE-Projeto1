#ifndef UART_MODBUS_H_
#define UART_MODBUS_H_

void start_uart();
void set_options();
unsigned char * create_buffer(char device_code, char request_code, char subcode);
void writeModbus(unsigned char * buffer);
int readModbus();

#endif /* UART_MODBUS_H_ */