#include "XmlWriter.h"

#include <assert.h>



XmlWriter::XmlWriter(std::ostream& stream)
    : stream(stream)
{

}



void XmlWriter::write_start_document(const char* root, const char* attribute, const char* value)
{
    this->stream << "<?xml version=\"1.0\"?>\n";
    this->write_start_element(root, attribute, value);
}



void XmlWriter::write_start_element(const char* tag, const char* attribute, const char* value)
{
    assert(tag != nullptr);

    this->tags.push(tag);
    this->write_indent();

    this->stream << "<" << tag;

    if ((attribute != nullptr) && (value != nullptr)) {
        this->stream << " " << attribute << "=\"" << value << "\"";
    }

    this->stream << ">\n";
}



void XmlWriter::write_end_element()
{
    this->write_indent();
    this->stream << "</" << this->tags.top() << ">\n";
    this->tags.pop();
}



void XmlWriter::write_end_document()
{
    this->write_end_element();
}



void XmlWriter::write_indent() const
{
    for (std::size_t i = 0; i < this->tags.size()-1; ++i) {
        this->stream << this->indent;
    }
}

