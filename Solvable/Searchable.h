//
// Created by ariel on 1/11/19.
//

#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H

#include "../Utils/State.h"
#include "../SearchSolution.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template<class T>
class Searchable {

public:
    virtual ~Searchable() {}

    virtual void initialize(const vector<string> &details) = 0;
    virtual void setStartingPos(const string &info) = 0;
    virtual void setFinishPos(const string &info) = 0;
    virtual void setStructure(const vector<string> &details) = 0;

    virtual State<T> *getInitialState() const = 0;
    virtual State<T> *getGoalState() const = 0;
    virtual vector<State<T> *> getAllPossibleStates(State<T> *n) const = 0;
    virtual string toString() = 0;
};


#endif //EX4_SEARCHABLE_H
