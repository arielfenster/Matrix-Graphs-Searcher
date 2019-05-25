//
// Created by ariel on 1/14/19.
//

#ifndef EX4_HEURISTIC_H
#define EX4_HEURISTIC_H

#include "State.h"

template<class T>
class Heuristic {

public:
    virtual ~Heuristic() {}
    virtual void setGoal(State<T> *goal) = 0;
    virtual double evaluateFromNode(State<T> *current) = 0;
};

#endif //EX4_HEURISTIC_H
