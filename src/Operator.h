//
// Created by julinka on 11.5.18.
//

#ifndef EDITOR_OPERATOR_H
#define EDITOR_OPERATOR_H

#include <math.h>
#include "Cell.h"

enum class OperatorType { // skupiny <1,2>, <3,4>, <5,6>, <7,14>, <15, 17>
    PLUS = 1, // first type
    MINUS = 2, // first type
    MULTIPLY = 3, // second type
    DIVIDE = 4, // second type
    BRACKETOPEN = 5, // third type begin
    BRACKETCLOSE = 6,
    SINOPEN = 7,
    SQRTOPEN,
    ABSOPEN,
    COSOPEN,
    TANOPEN,
    ROUNDOPEN,
    LOGOPEN,
    LOG2OPEN = 14, // third type end
    SINCLOSE = 15, // forth type begin
    SQRTCLOSE,
    ABSCLOSE,
    COSCLOSE,
    TANCLOSE,
    ROUNDCLOSE,
    LOGCLOSE,
    LOG2CLOSE = 22, // forth type end
    AVGOPEN = 23, // third type
    SUMOPEN,
    MAXOPEN = 25, // third type
    AVGCLOSE = 26, // forth type
    SUMCLOSE,
    MAXCLOSE = 28 // forth type
};

class Operator : public Cell {
private:
    OperatorType basicOperator;

    int getWeightOfOperator(const OperatorType & value) const;

public:
    const double PI = 3.14159265;

    const double PIDEGREE = 180;

    Operator() = default;

    ~Operator() = default;

    explicit Operator(OperatorType newOperator);

    CellType getType() const override;

    const Operator *getValue() const override;

    void setValue(const int &newOperator);

    Operator *clone() const override;

    const std::string ToString(bool load) const override;

    void evaluate(std::vector<const Cell *> & inputVector) const override;

    OperatorType returnOperatorType() const;

    static bool IsClosedOperator(const OperatorType & operators);

    static bool IsOpenedOperator(const OperatorType & operators);

    bool HasHigherPrecedence(const OperatorType & topOfStack) const;

    OperatorType returnOpenedBracket() const;

    int getWeighOfOperator() const;

    double evaluateNumbers(const double &first, const double &second) const;

    double evaluateNumbers(const double &first) const;
};


#endif //EDITOR_OPERATOR_H