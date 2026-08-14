#include <iostream>
#include "console.h"
#include "expression.h"
#include "variables.h"

std::string console::parse(std::string string, bool isQuote, bool isVarStr, bool isVarFloat, bool createVar) const { // parse variables, strings and numbers
    std::string parsed;
    if (isQuote) {
        unsigned start = string.find("(\"")+2; // start past opening quotes
        unsigned end = string.find("\");"); // end before closing quotes
        parsed = string.substr(start,end-start); // get parsed string
    } else {
        if (isVarStr) { // if parsing a string variable
            if (createVar) { // if creating the string variable
                std::string parsedStr;
                variables variableHandler;
                unsigned start = string.find(".s<")+3; // start past opening
                unsigned end = string.find(">"); // end before closing
                unsigned startC = string.find("= (\"")+4; // start past opening content
                unsigned endC = string.find(");")-2; // end before closing content
                parsed = string.substr(start,end-start);
                parsedStr = string.substr(startC,endC-startC);
                variableHandler.createStringVar(parsed, parsedStr);
            } else { // if accessing premade string variable
                variables variableHandler;
                unsigned start = string.find("(s<")+3; // start past opening
                unsigned end = string.find(">);"); // end before closing
                parsed = string.substr(start,end-start); // get parsed variable name
                parsed = variableHandler.getStringVar(parsed); // get variable content, and prepare it to be returned
            }
        } else if (isVarFloat) { // if parsing a float variable
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
                unsigned start = string.find("(f<")+3; // start past opening
                unsigned end = string.find(">)"); // end before closing
                parsed = string.substr(start,end-start); // get parsed variable name
                parsed = std::to_string(variableHandler.getFloatVar(parsed)); // get variable content, and prepare it to be returned
            }
        } else {
            unsigned start = string.find("(")+1; // start past opening
            unsigned end = string.find(");"); // end before closing
            parsed = string.substr(start,end-start);
        }
    }
    return parsed;
}

std::string console::push(std::string string) const { // console::push logic
    std::string parsed; // parsed string to push
    if (string.find("(\"") != std::string::npos) { // pushing regular string
        parsed = console::parse(string, true, false, false, false);
    } else if (string.find("(s<") != std::string::npos) { // pushing string variable
        parsed = console::parse(string, false, true, false, false);
    } else if (string.find("(f<") != std::string::npos) { // pushing float variable
        parsed = console::parse(string, false, false, true, false); 
    } else { // pushing numbers
        if (string.find("+") != std::string::npos) { // if pushing math
            const expression expInterp; // expression class
            parsed = std::to_string((expInterp.parseExpression(console::parse(string, false, false, false, false)))); // parsed expression result
        } else { // if pushing one number
            parsed = console::parse(string, false, false, false, false); // 
        }
    }
    return parsed;
}

void console::command(std::string consoleCommand) const { // execute system command
    std::system(consoleCommand.c_str());
}