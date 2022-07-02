
COMPILER = g++
COMPILER_FLAGS = -std=c++14 -c -g -Wall
LINKER = g++

img_engine : img_engine_example.o img.o pixel.o
	$(LINKER) main.o img.o pixel.o -lpng -o img_engine
img_engine_example.o : img_engine_example.cpp img.h pixel.h
	$(COMPILER) $(COMPILER_FLAGS) img_engine_example.cpp
img.o : img.h img.cpp
	$(COMPILER) $(COMPILER_FLAGS) img.cpp
pixel.o : pixel.h img.h pixel.cpp img.cpp
	$(COMPILER) $(COMPILER_FLAGS) pixel.cpp
clean: 
	rm -f *.o img_engine