//
// Created by julinka on 11.5.18.
//

#include "Number.h"

Number::Number(const double & newNumber): Cell(), number(newNumber) {}

CellType Number::getType() const {
    return CellType::NUMBER;
}

const double & Number::getValue() const {
    return number;
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
