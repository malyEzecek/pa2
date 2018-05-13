//
// Created by julinka on 11.5.18.
//

#include "Number.h"

Number::Number(const double & newNumber): number(newNumber) {}

CommandType Number::getType() const {
    return CommandType::NUMBER;
}
const Cell & Number::getValue() const {
    return *this;
}

Cell & Number::getValue() {
    return *this;
}

void Number::setValue(const double & newNumber) {
    number = newNumber;
}
