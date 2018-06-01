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
    Expression * newExpression = new Expression();
    for( int i = 0; i < (int)this->parsedStringToCells.size(); ++i){
        if(this->parsedStringToCells[i]->getType() == CellType::NUMBER)
            newExpression->parsedStringToCells.push_back(new Number( ((Number *)this->parsedStringToCells[i]->getValue())->getValue() ));
        else if(this->parsedStringToCells[i]->getType() == CellType::REFERENCE)
            newExpression->parsedStringToCells.push_back(new Reference( ((Reference *)this->parsedStringToCells[i]->getValue())->getXCoor(), ((Reference *)this->parsedStringToCells[i]->getValue())->getYCoor()));
        else if(this->parsedStringToCells[i]->getType() == CellType::OPERATION)
            newExpression->parsedStringToCells.push_back(new Operator( ((Operator *)this->parsedStringToCells[i]->getValue())->returnOperatorType() ));
    }
    return newExpression;
}

Expression::Expression(std::vector<Cell *> &parsedCells, bool reference) : reference(reference) {
    for(int i = 0; i < (int)parsedCells.size(); ++i){
        parsedStringToCells.push_back(parsedCells[i]);
    }
}

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

void Expression::evaluate(std::vector< const Cell *> &inputVector) const {
    for(const Cell *  cell : parsedStringToCells){
        inputVector.push_back(cell);
    }
}

const Expression *Expression::getValue() const { //todo neco s tim udelej prosimte
    return nullptr;
}
