#include <string>

#include "File.hpp"

File::File(std::string path)
    :mPath(path)
{
}

void File::write(std::string line, bool newLine)
{
    mFile.open(mPath, std::ios::out | std::ios::app | std::ios::binary);
    mFile << line;
    if (newLine)
        mFile << '\n';
    mFile.close();
}

std::string File::search(unsigned int index)
{
    unsigned int count = 0;

    mFile.open(mPath, std::ios::in);

    std::string fileLine;
    std::string word;
    while (!mFile.eof())
    {
        if (++count != index)
        {
            continue;
        }

        std::getline(mFile, fileLine);
        mFile.close();
        return fileLine;
    }

    return std::string();
}

std::fstream* File::getFile()
{
    return &mFile;
}