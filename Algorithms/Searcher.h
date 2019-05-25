//
// Created by ariel on 1/13/19.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include "../Utils/State.h"
#include "../Solvable/Searchable.h"
#include "../SearchSolution.h"

template<class T>
class Searcher {

protected:
    int m_numNodesEvaluated;
    virtual vector<State<T> *> backtrace(State<T> *node);

public:
    Searcher() : m_numNodesEvaluated(0) {}
    virtual ~Searcher() {}

    virtual vector<State<T>*> search(Searchable<T> *searchable) = 0;
    virtual int getNumberOfNodesEvaluated() {
        return m_numNodesEvaluated;
    }
};

template<class T>
vector<State<T> *> Searcher<T>::backtrace(State<T> *node) {
    vector<State<T> *> vec;
    State<T>* temp = node;
    while (temp->getCameFrom() != nullptr) {
        vec.insert(vec.begin(), temp);
        temp = temp->getCameFrom();
    }
    // If no nodes were inserted to the vector because the goal node wasn't reached
    if (vec.empty()) {
        return vec;
    }
    vec.insert(vec.begin(), temp);
    return vec;
}


#endif //EX4_SEARCHER_H
