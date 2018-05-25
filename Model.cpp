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
    for (int i = 0; i < height; ++i)
        spreadSheet[i].resize(width);
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            spreadSheet[i][j] = nullptr;
}

Model::~Model() {
    for (int i = 0; i < getHeight(); ++i) {
        for (int t = 0; t < width; ++t)
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


    for(int i = 0; i < height; ++i ){
        for(int j = xCoor; j < width; ++j){
            if(spreadSheet[i][j])
                delete spreadSheet[i][j];
        }
    }

    for(int i = yCoor; i < height; ++i){
        for(int j = 0; j < width; ++j){
            if(spreadSheet[i][j])
                delete spreadSheet[i][j];
        }
    }

    int previousWidth = width;
    int previousHeight = height;
    height = (unsigned) yCoor;
    width = (unsigned) xCoor;

    spreadSheet.resize((unsigned long) yCoor);
    for (int i = 0; i < height; ++i)
        spreadSheet[i].resize((unsigned long) xCoor);

    for (int i = 0; i < previousHeight; ++i) {
        for (int t = previousWidth; t < width; ++t)
            spreadSheet[i][t] = nullptr;
    }

    for (int i = previousHeight; i < height; ++i){
        for(int j = 0; j < width; ++j){
            spreadSheet[i][j] = nullptr;
        }
    }
}

void Model::deleteValue(const int &yCoord, const int &xCoor) {
    if (spreadSheet[yCoord][xCoor]) {
        delete spreadSheet[yCoord][xCoor];
        spreadSheet[yCoord][xCoor] = nullptr;
    } else {
        throw "This Cell is empty.\n";
    }

}

