#include <iostream>
#include <sstream>

class expression {
    public:
        float parseExpression(const std::string &expString) const;
        bool isExpression(const std::string &expString) const;
};