#ifndef DIRECTORYEXPORTER_H
#define DIRECTORYEXPORTER_H

#include <fstream>
#include <windows.h>

#include "XmlWriter.h"



class DirectoryExporter
{
public:
    DirectoryExporter();

    uint64_t to_xml(const char* path, const char* file);

private:
    uint64_t scan(const char* path);
    bool is_directory(WIN32_FIND_DATA& find_data) const;
    bool is_special(const char* file) const;


    std::ofstream stream;
    XmlWriter xml_writer;
};

#endif // DIRECTORYEXPORTER_H
