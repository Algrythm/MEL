#include <iostream>

class filesys {
    public:
        void createFile(std::string name);
        std::string readFile(std::string name);
        void writeFile(std::string name, std::string content);
        void removeFile(std::string name);
};