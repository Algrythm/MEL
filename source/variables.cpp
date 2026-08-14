#include <iostream>
#include <map>
#include "variables.h"

std::map<std::string, std::string> stringVars;
std::map<std::string, float> floatVars;

void variables::createStringVar(std::string name, std::string content) {
    stringVars[name] = content;
}

void variables::createFloatVar(std::string name, float content) {
    floatVars[name] = content;
}

std::string variables::getStringVar(std::string name) {
    return stringVars.at(name);
}

float variables::getFloatVar(std::string name) {
    return floatVars.at(name);
}