#ifndef DIRECTORYSCANNER_H
#define DIRECTORYSCANNER_H

#include <fstream>
#include <windows.h>

#include "XmlWriter.h"



class DirectoryScanner
{
public:
    DirectoryScanner();

    uint64_t export_to_xml(const char* path, const char* file);

private:
    uint64_t scan(const char* path);
    bool is_directory(WIN32_FIND_DATA& find_data) const;
    bool is_special(const char* file) const;


    std::ofstream stream;
    XmlWriter xml_writer;
};

#endif // DIRECTORYSCANNER_H
