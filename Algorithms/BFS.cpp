//
// Created by daniel on 1/12/19.
//

#include <queue>
#include <map>
#include "BFS.h"
#include "../Solvable/Matrix.h"
#include "../Utils/State.h"


template<class T>
vector<State<T>*> BFS<T>::search(Searchable<State<T> *> *problem) {
    vector<State<T> *> adjacentNodes;
    //create a queue
    queue<State<T> *> queue;
    //get the the initial state
    State<T> *state;
    state = problem->getInitialState();
    queue.push(state);

    while (!queue.empty()) {
        queue.pop();
        this->m_numNodesEvaluated++;

        if (problem->getInitialState() == state) {
            break;
        }
        adjacentNodes = problem->getAllPossibleStates(state);
        //check if we visited adjacent nodes
        for (auto iter: adjacentNodes) {
            State<T> *node = iter;
            if (!node->getIsVisited()) {
                node->setCameFrom(iter);
                //add to the queue
                queue.push(node);

            }
        }
    }
    State<T> *goalNode = problem->getGoalState();
    vector<State<T> *> nodesToReturn = this->backtrace(goalNode);
    return nodesToReturn;



}
