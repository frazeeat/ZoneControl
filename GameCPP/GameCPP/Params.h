//
//  Params.h
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 5/28/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#ifndef __CSE486AIProject__Params__
#define __CSE486AIProject__Params__

#include <stdio.h>
#include <string>
#include <unordered_map>

class Params {
public:
    static const char separatorChar;
    
    Params(std::string filename);
    
    bool isDefined(const std::string &key) const;
    bool boolValue(const std::string &key) const;
    std::string stringValue(const std::string &key) const;
    int intValue(const std::string &key) const;
    char charValue(const std::string &key) const;
    
private:
    
    std::unordered_map<std::string, std::string> map;
    
};



#endif /* defined(__CSE486AIProject__Params__) */
