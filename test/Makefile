
CC = g++
FLAGS = -std=c++11

all : test_sort.o

test_sort.o :
	@echo Building test files
	$(CC) $(FLAGS) -o test_sort test_sort.cpp

	

check : all
	./test_sort
	
clean :
	rm test_sort
