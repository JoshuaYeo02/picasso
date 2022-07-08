# This files makes the program picasso
COMPILER = g++
COMPILER_FLAGS = -std=c++14 -c -g -Wall
LINKER = g++ 

picasso : main.o img.o pixel.o evolution.o
	$(LINKER) main.o img.o pixel.o evolution.o -lpng -o picasso
	rm -f *.o
main.o : main.cpp
	$(COMPILER) $(COMPILER_FLAGS) main.cpp
img.o : ./img_engine/img.h ./img_engine/img.cpp
	$(COMPILER) $(COMPILER_FLAGS) ./img_engine/img.cpp
pixel.o : ./img_engine/pixel.h ./img_engine/pixel.cpp
	$(COMPILER) $(COMPILER_FLAGS) ./img_engine/pixel.cpp
evolution.o : ./evolution_engine/evolution.cpp ./evolution_engine/evolution.h
	$(COMPILER) $(COMPILER_FLAGS) ./evolution_engine/evolution.cpp
clean: 
	rm -f *.o demo