#include <iostream>
#include <map>
#include "variables.h"

std::map<std::string, std::string> stringVars;
std::map<std::string, float> floatVars;
std::map<std::string, std::string> inputVars;

void variables::createStringVar(const std::string &name, const std::string &content) {
    stringVars[name] = content;
}

void variables::createFloatVar(const std::string &name, const float content) {
    floatVars[name] = content;
}

void variables::createInputVar(const std::string &name) {
    char input[100];
    std::cin.getline(input, sizeof(input));
    inputVars[name] = input;
}

void variables::removeStringVar(const std::string &name) {
    stringVars.erase(name);
}

void variables::removeFloatVar(const std::string &name) {
    floatVars.erase(name);
}

void variables::removeInputVar(const std::string &name) {
    inputVars.erase(name);
}

std::string variables::getStringVar(const std::string &name) {
    return stringVars.at(name);
}

std::string variables::getInputVar(const std::string &name) {
    return inputVars.at(name);
}

float variables::getFloatVar(const std::string &name) {
    return floatVars.at(name);
}