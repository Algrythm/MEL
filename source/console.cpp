#include <iostream>
#include "console.h"
#include "expression.h"
#include "variables.h"
#include "filesys.h"
#include "function.h"
#include <limits>


std::string console::parse(std::string string, bool isQuote) { // parse variables, strings and numbers
    std::string parsed;
    if (isQuote) {
        unsigned start = string.find("(\"")+2; // start past opening quotes
        unsigned end = string.find("\");"); // end before closing quotes
        parsed = string.substr(start,end-start); // get parsed string
    } 
    else {
        unsigned start = string.find("(")+1; // start past opening
        unsigned end = string.find(");"); // end before closing
        parsed = string.substr(start,end-start);
    }
    return parsed;
}

std::string console::parseInput(std::string string, bool createVar, bool getVal) {
    std::string parsed;
    if (createVar) { // if creating the input variable
        std::string parsedStr;
        variables variableHandler;
        unsigned start = string.find(".i<")+3; // start past opening
        unsigned end = string.find(">;"); // end before closing
        parsed = string.substr(start,end-start);
        variableHandler.createInputVar(parsed);
    } else { // if accessing premade input variable
        variables variableHandler;
        unsigned start = string.find("i<")+2; // start past opening
        unsigned end = string.find(">"); // end before closing
        parsed = string.substr(start,end-start); // get parsed variable name
        if (getVal) {
            parsed = variableHandler.getInputVar(parsed); // get variable content, and prepare it to be returned
        }
    }
    return parsed;
}

std::string console::parseStr(std::string string, bool createVar, bool getVal) {
    std::string parsed;
    if (createVar) { // if creating the string variable
        std::string parsedStr;
        variables variableHandler;
        unsigned start = string.find(".s<")+3; // start past opening
        unsigned end = string.find(">"); // end before closing
        unsigned startC = string.find("= (\"")+4; // start past opening content
        unsigned endC = string.find(");")-1; // end before closing content
        parsed = string.substr(start,end-start);
        parsedStr = string.substr(startC,endC-startC);
        variableHandler.createStringVar(parsed, parsedStr);
    } else { // if accessing premade string variable
        variables variableHandler;
        unsigned start = string.find("s<")+2; // start past opening
        unsigned end = string.find(">"); // end before closing
        parsed = string.substr(start,end-start); // get parsed variable name
        if (getVal) {
            parsed = variableHandler.getStringVar(parsed); // get variable content, and prepare it to be returned
        }
    }
    return parsed;
}

void console::parseRCall(std::string string) {
    function functionHandler;
    std::string parsedName;
    int parsedRepeats;
    unsigned start = string.find("(\"")+2; // start past opening
    unsigned end = string.find("\", "); // end before closing
    unsigned start2 = string.find(", ")+2; // start past opening
    unsigned end2 = string.find(");"); // end before closing
    parsedName = string.substr(start,end-start);
    if (string.substr(start2, end2-start2) == "||inf||") {
        parsedRepeats = std::numeric_limits<int>::max();
    } else {
        parsedRepeats = std::stoi(string.substr(start2, end2-start2));
    }
    functionHandler.rcallFunction(parsedName, parsedRepeats);
}

std::string console::parseFloat(std::string string, bool createVar, bool getVal) {
    std::string parsed;
    if (createVar) { // if creating the float variable
        std::string parsedFloatStr;
        float parsedFloat;
        variables variableHandler;
        unsigned start = string.find(".f<")+3; // start past opening
        unsigned end = string.find(">"); // end before closing
        unsigned startC = string.find("= (")+3; // start past opening content
        unsigned endC = string.find(");"); // end before closing content
        parsed = string.substr(start,end-start);
        parsedFloatStr = string.substr(startC,endC-startC);
        parsedFloat = std::stof(parsedFloatStr);
        variableHandler.createFloatVar(parsed, parsedFloat);
    } else { // if accessing premade float variable
        variables variableHandler;
        unsigned start = string.find("f<")+2; // start past opening
        unsigned end = string.find(">"); // end before closing
        parsed = string.substr(start,end-start); // get parsed variable name
        if (getVal) {
            parsed = std::to_string(variableHandler.getFloatVar(parsed)); // get variable content, and prepare it to be returned
        }
    }
    return parsed;
}

std::string console::parseFile(std::string string, bool isWrite, bool isCreate, bool isDel) {
    filesys fileSysHandler;
    variables variableHandler;
    std::string parsed;
    std::string parsedContent;
    if (isWrite) {
        unsigned start = string.find("(\"")+2; // start past opening
        unsigned end = string.find("\","); // end before closing
        parsed = string.substr(start,end-start); // get parsed file name
        unsigned startC = string.find(", ")+2; // start past opening
        unsigned endC = string.find(");"); // end before closing
        parsedContent = string.substr(startC, endC-startC);
        if (parsedContent.find("s<") != std::string::npos) {
            parsedContent = console::parseStr(parsedContent, false, true);
        } else if (parsedContent.find("i<") != std::string::npos) {
            parsedContent = console::parseInput(parsedContent, false, true);
        } else {
            startC = string.find(", \"")+3; // access string instead of parsedcontent
            endC = string.find("\")");
            parsedContent = string.substr(startC, endC-startC);
        }
        fileSysHandler.writeFile(parsed, parsedContent);
    } else {
        if (isCreate) {
            unsigned start = string.find("(\"")+2; // start past opening
            unsigned end = string.find("\")"); // end before closing
            parsed = string.substr(start,end-start); // get parsed file name
            fileSysHandler.createFile(parsed);
        } else if (isDel) {
            unsigned start = string.find("(\"")+2; // start past opening
            unsigned end = string.find("\")"); // end before closing
            parsed = string.substr(start,end-start); // get parsed file name
            fileSysHandler.removeFile(parsed);
        } else {
            variables variableHandler;
            std::string parsedVarName;
            unsigned start = string.find("(\"")+2; // start past opening
            unsigned end = string.find("\", "); // end before closing
            unsigned startC = string.find(", s<")+4; // start past opening
            unsigned endC = string.find(">)"); // end before closing
            parsed = string.substr(start,end-start); // get parsed file name
            parsedVarName = string.substr(startC, endC-startC);
            parsedContent = fileSysHandler.readFile(parsed);
            variableHandler.createStringVar(parsedVarName, parsedContent);
        }
    }
    return parsedContent;
}

bool console::parseIf(std::string string, bool notIf) {
    if (notIf) { // if checking if NOT value
        std::string parsedFirst;
        std::string parsedSecond;
        variables variableHandler;
        unsigned start = string.find("(")+1; // start past opening
        unsigned end = string.find(" == "); // end before closing
        unsigned start2 = string.find(" == ")+4; // start past opening
        unsigned end2 = string.find(")"); // end before closing
        parsedFirst = string.substr(start, end-start);
        parsedSecond = string.substr(start2, end2-start2);
        if (parsedFirst.find("s<") != std::string::npos) { // variable type checks
            start = parsedFirst.find("s<")+2;
            end = parsedFirst.find(">");
            parsedFirst = parsedFirst.substr(start, end-start);
            parsedFirst = variableHandler.getStringVar(parsedFirst);
        } else if (parsedFirst.find("i<") != std::string::npos) {
            start = parsedFirst.find("i<")+2;
            end = parsedFirst.find(">");
            parsedFirst = parsedFirst.substr(start, end-start);
            parsedFirst = variableHandler.getInputVar(parsedFirst);
        } else if (parsedFirst.find("f<") != std::string::npos) {
            start = parsedFirst.find("f<")+2;
            end = parsedFirst.find(">");
            parsedFirst = parsedFirst.substr(start, end-start);
            parsedFirst = std::to_string(variableHandler.getFloatVar(parsedFirst));
        }
        if (parsedSecond.find("s<") != std::string::npos) { // variable type checks
            start2 = parsedSecond.find("s<")+2;
            end2 = parsedSecond.find(">");
            parsedSecond = parsedSecond.substr(start2, end2-start2);
            parsedSecond = variableHandler.getStringVar(parsedSecond);
        } else if (parsedSecond.find("i<") != std::string::npos) {
            start2 = parsedSecond.find("i<")+2;
            end2 = parsedSecond.find(">");
            parsedSecond = parsedSecond.substr(start2, end2-start2);
            parsedSecond = variableHandler.getInputVar(parsedSecond);
        } else if (parsedSecond.find("f<") != std::string::npos) {
            start2 = parsedSecond.find("f<")+2;
            end2 = parsedSecond.find(">");
            parsedSecond = parsedSecond.substr(start2, end2-start2);
            parsedSecond = std::to_string(variableHandler.getFloatVar(parsedSecond));
        }

        if (parsedFirst == parsedSecond) {return false;} else {return true;} // if not logic
    } else { // checking IF value
        std::string parsedFirst;
        std::string parsedSecond;
        variables variableHandler;
        unsigned start = string.find("(")+1; // start past opening
        unsigned end = string.find(" == "); // end before closing
        unsigned start2 = string.find(" == ")+4; // start past opening
        unsigned end2 = string.find(")"); // end before closing
        parsedFirst = string.substr(start, end-start);
        parsedSecond = string.substr(start2, end2-start2);
        if (parsedFirst.find("s<") != std::string::npos) { // variable type checks
            start = parsedFirst.find("s<")+2;
            end = parsedFirst.find(">");
            parsedFirst = parsedFirst.substr(start, end-start);
            parsedFirst = variableHandler.getStringVar(parsedFirst);
        } else if (parsedFirst.find("i<") != std::string::npos) {
            start = parsedFirst.find("i<")+2;
            end = parsedFirst.find(">");
            parsedFirst = parsedFirst.substr(start, end-start);
            parsedFirst = variableHandler.getInputVar(parsedFirst);
        } else if (parsedFirst.find("f<") != std::string::npos) {
            start = parsedFirst.find("f<")+2;
            end = parsedFirst.find(">");
            parsedFirst = parsedFirst.substr(start, end-start);
            parsedFirst = std::to_string(variableHandler.getFloatVar(parsedFirst));
        }
        if (parsedSecond.find("s<") != std::string::npos) { // variable type checks
            start2 = parsedSecond.find("s<")+2;
            end2 = parsedSecond.find(">");
            parsedSecond = parsedSecond.substr(start2, end2-start2);
            parsedSecond = variableHandler.getStringVar(parsedSecond);
        } else if (parsedSecond.find("i<") != std::string::npos) {
            start2 = parsedSecond.find("i<")+2;
            end2 = parsedSecond.find(">");
            parsedSecond = parsedSecond.substr(start2, end2-start2);
            parsedSecond = variableHandler.getInputVar(parsedSecond);
        } else if (parsedSecond.find("f<") != std::string::npos) {
            start2 = parsedSecond.find("f<")+2;
            end2 = parsedSecond.find(">");
            parsedSecond = parsedSecond.substr(start2, end2-start2);
            parsedSecond = std::to_string(variableHandler.getFloatVar(parsedSecond));
        }

        if (parsedFirst == parsedSecond) {return true;} else {return false;} // if logic
    }
}

std::string console::push(std::string string) { // console::push logic
    std::string parsed; // parsed string to push
    if (string.find("(\"") != std::string::npos) { // pushing regular string
        parsed = console::parse(string, true);
    } else if (string.find("(s<") != std::string::npos) { // pushing string variable
        parsed = console::parseStr(string, false, true);
    } else if (string.find("(f<") != std::string::npos) { // pushing float variable
        parsed = console::parseFloat(string, false, true);
    } else if (string.find("(i<") != std::string::npos) { // pushing input variable
        parsed = console::parseInput(string, false, true);
    } else { // pushing numbers
        if (string.find("+") != std::string::npos) { // if pushing math
            const expression expInterp; // expression class
            parsed = std::to_string((expInterp.parseExpression(console::parse(string, false)))); // parsed expression result
        } else { // if pushing one number
            parsed = console::parse(string, false); // 
        }
    }
    return parsed;
}

void console::command(std::string consoleCommand) { // execute system command
    std::system(consoleCommand.c_str());
}