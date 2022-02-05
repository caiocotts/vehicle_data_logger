vdl: vdl.o
	c++ vdl.o -o vdl

vdl.o: vdl.cpp
	c++ -c vdl.cpp

refman:
	doxygen ceng252

clean:
	rm -rf *.o rtf