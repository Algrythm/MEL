#include <iostream>

class console {
    public:
        std::string push(std::string string) const;
        std::string parse(std::string string, bool isQuote) const;
        std::string parseInput(std::string string, bool createVar, bool getVal) const;
        std::string parseStr(std::string string, bool createVar, bool getVal) const;
        std::string parseFloat(std::string string, bool createVar, bool getVal) const;
        void command(std::string consoleCommand) const;
};