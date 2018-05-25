//
// Created by julinka on 11.5.18.
//

#include "Operator.h"

Operator::Operator(OperatorType newOperator) : basicOperator(newOperator) {}

CellType Operator::getType() const {
    return CellType::BASICOPERATOR;
}

const Operator *Operator::getValue() const {
    return this;
}

void Operator::setValue(const int &newOperator) {
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

OperatorType Operator::returnOperatorType() const {
    return basicOperator;
}


bool Operator::IsOpeningOperator() const {
    if ((int)basicOperator >= 7 && (int)basicOperator < 14)
        return true;
    else return false;
}


