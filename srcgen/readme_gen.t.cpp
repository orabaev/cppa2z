#include <catch.hpp>
#include <readme_gen.h>
#include <iostream>
#include <fstream>

using namespace std;

namespace srcgen {

TEST_CASE( "readme_gen.generate" ) {
    ofstream fout("README.md");
    auto& out = fout;
    //auto& out = cout;

    readme_gen gen(out);
    gen.generate();
}

} // namespace srcgen
