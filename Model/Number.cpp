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
    return Cell::editToWideOfCell(editString);
}

Number *Number::clone() const {
    return new Number(*this);
}

void Number::evaluate(std::vector<const Cell *> &inputVector) const {
    inputVector.push_back(this);
}
