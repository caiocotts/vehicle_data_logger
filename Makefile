vdl: vdl.o logger.o serial.o nmea.o dlgps.o sensehat.o
	c++ vdl.o logger.o serial.o nmea.o dlgps.o sensehat.o -lm -lRTIMULib -o vdl
	
vdl.o: vdl.cpp vdl.h logger.h serial.h nmea.h dlgps.h
	c++ vdl.cpp -c

logger.o: logger.cpp logger.h serial.h nmea.h dlgps.h sensehat.h
	c++ logger.cpp -c

serial.o: serial.cpp serial.h
	c++ serial.cpp -c

dlgps.o: dlgps.cpp dlgps.h
	c++ dlgps.cpp -c

nmea.o: nmea.cpp nmea.h
	c++ nmea.cpp -c

sensehat.o: sensehat.cpp sensehat.h
	c++ sensehat.cpp -c
        
clean:
	touch *
	rm -rf *.o rtf 