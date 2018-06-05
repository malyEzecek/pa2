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
/** Width of the table. **/
    unsigned width;
/** Height of the table. **/
    unsigned height;
/** Boolean that checks if table was resized. **/
    bool resized;

/** 2D array of Cell pointers. Storage of the main program information.**/
    std::vector<std::vector<Cell *>> spreadSheet;
/** My new experiment how to make Singleton class in C++.**/
    static Model *instance;

/**
 * Default constructor. Singleton class.
 */
    Model();
/**
 * Default destructor.Singleton class.
 */
    ~Model();


public:
/** default table width **/
    static const unsigned WIDTH = 10;
/** default table hight **/
    static const unsigned HIGHT = 25;
/**
 * @return actual table height
 */
    unsigned getHeight() const;

/**
 * @return actual table width
 */
    unsigned getWidth() const;
/**
 * The main function that helps us to implement Singleton class.
 * @return the only one existing instance of class Model.
 */
    static Model *getInstance();
/**
 * "Helper function" that calls private destructor.
 */
    static void releaseInstance();
/**
 *
 * @param height number of row in the table
 * @param width number of column in the table
 * @return const pointer to the element on (height -1, row) position.
 */
    const Cell *getElement(const int &height, const int &width) const;
/**
 * Resize table. DELETE CELL VALUES FROM THE TABLE IF IT'S OUT OF THE TABLE BOARDERS.
 * @param xCoor new width
 * @param yCoor new height
 */
    void resizeTable(const int &xCoor, const int &yCoor);

    /**
     * Traditional insertation of different value kinds to the certain position in the table.
     * @param xCoor certain column number in the table
     * @param yCoor certain row number in the table
     * @param cell value to insert
     */

    void setValue(const int &xCoor, const int &yCoor, const Cell *cell);
/**
 * Traditional delete of any cells in the table.
 * @param yCoord certain row number in the table
 * @param xCoor certain column number in the table
 */
    void deleteValue(const int &yCoord, const int &xCoor);
/**
 * Shows if table was resized before.
 * @return true or false
 */
    bool wasResized() const;
/**
 * Clear out the whole table. All pointers = nullptr.
 * It is used in load process.
 */
    void clearTable();

};

#endif //EDITOR_MODEL_H