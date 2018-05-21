//
// Created by julinka on 11.5.18.
//

#include "Text.h"

Text::Text(const std::string &newText) : Cell(), text(newText) {}

CellType Text::getType() const {
    return CellType::TEXT;
}

const std::string & Text::getValue() const {
    return text;
}

std::string & Text::getValue() {
    return text;
}

void Text::setValue(const std::string &newText) {
    text = newText;
}

const std::string Text::ToString() const {
    return Cell::editToWideOfCell(text);
}

Text *Text::clone() const {
    return new Text(*this);
}
