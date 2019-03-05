#ifndef KEYPAD_DRIVER
#define KEYPAD_DRIVER

#include<stdint.h>
#include<wiringPi.h>

#define uint8 uint8_t


extern void init_pins(void);
extern void init_rows(void);
extern void init_cols(void);
extern uint8 colscan(void);
extern uint8 keyscan(void);
extern uint8 keyscan2(void);
extern uint8 get_row(void);
extern uint8 get_col(void);

#endif
