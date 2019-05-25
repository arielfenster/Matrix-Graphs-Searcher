//
// Created by ariel on 1/11/19.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H

#include <string>


template<class T>
class State {
    T *m_state;
    double m_cost;
    State<T> *m_cameFrom;
    bool m_isVisited;

public:
    explicit State(T *state) {
        m_state = state;
        m_cost = 0;
        m_cameFrom = nullptr;
        m_isVisited = false;
    }

    State(T *state, double cost) {
        m_state = state;
        m_cost = cost;
        m_cameFrom = nullptr;
        m_isVisited = false;
    }

    ~State() {}

    bool operator==(const State<T> *s) const {
        return m_state == s->getState();
    }

    bool operator!=(const State<T> *s) const {
        return !(*this == s);
    }

    State<T> &operator=(const State<T> *s) {
        m_state = s->getState();
        m_cost = s->getCost();
        m_cameFrom = s->getCameFrom();
        m_isVisited = s->isVisited();
        return *this;
    }

    void setCost(double cost) {
        m_cost = cost;
    }

    void setCameFrom(State<T> *s) {
        m_cameFrom = s;
        m_isVisited = true;
    }

    T *getState() const {
        return m_state;
    }

    double getCost() const {
      return m_cost;
    }

    double getOriginalCost() const {
        if (m_cameFrom == nullptr) {
            return m_cost;
        }
        return m_cost - m_cameFrom->getCost();
    }

    State<T> *getCameFrom() const {
        return m_cameFrom;
    }

    bool isVisited() const {
        return m_isVisited;
    }
};


#endif //EX4_STATE_H
