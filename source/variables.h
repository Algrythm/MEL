#include <iostream>
#include <map>

class variables {
    public:
        void createStringVar(std::string name, std::string content);
        void createFloatVar(std::string name, float content);
        std::string getStringVar(std::string name);
        float getFloatVar(std::string name);
};