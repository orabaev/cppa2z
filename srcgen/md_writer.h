#ifndef SRCGEN_MD_WRITER_H
#define SRCGEN_MD_WRITER_H

#include <ostream>
#include <string>

namespace srcgen {

// md_writer mechanism class
// implements utility function to generate README.md
class md_writer {
public:
    md_writer()                       = delete;
    md_writer(md_writer&)             = delete;
    md_writer(md_writer&&)            = delete;
    md_writer& operator=(md_writer&)  = delete;
    md_writer& operator=(md_writer&&) = delete;
    ~md_writer()                      = default;

    md_writer(std::ostream& out);

    md_writer& heading1(const std::string& str);
    md_writer& heading2(const std::string& str);
    md_writer& heading3(const std::string& str);
    md_writer& write(const std::string& str);
    md_writer& bold(const std::string& str);
    md_writer& newline();

    md_writer& link_to_repo_file(
                     const std::string& name
                   , const std::string& file_path
                   , const int line_number
               );

private:
    std::ostream& m_out; 

};

} // namespace srcgen

#endif // SRCGEN_MD_WRITER_H
