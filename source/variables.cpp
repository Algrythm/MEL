#include <iostream>
#include <map>
#include "variables.h"

std::map<std::string, std::string> stringVars;
std::map<std::string, float> floatVars;
std::map<std::string, std::string> inputVars;

void variables::createStringVar(std::string name, std::string content) {
    stringVars[name] = content;
}

void variables::createFloatVar(std::string name, float content) {
    floatVars[name] = content;
}

void variables::createInputVar(std::string name) {
    std::string input;
    std::cin >> input;
    inputVars[name] = input;
}

std::string variables::getStringVar(std::string name) {
    return stringVars.at(name);
}

std::string variables::getInputVar(std::string name) {
    return inputVars.at(name);
}

float variables::getFloatVar(std::string name) {
    return floatVars.at(name);
}