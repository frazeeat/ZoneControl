//
//  BoardGameMove.cpp
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 6/7/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#include "BoardGameMove.h"
#include <sstream>
#include <iterator>

BoardGameMove::BoardGameMove() {
    coordinates = {0, 0};
}

BoardGameMove::BoardGameMove(int numcoordinates) {
    coordinates = std::vector<int>(2*numcoordinates, 0);
}

BoardGameMove::BoardGameMove(std::vector<int> cdnts) {
    coordinates = cdnts;
}

BoardGameMove::BoardGameMove(std::string s) {
    parseMove(s);
}

int BoardGameMove::getRowI(int i) const {
    return coordinates[i*2];
}

int BoardGameMove::getColI(int i) const {
    return coordinates[i*2 + 1];
}

void BoardGameMove::setRowI(int i, int row) {
    coordinates[i*2] = row;
}

void BoardGameMove::setColI(int i, int col) {
    coordinates[i*2 + 1] = col;
}

int BoardGameMove::getNumCoordinates() {
    return static_cast<int>(coordinates.size()/2);
}

std::string BoardGameMove::toString() const {
    std::ostringstream oss;
    std::copy(coordinates.begin(), coordinates.end(),
              std::ostream_iterator<int>(oss, " "));
    std::string mvStr = oss.str();
    return mvStr.substr(0, mvStr.length()-1);
}

void BoardGameMove::parseMove(const std::string s) {
    std::istringstream iss(s);
    std::copy(std::istream_iterator<int>(iss), std::istream_iterator<int>(),
              coordinates.begin());
}