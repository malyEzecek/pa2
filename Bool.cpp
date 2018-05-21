//
// Created by julinka on 10.5.18.
//

#include "Bool.h"


Bool::Bool(const bool &newValue) : Cell(), value(newValue) {}

CellType Bool::getType() const {
    return CellType::BOOLEAN;
}

bool Bool::getValue() const {
    return value;
}

bool Bool::getValue() {
    return value;
}

void Bool::setValue(const bool &value) {
    this->value = value;
}

const std::string Bool::ToString() const {
    std::string editString;
    if (value)
        editString = "true";
    else
        editString = "false";
    return Cell::editToWideOfCell(editString);

}

Bool *Bool::clone() const {
    return new Bool(*this);
}
