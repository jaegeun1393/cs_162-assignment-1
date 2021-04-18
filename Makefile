CC=g++
EXE_FILE=muldiv_print

all: $(EXE_FILE)

$(EXE_FILE): econdata.o econdata.hpp explore_econdata.cpp 
	$(CC) econdata.o explore_econdata.cpp -o $(EXE_FILE)

muldiv.o: econdata.hpp econdata.cpp
	$(CC) -c econdata.cpp

clean:
	rm -f *.o $(EXE_FILE)