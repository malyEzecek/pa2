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
#include <cmath>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include "Model.h"

enum class CommandType {
    CLEAR,
    SET,
    EXIT,
    SAVE,
    LOAD,
    RESIZE,
    GETVALUE
};

class InvalidInput {
private:
    std::string warningOfInvalidInput;
public:

    explicit InvalidInput(const std::string &warning) : warningOfInvalidInput(warning) {}

    const std::string &getStr() const {
        return warningOfInvalidInput;
    }
};

class InvalidExpressionOrReference {
private:
    std::string warningOfInvalidExpressionReference;

public:
    explicit InvalidExpressionOrReference(const std::string &warning) : warningOfInvalidExpressionReference(warning) {}

    const std::string &getStr() const {
        return warningOfInvalidExpressionReference;
    }
};


class Command {
private:
    CommandType typeOfCommand;

    static const int maxCharInCommand = 9;

    CommandType parseToCommand(std::string &inputString, bool *delimiters) const;

    void checkParsedStrCoordinates(int &xCoor, int &yCoor, std::string &inputString, std::string &xCoorString,
                                   std::string &yCoorString, bool *delimiters, bool firstParameter) const;

    void parseStringToCoordinates(int &xCoor, int &yCoor, std::string &inputString, bool *delimiters,
                                  bool firstParameter = true) const;

    Cell *parseStringToCell(std::string inputString, bool *delimiters) const;

    CommandType SwitchTypeOfCommand(const std::string &parsedCommand) const;

    void getValueCommand(std::string &temporaryForCutting, bool *delimiters);

    void exitCommand(std::string &temporaryForCutting, bool *delimiters, bool &exit);

    void saveCommand(std::string &temporaryForCutting, bool &exit);

    void loadCommand(std::string &temporaryForCutting, bool &exit);

    void ExecuteCommand(std::string &temporaryForCutting, bool *delimiters, bool &exit);

    void deleteThisUglySpaces(std::string &inputString) const;

    void parseStringToNumber(std::string &inputString, std::string &number) const;

    std::string parseStringToText(std::string &inputString) const;

    void parseStringToBool(std::string &inputString) const;

    void parseExpressionFinalControl(std::vector<Cell *> &possibleCells, std::string &inputString, bool &operatorFirstType,
                                     bool &operatorSecondType, int &brackets, OperatorType *&mathOperator) const;

    void parseExpressionMathematicalPart(std::vector<Cell *> &possibleCells, std::string &inputString,
                                         bool &operatorFirstType, bool &operatorSecondType,
                                         OperatorType *&mathOperator, int &amountOfBracketsForMathFunc,
                                         int &brackets) const;

    void parseExpressionBracketsPart(std::vector<Cell *> &possibleCells, std::string &inputString, bool &operatorSecondType,
                                     int &brackets, int &amountOfBracketsForMathFunc,
                                     OperatorType *&mathOperator) const;

    void parseExpressionBasicOperatorPart(std::vector<Cell *> &possibleCells, std::string &inputString,
                                          bool &operatorFirstType) const;

    void parseExpressionNumberPart(std::vector<Cell *> &possibleCells, std::string &inputString,
                                   bool &operatorFirstType) const;

    void parseExpression(std::vector<Cell *> &possibleCells, std::string &inputString, bool *delimiters,
                         bool &reference) const;

    void parseToXYString(std::string &inputString, std::string &xCoorString, std::string &yCoorString,
                         std::vector<char> &delim, bool first, bool breakMoment, int &position, bool *delimiters) const;

    OperatorType *parseStringToMathFunction(std::string &inputString) const;

    OperatorType *parseStringToAggregationFunction(std::string &inputString) const;

    void parseAggregationFuncValue(std::string &inputString, std::vector<Cell *> &possibleCells,
                                   const OperatorType *aggregationFunction, bool *delimiters) const;

    void referenceEvaluation(const Cell *actualCell, std::vector<const Cell *> &detectorOfCyclus,
                             std::vector<const Cell *> &expressionWithoutReferences) const;

    void InfixToPostfix(std::vector<const Cell *> &expressionWithoutReferences,
                        std::vector<const Cell *> &insideOfExpression) const;

    void getResizeParameters(std::string &temporaryForCutting, int &yCoor, int &xCoor) const;

    void getCoord(std::string &temporaryForCutting, std::string &cord) const;

    void getLoadSaveParameter(std::string &temporaryForCutting, std::string &loadingPath, bool &exit) const;

    void writeToFile(std::ofstream &myFileSave) const;

    void exitOrHelpCorrectCommand(std::string &temporaryForCutting) const;

    bool SaveTableBeforeExit(const std::string &decision) const;

    void getInverseOperator(OperatorType *&mathOperator, OperatorType &reversedOperator) const;

    void evaluatePostfixExpressionBasicOpearators(const Cell * cellPointer, std::stack<const Number *> &ss) const;

    const Number *evaluatePostfixExpression(std::vector<const Cell *> &postfixExpression) const;

    void postfixExpressionError(std::stack<const Number *> ss) const;

    void parseExpressionError(std::vector<Cell *> &possibleCells) const;

public:

    static const std::string SMALLTABLESIZE;

    static const std::string OPENFILEERROR;

    static const std::string COMMANDDOESNTEXISTS;

    static const std::string INVALIDPARAMETER;

    static const std::string INVALIDEXPRESSION;

    static const std::string NULLREFERENCE;

    static const std::string INVALIDREFERNCEINSIDEEXPRESSION;

    static const std::string CYCLICDEPENDENCY;

    Command();

    void SetCommand(const std::string &inputString, bool &exit);

    CommandType returnCommandType() const;

    const Number *evaluateExpression(const Cell *expression, std::vector<const Cell *> &checkReferences) const;

    void evaluateReference(const unsigned &height, const unsigned &width, std::vector<const Cell *> &checkCycles) const;

};


#endif //EDITOR_COMMAND_H