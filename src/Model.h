//
// Created by julinka on 2.5.18.
//
#pragma once

#include <vector>
#include "Bool.h"
#include "Reference.h"
#include "Number.h"
#include "Text.h"
#include "Expression.h"
#include "Operator.h"

#ifndef EDITOR_MODEL_H
#define EDITOR_MODEL_H

class Model {
private:

    unsigned width;
    unsigned height;

    bool resized;

    Model();

    ~Model();

    std::vector<std::vector<Cell *>> spreadSheet;
    static Model *instance;

public:

    static const unsigned WIDTH = 10;

    static const unsigned HIGHT = 25;

    unsigned getHeight() const;

    unsigned getWidth() const;

    static Model *getInstance();

    static void releaseInstance();

    const Cell *getElement(const int &height, const int &width) const;

    void resizeTable(const int &xCoor, const int &yCoor);

    void setValue(const int &xCoor, const int &yCoor, const Cell *cell);

    void deleteValue(const int &yCoord, const int &xCoor);

    bool wasResized() const;

    void clearTable();

};

#endif //EDITOR_MODEL_H