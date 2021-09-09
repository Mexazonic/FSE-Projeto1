#include "uart.h"

int inicia_modbus() {
    
    uart0_filestream = -1;
    uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);      //Open in non blocking read/write mode
    if (uart0_filestream == -1)
    {
        printf("Erro - Não foi possível iniciar a UART.\n");
    }
    else
    {
        printf("UART inicializada!\n");
    }    

    tcgetattr(uart0_filestream, &options);

    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);
}

float solicita_modbus(char device_code, char request_code, char subcode) {

    unsigned char tx_buffer[20] = {device_code, request_code, subcode, 8, 5, 5, 1};
    short crc = calcula_CRC(tx_buffer, 7);
    memcpy(&tx_buffer[7], (const void *)&crc, 2);
    int tx_length = 9;
    if (uart0_filestream != -1)
    {
        int count = write(uart0_filestream, &tx_buffer[0], tx_length);
        
        if (count < 0)
        {
            printf("UART TX error\n");
        }

        usleep(100000);
    }

    int rx_length = 0;
    unsigned char rx_buffer[256];
    float resposta;

    rx_length = read(uart0_filestream, (void *)rx_buffer, 255);
    memcpy(&resposta, &rx_buffer[3], 4);
    return resposta;
}


void envia_modbus(char device_code, char request_code, char subcode, int control_value) {

    unsigned char tx_buffer[20] = {device_code, request_code, subcode, 8, 5, 5, 1};
    memcpy(&tx_buffer[7], (const void *)&control_value, 4);
    short crc = calcula_CRC(tx_buffer, 11);
    memcpy(&tx_buffer[11], (const void *)&crc, 2);
    int tx_length = 13;

    if (uart0_filestream != -1)
    {
        int count = write(uart0_filestream, &tx_buffer[0], tx_length);
        if (count < 0)
        {
            printf("UART TX error\n");
        }
        usleep(100000);
    }
}

void fecha_modbus() {
    close(uart0_filestream);
}