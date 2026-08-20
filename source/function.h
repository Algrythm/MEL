#include <iostream>

class function {
    public:
        int callFunction(std::string name);
        int rcallFunction(std::string name, int repeats);
        void importFunctions(std::string dir);
};