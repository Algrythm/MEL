#include <iostream>
#include "filesys.h"
#include <fstream>
#include <filesystem>
#include <regex>

void filesys::createFile(std::string name) {
    std::ofstream file(name);
    file.close();
}

void filesys::writeFile(std::string name, std::string content) {
    std::ofstream file(name);
    file << content;
    file.close();
}

std::string filesys::readFile(std::string name) {
    std::ifstream file(name);
    std::string content;
    std::getline(file, content);
    return content;
}

void filesys::removeFile(std::string name) {
    std::filesystem::remove(name);
}