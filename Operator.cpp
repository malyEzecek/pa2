//
// Created by julinka on 11.5.18.
//

#include "Operator.h"

Operator::Operator(OperatorType newOperator) : basicOperator(newOperator) {}

CellType Operator::getType() const {
    return CellType::BASICOPERATOR;
}

const OperatorType Operator::getValue() const {
    return basicOperator;
}

void Operator::setValue(const int & newOperator) {
    basicOperator = (OperatorType) newOperator;
}

Operator *Operator::clone() const {
    return new Operator(*this);
}

const std::string Operator::ToString() const {
    return std::__cxx11::string();
}

