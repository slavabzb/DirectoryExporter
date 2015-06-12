#include <iostream>

#include "export_directory.h"



int main()
{
    const char* path = "C:\\My Cool Folder";
    std::cout << export_directory(std::cout, path) << "\n";
    return 0;
}

