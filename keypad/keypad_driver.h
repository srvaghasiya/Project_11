#ifndef _KEYPAD_DRIVER_H_
#define _KEYPAD_DRIVER_H_

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

extern uint8 abc;

#endif
