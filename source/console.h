#include <iostream>

class console {
    public:
        std::string push(std::string string);
        std::string parse(std::string string, bool isQuote);
        std::string parseInput(std::string string, bool createVar, bool getVal);
        std::string parseStr(std::string string, bool createVar, bool getVal);
        std::string parseFloat(std::string string, bool createVar, bool getVal);
        std::string parseFile(std::string string, bool isWrite, bool isCreate, bool isDel);
        void parseRCall(std::string string);
        bool parseIf(std::string string, bool notIf);
        void command(std::string consoleCommand);
};