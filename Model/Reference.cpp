//
// Created by julinka on 11.5.18.
//

#include "Reference.h"

Reference::Reference(const int & XPosition, const int & YPosition) : Cell(), XCoor(XPosition), YCoor(YPosition) {}

CellType Reference::getType() const {
    return CellType::REFERENCE;
}


void Reference::setValue(const int & XPosition, const int & YPosition) {
    XCoor = XPosition;
    YCoor = YPosition;
}

int Reference::getXCoor() const {
    return XCoor;
}

int Reference::getYCoor() const {
    return YCoor;
}

const std::string Reference::ToString(bool load) const {
    std::string editString = "$";
    editString += std::to_string(XCoor) + '$' + std::to_string(YCoor);

    if (!load)
        return Cell::editToWideOfCell(editString);
    return " " + editString + " ";
}

Reference *Reference::clone() const {
    return new Reference(*this);
}

void Reference::evaluate(std::vector<const Cell *> &inputVector) const {
    inputVector.push_back(this);
}

const Reference *Reference::getValue() const {
    return this;
}
