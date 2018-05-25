//
// Created by julinka on 11.5.18.
//

#include "Operator.h"

Operator::Operator(OperatorType newOperator) : basicOperator(newOperator) {}

CellType Operator::getType() const {
    return CellType::BASICOPERATOR;
}

const Operator * Operator::getValue() const {
    return this;
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

void Operator::evaluate(std::vector<const Cell *> &inputVector) const {
    inputVector.push_back(this);
}


