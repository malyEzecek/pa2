//
// Created by julinka on 2.5.18.
//
#include <iostream>
#include <string>
#include "View.h"

void View::Refresh() {}

/**
 * Get model as a parameter and transform the information from the model
 * to an typical "Excel table".
 * @param model
 */

void View::createTable( const Model & model ) {
    std::string columnName = "    A     ";
    int line = 0;
    for( int i = 0, actualPositionLastLetter = 5, traverse = 0; i < model.getWidth(); ++i ){
        if( i % 26 ){
            if( traverse % 2 ){
                for(int t = 0; t < (int) columnName.size(); ++t)
            }

            columnName[actualPositionLastLetter] = 'A';
            ++actualPositionLastLetter;
            columnName[actualPositionLastLetter]
        }
        std::cout << columnName;

    }
    for( unsigned i = 0; i < model.getHeight(); ++i ){
        for( unsigned t = 0; t < model.getWidth(); ++t ){
            // todo vykreslit element
        }
    }
}
void View::clearTable() {}