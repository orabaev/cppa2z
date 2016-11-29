#ifndef SRCGEN_README_GEN_H
#define SRCGEN_README_GEN_H

#include <md_writer.h>

namespace srcgen {

// readme_gen mechanism class
// generates README.md content
class readme_gen {
public:
    readme_gen()                        = delete;
    readme_gen(readme_gen&)             = delete;
    readme_gen(readme_gen&&)            = delete;
    readme_gen& operator=(readme_gen&)  = delete;
    readme_gen& operator=(readme_gen&&) = delete;
    ~readme_gen()                       = default;

    readme_gen(std::ostream& out);

    void generate();

private:
    void section(const std::string& section, const std::string& file_path);
    void caption();
    void algorithms();
    void iterators();
    void streams();

private:
    md_writer m_writer;

};

} // namespace srcgen

#endif // SRCGEN_README_GEN_H
