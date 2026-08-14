#include <iostream>
#include "console.h"
#include "expression.h"
#include "variables.h"

std::string console::parse(std::string string, bool isQuote, bool isVarStr, bool isVarFloat, bool createVar) const {
    std::string parsed;
    if (isQuote) {
        unsigned start = string.find("(\"")+2; // start past opening quotes
        unsigned end = string.find("\");"); // end before closing quotes
        parsed = string.substr(start,end-start);
    } else {
        if (isVarStr) {
            if (createVar) {
                std::string parsedStr;
                variables variableHandler;
                unsigned start = string.find(".s<")+3; // start past opening
                unsigned end = string.find(">"); // end before closing
                unsigned startC = string.find("= (\"")+4; // start past opening content
                unsigned endC = string.find(");")-2; // end before closing content
                parsed = string.substr(start,end-start);
                parsedStr = string.substr(startC,endC-startC);
                variableHandler.createStringVar(parsed, parsedStr);
            } else {
                variables variableHandler;
                unsigned start = string.find("(s<")+3; // start past opening
                unsigned end = string.find(">);"); // end before closing
                parsed = string.substr(start,end-start);
                parsed = variableHandler.getStringVar(parsed);
            }
        } else if (isVarFloat) {
            if (createVar) {
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
            } else {
                variables variableHandler;
                unsigned start = string.find("(f<")+3; // start past opening
                unsigned end = string.find(">)"); // end before closing
                parsed = string.substr(start,end-start);
                parsed = std::to_string(variableHandler.getFloatVar(parsed));
            }
        } else {
            unsigned start = string.find("(")+1; // start past opening
            unsigned end = string.find(");"); // end before closing
            parsed = string.substr(start,end-start);
        }
    }
    return parsed;
}

std::string console::push(std::string string) const {
    std::string parsed;
    float solved;
    if (string.find("(\"") != std::string::npos) {
        parsed = console::parse(string, true, false, false, false);
    } else if (string.find("(s<") != std::string::npos) {
        parsed = console::parse(string, false, true, false, false);
    } else if (string.find("(f<") != std::string::npos) {
        parsed = console::parse(string, false, false, true, false);
    } else {
        if (string.find("+") != std::string::npos) {
            const expression expInterp;
            parsed = std::to_string((expInterp.parseExpression(console::parse(string, false, false, false, false))));
        } else {
            parsed = console::parse(string, false, false, false, false);
        }
    }
    return parsed;
}

void console::command(std::string consoleCommand) const {
    std::system(consoleCommand.c_str());
}