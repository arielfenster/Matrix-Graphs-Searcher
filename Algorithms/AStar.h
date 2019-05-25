//
// Created by ariel on 1/14/19.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include "BestFirstSearch.h"
#include "../Utils/Heuristic.h"
#include "../Utils/State.h"

template<class T>
class AStar : public BestFirstSearch<T> {
    Heuristic<T> *m_heuristic;

protected:
    virtual double costBetweenNodes(State<T> *start, State<T> *end) const {
        if (start == end) {
            return m_heuristic->evaluateFromNode(end);
        }
//        return start->getCost() + end->getOriginalCost() + m_heuristic->evaluateFromNode(end);
        return start->getCost() + end->getOriginalCost();
    }

public:
    explicit AStar(Heuristic<T> *h) : m_heuristic(h) {}

    virtual ~AStar() {}

    virtual vector<State<T> *> search(Searchable<T> *searchable) {
        m_heuristic->setGoal(searchable->getGoalState());
        return BestFirstSearch<T>::search(searchable);
    }
};


#endif //EX4_ASTAR_H
