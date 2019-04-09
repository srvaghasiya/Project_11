default: truthOrDare

LIBS = -lwiringPi -lpthread

truthOrDare: app.o comm_driver.o keypad_driver.o lcd_driver.o rotor_driver.o shiftReg_driver.o
	cc ./object/app.o ./object/comm_driver.o ./object/keypad_driver.o ./object/lcd_driver.o ./object/rotor_driver.o ./object/shiftReg_driver.o -o truthOrDare $(LIBS)

app.o: ./application/app.c ./application/app.h
	cc -c ./application/app.c -o ./object/app.o $(LIBS)

comm_driver.o: ./communication/comm_driver.c ./communication/comm_driver.h
	cc -c ./communication/comm_driver.c -o ./object/comm_driver.o $(LIBS)

keypad_driver.o: ./keypad/keypad_driver.c ./keypad/keypad_driver.h
	cc -c ./keypad/keypad_driver.c -o ./object/keypad_driver.o $(LIBS)

lcd_driver.o: ./lcd/lcd_driver.c ./lcd/lcd_driver.h
	cc -c ./lcd/lcd_driver.c -o ./object/lcd_driver.o $(LIBS)

rotor_driver.o: ./rotor/rotor_driver.c ./rotor/rotor_driver.h
	cc -c ./rotor/rotor_driver.c -o ./object/rotor_driver.o $(LIBS)

shiftReg_driver.o: ./shiftReg/shiftReg_driver.c ./shiftReg/shiftReg_driver.h
	cc -c ./shiftReg/shiftReg_driver.c -o ./object/shiftReg_driver.o $(LIBS)

clean:
	rm -f ./object/app.o ./object/comm_driver.o ./object/keypad_driver.o ./object/lcd_driver.o ./object/rotor_driver.o ./object/shiftReg_driver.o
	rm -f truthOrDare
