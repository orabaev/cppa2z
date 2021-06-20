#include <readme_gen.h>
#include <parse_util.h>
#include <fstream>
#include <iostream>

using namespace std;

namespace srcgen {

readme_gen::readme_gen(std::ostream& out)
:  m_writer(out)
{
    // travis build status
    out << "[![Build Status](https://travis-ci.org/orabaev/cppa2z.svg?branch=master)](https://travis-ci.org/orabaev/cppa2z)  \n";
}

void readme_gen::generate() {
    caption();
    modern_11_14();
    modern_17();
    algorithms();
    iterators();
    streams();
}

void readme_gen::section(const string& section, const string& file_path) {
    m_writer.bold(section);

    ifstream fin(file_path);
    const auto test_case_lines = extract_test_case_lines(fin);

    for (const auto& value : test_case_lines) {
        string normalized_test_case_name;

        copy_all_or_after(
              cbegin(value.second)
            , cend(value.second)
            , '.'
            , back_inserter(normalized_test_case_name)
        );

        m_writer.link_to_repo_file(normalized_test_case_name, file_path, value.first);
        m_writer.html_space().html_space();
    }

    if ( !fin.is_open() ) {
        cerr << "FAILED TO GENERATE SECTION " << section << " FILE " << file_path << endl;
    }
}

void readme_gen::caption() {
    m_writer.heading1("cppa2z");
    m_writer.write("Document modern C++ using unit tests");
    m_writer.newline();
}

void readme_gen::modern_11_14() {
    m_writer.heading2("C++11/14");
    section("lambda"                , "./modern_11_14/lambda.t.cpp");
    section("type deduction"        , "./modern_11_14/type_deduction.t.cpp");
    section("range-based for loop"  , "./modern_11_14/range_loop.t.cpp");
    section("move symantics"        , "./modern_11_14/move_symantics.t.cpp");
    section("class members"         , "./modern_11_14/class_members.t.cpp");
    section("smart pointers"        , "./modern_11_14/smart_pointers.t.cpp");
    section("literals"              , "./modern_11_14/literals.t.cpp");
    section("compile-time"          , "./modern_11_14/compile_time.t.cpp");
    section("templates"             , "./modern_11_14/templates.t.cpp");

    m_writer.newline();
}

void readme_gen::modern_17() {
    m_writer.heading2("C++17");
    section("utility types"         , "./modern_17/utility_types.t.cpp");
    section("structured bindings"   , "./modern_17/structured_bindings.t.cpp");
    section("features", "./modern_17/features_17.t.cpp");
    m_writer.newline();
}

void readme_gen::concurrency()
{
    m_writer.heading2("concurrency");
    section("thread"         , "./concurrency/thread.t.cpp");
    m_writer.newline();
}

void readme_gen::algorithms() {
    m_writer.heading2("algorithms");

    section("non modifying"      , "./algorithms/non_modifying_sequence.t.cpp");
    section("modifying"          , "./algorithms/modifying_sequence.t.cpp");
    section("partitioning"       , "./algorithms/partitioning.t.cpp");
    section("sorting"            , "./algorithms/sorting.t.cpp");
    section("set operations"     , "./algorithms/set_operations.t.cpp");
    section("heap operations"    , "./algorithms/heap.t.cpp");
    section("min max"            , "./algorithms/min_max.t.cpp");
    section("permutation"        , "./algorithms/permutation.t.cpp");
    section("numeric operations" , "./algorithms/numeric_operations.t.cpp");
    
    m_writer.newline();
}

void readme_gen::iterators() {
    m_writer.heading2("iterators");

    section("adaptors"         , "./iterators/iterator_adaptors.t.cpp");
    section("operations"       , "./iterators/iterator_operations.t.cpp");
    section("stream iterators" , "./iterators/stream_iterators.t.cpp");
    
    m_writer.newline();
}

void readme_gen::streams() {
    m_writer.heading2("streams");

    m_writer.heading3("istream");
    section("input functions"   , "./streams/istream_input.t.cpp");
    section("miscellaneous"     , "./streams/istream_misc.t.cpp");
    section("istringstream"     , "./streams/istringstream.t.cpp");
    section("ifstream"          , "./streams/ifstream.t.cpp");
    m_writer.newline();

    m_writer.heading3("ostream");
    section("output functions"  , "./streams/ostream_output.t.cpp");
    section("miscellaneous"     , "./streams/ostream_misc.t.cpp");
    section("ostringstream"     , "./streams/ostringstream.t.cpp");
    section("ofstream"          , "./streams/ofstream.t.cpp");
    m_writer.newline();

    m_writer.heading3("manipulators");
    section("adjust"            , "./streams/adjust_manipulators.t.cpp");
    section("floating-point"    , "./streams/float_manipulators.t.cpp");
    section("numeric"           , "./streams/numeric_manipulators.t.cpp");
    section("time/money"        , "./streams/time_money_manipulators.t.cpp");
    section("flush"             , "./streams/flush_manipulators.t.cpp");
    section("white space"       , "./streams/ws_manipulators.t.cpp");
    section("char"              , "./streams/char_manipulators.t.cpp");
    m_writer.newline();
}

} // namespac esrcgen
