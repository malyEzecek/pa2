//
// Created by julinka on 11.5.18.
//

#include "Text.h"

Text::Text(const std::string newText): text(newText) {}

CommandType Text::getType() const {
    return CommandType::TEXT;
}

const Cell & Text::getValue() const {
    return *this;
}

Cell & Text::getValue(){
    return *this;
}

void Text::setValue(const std::string newText){
    text = newText;
}