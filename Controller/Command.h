//
// Created by julinka on 19.5.18.
//
#pragma once
#ifndef EDITOR_COMMAND_H
#define EDITOR_COMMAND_H

#include <vector>
#include <cstdlib>
#include <stack>
#include <iostream>
#include <sstream>
#include <math.h>
#include "../Model/Model.h"

enum class CommandType {
    CLEAR,
    SET,
    EXIT,
    SAVE,
    LOAD,
    RESIZE
};


class Command {
private:
    CommandType typeOfCommand;
    static const int maxCharInCommand = 7;
    static const int FirstA = 97; // in ASCII code

    CommandType parseToCommand(std::string &inputString, bool *delimiters) const;

    void parseStringToCoordinates(int &xCoor, int &yCoor, std::string &inputString, bool *delimiters) const;

    Cell *parseStringToCell(std::string inputString, bool *delimiters) const;

    CommandType SwitchTypeOfCommand(const std::string &parsedCommand) const;

    void ExecuteCommand(std::string &temporaryForCutting, bool *delimiters, bool & exit);

    void deleteThisUglySpaces(std::string &inputString) const;

    void parseStringToNumber(std::string &inputString, std::string &number) const;

    std::string parseStringToText(std::string &inputString) const;

    void parseStringToBool(std::string &inputString) const;

    void parseExpression(std::vector<Cell *> &possibleCells, std::string &inputString, bool *delimiters, bool & reference) const;

    void parseToXYString(std::string &inputString, std::string &xCoorString, std::string &yCoorString,
                         std::vector<char> &delim, bool first, bool breakMoment, int &position, bool *delimiters) const;

    OperatorType *parseStringToMathFunction(std::string &inputString) const;

    OperatorType *parseStringToAggregationFunction(std::string &inputString) const;

    void parseAggregationFuncValue(std::string &inputString, std::vector<Cell *> &possibleCells,
                                   const OperatorType *aggregationFunction, bool *delimiters) const;

    void referenceEvaluation(const Cell *actualCell, std::vector<const Cell *> &detectorOfCyclus, std::vector<const Cell * > &expressionWithoutReferences) const;

    void InfixToPostfix(std::vector<const Cell *> &expressionWithoutReferences, std::vector<const Cell *> &insideOfExpression) const;

    void getResizeParameters(std::string & temporaryForCutting, int &yCoor, int & xCoor) const;

    void getCoord(std::string &temporaryForCutting, std::string &cord) const;

    void getLoadSaveParameter(std::string &temporaryForCutting, std::string &loadingPath, bool & exit) const;

    void writeToFile(std::ofstream & myFileSave) const;

    void exitOrHelpCorrectCommand(std::string & temporaryForCutting) const;

    bool SaveTableBeforeExit(const std::string & decision) const;

    void getInverseOperator(OperatorType * & mathOperator, OperatorType & reversedOperator) const;

    const Number * evaluatePostfixExpression(std::vector<const Cell *> &postfixExpression) const;

public:

    Command();
    void SetCommand(const std::string &inputString, bool & exit);

    CommandType returnCommandType() const;

    void evaluateExpression(const int & yCoor, const int & xCoor) const;

};


#endif //EDITOR_COMMAND_H