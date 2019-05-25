//
// Created by ariel on 1/12/19.
//

#include "SearchSolution.h"

#define UP "UP"
#define DOWN "DOWN"
#define RIGHT "RIGHT"
#define LEFT "LEFT"

SearchSolution::SearchSolution() {}

SearchSolution::~SearchSolution() {}

/**
 * Receives a list of nodes the searching algorithm traversed to, in order from start to finish, and sets the member
 * to be the string representation of the moves the algorithm performed.
 * @param list - list of nodes the searching algorithm traversed to
 */
void SearchSolution::setSolution(vector<State<Position> *> &nodes) {
    if (nodes.empty()) {
        m_path = "";
        return;
    }
    for (int i = 1; i < nodes.size(); i++) {
        auto prevPos = nodes.at(i - 1)->getState();
        auto postPos = nodes.at(i)->getState();
        m_path += this->getDirection(prevPos, postPos) + ", ";
    }
//    m_path.erase(m_path.size()-2,2);
    m_path.erase(m_path.size() - 2, m_path.size());
}

string SearchSolution::getDirection(Position *prev, Position *post) const {
    if (post->getX() > prev->getX()) {
        return DOWN;
    }
    if (post->getX() < prev->getX()) {
        return UP;
    }
    if (post->getY() > prev->getY()) {
        return RIGHT;
    }
    return LEFT;
}

string SearchSolution::getSolution() const {
    return m_path;
}

