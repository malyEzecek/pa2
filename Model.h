//
// Created by julinka on 2.5.18.
//
#include <vector>
#include "Column.h"

#ifndef EDITOR_MODEL_H
#define EDITOR_MODEL_H

class Model {
private:
    unsigned width;
    unsigned height;
    /**
     * Todo..todo..todo..todotodotodo.todotodoooooooootdoddododo int nahrad cellem
     */
    std::vector<Column> spreadSheet;

public:

    Model();

    Model( const int & width, const int & height );

    unsigned getHeight() const;

    unsigned getWidth() const;

};

#endif //EDITOR_MODEL_H
