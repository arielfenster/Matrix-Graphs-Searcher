//
// Created by ariel on 1/10/19.
//

#ifndef EX4_STRINGREVERSER_H
#define EX4_STRINGREVERSER_H

#include "../Algorithms/Solver.h"
#include <string>
#include <algorithm>

using namespace std;

class StringReverser : public Solver<string, string> {

public:
    StringReverser() {}

    ~StringReverser() {}

    string * solve(string * p) override{
        reverse(p->begin(), p->end());
        return p;
    }


};



#endif //EX4_STRINGREVERSER_H
