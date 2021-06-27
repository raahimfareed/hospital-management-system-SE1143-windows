#pragma once
#include <string>
#include <fstream>

// Unified class for file handling
class File
{
public:
    File(std::string path);
    void write(std::string line, bool newLine = true);
    std::string search(unsigned int index);
    std::fstream* getFile();

private:
    std::string mPath;
    std::fstream mFile;
};