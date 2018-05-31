//
// Created by julinka on 11.5.18.
//

#include "Number.h"

Number::Number(const double & newNumber): Cell(), number(newNumber) {}

CellType Number::getType() const {
    return CellType::NUMBER;
}

const Number *Number::getValue() const {
    return this;
}

double & Number::getValue() {
    return number;
}

void Number::setValue(const double & newNumber) {
    number = newNumber;
}

const std::string Number::ToString() const {

    std::string editString = std::to_string(number);
    editString = cutStringWithDouble(editString);
    return Cell::editToWideOfCell(editString);
}

Number *Number::clone() const {
    return new Number(*this);
}

void Number::evaluate(std::vector<const Cell *> &inputVector) const {
    inputVector.push_back(this);
}

std::string Number::cutStringWithDouble(const std::string &editString) const {
    int numbersOfZeroes = 0;
    bool dot = false;
    std::string returnString;

    for(const char & i : editString){
        if(dot){
            if (i == '0') {
                if(numbersOfZeroes >=2)
                    break;
                ++numbersOfZeroes;
            }
            returnString += i;
            continue;
        }
        returnString += i;
        if(i == '.'){
            dot = true;
            continue;
        }
    }
    if (returnString[returnString.size() - 1] == '.')
        return returnString.substr(0, returnString.size() - 4);

    return returnString;
}
