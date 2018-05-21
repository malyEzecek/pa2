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

const int Reference::getXCoor() const {
    return XCoor;
}

const int Reference::getYCoor() const {
    return YCoor;
}

const std::string Reference::ToString() const {
    std::string editString = "$";
    editString += std::to_string(XCoor) += std::to_string(YCoor);
    return Cell::editToWideOfCell(editString);
}

Reference *Reference::clone() const {
    return new Reference(*this);
}
