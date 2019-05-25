//
// Created by ariel on 1/12/19.
//

#ifndef EX4_SearchSOLUTION_H
#define EX4_SearchSOLUTION_H

#include "Utils/State.h"
#include "Utils/Position.h"
#include <string>
#include <vector>

using namespace std;

class SearchSolution {
    string m_path;

private:
    string getDirection(Position* prev, Position* post) const;
public:
    SearchSolution();
    ~SearchSolution();
    void setSolution(vector<State<Position>*> &nodes);
    string getSolution() const;
};

#endif //EX4_SearchSOLUTION_H
