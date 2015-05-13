
CC = g++
FLAGS = -std=c++0x
INCLUDE = -I ../

all : test_sort.o

test_sort.o :
	@echo Building test files
	$(CC) $(FLAGS) $(INCLUDE) -o test_sort algorithms/test_sort.cpp

timer_sort.o :
	$(CC) $(FLAGS) $(INCLUDE) -o timer_sort algorithms/timer_sort.cpp

test : all
	./test_sort

time :  timer_sort.o
	./timer_sort

clean :
	rm test_sort timer_sort
