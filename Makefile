CXX = g++
CXXFLAGS = -Wall -std=c++14
INCLUDE = -I. -I./srcgen
COMPILE = $(CXX) $(CXXFLAGS) $(INCLUDE) -c
LINK = $(CXX) $(CXXFLAGS) -o

CPP_FILES := main.cpp $(wildcard srcgen/*.cpp) $(wildcard modern/*.cpp) $(wildcard algorithms/*.cpp) $(wildcard iterators/*.cpp) $(wildcard streams/*.cpp)
OBJ_FILES := $(notdir $(CPP_FILES:.cpp=.o))

default: cppa2z

run:
	./cppa2z
	
cppa2z: $(OBJ_FILES)
	$(LINK) cppa2z $(OBJ_FILES)

	./cppa2z

main.o: main.cpp
	$(COMPILE) main.cpp

#
# srcgen
#
parse_util.o: ./srcgen/parse_util.h ./srcgen/parse_util.cpp
	$(COMPILE) ./srcgen/parse_util.cpp

parse_util.t.o: ./srcgen/parse_util.h ./srcgen/parse_util.cpp ./srcgen/parse_util.t.cpp
	$(COMPILE) ./srcgen/parse_util.t.cpp

md_writer.o: ./srcgen/md_writer.h ./srcgen/md_writer.cpp
	$(COMPILE) ./srcgen/md_writer.cpp

md_writer.t.o: ./srcgen/md_writer.h ./srcgen/md_writer.cpp ./srcgen/md_writer.t.cpp
	$(COMPILE) ./srcgen/md_writer.t.cpp

readme_gen.o: ./srcgen/readme_gen.h ./srcgen/readme_gen.cpp
	$(COMPILE) ./srcgen/readme_gen.cpp

readme_gen.t.o: ./srcgen/readme_gen.h ./srcgen/readme_gen.cpp ./srcgen/readme_gen.t.cpp
	$(COMPILE) ./srcgen/readme_gen.t.cpp

#
# modern
#
lambda.t.o: ./modern/lambda.t.cpp
	$(COMPILE) ./modern/lambda.t.cpp

type_deduction.t.o: ./modern/type_deduction.t.cpp
	$(COMPILE) ./modern/type_deduction.t.cpp

move_symantics.t.o: ./modern/move_symantics.t.cpp
	$(COMPILE) ./modern/move_symantics.t.cpp

range_loop.t.o: ./modern/range_loop.t.cpp
	$(COMPILE) ./modern/range_loop.t.cpp

class_members.t.o: ./modern/class_members.t.cpp
	$(COMPILE) ./modern/class_members.t.cpp

smart_pointers.t.o: ./modern/smart_pointers.t.cpp
	$(COMPILE) ./modern/smart_pointers.t.cpp

literals.t.o: ./modern/literals.t.cpp
	$(COMPILE) ./modern/literals.t.cpp

compile_time.t.o: ./modern/compile_time.t.cpp
	$(COMPILE) ./modern/compile_time.t.cpp

templates.t.o: ./modern/templates.t.cpp
	$(COMPILE) ./modern/templates.t.cpp

#
# algorithms
#
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

numeric_operations.t.o: ./algorithms/numeric_operations.t.cpp
	$(COMPILE) ./algorithms/numeric_operations.t.cpp

#
# iterators
#
iterator_adaptors.t.o: ./iterators/iterator_adaptors.t.cpp
	$(COMPILE) ./iterators/iterator_adaptors.t.cpp

stream_iterators.t.o: ./iterators/stream_iterators.t.cpp
	$(COMPILE) ./iterators/stream_iterators.t.cpp

iterator_operations.t.o: ./iterators/iterator_operations.t.cpp
	$(COMPILE) ./iterators/iterator_operations.t.cpp

#
# streams
#
istream_input.t.o: ./streams/istream_input.t.cpp
	$(COMPILE) ./streams/istream_input.t.cpp

istream_misc.t.o: ./streams/istream_misc.t.cpp
	$(COMPILE) ./streams/istream_misc.t.cpp

istringstream.t.o: ./streams/istringstream.t.cpp
	$(COMPILE) ./streams/istringstream.t.cpp

ifstream.t.o: ./streams/ifstream.t.cpp
	$(COMPILE) ./streams/ifstream.t.cpp

ostream_output.t.o: ./streams/ostream_output.t.cpp
	$(COMPILE) ./streams/ostream_output.t.cpp

ostream_misc.t.o: ./streams/ostream_misc.t.cpp
	$(COMPILE) ./streams/ostream_misc.t.cpp

ostringstream.t.o: ./streams/ostringstream.t.cpp
	$(COMPILE) ./streams/ostringstream.t.cpp

ofstream.t.o: ./streams/ofstream.t.cpp
	$(COMPILE) ./streams/ofstream.t.cpp

adjust_manipulators.t.o: ./streams/adjust_manipulators.t.cpp
	$(COMPILE) ./streams/adjust_manipulators.t.cpp

float_manipulators.t.o: ./streams/float_manipulators.t.cpp
	$(COMPILE) ./streams/float_manipulators.t.cpp

numeric_manipulators.t.o: ./streams/numeric_manipulators.t.cpp
	$(COMPILE) ./streams/numeric_manipulators.t.cpp

time_money_manipulators.t.o: ./streams/time_money_manipulators.t.cpp
	$(COMPILE) ./streams/time_money_manipulators.t.cpp

flush_manipulators.t.o: ./streams/flush_manipulators.t.cpp
	$(COMPILE) ./streams/flush_manipulators.t.cpp

flags_manipulators.t.o: ./streams/flags_manipulators.t.cpp
	$(COMPILE) ./streams/flags_manipulators.t.cpp

ws_manipulators.t.o: ./streams/ws_manipulators.t.cpp
	$(COMPILE) ./streams/ws_manipulators.t.cpp

char_manipulators.t.o: ./streams/char_manipulators.t.cpp
	$(COMPILE) ./streams/char_manipulators.t.cpp

.PHONY: clean
clean:
	$(RM) cppa2z *.o


