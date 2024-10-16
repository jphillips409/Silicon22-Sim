OBJECTS = plf.o frag.o tele.o array.o sle.o decay.o   mScat.o fragment.o tower.o  MomDist.o moscow.o ring.o ttt.o fiber.o gobbi.o gtele.o
ALLOBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
CFLAGS= -c -ggdb -std=c++17 -I$(shell root-config --incdir)  -I/home/Neon16/Si22_sims/simlib

COMPILER= c++
LINKOPTION = $(shell root-config --libs) 
LIB =/home/Neon16/Si22_sims/simlib/simlib.a



sim: sim.o $(OBJECTS)
	$(COMPILER) -o sim sim.o $(OBJECTS) $(LIB) $(LINKOPTION)
 

$(ALLOBJECTS): %.o : %.cpp
	$(COMPILER) $(CFLAGS) $< -o $@


clean:
	rm -f *.o

