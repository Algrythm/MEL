#include <iostream>
#include "filesys.h"
#include <fstream>
#include <filesystem>
#include <regex>

void filesys::createFile(const std::string &name) {
    std::ofstream file(name);
    file.close();
}

void filesys::writeFile(const std::string &name, const std::string &content) {
    std::ofstream file(name);
    file << content;
    file.close();
}

std::string filesys::readFile(const std::string &name) {
    std::ifstream file(name);
    std::string content;
    std::getline(file, content);
    return content;
}

void filesys::removeFile(const std::string &name) {
    std::filesystem::remove(name);
}