CC = g++

all: dictionary.cpp

dictionary.cpp:
	$(CC) -O3 -I. dictionary.cpp -o dictionary 
debug:
	$(CC) -g -O3 -I. dictionary.cpp -o dictionary 
run:
	./dictionary
clean:
	rm dictionary

.PHONY: dictionary.cpp clean run