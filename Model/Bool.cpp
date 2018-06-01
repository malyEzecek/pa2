//
// Created by julinka on 10.5.18.
//

#include "Bool.h"


Bool::Bool(const bool newValue) : Cell(), value(newValue) {}

CellType Bool::getType() const {
    return CellType::BOOLEAN;
}

const Bool * Bool::getValue() const {
    return this;
}


void Bool::setValue(const bool &value) {
    this->value = value;
}

const std::string Bool::ToString(bool load) const {
    std::string editString;
    if (value)
        editString = "true";
    else
        editString = "false";

    if(!load)
        return "\033[0;36m" + Cell::editToWideOfCell(editString) + "\033[0m";
    else
        return editString;
}

Bool *Bool::clone() const {
    return new Bool(*this);
}

void Bool::evaluate(std::vector<const Cell *> &inputVector) const {
    inputVector.push_back(this);
;}
