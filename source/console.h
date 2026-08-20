#include <iostream>

class console {
    public:
        std::string push(std::string string) const;
        std::string parse(std::string string, bool isQuote) const;
        std::string parseInput(std::string string, bool createVar, bool getVal) const;
        std::string parseStr(std::string string, bool createVar, bool getVal) const;
        std::string parseFloat(std::string string, bool createVar, bool getVal) const;
        std::string parseFile(std::string string, bool isWrite, bool isCreate, bool isDel) const;
        void parseRCall(std::string string) const;
        bool parseIf(std::string string, bool notIf) const;
        void command(std::string consoleCommand) const;
};