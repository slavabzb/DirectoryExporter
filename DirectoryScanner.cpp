#include "DirectoryScanner.h"

#include <shlwapi.h>



DirectoryScanner::DirectoryScanner()
    : xml_writer(stream)
{

}



uint64_t DirectoryScanner::export_to_xml(const char* path, const char* file)
{
    this->stream.open(file);
    if (!this->stream.is_open()) {
        return false;
    }

    xml_writer.write_start_document("tree");

    uint64_t result = this->scan(path);

    xml_writer.write_end_document();

    return result;
}



uint64_t DirectoryScanner::scan(const char* path)
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

    uint64_t result = 0;

    do {
        const char* file = find_data.cFileName;
        if (!this->is_special(file)) {
            if (this->is_directory(find_data)) {
                this->xml_writer.write_start_element("directory", "name", file);
            }
            else {
                this->xml_writer.write_start_element("file", "name", file);
            }

            char subdirectory[strlen(path)+strlen(file)];
            strcpy_s(subdirectory, sizeof(subdirectory), path);
            PathAppend(subdirectory, file);
            result = this->scan(subdirectory);

            this->xml_writer.write_end_element();
        }
    }
    while (FindNextFile(handle, &find_data));

    FindClose(handle);

    return result;
}



bool DirectoryScanner::is_directory(WIN32_FIND_DATA& find_data) const
{
    if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        return true;
    }

    return false;
}



bool DirectoryScanner::is_special(const char* file) const
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

