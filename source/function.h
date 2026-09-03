#include <iostream>

class function {
    public:
        int callFunction(const std::string &name);
        int rcallFunction(const std::string &name, const int repeats);
        void importFunctions(const std::string &dir);
};