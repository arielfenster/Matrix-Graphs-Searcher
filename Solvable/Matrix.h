//
// Created by ariel on 1/11/19.
//

#ifndef EX4_MATRIX_H
#define EX4_MATRIX_H

#include "Searchable.h"
#include "../Utils/Position.h"
#include "../Utils/State.h"
#include <string>
#include <vector>

using namespace std;

class Matrix : public Searchable<Position> {
    int m_numRows, m_numCols;
    int m_startR, m_startC;
    int m_goalR, m_goalC;
    State<Position> **m_matrix;

    int getNumColsFromStr(const string &line) const;

public:
    Matrix();
    virtual ~Matrix();

    virtual void initialize(const vector<string>& info);

    virtual void setStartingPos(const string &info);
    virtual void setFinishPos(const string& info);
    virtual void setStructure(const vector<string>& details);

    virtual State<Position> *getInitialState() const;
    virtual State<Position> *getGoalState() const;
    virtual vector<State<Position> *> getAllPossibleStates(State<Position> *n) const;

    void setSizes(int rows, int cols);
    virtual string toString();
//    int getRows() const;
//    int getCols() const;
};


#endif //EX4_MATRIX_H
