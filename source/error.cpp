#include <iostream>
#include "error.h"

void error::throwError(const int errorCode, const int lineNum, const std::string &line) const {
    switch (errorCode) {
        case 1:
            std::cout << "!!MEL INTERPRETER SYNTAX ERROR!!\nLINE " + std::to_string(lineNum) << std::endl;
            std::cout << "'" + line + "'" + " is not recognized!" << std::endl;
            std::cout << "ERROR CODE: " + std::to_string(errorCode) << std::endl;
            break;
        default:
            std::cout << "!!MEL INTERPRETER ERROR!!\nLINE " + std::to_string(lineNum) << std::endl;
            std::cout << "LINE: '" + line + "'" << std::endl;
            std::cout << "ERROR CODE: " + std::to_string(errorCode) << std::endl;
            break;
    }
}