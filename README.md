# Projeto 1 - 2020/2
Executar Projeto

> gcc main.c uart/uart.c crc16/crc16.c bme/bme280.c csv/csv.c driver_lcd/lcd.c PID/pid.c on_off/on_off.c gpio/gpio.c menu/menu.c -lwiringPi controle/controle.c


> ./a.out

## 1. Enunciado

Este trabalho tem por objetivo a implementação do software de uma bancada para testes de controle de temperatura de um sistema que possui internamente dois dispositivos para alterar sua temperatura. O primeiro é um resistor de potência de 15 Watts utilizado para aumentar temperatura e o segundo, uma ventoinha que puxa o ar externo (temperatura ambiente) para reduzir a temperatura do sistema. [Continuação](https://gitlab.com/fse_fga/projetos_2021_1/projeto-1-2021-1)

## Menu
O menu simples apresenta a interação do usuário com seu desejo de alinhar os requisitos solicitados pelo enunciado. Conforme a imagem abaixo:

### Setando Opções
#### On Off
![Menu](https://imgur.com/L3fscsj.png)
#### PID
![Menu2](https://imgur.com/dRPhz1W.png)

## Conclusões
Após a setagem das variáveis começa o processo de execução do [controle do sistema](https://github.com/Mexazonic/FSE-Projeto1/blob/main/base/controle/controle.c) e a partir daí toda a lógica das bibliotecas modularizadas começam a executar. Mas por algum motivo e/ou erro na implementação mesmo após algum tempo o valor da temperatura interna permanece inalterado conforme podemos observar no gráfico abaixo:

![Gráfico](https://imgur.com/aaGQChc.png)

Para tentar reparar esse erro tentei obter o "log" para melhor compreensão do que poderia estar acontecendo:

![Debug](https://imgur.com/FCl7V78.png)

Podemos notar que a intensidade do resistor é acionada entretanto não há alterações e a TI continua constante. A estrutura do csv também é montada e sua ausência é pelo experimento não ter sido concretizado de fato.

## Referências
[Enunciado](https://gitlab.com/fse_fga/projetos_2021_1/projeto-1-2021-1/-/blob/main/README.md)
[Controle Liga/Desliga - Wikipedia](https://pt.wikipedia.org/wiki/Controle_liga-desliga)  
[Controle PID - Wikipedia](https://pt.wikipedia.org/wiki/Controlador_proporcional_integral_derivativo)  
[Driver da Bosh para o sensor BME280](https://github.com/BoschSensortec/BME280_driver)  
[Biblioteca BCM2835 - GPIO](http://www.airspayce.com/mikem/bcm2835/)  
[Controle do LCD 16x2 em C](http://www.bristolwatch.com/rpi/i2clcd.htm)  
[Biblioteca WiringPi GPIO](http://wiringpi.com)  
[PWM via WiringPi](https://www.electronicwings.com/raspberry-pi/raspberry-pi-pwm-generation-using-python-and-c)
