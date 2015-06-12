#include "export_directory.h"

#include <windows.h>
#include <shlwapi.h>



bool is_special(const char* file)
{
    const char special_directories[][3] = { {"."}, {".."} };

    bool special = false;
    for (auto pattern : special_directories) {
        if (!strcmp(file, pattern)) {
            special = true;
            break;
        }
    }

    return special;
}



bool is_directory(WIN32_FIND_DATA& find_data)
{
    if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        return true;
    }

    return false;
}



void write_element(std::ostream& stream, const char* tag, const char* element, int indent)
{
    for (int i = 0; i < indent; ++i) {
        stream << "  ";
    }

    stream << "<" << tag << ">" << element << "</" << tag << ">\n";
}



int recursive_scan(std::ostream& stream, const char* path, int indent)
{
    if (path == nullptr) {
        return 1;
    }

    char directory[strlen(path)+1];
    strcpy_s(directory, sizeof(directory), path);
    PathAppend(directory, "\\*");

    WIN32_FIND_DATA find_data;
    HANDLE handle;

    handle = FindFirstFile(directory, &find_data);
    if (handle == INVALID_HANDLE_VALUE) {
        return GetLastError();
    }

    do {
        const char* file = find_data.cFileName;
        if (!is_special(file)) {
            if (is_directory(find_data)) {
                write_element(stream, "directory", file, indent);
            }
            else {
                write_element(stream, "file", file, indent);
            }

            char subdirectory[strlen(path)+strlen(file)];
            strcpy_s(subdirectory, sizeof(subdirectory), path);
            PathAppend(subdirectory, file);
            recursive_scan(stream, subdirectory, indent+1);
        }
    }
    while (FindNextFile(handle, &find_data));

    FindClose(handle);

    return 0;
}



int export_directory(std::ostream& stream, const char* path)
{
    stream << "<?xml version=\"1.0\"?>\n";
    stream << "<tree directory=\"" << path << "\">\n";

    recursive_scan(stream, path, 1);

    stream << "<\\tree>\n";

    return 0;
}
