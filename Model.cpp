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

Model::Model(): width(20), height(30) {}

Model::Model(const int &width, const int &height) {

    this->width = width;
    this->height = height;

}
