#include <iostream>
#include "function.h"
#include <map>
#include <fstream>
#include "interpreter.h"

std::string funcDir;

int function::callFunction(std::string name) { // locate function in preimported function directory and interpret it
    int curLine = 0;
    std::ifstream file(funcDir + "/" + name + ".f");
    std::string funcContent;
    while (std::getline(file, funcContent)) {
        if (interpret(funcContent, curLine) == 1) { // if there is an error in interpretation
            return 0;
        }

        curLine++;
    }
    return 0;
}

void function::importFunctions(std::string dir) { // save func directory
    funcDir = dir;
}