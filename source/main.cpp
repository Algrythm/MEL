#include <iostream>
#include <fstream>
#include "interpreter.h"
#include "console.h"
#include <ctime>
#include "variables.h"
#include <cstring>

std::string version = "MEL V0.1.5";

std::string getFileName(int argc, char *argv[]) {
    std::string fileName;
    if (argc > 1) { // there is a command line arg
        char versionCommand[] = "--version";
        if (std::strcmp(argv[1],versionCommand) == 0) {
            std::cout << version << std::endl;
            return "none";
        } else {
            fileName = argv[1];
            return fileName;
        }
    } else { // no command line filename
        std::cout << "No file specified!" << std::endl;
        std::cout << "Please enter file directory to open: " << std::endl;
        std::cin >> fileName;
        return fileName;
    }
}

int main(int argc, char *argv[]) {
    time_t curTime;
    variables variableHandler;
    std::string fileName = getFileName(argc, argv); // call getfilename to either pull from arguments or input
    if (fileName == "none") {return 0;}
    int curLine = 0; // track current line
    std::string fileContent;
    std::ifstream file(fileName);
    while (std::getline(file, fileContent)) { // iterate through lines
        time(&curTime);
        variableHandler.createStringVar("sys::curTime", std::to_string(curTime));
        if (interpret(fileContent, curLine) == 1) { // if there is an error in interpretation
            return 0;
        }

        curLine++;
    }
    return 0;
}