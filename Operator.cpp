//
// Created by julinka on 11.5.18.
//

#include "Operator.h"

Operator::Operator(const int & newOperator) : basicOperator((OperatorType)newOperator) {}

CellType Operator::getType() const {
    return CellType::BASICOPERATOR;
}

const Cell & Operator::getValue() const {
    return *this;
}

Cell & Operator::getValue() {
    return *this;
}

void Operator::setValue(const int & newOperator) {
    basicOperator = (OperatorType) newOperator;
}