#ifndef LCD_H_
#define LCD_H_

void lcd_init(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);

void escreve_lcd(float ti, float te, float tr);
void typeInt(int i);
void typeFloat(float myFloat);
void lcdLoc(int line);
void ClrLcd(void); 
void typeln(const char *s);
void typeChar(char val);

#endif /* LCD_H_ */