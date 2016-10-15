//
//  Params.cpp
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 5/28/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#include "Params.h"
#include <fstream>
#include <iostream>
#include <algorithm>

const char Params::separatorChar =
#ifdef _WIN32
'\\';
#else
'/';
#endif


Params::Params(std::string fileName) {
    std::ifstream infile;
    try {
		//infile.exceptions(std::ios::failbit | std::ios::badbit);
        infile.open(fileName);
        std::string line;
		while (std::getline(infile, line)) {
            if (line.empty())
                continue;
            std::transform(line.begin(), line.end(), line.begin(), ::toupper);
            size_t equalPos = line.find('=');
            map[line.substr(0, equalPos)] = line.substr(equalPos+1);
        }
        infile.close();
    }
    catch (std::exception e) {
        std::cerr << "Problem reading " << fileName << std::endl;
        infile.close();
        std::exit(EXIT_FAILURE);
    }
}

bool Params::isDefined(const std::string &key) const {
    return map.find(key) != map.end();
}

bool Params::boolValue(const std::string &key) const {
    return map.find(key)->second == "TRUE";
}

std::string Params::stringValue(const std::string &key) const {
    return map.find(key)->second;
}

int Params::intValue(const std::string &key) const {
    return std::stoi(map.find(key)->second);
}

char Params::charValue(const std::string &key) const {
    return map.find(key)->second[0];
}