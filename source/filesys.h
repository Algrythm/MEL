#include <iostream>

class filesys {
    public:
        void createFile(const std::string &name);
        std::string readFile(const std::string &name);
        void writeFile(const std::string &name, const std::string &content);
        void removeFile(const std::string &name);
};