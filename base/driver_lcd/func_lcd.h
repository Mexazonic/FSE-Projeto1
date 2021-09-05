#ifndef LCD_H_
#define LCD_H_

void lcd_init(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);

// Funções
void typeFloat(float myFloat);
void typeInt(int i);
void ClrLcd(void);
void lcdLoc(int line);
void typeChar(char val);
void typeInt(int i);
void typeln(const char *s);

void print_lcd(); //print lcd

#endif