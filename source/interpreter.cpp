#include <iostream>
#include <fstream>
#include "interpreter.h"
#include "console.h"
#include "expression.h"
#include <sstream>
#include <vector>
#include <filesystem>
#include "filesys.h"
#include "variables.h"
#include "function.h"
#include "error.h"

bool ifSkip = false;

int interpret(std::string line, int lineNum) {
    console consoleInterp;
    error errorHandler;
    if (line.find("    ") != std::string::npos) { // remove indents
        line = line.substr(4,line.length()-4);
    }
    try {
        if (ifSkip) {
            if (line == "}ENDIF") {
                ifSkip = false;
            }
        } else {
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
            } else if (line.substr(0,9) == "variables") { // variable module
                variables variableHandler;
                if (line.substr(9,7) == "::remS(") {
                    variableHandler.removeStringVar(consoleInterp.parseStr(line, false, false));
                } else if (line.substr(9,7) == "::remF(") {
                    variableHandler.removeFloatVar(consoleInterp.parseStr(line, false, false));
                } else if (line.substr(9,7) == "::remI(") {
                    variableHandler.removeInputVar(consoleInterp.parseInput(line, false, false));
                }
            } else if (line.substr(0,3) == "if(") {
                ifSkip = !consoleInterp.parseIf(line, false); // negative parseif to determine whether to skip
            } else if (line.substr(0,4) == "ifn(") {
                ifSkip = !consoleInterp.parseIf(line, true); // negative parseif to determine whether to skip, not if true.
            } else if (line.substr(0,7) == "#import") {
                function functionHandler;
                functionHandler.importFunctions(consoleInterp.parse(line, true));
                return 0;
            } else if (line.substr(0,3) == ".s<") {
                consoleInterp.parseStr(line, true, false);
                return 0;
            } else if (line.substr(0,3) == ".f<") {
                consoleInterp.parseFloat(line, true, false);
                return 0;
            } else if (line.substr(0,3) == ".i<") {
                consoleInterp.parseInput(line, true, false);
                return 0;
            } else if (line.substr(0,5) == "call(") {
                function functionHandler;
                std::string funcName = consoleInterp.parse(line, true);
                functionHandler.callFunction(funcName);
                return 0;
            } else if (line.substr(0,6) == "rcall(") {
                consoleInterp.parseRCall(line);
                return 0;
            } else if (line.substr(0,11) == "terminate()") {
                exit(0);
            } else if (line.substr(0,7) == "filesys") {
                if (line.substr(7,7) == "::write") {
                    consoleInterp.parseFile(line, true, false, false);
                } else if (line.substr(7,6) == "::read") {
                    consoleInterp.parseFile(line, false, false, false);
                } else if (line.substr(7,8) == "::create") {
                    consoleInterp.parseFile(line, false, true, false);
                } else if (line.substr(7,8) == "::remove") {
                    consoleInterp.parseFile(line, false, false, true);
                }
            } else if (line == "") {
                return 0; //ignore blank lines
            } else if (line.substr(0,8) == "BEGINIF{" || line.substr(0,6) == "}ENDIF") {
                return 0; // ignore
            } else { // syntax error (not recognized)
                errorHandler.throwError(1, lineNum, line);
            }
        }
    } catch(int errorcode) {
        errorHandler.throwError(errorcode, lineNum, line);
    }
    return 0;
}