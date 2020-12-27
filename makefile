
CC = g++

LDLIBS = `pkg-config --cflags --libs opencv4`

CFLAGS = -g -Wall -O3

all: PCB_Thinning

PCB_Thinning: main.cpp LinkedList.o 
	$(CC) main.cpp LinkedList.o $(LDLIBS) $(CFLAGS) -o PCB_Thinning 
	
	
LinkedList.o: LinkedList.cpp
	$(CC) -c LinkedList.cpp
	
clean:
	rm *.o PCB_Thinning
