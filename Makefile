CC = g++
CFLAGS = -Wall

default: cppa2z
	$(RM) *.o

run:
	./cppa2z

cppa2z: main.o non_modifying_sequence.t.o
	$(CC) $(CFLAGS) -o cppa2z main.o non_modifying_sequence.t.o

main.o: main.cpp
	$(CC) $(CFLAGS) -I. -c main.cpp

non_modifying_sequence.t.o:
	$(CC) $(CFLAGS) -I. -c ./algorithms/non_modifying_sequence.t.cpp

.PHONY: clean
clean:
	$(RM) cppa2z *.o

