# This files makes the program evolution_engine_demo
COMPILER = g++
COMPILER_FLAGS = -std=c++14 -c -g -Wall
LINKER = g++ 

evolution_engine_example : evolution_engine_example.o evolution.o
	$(LINKER) evolution_engine_example.o evolution.o ../../img_engine/img.o ../../img_engine/pixel.o -lpng -o demo
evolution_engine_example.o : evolution_engine_example.cpp
	$(COMPILER) $(COMPILER_FLAGS) evolution_engine_example.cpp
evolution.o : ../evolution.h ../evolution.cpp
	$(COMPILER) $(COMPILER_FLAGS) ../evolution.cpp
clean: 
	rm -f *.o demo