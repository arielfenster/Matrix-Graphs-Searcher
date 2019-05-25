//
// Created by ariel on 1/10/19.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H


template<class Problem, class Solution>
class Solver {
public:
    virtual ~Solver() {}
    virtual Solution* solve(Problem* problem) = 0;
};

#endif //EX4_SOLVER_H
