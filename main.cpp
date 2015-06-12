#include <iostream>

#include "DirectoryScanner.h"



int main()
{
    const char* path = "C:\\My Cool Folder";
    const char* file = "Tree.xml";

    DirectoryScanner directory_scanner;
    directory_scanner.export_to_xml(path, file);

    return 0;
}

