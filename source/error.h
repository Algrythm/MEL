#include <iostream>

class error {
    public:
        void throwError(int errorCode, int lineNum, std::string line) const;
};