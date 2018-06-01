//
// Created by julinka on 2.5.18.
//


#include "Model.h"

Model *Model::instance = nullptr;

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
    for (unsigned i = 0; i < height; ++i)
        spreadSheet[i].resize(width);
    for (unsigned i = 0; i < height; ++i)
        for (unsigned j = 0; j < width; ++j)
            spreadSheet[i][j] = nullptr;

    resized = false;
}

Model::~Model() {
    for (unsigned i = 0; i < getHeight(); ++i) {
        for (unsigned t = 0; t < width; ++t)
            if (spreadSheet[i][t])
                delete spreadSheet[i][t];
    }
}


const Cell *Model::getElement(const int &height, const int &width) const {
    return spreadSheet[height - 1][width];

}

Model *Model::getInstance() {
    if (instance == 0) {
        instance = new Model();
    }

    return instance;
}

void Model::setValue(const int &yCoor, const int &xCoor, const Cell *cell) {
    if(spreadSheet[yCoor][xCoor])
        delete spreadSheet[yCoor][xCoor];
    switch (cell->getType()) {
        case CellType::BOOLEAN : {
            spreadSheet[yCoor][xCoor] = cell->clone();
            break;
        }
        case CellType::REFERENCE : {
            spreadSheet[yCoor][xCoor] = cell->clone();
            break;
        }
        case CellType::NUMBER : {
            spreadSheet[yCoor][xCoor] = cell->clone();
            break;
        }
        case CellType::TEXT: {
            spreadSheet[yCoor][xCoor] = cell->clone();
            break;
        }
        case CellType::EXPRESSION: {
            spreadSheet[yCoor][xCoor] = cell->clone();
            break;
        }
        case CellType::OPERATION: {
            spreadSheet[yCoor][xCoor] = cell->clone(); // todo class Operation + kopirujici konstruktor
            break;
        }
    }
}

void Model::resizeTable(const int &yCoor, const int &xCoor) {


    for(unsigned i = 0; i < height; ++i ){
        for(int j = xCoor; (unsigned)j < width; ++j){
            if(spreadSheet[i][j])
                delete spreadSheet[i][j];
        }
    }

    for(int i = yCoor; (unsigned)i < height; ++i){
        for(unsigned j = 0; j < width; ++j){
            if(spreadSheet[i][j])
                delete spreadSheet[i][j];
        }
    }

    unsigned previousWidth = width;
    unsigned previousHeight = height;
    height = (unsigned) yCoor;
    width = (unsigned) xCoor;

    spreadSheet.resize((unsigned long) yCoor);
    for (unsigned i = 0; i < height; ++i)
        spreadSheet[i].resize((unsigned long) xCoor);

    for (unsigned i = 0; i < previousHeight; ++i) {
        for (unsigned t = previousWidth; t < width; ++t)
            spreadSheet[i][t] = nullptr;
    }

    for (unsigned i = previousHeight; i < height; ++i){
        for(unsigned j = 0; j < width; ++j){
            spreadSheet[i][j] = nullptr;
        }
    }
    resized = true;
}

void Model::deleteValue(const int &yCoord, const int &xCoor) {
    if (spreadSheet[yCoord][xCoor]) {
        delete spreadSheet[yCoord][xCoor];
        spreadSheet[yCoord][xCoor] = nullptr;
    } else {
        throw "This Cell is empty.\n";
    }

}

bool Model::wasResized() const {
    if(resized)
        return true;
    return false;
}

