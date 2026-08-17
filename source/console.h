#include <iostream>

class console {
    public:
        std::string push(std::string string) const;
        std::string parse(std::string string, bool isQuote, bool isVarStr, bool isVarFloat, bool createVar) const;
        std::string parseInput(std::string string, bool createVar) const;
        void command(std::string consoleCommand) const;
};