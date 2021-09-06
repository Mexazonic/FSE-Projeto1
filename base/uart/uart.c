#include <stdio.h>
#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>        //Used for UART
#include <string.h>
#include "crc16/crc16.h"
#include "uart.h"

//Globals
int uart0_filestream; // filestream

void start_uart() {
    
    uart0_filestream = -1;
    uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);      //Open in non blocking read/write mode
    
    if (uart0_filestream == -1)
        printf("Erro - Não foi possível iniciar a UART.\n");
    else
        printf("UART inicializada!\n");
        
}

struct termios options;
void set_options(){

    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);

    tcsetattr(uart0_filestream, TCSANOW, &options);
}


unsigned char tx_buffer[20]; // buffer data
unsigned char *p_tx_buffer; // pointer to buffer data

unsigned char * create_buffer(char esp_codigo, char codigo_operacao, char subcodigo) {

    p_tx_buffer = &tx_buffer[0];
    *p_tx_buffer++ = 0x01; *p_tx_buffer++ = codigo_operacao; *p_tx_buffer++ = subcodigo;
    *p_tx_buffer++ = 8;
    *p_tx_buffer++ = 5;
    *p_tx_buffer++ = 5;
    *p_tx_buffer++ = 1;

    printf("Buffers de memória criados!\n");
    
    char str[7] = { 0x01, 0x23, 0xC1, 8, 5, 5, 1 };
    int crc = calcula_CRC(str, 7);

    char byte1 = crc & 0xff;
    char byte2 = (crc >> 8) & 0xff;
    *p_tx_buffer++ = byte1;
    *p_tx_buffer++ = byte2;

    printf("CRC: %d, %c, %c\n", crc, byte1, byte2);


    return tx_buffer;
    }


void writeModbus(unsigned char * buffer) {

    if (uart0_filestream != -1)
    {
        printf("Escrevendo caracteres na UART ...");
        int count = write(uart0_filestream, &buffer[0], 9);
        
        if (count < 0)
            printf("UART TX error\n");
        
        else
            printf("escrito.\n");
    }
}


int readModbus() {
    if (uart0_filestream != -1)
    {
        // Read up to 255 characters from the port if they are there
        unsigned char rx_buffer[256];
        int rx_length = read(uart0_filestream, (void*)rx_buffer, 255);      //Filestream, buffer to store in, number of bytes to read (max)
        if (rx_length < 0)
        {
            printf("Erro na leitura.\n"); //An error occured (will occur if there are no bytes)
        }
        else if (rx_length == 0)
        {
            printf("Nenhum dado disponível.\n"); //No data waiting
        }
        else
        {
            //Bytes received
            rx_buffer[rx_length] = '\0';
            int x = (rx_buffer[3] << 24) | (rx_buffer[4] << 16) | (rx_buffer[5] << 8) | rx_buffer[6];
            printf("%i Bytes lidos float: %d\n", rx_length, x);
            //printf("%i Bytes lidos hehe: %s\n\n", rx_length, rx_buffer);
            return x;
        }
    }

    close(uart0_filestream);
}