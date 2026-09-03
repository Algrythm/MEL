#include <iostream>

class console {
    public:
        std::string push(const std::string &string);
        std::string parse(const std::string &string, const bool isQuote);
        std::string parseInput(const std::string &string, const bool createVar, const bool getVal);
        std::string parseStr(const std::string &string, const bool createVar, const bool getVal);
        std::string parseFloat(const std::string &string, const bool createVar, const bool getVal);
        std::string parseFile(const std::string &string, const bool isWrite, const bool isCreate, const bool isDel);
        void parseRCall(const std::string &string);
        bool parseIf(const std::string &string, const bool notIf);
        void command(const std::string &consoleCommand);
};