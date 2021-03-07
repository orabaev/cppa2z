[![Build Status](https://travis-ci.org/orabaev/cppa2z.svg?branch=master)](https://travis-ci.org/orabaev/cppa2z)  
# cppa2z
Document modern C++ using unit tests   
## C++11/14
**lambda** [[]](./modern_11_14/lambda.t.cpp#L10) &nbsp;&nbsp;[(int x)](./modern_11_14/lambda.t.cpp#L28) &nbsp;&nbsp;[[=]](./modern_11_14/lambda.t.cpp#L39) &nbsp;&nbsp;[mutable](./modern_11_14/lambda.t.cpp#L54) &nbsp;&nbsp;[[&]](./modern_11_14/lambda.t.cpp#L69) &nbsp;&nbsp;[[&x, y]](./modern_11_14/lambda.t.cpp#L85) &nbsp;&nbsp;[-> type](./modern_11_14/lambda.t.cpp#L100) &nbsp;&nbsp;[[=, &x]](./modern_11_14/lambda.t.cpp#L112) &nbsp;&nbsp;[[&, x]](./modern_11_14/lambda.t.cpp#L128) &nbsp;&nbsp;[[this]](./modern_11_14/lambda.t.cpp#L145) &nbsp;&nbsp;[(auto x)](./modern_11_14/lambda.t.cpp#L174) &nbsp;&nbsp;[(x = value)](./modern_11_14/lambda.t.cpp#L199) &nbsp;&nbsp;[callback](./modern_11_14/lambda.t.cpp#L234) &nbsp;&nbsp;**type deduction** [auto](./modern_11_14/type_deduction.t.cpp#L9) &nbsp;&nbsp;[decltype](./modern_11_14/type_deduction.t.cpp#L107) &nbsp;&nbsp;[decltype(auto)](./modern_11_14/type_deduction.t.cpp#L153) &nbsp;&nbsp;**range-based for loop** [for (auto v : r)](./modern_11_14/range_loop.t.cpp#L9) &nbsp;&nbsp;[(const auto& v : r)](./modern_11_14/range_loop.t.cpp#L28) &nbsp;&nbsp;[(auto& v : r)](./modern_11_14/range_loop.t.cpp#L44) &nbsp;&nbsp;**move symantics** [rvalue references](./modern_11_14/move_symantics.t.cpp#L9) &nbsp;&nbsp;[move](./modern_11_14/move_symantics.t.cpp#L58) &nbsp;&nbsp;[forward](./modern_11_14/move_symantics.t.cpp#L108) &nbsp;&nbsp;[special member functions](./modern_11_14/move_symantics.t.cpp#L123) &nbsp;&nbsp;**class members** [delegating constructors](./modern_11_14/class_members.t.cpp#L6) &nbsp;&nbsp;[default functions](./modern_11_14/class_members.t.cpp#L50) &nbsp;&nbsp;[deleted functions](./modern_11_14/class_members.t.cpp#L93) &nbsp;&nbsp;[explicit virtual overrides](./modern_11_14/class_members.t.cpp#L189) &nbsp;&nbsp;[final specifier](./modern_11_14/class_members.t.cpp#L209) &nbsp;&nbsp;**smart pointers** [nullptr](./modern_11_14/smart_pointers.t.cpp#L8) &nbsp;&nbsp;[unique_ptr](./modern_11_14/smart_pointers.t.cpp#L47) &nbsp;&nbsp;[shared_ptr](./modern_11_14/smart_pointers.t.cpp#L193) &nbsp;&nbsp;[weak_ptr](./modern_11_14/smart_pointers.t.cpp#L415) &nbsp;&nbsp;**literals** [binary](./modern_11_14/literals.t.cpp#L6) &nbsp;&nbsp;[user-defined](./modern_11_14/literals.t.cpp#L36) &nbsp;&nbsp;[std-user-defined](./modern_11_14/literals.t.cpp#L48) &nbsp;&nbsp;[digit separators](./modern_11_14/literals.t.cpp#L70) &nbsp;&nbsp;**compile-time** [static assertions](./modern_11_14/compile_time.t.cpp#L10) &nbsp;&nbsp;[constexpr](./modern_11_14/compile_time.t.cpp#L21) &nbsp;&nbsp;**templates** [template aliases](./modern_11_14/templates.t.cpp#L17) &nbsp;&nbsp;[variadic templates](./modern_11_14/templates.t.cpp#L67) &nbsp;&nbsp;  
## C++17
**utility types** [any](./modern_17/utility_types.t.cpp#L11) &nbsp;&nbsp;[optional](./modern_17/utility_types.t.cpp#L46) &nbsp;&nbsp;[variant](./modern_17/utility_types.t.cpp#L100) &nbsp;&nbsp;[tuple](./modern_17/utility_types.t.cpp#L217) &nbsp;&nbsp;[string_view](./modern_17/utility_types.t.cpp#L263) &nbsp;&nbsp;**structured bindings** [data members](./modern_17/structured_bindings.t.cpp#L9) &nbsp;&nbsp;[arrays](./modern_17/structured_bindings.t.cpp#L71) &nbsp;&nbsp;[tuple ](./modern_17/structured_bindings.t.cpp#L95) &nbsp;&nbsp;[range loop ](./modern_17/structured_bindings.t.cpp#L108) &nbsp;&nbsp;  
## algorithms
**non modifying** [adjacent_find](./algorithms/non_modifying_sequence.t.cpp#L10) &nbsp;&nbsp;[all_of(C++11)](./algorithms/non_modifying_sequence.t.cpp#L48) &nbsp;&nbsp;[any_of(C++11)](./algorithms/non_modifying_sequence.t.cpp#L60) &nbsp;&nbsp;[count](./algorithms/non_modifying_sequence.t.cpp#L72) &nbsp;&nbsp;[count_if](./algorithms/non_modifying_sequence.t.cpp#L82) &nbsp;&nbsp;[equal](./algorithms/non_modifying_sequence.t.cpp#L94) &nbsp;&nbsp;[find](./algorithms/non_modifying_sequence.t.cpp#L144) &nbsp;&nbsp;[find_first_of](./algorithms/non_modifying_sequence.t.cpp#L159) &nbsp;&nbsp;[find_if](./algorithms/non_modifying_sequence.t.cpp#L200) &nbsp;&nbsp;[find_if_not](./algorithms/non_modifying_sequence.t.cpp#L217) &nbsp;&nbsp;[find_end](./algorithms/non_modifying_sequence.t.cpp#L234) &nbsp;&nbsp;[for_each](./algorithms/non_modifying_sequence.t.cpp#L270) &nbsp;&nbsp;[for_each_n(C++17)](./algorithms/non_modifying_sequence.t.cpp#L296) &nbsp;&nbsp;[mismatch](./algorithms/non_modifying_sequence.t.cpp#L322) &nbsp;&nbsp;[none_of(C++11)](./algorithms/non_modifying_sequence.t.cpp#L368) &nbsp;&nbsp;[search](./algorithms/non_modifying_sequence.t.cpp#L380) &nbsp;&nbsp;[search_n](./algorithms/non_modifying_sequence.t.cpp#L421) &nbsp;&nbsp;**modifying** [copy](./algorithms/modifying_sequence.t.cpp#L10) &nbsp;&nbsp;[copy_backward](./algorithms/modifying_sequence.t.cpp#L61) &nbsp;&nbsp;[copy_if(C++11)](./algorithms/modifying_sequence.t.cpp#L74) &nbsp;&nbsp;[copy_n(C++11)](./algorithms/modifying_sequence.t.cpp#L90) &nbsp;&nbsp;[fill](./algorithms/modifying_sequence.t.cpp#L103) &nbsp;&nbsp;[fill_n](./algorithms/modifying_sequence.t.cpp#L116) &nbsp;&nbsp;[generate](./algorithms/modifying_sequence.t.cpp#L131) &nbsp;&nbsp;[generate_n](./algorithms/modifying_sequence.t.cpp#L147) &nbsp;&nbsp;[iter_swap](./algorithms/modifying_sequence.t.cpp#L163) &nbsp;&nbsp;[move(C++11)](./algorithms/modifying_sequence.t.cpp#L187) &nbsp;&nbsp;[move_backward(C++11)](./algorithms/modifying_sequence.t.cpp#L203) &nbsp;&nbsp;[remove](./algorithms/modifying_sequence.t.cpp#L218) &nbsp;&nbsp;[remove_if](./algorithms/modifying_sequence.t.cpp#L232) &nbsp;&nbsp;[remove_copy](./algorithms/modifying_sequence.t.cpp#L248) &nbsp;&nbsp;[remove_copy_if](./algorithms/modifying_sequence.t.cpp#L262) &nbsp;&nbsp;[replace](./algorithms/modifying_sequence.t.cpp#L278) &nbsp;&nbsp;[replace_if](./algorithms/modifying_sequence.t.cpp#L291) &nbsp;&nbsp;[replace_copy](./algorithms/modifying_sequence.t.cpp#L307) &nbsp;&nbsp;[replace_copy_if](./algorithms/modifying_sequence.t.cpp#L330) &nbsp;&nbsp;[reverse](./algorithms/modifying_sequence.t.cpp#L353) &nbsp;&nbsp;[reverse_copy](./algorithms/modifying_sequence.t.cpp#L366) &nbsp;&nbsp;[rotate](./algorithms/modifying_sequence.t.cpp#L380) &nbsp;&nbsp;[sample(C++17)](./algorithms/modifying_sequence.t.cpp#L422) &nbsp;&nbsp;[shuffle(C++11)](./algorithms/modifying_sequence.t.cpp#L440) &nbsp;&nbsp;[swap](./algorithms/modifying_sequence.t.cpp#L457) &nbsp;&nbsp;[swap_ranges](./algorithms/modifying_sequence.t.cpp#L481) &nbsp;&nbsp;[transform](./algorithms/modifying_sequence.t.cpp#L498) &nbsp;&nbsp;[unique](./algorithms/modifying_sequence.t.cpp#L539) &nbsp;&nbsp;[unique_copy](./algorithms/modifying_sequence.t.cpp#L567) &nbsp;&nbsp;**partitioning** [is_partitioned(C++11)](./algorithms/partitioning.t.cpp#L6) &nbsp;&nbsp;[partition](./algorithms/partitioning.t.cpp#L26) &nbsp;&nbsp;[partition_copy(C++11)](./algorithms/partitioning.t.cpp#L63) &nbsp;&nbsp;[partition_point(C++11)](./algorithms/partitioning.t.cpp#L89) &nbsp;&nbsp;[stable_partition](./algorithms/partitioning.t.cpp#L116) &nbsp;&nbsp;**sorting** [is_sorted(C++11)](./algorithms/sorting.t.cpp#L8) &nbsp;&nbsp;[is_sorted_until(C++11)](./algorithms/sorting.t.cpp#L30) &nbsp;&nbsp;[nth_element](./algorithms/sorting.t.cpp#L70) &nbsp;&nbsp;[partial_sort](./algorithms/sorting.t.cpp#L108) &nbsp;&nbsp;[partial_sort_copy](./algorithms/sorting.t.cpp#L134) &nbsp;&nbsp;[sort](./algorithms/sorting.t.cpp#L169) &nbsp;&nbsp;[stable_sort](./algorithms/sorting.t.cpp#L201) &nbsp;&nbsp;**set operations** [includes](./algorithms/set_operations.t.cpp#L7) &nbsp;&nbsp;[inplace_merge](./algorithms/set_operations.t.cpp#L40) &nbsp;&nbsp;[merge](./algorithms/set_operations.t.cpp#L75) &nbsp;&nbsp;[set_difference](./algorithms/set_operations.t.cpp#L114) &nbsp;&nbsp;[set_intersecion](./algorithms/set_operations.t.cpp#L154) &nbsp;&nbsp;[set_symmetric_difference](./algorithms/set_operations.t.cpp#L194) &nbsp;&nbsp;[set_union](./algorithms/set_operations.t.cpp#L235) &nbsp;&nbsp;**heap operations** [is_heap(C++11)](./algorithms/heap.t.cpp#L8) &nbsp;&nbsp;[is_heap_until(C++11)](./algorithms/heap.t.cpp#L52) &nbsp;&nbsp;[make_heap](./algorithms/heap.t.cpp#L132) &nbsp;&nbsp;[push_heap](./algorithms/heap.t.cpp#L152) &nbsp;&nbsp;[pop_heap](./algorithms/heap.t.cpp#L180) &nbsp;&nbsp;[sort_heap](./algorithms/heap.t.cpp#L221) &nbsp;&nbsp;**min max** [clamp(C++17)](./algorithms/min_max.t.cpp#L8) &nbsp;&nbsp;[max](./algorithms/min_max.t.cpp#L32) &nbsp;&nbsp;[max_element](./algorithms/min_max.t.cpp#L76) &nbsp;&nbsp;[min](./algorithms/min_max.t.cpp#L98) &nbsp;&nbsp;[min_element](./algorithms/min_max.t.cpp#L143) &nbsp;&nbsp;[minmax(C++11)](./algorithms/min_max.t.cpp#L165) &nbsp;&nbsp;[minmax_element(C++11)](./algorithms/min_max.t.cpp#L215) &nbsp;&nbsp;**permutation** [is_permutation(C++11)](./algorithms/permutation.t.cpp#L8) &nbsp;&nbsp;[lexicographical_compare](./algorithms/permutation.t.cpp#L71) &nbsp;&nbsp;[next_permutation](./algorithms/permutation.t.cpp#L134) &nbsp;&nbsp;[prev_permutation](./algorithms/permutation.t.cpp#L197) &nbsp;&nbsp;**numeric operations** [accumulate](./algorithms/numeric_operations.t.cpp#L9) &nbsp;&nbsp;[adjacent_difference](./algorithms/numeric_operations.t.cpp#L42) &nbsp;&nbsp;[inner_product](./algorithms/numeric_operations.t.cpp#L69) &nbsp;&nbsp;[iota](./algorithms/numeric_operations.t.cpp#L112) &nbsp;&nbsp;[partial_sum](./algorithms/numeric_operations.t.cpp#L127) &nbsp;&nbsp;[reduce(C++17)](./algorithms/numeric_operations.t.cpp#L155) &nbsp;&nbsp;[exclusive_scan(C++17)](./algorithms/numeric_operations.t.cpp#L185) &nbsp;&nbsp;[inclusive_scan(C++17)](./algorithms/numeric_operations.t.cpp#L224) &nbsp;&nbsp;[transform_reduce(C++17)](./algorithms/numeric_operations.t.cpp#L257) &nbsp;&nbsp;[transform_exclusive_scan(C++17)](./algorithms/numeric_operations.t.cpp#L279) &nbsp;&nbsp;[transform_inclusive_scan(C++17)](./algorithms/numeric_operations.t.cpp#L304) &nbsp;&nbsp;  
## iterators
**adaptors** [back_inserter](./iterators/iterator_adaptors.t.cpp#L18) &nbsp;&nbsp;[front_inserter](./iterators/iterator_adaptors.t.cpp#L47) &nbsp;&nbsp;[inserter](./iterators/iterator_adaptors.t.cpp#L76) &nbsp;&nbsp;[make_move_iterator](./iterators/iterator_adaptors.t.cpp#L117) &nbsp;&nbsp;[make_reverse_iterator](./iterators/iterator_adaptors.t.cpp#L136) &nbsp;&nbsp;**operations** [advance](./iterators/iterator_operations.t.cpp#L12) &nbsp;&nbsp;[distance](./iterators/iterator_operations.t.cpp#L34) &nbsp;&nbsp;[next](./iterators/iterator_operations.t.cpp#L65) &nbsp;&nbsp;[prev](./iterators/iterator_operations.t.cpp#L93) &nbsp;&nbsp;**stream iterators** [istream_iterator](./iterators/stream_iterators.t.cpp#L15) &nbsp;&nbsp;[istreambuf_iterator](./iterators/stream_iterators.t.cpp#L46) &nbsp;&nbsp;[ostream_iterator](./iterators/stream_iterators.t.cpp#L64) &nbsp;&nbsp;[ostreambuf_iterator](./iterators/stream_iterators.t.cpp#L82) &nbsp;&nbsp;  
## streams
### istream
**input functions** [operator >>](./streams/istream_input.t.cpp#L8) &nbsp;&nbsp;[gcount](./streams/istream_input.t.cpp#L61) &nbsp;&nbsp;[get](./streams/istream_input.t.cpp#L133) &nbsp;&nbsp;[getline](./streams/istream_input.t.cpp#L246) &nbsp;&nbsp;[std::getline](./streams/istream_input.t.cpp#L304) &nbsp;&nbsp;[ignore](./streams/istream_input.t.cpp#L358) &nbsp;&nbsp;[peek](./streams/istream_input.t.cpp#L396) &nbsp;&nbsp;[putback](./streams/istream_input.t.cpp#L418) &nbsp;&nbsp;[read](./streams/istream_input.t.cpp#L454) &nbsp;&nbsp;[readsome](./streams/istream_input.t.cpp#L509) &nbsp;&nbsp;[unget](./streams/istream_input.t.cpp#L552) &nbsp;&nbsp;**miscellaneous** [tellg](./streams/istream_misc.t.cpp#L9) &nbsp;&nbsp;[seekg](./streams/istream_misc.t.cpp#L44) &nbsp;&nbsp;[sentry](./streams/istream_misc.t.cpp#L126) &nbsp;&nbsp;[sync](./streams/istream_misc.t.cpp#L143) &nbsp;&nbsp;**istringstream** [ctor](./streams/istringstream.t.cpp#L6) &nbsp;&nbsp;[opearator=](./streams/istringstream.t.cpp#L21) &nbsp;&nbsp;[swap](./streams/istringstream.t.cpp#L34) &nbsp;&nbsp;[rdbuf](./streams/istringstream.t.cpp#L58) &nbsp;&nbsp;[str](./streams/istringstream.t.cpp#L68) &nbsp;&nbsp;**ifstream** [ctor](./streams/ifstream.t.cpp#L7) &nbsp;&nbsp;[operator=](./streams/ifstream.t.cpp#L66) &nbsp;&nbsp;[swap](./streams/ifstream.t.cpp#L85) &nbsp;&nbsp;[rdbuf](./streams/ifstream.t.cpp#L120) &nbsp;&nbsp;[is_open](./streams/ifstream.t.cpp#L130) &nbsp;&nbsp;[open](./streams/ifstream.t.cpp#L156) &nbsp;&nbsp;[close](./streams/ifstream.t.cpp#L187) &nbsp;&nbsp;  
### ostream
**output functions** [operator << ](./streams/ostream_output.t.cpp#L8) &nbsp;&nbsp;[put](./streams/ostream_output.t.cpp#L64) &nbsp;&nbsp;[write](./streams/ostream_output.t.cpp#L87) &nbsp;&nbsp;**miscellaneous** [tellp](./streams/ostream_misc.t.cpp#L7) &nbsp;&nbsp;[seekp](./streams/ostream_misc.t.cpp#L27) &nbsp;&nbsp;[ sentry](./streams/ostream_misc.t.cpp#L102) &nbsp;&nbsp;[flush](./streams/ostream_misc.t.cpp#L117) &nbsp;&nbsp;**ostringstream** [ctor](./streams/ostringstream.t.cpp#L6) &nbsp;&nbsp;[opearator=](./streams/ostringstream.t.cpp#L61) &nbsp;&nbsp;[swap](./streams/ostringstream.t.cpp#L74) &nbsp;&nbsp;[rdbuf](./streams/ostringstream.t.cpp#L98) &nbsp;&nbsp;[str](./streams/ostringstream.t.cpp#L108) &nbsp;&nbsp;**ofstream** [ctor](./streams/ofstream.t.cpp#L7) &nbsp;&nbsp;[operator=](./streams/ofstream.t.cpp#L114) &nbsp;&nbsp;[swap](./streams/ofstream.t.cpp#L130) &nbsp;&nbsp;[rdbuf](./streams/ofstream.t.cpp#L161) &nbsp;&nbsp;[is_open](./streams/ofstream.t.cpp#L171) &nbsp;&nbsp;[open](./streams/ofstream.t.cpp#L194) &nbsp;&nbsp;[close](./streams/ofstream.t.cpp#L223) &nbsp;&nbsp;  
### manipulators
**adjust** [left](./streams/adjust_manipulators.t.cpp#L6) &nbsp;&nbsp;[right](./streams/adjust_manipulators.t.cpp#L34) &nbsp;&nbsp;[internal](./streams/adjust_manipulators.t.cpp#L62) &nbsp;&nbsp;[setfill](./streams/adjust_manipulators.t.cpp#L96) &nbsp;&nbsp;[setw](./streams/adjust_manipulators.t.cpp#L111) &nbsp;&nbsp;**floating-point** [showpoint](./streams/float_manipulators.t.cpp#L10) &nbsp;&nbsp;[noshowpoint](./streams/float_manipulators.t.cpp#L30) &nbsp;&nbsp;[fixed](./streams/float_manipulators.t.cpp#L50) &nbsp;&nbsp;[scientific](./streams/float_manipulators.t.cpp#L62) &nbsp;&nbsp;[hexfloat](./streams/float_manipulators.t.cpp#L74) &nbsp;&nbsp;[defaultfloat](./streams/float_manipulators.t.cpp#L86) &nbsp;&nbsp;[setprecision](./streams/float_manipulators.t.cpp#L98) &nbsp;&nbsp;**numeric** [boolalpha](./streams/numeric_manipulators.t.cpp#L6) &nbsp;&nbsp;[noboolalpha](./streams/numeric_manipulators.t.cpp#L39) &nbsp;&nbsp;[showbase](./streams/numeric_manipulators.t.cpp#L72) &nbsp;&nbsp;[noshowbase](./streams/numeric_manipulators.t.cpp#L122) &nbsp;&nbsp;[showpos](./streams/numeric_manipulators.t.cpp#L172) &nbsp;&nbsp;[noshowpos](./streams/numeric_manipulators.t.cpp#L192) &nbsp;&nbsp;[uppercase](./streams/numeric_manipulators.t.cpp#L212) &nbsp;&nbsp;[nouppercase](./streams/numeric_manipulators.t.cpp#L232) &nbsp;&nbsp;[hex](./streams/numeric_manipulators.t.cpp#L252) &nbsp;&nbsp;[oct](./streams/numeric_manipulators.t.cpp#L284) &nbsp;&nbsp;[dec](./streams/numeric_manipulators.t.cpp#L316) &nbsp;&nbsp;[setbase](./streams/numeric_manipulators.t.cpp#L336) &nbsp;&nbsp;**time/money** [put_money](./streams/time_money_manipulators.t.cpp#L6) &nbsp;&nbsp;[get_money](./streams/time_money_manipulators.t.cpp#L39) &nbsp;&nbsp;[put_time](./streams/time_money_manipulators.t.cpp#L65) &nbsp;&nbsp;[get_time](./streams/time_money_manipulators.t.cpp#L127) &nbsp;&nbsp;**flush** [unitbuf](./streams/flush_manipulators.t.cpp#L7) &nbsp;&nbsp;[nounitbuf](./streams/flush_manipulators.t.cpp#L26) &nbsp;&nbsp;[flush](./streams/flush_manipulators.t.cpp#L44) &nbsp;&nbsp;[endl](./streams/flush_manipulators.t.cpp#L69) &nbsp;&nbsp;**white space** [skipws](./streams/ws_manipulators.t.cpp#L6) &nbsp;&nbsp;[noskipws](./streams/ws_manipulators.t.cpp#L22) &nbsp;&nbsp;[ws](./streams/ws_manipulators.t.cpp#L38) &nbsp;&nbsp;**char** [ends](./streams/char_manipulators.t.cpp#L7) &nbsp;&nbsp;[quoted](./streams/char_manipulators.t.cpp#L22) &nbsp;&nbsp;  
