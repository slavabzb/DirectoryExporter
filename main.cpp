#include <iostream>

#include "DirectoryExporter.h"



int main()
{
    const char* path = "C:\\My Cool Folder";
    const char* file = "Tree.xml";

    DirectoryExporter directory_exporter;

    return directory_exporter.to_xml(path, file);
}

