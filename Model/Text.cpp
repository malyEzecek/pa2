//
// Created by julinka on 11.5.18.
//

#include "Text.h"

Text::Text(const std::string &newText) : Cell(), text(newText) {}

CellType Text::getType() const {
    return CellType::TEXT;
}

const Text * Text::getValue() const {
    return this;
}

std::string & Text::getValue() {
    return text;
}

void Text::setValue(const std::string &newText) {
    text = newText;
}

const std::string Text::ToString() const {

    std::string returnString = "\033[0;31m" + Cell::editToWideOfCell(text)+ " \033[0m";

    return returnString;
}

Text *Text::clone() const {
    return new Text(*this);
}

void Text::evaluate(std::vector<const Cell *> &inputVector) const {
    inputVector.push_back(this);
}

