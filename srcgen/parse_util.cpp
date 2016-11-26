#include <parse_util.h>
#include <vector>

using namespace std;

namespace srcgen {

bool is_test_case(const string& line_of_code) {
    const string test_case{"TEST_CASE("};     

    auto not_space = [](char x) { return !isspace(x); }; 
    //skip white spaces
    const auto bit = find_if(
                          cbegin(line_of_code)
                        , cend(line_of_code)
                        , not_space
                    );     

    const auto sit = search(
                          bit
                        , cend(line_of_code)
                        , cbegin(test_case)
                        , cend(test_case)
                     );

    bool found_at_the_begining = ( bit == sit && sit != cend(line_of_code) );
    return found_at_the_begining;
}

string get_test_case_name(const string& test_case_line) {
    string test_case_name;

    copy_delimited(
          cbegin(test_case_line)
        , cend(test_case_line)
        , '"' 
        , '"' 
        , back_inserter(test_case_name)
    );

    return test_case_name;   
}

vector<pair<int, string>> extract_test_case_lines(istream& in) {
    vector<pair<int, string>> vec; 
    int line_number = 0; 
    string line_of_code;

    while ( getline(in, line_of_code) ) {
        ++line_number;    
        if (is_test_case(line_of_code)) {
            vec.emplace_back(line_number, get_test_case_name(line_of_code));
        }
    }

    return vec;
}

} // namespace srcgen
