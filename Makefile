CC = g++
CFLAGS = -Wall -std=c++14

default: cppa2z

run:
	./cppa2z
	
cppa2z: main.o non_modifying_sequence.t.o modifying_sequence.t.o partitioning.t.o sorting.t.o
	$(CC) $(CFLAGS) -o cppa2z main.o non_modifying_sequence.t.o modifying_sequence.t.o partitioning.t.o sorting.t.o
	./cppa2z

main.o: main.cpp
	$(CC) $(CFLAGS) -I. -c main.cpp

non_modifying_sequence.t.o: ./algorithms/non_modifying_sequence.t.cpp
	$(CC) $(CFLAGS) -I. -c ./algorithms/non_modifying_sequence.t.cpp

modifying_sequence.t.o: ./algorithms/modifying_sequence.t.cpp
	$(CC) $(CFLAGS) -I. -c ./algorithms/modifying_sequence.t.cpp

partitioning.t.o: ./algorithms/partitioning.t.cpp
	$(CC) $(CFLAGS) -I. -c ./algorithms/partitioning.t.cpp

sorting.t.o: ./algorithms/sorting.t.cpp
	$(CC) $(CFLAGS) -I. -c ./algorithms/sorting.t.cpp


.PHONY: clean
clean:
	$(RM) cppa2z *.o

