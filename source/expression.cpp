#include <iostream>
#include "expression.h"
#include <vector>
#include <sstream>

float expression::parseExpression(std::string expString) const {
    int iterations = 0;
    float solvedFloat = 0;
    std::stringstream ss(expString);
    std::string item;
    std::vector<std::string> items = {};

    while (ss >> item) {
        items.push_back(item);
        iterations++;
    }

    for (int i = 0; i < iterations; i++) {
        if (std::isdigit(items[i][0])) {
            if (items[i+1] == "+") {
                solvedFloat = std::stof(items[i]) + std::stof(items[i+2]);
                i = i + 2;
            }
        }
    }
    return solvedFloat;
}