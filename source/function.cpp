#include <iostream>
#include "function.h"
#include <map>
#include <fstream>
#include "interpreter.h"
#include "variables.h"

std::string funcDir;

int function::callFunction(const std::string &name) { // locate function in preimported function directory and interpret it
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

int function::rcallFunction(const std::string &name, const int repeats) { // locate function in preimported function directory and interpret the amount of times specified
    int curLine = 0;;
    time_t curTime;
    variables variableHandler;
    for (int i = 0; i < repeats; i++) {
        std::ifstream file(funcDir + "/" + name + ".f");
        std::string funcContent;
        curLine = 0;
        while (std::getline(file, funcContent)) {
            time(&curTime);
            variableHandler.createStringVar("sys::curTime", std::to_string(curTime)); // during an rcall, main will not be able to update the curTime var, so we do it here
            if (interpret(funcContent, curLine) == 1) { // if there is an error in interpretation
                return 0;
            }
            curLine++;
        }
    }
    return 0;
}

void function::importFunctions(const std::string &dir) { // save func directory
    funcDir = dir;
}