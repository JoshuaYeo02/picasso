# This files makes the program picasso
COMPILER = g++
COMPILER_FLAGS = -std=c++14 -c -g -Wall 
LINKER = g++ 
MAC = -I/opt/homebrew/Cellar/libpng/1.6.37/include/libpng16
MAC_LINKER = g++ -I/opt/homebrew/Cellar/libpng/1.6.37/include/libpng16 -L/opt/homebrew/Cellar/libpng/1.6.37/lib -lpng16 -lz

picasso : main.o img.o pixel.o evolution.o
ifdef mac
	$(MAC_LINKER) main.o img.o pixel.o evolution.o -o picasso
	rm -f *.o
else
	$(LINKER) main.o img.o pixel.o evolution.o -lpng -o picasso
	rm -f *.o
endif
main.o : main.cpp
ifdef mac
	$(COMPILER) $(MAC) $(COMPILER_FLAGS) main.cpp
else
	$(COMPILER) $(COMPILER_FLAGS) main.cpp
endif
img.o : ./img_engine/img.h ./img_engine/img.cpp
ifdef mac
	$(COMPILER) $(MAC) $(COMPILER_FLAGS) ./img_engine/img.cpp
else
	$(COMPILER) $(COMPILER_FLAGS) ./img_engine/img.cpp
endif
pixel.o : ./img_engine/pixel.h ./img_engine/pixel.cpp
ifdef mac
	$(COMPILER) $(MAC) $(COMPILER_FLAGS) ./img_engine/pixel.cpp
else
	$(COMPILER) $(COMPILER_FLAGS) ./img_engine/pixel.cpp
endif
evolution.o : ./evolution_engine/evolution.cpp ./evolution_engine/evolution.h
ifdef mac
	$(COMPILER) $(MAC) $(COMPILER_FLAGS) ./evolution_engine/evolution.cpp
else
	$(COMPILER) $(COMPILER_FLAGS) ./evolution_engine/evolution.cpp
endif
clean: 
	rm -f *.o picasso