//
// Created by julinka on 2.5.18.
//
#pragma once
#include <vector>
#include "Cell.h"

#ifndef EDITOR_MODEL_H
#define EDITOR_MODEL_H

class Model {
private:

    static unsigned width;
    static unsigned height;

    Model();
    /**
     * Todo..todo..todo..todotodotodo.todotodoooooooootdoddododo int nahrad Cell *
     */
    static std::vector<std::vector<Cell>> spreadSheet;
    static Model * instance;

public:

    unsigned getHeight() const;

    unsigned getWidth() const;

    static Model * getInstance();

    const Cell & getElement(const int & width, const int & height) const;

    void setWidth(unsigned int width);

    void setHeight(unsigned int height);

    void resizeTable();

    void setValue(const int & xCoor, const int & yCoor, const Cell & cell);

};

#endif //EDITOR_MODEL_H
