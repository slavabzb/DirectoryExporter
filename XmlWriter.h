#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <ostream>
#include <stack>



class XmlWriter
{
public:
    XmlWriter(std::ostream& stream);

    void write_start_document(const char* root);
    void write_start_element(const char* tag, const char* attribute = nullptr, const char* value = nullptr);
    void write_end_element();
    void write_end_document();

private:
    void write_indent() const;



    std::ostream& stream;
    std::stack<const char*> tags;

    const char* indent = "  ";
};

#endif // XMLWRITER_H
