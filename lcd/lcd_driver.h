#ifndef LCD_DRIVER
#define LCD_DRIVER

#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

#define I2C_ADDR   0x27 // I2C device address

#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command

#define LINE1  0x80 // 1st line
#define LINE2  0xC0 // 2nd line

#define LCD_BACKLIGHT   0x08  // On
// LCD_BACKLIGHT = 0x00  # Off

#define ENABLE  0b00000100 // Enable bit

extern void lcd_init(void);
extern void lcd_byte(int bits,int mode);
extern void lcd_toggle_enable(int bits);

extern void typeInt(int i);
extern void typeFloat(float myFloat);
extern void lcdLoc(int line); //move cursor
extern void ClrLcd(void);
extern void typeln(const char *s);
extern void typeChar(char val);

static void init_i2c();

int fd;

#endif
