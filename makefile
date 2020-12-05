
CC = g++

OPENCV_LIBS = $(shell pkg-config --cflags --libs opencv4)

CFLAGS = -g -Wall

all: PCB_Thinning_stlList PCB_Thinning_LinkedList PCB_Thinning_pthread

PCB_Thinning_LinkedList: main_LinkedList.cpp LinkedList.o 
	$(CC) main_LinkedList.cpp LinkedList.o $(OPENCV_LIBS) $(CFLAGS) -o PCB_Thinning_LinkedList 
	
PCB_Thinning_stlList: main.cpp
	$(CC) main.cpp $(OPENCV_LIBS) $(CFLAGS) -o PCB_Thinning_stlList 
	
PCB_Thinning_pthread: main_pthread.cpp
	$(CC) main_pthread.cpp $(OPENCV_LIBS) -lpthread $(CFLAGS) -o PCB_Thinning_pthread
	
LinkedList.o: LinkedList.cpp
	$(CC) -c LinkedList.cpp
	
clean:
	rm *.o PCB_Thinning_LinkedList PCB_Thinning_stlList PCB_Thinning_pthread
