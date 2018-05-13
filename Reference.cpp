//
// Created by julinka on 11.5.18.
//

#include "Reference.h"

Reference::Reference(const std::string &newPosition) : position(newPosition) {}

CommandType Reference::getType() const {
    return CommandType::REFERENCE;
}

const Cell &Reference::getValue() const {
    return *this;
}

Cell &Reference::getValue() {
    return *this;
}

void Reference::setValue(const std::string &newPosition) {
    position = newPosition;
}

int Reference::getXCoor() const {
/*
 * todo
 */
}

int Reference::getYCoor() const {
    /*
     * todo
     */

}