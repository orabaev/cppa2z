#include <algorithm>

namespace srcgen {

// searches for the first and for the second delimiters in the range
// returns pair of iterators to the elements containing delimiters
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

}
