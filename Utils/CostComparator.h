//
// Created by ariel on 1/13/19.
//

#ifndef EX4_COSTCOMPARATOR_H
#define EX4_COSTCOMPARATOR_H

#include "State.h"
#include "Position.h"

template<class T>
class CostComparator {

public:
    bool operator()(const State<T> *s1, const State<T> *s2) const {
        if(s1->getCost() == s2->getCost()){
            Position * p1 = s1->getState();
            Position * p2 = s2->getState();
            if(p1->getX() == p2->getX())
                return p1->getY() < p2->getY();
            return p1->getX() < p2->getX();
        }
        return s1->getCost() < s2->getCost();
    }
};

#endif //EX4_COSTCOMPARATOR_H
