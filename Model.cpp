//
// Created by julinka on 2.5.18.
//
#include "Model.h"

unsigned Model::getHeight() const {
    return height;
}

unsigned Model::getWidth() const {
    return width;
}

Model::Model(): width(20), height(30) {
    spreadSheet.resize(height);
    for( int i = 0; i < height; ++i )
        spreadSheet[i].resize(width);
//    for( int i = 0; i < height; ++i ){
//        for( int t = 0; t < width; ++t )
//            spreadSheet[i][t] = new Cell;
//    }
}

Model::Model(const int &width, const int &height): width(width), height(height) {
    spreadSheet.resize(height);
    for( int i = 0; i < height; ++i )
        spreadSheet[i].resize(width);

    for( int i = 0; i < height; ++i ){
        for( int t = 0; t < width; ++t )
            spreadSheet[i][t] = nullptr;
    }
}
Model::~Model() {
    for( int i = 0; i < height; ++i ){
        for( int t = 0; t < width; ++t )
            if( spreadSheet[i][t] )
                delete spreadSheet[i][t];
    }
}

const Cell * Model::getElement(const int & height, const int & width) const{
    return spreadSheet[height - 1][width];

}
