//
// Created by julinka on 10.5.18.
//
#include "Cell.h"

Cell::Cell() : sizeOfCell(0), mode(defaultWidthOfCell) {}

int Cell::getCellSize() const {
    return sizeOfCell;
}

std::string Cell::editToWideOfCell(const std::string &editString) const {
    std::string returnString;
    if (editString.size() > Cell::mode) {
        returnString = editString.substr(0, (unsigned long) (Cell::mode - 1));
    } else if (editString.size() < Cell::mode) {
        returnString = editString;
        for (int i = 0; i < Cell::mode - editString.size(); ++i) {
            returnString.insert(returnString.begin(), ' ');
        }
    } else
        returnString = editString;
    return returnString;
}
