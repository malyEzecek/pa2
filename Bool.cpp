//
// Created by julinka on 10.5.18.
//

#include "Bool.h"

Bool::Bool(const bool & newValue) : value(newValue) {}

CommandType Bool::getType() const{
    return CommandType::BOOLEAN;
}

const Cell & Bool::getValue() const{
    return *this;
}

Cell & Bool::getValue(){
    return *this;
}

void Bool::setValue(const bool & value){
    this->value = value;
}
