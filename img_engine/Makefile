
COMPILER = g++
COMPILER_FLAGS = -std=c++14 -c -g -Wall
LINKER = g++

img_engine : main.o img.o pixel.o
	$(LINKER) main.o img.o pixel.o -lpng -o img_engine
main.o : main.cpp img.h pixel.h
	$(COMPILER) $(COMPILER_FLAGS) main.cpp
img.o : img.h img.cpp
	$(COMPILER) $(COMPILER_FLAGS) img.cpp
pixel.o : pixel.h img.h pixel.cpp img.cpp
	$(COMPILER) $(COMPILER_FLAGS) pixel.cpp
clean: 
	rm -f *.o img_engine