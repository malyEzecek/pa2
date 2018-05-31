//
// Created by julinka on 11.5.18.
//

#include "Operator.h"

Operator::Operator(OperatorType newOperator) : basicOperator(newOperator) {}

CellType Operator::getType() const {
    return CellType::OPERATION;
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
    std::string returnString;
    switch (basicOperator) {
        case OperatorType::PLUS: {
            return returnString += " + ";
        }
        case OperatorType::MINUS: {
            return returnString += " - ";
        }
        case OperatorType::MULTIPLY: {
            return returnString += " * ";
        }
        case OperatorType::DIVIDE: {
            return returnString += " / ";
        }
        case OperatorType::BRACKETOPEN: {
            return returnString += " ( ";
        }
        case OperatorType::SINOPEN: {
            return returnString += " sin( ";
        }
        case OperatorType::ABSOPEN: {
            return returnString += " abs( ";
        }
        case OperatorType::COSOPEN: {
            return returnString += " cos( ";
        }
        case OperatorType::TANOPEN: {
            return returnString += " tan( ";
        }
        case OperatorType::ROUNDOPEN: {
            return returnString += " round( ";
        }
        case OperatorType::LOGOPEN: {
            return returnString += " log( ";
        }
        case OperatorType::LOG2OPEN: {
            return returnString += " log2( ";
        }
        case OperatorType::AVGOPEN: {
            return returnString += " avg( ";
        }
        case OperatorType::SUMOPEN: {
            return returnString += " sum( ";
        }
        case OperatorType::MAXOPEN: {
            return returnString += " max( ";
        }
        default:
            return returnString += " ) ";
    }
}

void Operator::evaluate(std::vector<const Cell *> &inputVector) const {
    inputVector.push_back(this);
}

OperatorType Operator::returnOperatorType() const {
    return basicOperator;
}

bool Operator::IsClosedOperator(const OperatorType &operators) {
    if ((operators >= OperatorType::SINCLOSE && operators <= OperatorType::LOG2CLOSE) ||
        operators >= OperatorType::AVGCLOSE || operators == OperatorType::BRACKETCLOSE)
        return true;
    return false;
}

bool Operator::HasHigherPrecedence(const OperatorType &topOfStack) const {
    int topWeight = getWeightOfOperator(topOfStack);
    int valueWeight = getWeightOfOperator(basicOperator);
    return topWeight >= valueWeight ? true : false;
}

int Operator::getWeightOfOperator(const OperatorType & value) const {
    switch (value) {
        case OperatorType::PLUS:
        case OperatorType::MINUS:
            return 1;
        case OperatorType::MULTIPLY:
        case OperatorType::DIVIDE:
            return 2;
    }
}

bool Operator::IsOpenedOperator(const OperatorType &operators) {
    if ((operators == OperatorType::BRACKETOPEN ||
         (operators >= OperatorType::SINOPEN && operators <= OperatorType::LOG2OPEN) ||
         (operators >= OperatorType::AVGOPEN && operators <= OperatorType::MAXOPEN))){
        return true;
    }
    return false;
}

OperatorType Operator::returnOpenedBracket() const {
    if (basicOperator == OperatorType::BRACKETCLOSE)
        return OperatorType::BRACKETCLOSE;
    else if (basicOperator >= OperatorType::SINCLOSE && basicOperator <= OperatorType::LOG2CLOSE)
        return (OperatorType)(((int) basicOperator )- 8);
    else if (basicOperator >= OperatorType::AVGCLOSE)
        return (OperatorType)(((int) basicOperator )- 4);
}



