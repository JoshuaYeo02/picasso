# This files makes the program img_engine_example
COMPILER = g++
COMPILER_FLAGS = -std=c++14 -c -g -Wall
LINKER = g++ 

img_engine_example : img_engine_example.o img.o pixel.o
	$(LINKER) img_engine_example.o img.o pixel.o -lpng -o demo
img_engine_example.o : img_engine_example.cpp
	$(COMPILER) $(COMPILER_FLAGS) img_engine_example.cpp
img.o : ../img.h ../img.cpp
	$(COMPILER) $(COMPILER_FLAGS) ../img.cpp
pixel.o : ../pixel.h ../pixel.cpp
	$(COMPILER) $(COMPILER_FLAGS) ../pixel.cpp
clean: 
	rm -f *.o demo