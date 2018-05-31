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
    std::string returnString;
    switch (basicOperator){
        case OperatorType::PLUS:{
            return returnString+= " + ";
        }
        case OperatorType::MINUS:{
            return returnString+= " - ";
        }
        case OperatorType::MULTIPLY:{
            return returnString+= " * ";
        }
        case OperatorType::DIVIDE:{
            return returnString+= " / ";
        }
        case OperatorType::BRACKETOPEN:{
            return returnString+= " ( ";
        }
        case OperatorType::SINOPEN:{
            return returnString+= " sin( ";
        }
        case OperatorType::ABSOPEN:{
            return returnString+= " abs( ";
        }
        case OperatorType::COSOPEN:{
            return returnString+= " cos( ";
        }
        case OperatorType::TANOPEN:{
            return returnString+= " tan( ";
        }
        case OperatorType::ROUNDOPEN:{
            return returnString+= " round( ";
        }
        case OperatorType::LOGOPEN:{
            return returnString+= " log( ";
        }
        case OperatorType::LOG2OPEN:{
            return returnString+= " log2( ";
        }
        case OperatorType::AVGOPEN:{
            return returnString+= " avg( ";
        }
        case OperatorType::SUMOPEN:{
            return returnString+= " sum( ";
        }
        case OperatorType::MAXOPEN:{
            return returnString+= " max( ";
        }
        default:
            return returnString+= " ) ";
    }
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


