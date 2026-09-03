#include <iostream>

class error {
    public:
        void throwError(const int errorCode, const int lineNum, const std::string &line) const;
};