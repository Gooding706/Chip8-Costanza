#include "fileStructure.h"
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> get_files(const std::string& directory)
{
    std::vector<std::string> files;

    DIR* dir = opendir(directory.c_str());
    if (!dir) {
        std::cerr << "Error: could not open directory " << directory << std::endl;
        return files;
    }
    struct dirent* dirent;
    while ((dirent = readdir(dir))) {
        if (dirent->d_type == DT_REG)
        {
            std::string filename = directory + dirent->d_name;
            if(dirent->d_name[0] != '.')
            {
              files.push_back(filename);
            }
        }
    }
    closedir(dir);
    return files;
}
