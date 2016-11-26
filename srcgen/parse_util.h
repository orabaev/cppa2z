#ifndef  SRCGEN_PARSE_UTIL_H
#define  SRCGEN_PARSE_UTIL_H

#include <algorithm>
#include <string>
#include <vector>
#include <istream>

namespace srcgen {

// searches for the first and for the second delimiters in the range
// returns pair of iterators to the elements containing delimiters
template<class InputIt, class T>
auto find_delimiters(
      InputIt first_it
    , InputIt last_it
    , const T& first_delim
    , const T& second_delim
);

// copies delimited elements in the range to another range
// returns pair containing success flag and iterator to
// the element right after the second delimiter
template<class InputIt, class T, class OutputIt>
auto copy_delimited(
      InputIt first_it
    , InputIt last_it
    , const T& first_delim
    , const T& second_delim
    , OutputIt output_it
); 

// extract multiple dlimited elements in the range into
// the provided container
// returns number of extracted elements
template<class InputIt, class T, class Container>
auto extract_delimited(
      InputIt first_it
    , InputIt last_it
    , const T& first_delim
    , const T& second_delim
    , Container& container
);

// determine if given line of code is a test case
bool is_test_case(const std::string& line_of_code);

// returns test case name from the test case line of code
std::string get_test_case_name(const std::string& test_case_line);

// parses source file and returns vector of line numbers and 
// test case names
std::vector<std::pair<int, std::string>> extract_test_case_lines(std::istream& in);

// IMPLEMENTATION

template<class InputIt, class T>
auto find_delimiters(
      InputIt first_it
    , InputIt last_it
    , const T& first_delim
    , const T& second_delim
)
{
    auto ret = std::make_pair(last_it, last_it);

    ret.first = std::find(first_it, last_it, first_delim);
    if (last_it == ret.first) return ret;

    ret.second = std::find(std::next(ret.first), last_it, second_delim);
    return ret;
}

template<class InputIt, class T, class OutputIt>
auto copy_delimited(
      InputIt first_it
    , InputIt last_it
    , const T& first_delim
    , const T& second_delim
    , OutputIt output_it
) 
{
    auto delims = find_delimiters(
                      first_it
                    , last_it
                    , first_delim
                    , second_delim
                  );

    if (last_it == delims.second) return std::make_pair(false, last_it);

    copy(std::next(delims.first), delims.second, output_it);
    return std::make_pair(true, std::next(delims.second));
}

template<class InputIt, class T, class Container>
auto extract_delimited(
      InputIt first_it
    , InputIt last_it
    , const T& first_delim
    , const T& second_delim
    , Container& container
)
{
    bool extracted = false;
    for (;;) {
        typename Container::value_type to;
        auto pr = copy_delimited(
                      first_it
                    , last_it
                    , first_delim
                    , second_delim
                    , back_inserter(to)
                  );
        
        if (!pr.first) break;

        first_it = pr.second;
        container.push_back(std::move(to));
        extracted = true;
    } 

    return extracted;
}

} // namespace srcgen

#endif // SRCGEN_PARSE_UTIL_H
