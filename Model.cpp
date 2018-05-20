//
// Created by julinka on 2.5.18.
//
#include "Model.h"

Model * Model::instance = 0;

unsigned Model::getHeight() const {
    return height;
}

unsigned Model::getWidth() const {
    return width;
}

Model::Model() {
    width = 10;
    height = 25;
    spreadSheet.resize(height);
    for( int i = 0; i < height; ++i )
        spreadSheet[i].resize(width);
}


const Cell & Model::getElement(const int & height, const int & width) const{
    return spreadSheet[height - 1][width];

}

Model *Model::getInstance() {
    if (instance == 0)
    {
        instance = new Model();
    }

    return instance;
}

void Model::setWidth(unsigned int width) {
    Model::width = width;
}

void Model::setHeight(unsigned int height) {
    Model::height = height;
}

void Model::setValue(const int & xCoor, const int & yCoor, const Cell & cell){
   // spreadSheet[yCoor][xCoor] = cell;
}

void Model::resizeTable() {
   int width = this->width;

    spreadSheet.resize(height);
    for( int i = 0; i < height; ++i )
        spreadSheet[i].resize(width);
}


