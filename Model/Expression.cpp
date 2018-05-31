//
// Created by julinka on 12.5.18.
//

#include "Expression.h"

CellType Expression::getType() const{
    return CellType::EXPRESSION;
}

//const std::string Expression::ToString() {
//    return ;
//}

Expression *Expression::clone() const {
    return new Expression(*this);
}

Expression::Expression(std::vector<Cell *> &parsedCells, bool reference) : parsedStringToCells(parsedCells),
                                                                           reference(reference) {}

Expression::~Expression() {
    for (auto it : parsedStringToCells) {
        delete it;
    }
}

Expression::Expression() : reference(false) {}

const std::string Expression::ToString() const { // todo neco s tim udelej
    std::string returnString;

    return returnString;
}

void Expression::evaluate(std::vector<const Cell *> &inputVector) const {
    for(const Cell * cell : parsedStringToCells){
        inputVector.push_back(cell);
    }
}

const Expression *Expression::getValue() const { //todo neco s tim udelej prosimte
    return nullptr;
}
