//
// Created by daniel on 1/12/19.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H


#include "Searcher.h"
#include "../Utils/State.h"
#include "../Solvable/Searchable.h"
#include <queue>

using namespace std;

template<class T>
class BFS : public Searcher<T> {

public:
    BFS() {}

    vector<State<T> *> search(Searchable<T> *searchable) override;

    virtual ~BFS() {}
};

template<class T>
vector<State<T> *> BFS<T>::search(Searchable<T> *searchable) {
    vector<State<T> *> adjacentNodes;
    State<T> *node;
    node = searchable->getInitialState();
    //create a queue
    queue<State<T> *> queue;
    //get the initial state
    queue.push(node);
    node->setCameFrom(nullptr);
    this->m_numNodesEvaluated++;

    while (!queue.empty()) {
        node = queue.front();
        queue.pop();

        if (searchable->getGoalState() == node) {
            break;
        }
        adjacentNodes = searchable->getAllPossibleStates(node);
        //check if we visited adjacent nodes
        for (auto iter: adjacentNodes) {
            State<T> *n = iter;
            if (node->getCost() < 0) {
                continue;
            }
            if (!n->isVisited()) {
                n->setCameFrom(node);
                this->m_numNodesEvaluated++;
                //add to the queue
                queue.push(n);
            }
        }
    }
    return this->backtrace(searchable->getGoalState());
}

#endif //EX4_BFS_H
