CC = g++
CFLAGS = -Wall -std=c++14

default: cppa2z

run:
	./cppa2z
	
cppa2z: main.o non_modifying_sequence.t.o modifying_sequence.t.o partitioning.t.o sorting.t.o binary_search.t.o set_operations.t.o heap.t.o min_max.t.o permutation.t.o
	$(CC) $(CFLAGS) -o cppa2z main.o non_modifying_sequence.t.o modifying_sequence.t.o partitioning.t.o sorting.t.o binary_search.t.o set_operations.t.o heap.t.o min_max.t.o permutation.t.o

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

binary_search.t.o: ./algorithms/binary_search.t.cpp
	$(CC) $(CFLAGS) -I. -c ./algorithms/binary_search.t.cpp

set_operations.t.o: ./algorithms/set_operations.t.cpp
	$(CC) $(CFLAGS) -I. -c ./algorithms/set_operations.t.cpp

heap.t.o: ./algorithms/heap.t.cpp
	$(CC) $(CFLAGS) -I. -c ./algorithms/heap.t.cpp

min_max.t.o: ./algorithms/min_max.t.cpp
	$(CC) $(CFLAGS) -I. -c ./algorithms/min_max.t.cpp

permutation.t.o: ./algorithms/permutation.t.cpp
	$(CC) $(CFLAGS) -I. -c ./algorithms/permutation.t.cpp


.PHONY: clean
clean:
	$(RM) cppa2z *.o

