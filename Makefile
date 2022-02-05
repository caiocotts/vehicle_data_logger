vdl: vdl.o logger.o serial.o nmea.o dlgps.o
	c++ -lm vdl.o logger.o serial.o nmea.o dlgps.o -o vdl
	
vdl.o: vdl.cpp vdl.h logger.h serial.h nmea.h dlgps.h
	c++ vdl.cpp -c

logger.o: logger.cpp logger.h serial.h nmea.h dlgps.h
	c++ logger.cpp -c 

serial.o: serial.cpp serial.h
	c++ serial.cpp -c 

dlgps.o: dlgps.cpp dlgps.h
	c++ dlgps.cpp -c 

nmea.o: nmea.cpp nmea.h
	c++ nmea.cpp -c 
        
clean:
	touch *
	rm -rf *.o rtf 