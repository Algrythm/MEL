#include <iostream>
#include "expression.h"
#include <vector>
#include <algorithm>
#include <array>
#include <sstream>

std::array<char, 4> operators = {'+', '-', '/', '*'};

float expression::parseExpression(const std::string &expString) const {
    float solvedFloat = 0; // returned float
    std::vector<std::string> tokens; // all tokens in expression
    char lastOperator; // operator preceding current operand
    std::string token; // current working token
    std::stringstream ss(expString);

    while (ss >> token) {
        tokens.push_back(token);
    }

    for (int i = 0; i < tokens.size(); i++) {
        if (i == 0) { // if this is the first operand of the expression
            solvedFloat = std::stof(tokens[i]);
        } else if (!std::isdigit(tokens[i][0])) { // if token is an operator
            lastOperator = tokens[i][0];
        } else { // this is an operand, not the first operand
            switch (lastOperator) {
                case '+':
                    solvedFloat += std::stof(tokens[i]);
                    break;
                case '-':
                    solvedFloat -= std::stof(tokens[i]);
                    break;
                case '/':
                    solvedFloat /= std::stof(tokens[i]);
                    break;
                case '*':
                    solvedFloat *= std::stof(tokens[i]);
                    break;
            }
        }
    }

    return solvedFloat;
}

bool expression::isExpression(const std::string &expString) const {
    for (int i = 0; i < operators.size(); i++) {
        if (expString.find(operators[i]) != std::string::npos) {return true;} // if an operator is found in the string, return true
    }
    return false; // else false
}