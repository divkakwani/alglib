
CC = g++
FLAGS = -std=c++11
INCLUDE = -I ../

all : merge_sort.o

merge_sort.o :
	@echo Building test files
	$(CC) $(FLAGS) $(INCLUDE) -o merge_sort sort/merge_sort.cpp

timer_sort.o :
	$(CC) $(FLAGS) $(INCLUDE) -o timer_sort sort/timer_sort.cpp

test : all
	./merge_sort

time :  timer_sort.o
	./timer_sort

clean :
	rm merge_sort timer_sort
