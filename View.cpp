//
// Created by julinka on 2.5.18.
//
#include "View.h"

void View::Refresh() {}

void View::createTable()( const Model & model ) {
    for( unsigned i = 0; i < model.getHeight(); ++i ){
        for( unsigned t = 0; t < model.getWidth(); ++t ){
            // todo vykreslit element
        }
    }
}
void View::clearTable() {}