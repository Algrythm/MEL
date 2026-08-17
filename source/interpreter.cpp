#include <iostream>
#include <fstream>
#include "interpreter.h"
#include "console.h"
#include "expression.h"
#include <sstream>
#include <vector>
#include <filesystem>
#include "function.h"

int interpret(std::string line, int lineNum) {
    console consoleInterp;

    if (line.substr(0,7) == "console") { // console module
        if (line.substr(7,7) == "::push(") { // console::push();
            std::string coutString = consoleInterp.push(line); // call push function inside console class
            std::cout << coutString << std::endl; // cout result
            return 0;
        } else if (line.substr(7,8) == "::write(") { // console::write();
            std::string coutString = consoleInterp.push(line); // call push function inside console class
            std::cout << coutString; // cout result WITHOUT newline or buffer flush
            return 0;
        } else if (line.substr(7,10) == "::command(") { // console::command();
            std::string commandString = consoleInterp.parse(line, false); // parse manually
            consoleInterp.command(commandString.c_str()); // call system function inside console class
            return 0;
        }
    } else if (line.substr(0,2) == "#-") { // comment
        return 0; // ignore
    } else if (line.substr(0,7) == "#import") {
        function functionHandler;
        functionHandler.importFunctions(consoleInterp.parse(line, true));
        return 0;
    } else if (line.substr(0,3) == ".s<") {
        consoleInterp.parseStr(line, true);
        return 0;
    } else if (line.substr(0,3) == ".f<") {
        consoleInterp.parseFloat(line, true);
        return 0;
    } else if (line.substr(0,3) == ".i<") {
        consoleInterp.parseInput(line, true);
        return 0;
    } else if (line.substr(0,5) == "call(") {
        function functionHandler;
        std::string funcName = consoleInterp.parse(line, true);
        functionHandler.callFunction(funcName);
        return 0; 
    } else { // syntax error (not recognized)
        std::cout << "!!MEL INTERPRETER SYNTAX ERROR!!\nLINE " + std::to_string(lineNum) << std::endl;
        std::cout << "'" + line + "'" + " is not recognized!" << std::endl;
        return 1; // return 1 to indicate error to main
    }
    return 0;
}