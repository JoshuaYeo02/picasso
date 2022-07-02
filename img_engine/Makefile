# This files makes the .o files for Pixel and Img
COMPILER = g++
COMPILER_FLAGS = -std=c++14 -c -g -Wall

_ : img.o pixel.o
img.o : img.h img.cpp
	$(COMPILER) $(COMPILER_FLAGS) img.cpp
pixel.o : pixel.h img.h pixel.cpp img.cpp
	$(COMPILER) $(COMPILER_FLAGS) pixel.cpp
clean: 
	rm -f *.o