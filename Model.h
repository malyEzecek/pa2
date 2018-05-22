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

    Model();
    ~Model();
    /**
     * Todo..todo..todo..todotodotodo.todotodoooooooootdoddododo int nahrad Cell *
     */
    std::vector<std::vector<Cell *>> spreadSheet;
    static Model * instance;

public:

    unsigned getHeight() const;

    unsigned getWidth() const;

    static Model * getInstance();

    const Cell * getElement(const int & width, const int & height) const;

    void setWidth(unsigned int width);

    void setHeight(unsigned int height);

    void resizeTable(const int & xCoor, const int & yCoor);

    void setValue(const int & xCoor, const int & yCoor, const Cell * cell);

};

#endif //EDITOR_MODEL_H