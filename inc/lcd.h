#ifndef LCD_H_
#define LCD_H_

void lcd_init(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);

// added by Lewis
void typeInt(int i);
void typeFloat(float myFloat);
void lcdLoc(int line); //move cursor
void ClrLcd(void); // clr LCD return home
void typeLn(const char *s);
void typeChar(char val);

// added by Djorkaeff
void type_on_first_line(const char *s);
void type_on_second_line(const char *s);
void lcd_loc_first_line();
void lcd_loc_second_line();

#endif /* LCD_H_ */
