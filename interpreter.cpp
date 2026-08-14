#include <iostream>
#include <fstream>
#include "interpreter.h"
#include "console.h"
#include "expression.h"
#include <sstream>
#include <vector>
#include <filesystem>

int interpret(std::string line, int lineNum) {
    const console consoleInterp;

    if (line.substr(0,7) == "console") { // console module
        if (line.substr(7,7) == "::push(") { // console::push();
            std::string coutString = consoleInterp.push(line); // call push function inside console class
            std::cout << coutString << std::endl; // cout result
            return 0;
        } else if (line.substr(7,10) == "::command(") { // console::command();
            std::string commandString = consoleInterp.parse(line, true, false, false, false); // parse manually
            consoleInterp.command(commandString.c_str()); // call system function inside console class
            return 0;
        }
    } else if (line.substr(0,2) == "#-") { // comment
        return 0; // ignore
    } else if (line.substr(0,3) == ".s<") {
        consoleInterp.parse(line, false, true, false, true);
        return 0;
    } else if (line.substr(0,3) == ".f<") {
        consoleInterp.parse(line, false, false, true, true);
        return 0;
    } else { // syntax error (not recognized)
        std::cout << "!!MEL INTERPRETER SYNTAX ERROR!!\nLINE " + std::to_string(lineNum) << std::endl;
        std::cout << "'" + line + "'" + " is not recognized!" << std::endl;
        return 1; // return 1 to indicate error to main
    }
    return 0;
}