#include <iostream>
#include <map>

class variables {
    public:
        void createStringVar(const std::string &name, const std::string &content);
        void createFloatVar(const std::string &name, const float content);
        void createInputVar(const std::string &name);
        void removeStringVar(const std::string &name);
        void removeFloatVar(const std::string &name);
        void removeInputVar(const std::string &name);
        std::string getStringVar(const std::string &name);
        std::string getInputVar(const std::string &name);
        float getFloatVar(const std::string &name);
};