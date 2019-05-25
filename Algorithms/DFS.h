//
// Created by daniel on 1/13/19.
//

#ifndef EX4_DFS_H
#define EX4_DFS_H

#include <stack>
#include "Searcher.h"
#include "../Solvable/Searchable.h"

using namespace std;

template<class T>
class DFS : public Searcher<T> {
public:
    DFS();

    virtual vector<State<T> *> search(Searchable<T> *searchable);

    virtual ~DFS();
};

template<class T>
DFS<T>::~DFS() {
}

template<class T>
DFS<T>::DFS() {}

template<class T>
vector<State<T> *> DFS<T>::search(Searchable<T> *searchable) {
//    State<T> *cameFrom;
    vector<State<T> *> adjacentStates;
    //init the start and goal state
    stack<State<T> *> stack;
    State<T> *startState = searchable->getInitialState();
    State<T> *goalState = searchable->getGoalState();
    startState->setCameFrom(nullptr);
    this->m_numNodesEvaluated++;
    //push the first node/state
    stack.push(startState);

    while (!stack.empty()) {

        //init the top state to start, and pop this state out of the stack
        startState = stack.top();
        stack.pop();

        //if got to the the goal state-break
        if (startState == goalState) {
            break;
        }

        adjacentStates = searchable->getAllPossibleStates(startState);
        for (auto iter:adjacentStates) {

            State<T> *temp = iter;
            if (temp->getCost() == -1) {
                continue;
            }
            if (!temp->isVisited()) {
                temp->setCameFrom(startState);
                this->m_numNodesEvaluated++;
                stack.push(temp);
            }
        }
    }
    return this->backtrace(searchable->getGoalState());
}


#endif //EX4_DFS_H
