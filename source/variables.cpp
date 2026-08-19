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
    char input[];
    std::cin.getline(input, sizeof(input));
    inputVars[name] = input;
}

void variables::removeStringVar(std::string name) {
    stringVars.erase(name);
}

void variables::removeFloatVar(std::string name) {
    floatVars.erase(name);
}

void variables::removeInputVar(std::string name) {
    inputVars.erase(name);
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