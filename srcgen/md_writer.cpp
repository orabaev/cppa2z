#include <md_writer.h>

namespace srcgen {

md_writer::md_writer(std::ostream& out)
: m_out(out)
{

}

md_writer& md_writer::heading1(const std::string& str) {
    m_out << "# " << str << '\n';
    return *this;
}

md_writer& md_writer::heading2(const std::string& str) {
    m_out << "## " << str << '\n';
    return *this;
}

md_writer& md_writer::heading3(const std::string& str) {
    m_out << "### " << str << '\n';
    return *this;
}

md_writer& md_writer::write(const std::string& str) {
    m_out << str << ' ';
    return *this;
}

md_writer& md_writer::bold(const std::string& str) {
    m_out << "**" << str << "** ";
    return *this;
}

md_writer& md_writer::newline() {
    m_out << "  \n";
    return *this;
}

md_writer& md_writer::html_space() {
    m_out << "&nbsp;";
    return *this;
}

md_writer& md_writer::link_to_repo_file(
     const std::string& name
   , const std::string& file_path
   , const int line_number
) 
{
    m_out << '[' << name << "](" << file_path << "#L" << line_number << ") ";    
    return *this;
}

} // namespac esrcgen
