//
// Created by daniel on 1/8/19.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H


#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;


template<class P, class S>

class CacheManager {

public:
    virtual ~CacheManager() {}

    virtual bool isSolutionExists(P *problem) = 0;

    virtual string getSolution(string &problem) = 0;

    virtual void saveSolution(P *problem, S *solution) = 0;

    virtual void loadFromFile() = 0;

    virtual void writeToFile(P *problem, S *solution) = 0;


};


#endif //EX4_CACHEMANAGER_H