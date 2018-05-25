//
// Created by julinka on 11.5.18.
//

#ifndef EDITOR_OPERATOR_H
#define EDITOR_OPERATOR_H

#include "Cell.h"

enum class OperatorType {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    BRACKET,
    SIN,
    SQRT,
    ABS,
    COS,
    TAN,
    ROUND,
    AVG,
    SUM,
    LOG,
    LOG2,
    MAX
};

class Operator : public Cell {
private:
    OperatorType basicOperator;

public:
    Operator() = default;

    ~Operator() = default;

    explicit Operator(OperatorType newOperator);

    CellType getType() const;

    const Operator *getValue() const override;

    void setValue(const int &newOperator);

    Operator *clone() const override;

    const std::string ToString() const override;

    void evaluate(std::vector<const Cell *> & inputVector) const override;

};


#endif //EDITOR_OPERATOR_H