#include <readme_gen.h>
#include <parse_util.h>
#include <fstream>
#include <iostream>

using namespace std;

namespace srcgen {

readme_gen::readme_gen(std::ostream& out)
:  m_writer(out)
{

}

void readme_gen::generate() {
    caption();
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
}

} // namespac esrcgen
