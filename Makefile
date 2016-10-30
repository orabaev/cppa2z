CC = g++
CFLAGS = -Wall -std=c++14
INCLUDE = -I.
COMPILE = $(CC) $(CFLAGS) $(INCLUDE) -c

default: cppa2z

run:
	./cppa2z
	
cppa2z: main.o non_modifying_sequence.t.o modifying_sequence.t.o partitioning.t.o sorting.t.o binary_search.t.o set_operations.t.o heap.t.o min_max.t.o permutation.t.o
	$(CC) $(CFLAGS) -o cppa2z main.o non_modifying_sequence.t.o modifying_sequence.t.o partitioning.t.o sorting.t.o binary_search.t.o set_operations.t.o heap.t.o min_max.t.o permutation.t.o

	./cppa2z

main.o: main.cpp
	$(COMPILE) main.cpp

non_modifying_sequence.t.o: ./algorithms/non_modifying_sequence.t.cpp
	$(COMPILE) ./algorithms/non_modifying_sequence.t.cpp

modifying_sequence.t.o: ./algorithms/modifying_sequence.t.cpp
	$(COMPILE) ./algorithms/modifying_sequence.t.cpp

partitioning.t.o: ./algorithms/partitioning.t.cpp
	$(COMPILE) ./algorithms/partitioning.t.cpp

sorting.t.o: ./algorithms/sorting.t.cpp
	$(COMPILE) ./algorithms/sorting.t.cpp

binary_search.t.o: ./algorithms/binary_search.t.cpp
	$(COMPILE) ./algorithms/binary_search.t.cpp

set_operations.t.o: ./algorithms/set_operations.t.cpp
	$(COMPILE) ./algorithms/set_operations.t.cpp

heap.t.o: ./algorithms/heap.t.cpp
	$(COMPILE) ./algorithms/heap.t.cpp

min_max.t.o: ./algorithms/min_max.t.cpp
	$(COMPILE) ./algorithms/min_max.t.cpp

permutation.t.o: ./algorithms/permutation.t.cpp
	$(COMPILE) ./algorithms/permutation.t.cpp

.PHONY: clean
clean:
	$(RM) cppa2z *.o

