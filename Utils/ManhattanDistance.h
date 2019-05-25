//
// Created by ariel on 1/14/19.
//

#ifndef EX4_MANHATTANDISTANCE_H
#define EX4_MANHATTANDISTANCE_H

#include "Heuristic.h"
#include "Position.h"
#include <cmath>

class ManhattanDistance : public Heuristic<Position> {
    State<Position>* m_goal;

public:
    ManhattanDistance() : m_goal(nullptr) {}
    virtual ~ManhattanDistance() {}

    virtual void setGoal(State<Position>* goal) {
        m_goal = goal;
    }
    
    virtual double evaluateFromNode(State<Position>* current) {
        double val;
        val = abs(m_goal->getState()->getX() - current->getState()->getX());
        val += abs(m_goal->getState()->getY() - current->getState()->getY());
        return val;
    }
};
#endif //EX4_MANHATTANDISTANCE_H
