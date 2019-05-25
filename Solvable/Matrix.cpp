//
// Created by ariel on 1/11/19.
//

#include "Matrix.h"

Matrix::Matrix() {}

Matrix::~Matrix() {
    for (int i = 0; i < m_numRows * m_numCols; i++) {
        delete m_matrix[i];
    }
    delete m_matrix;
}

void Matrix::initialize(const vector<string> &details) {
    int rows = details.size() - 2;
    int cols = this->getNumColsFromStr(details.at(0));

    this->setSizes(rows, cols);
    this->setStartingPos(details.at(details.size() - 2));
    this->setFinishPos(details.at(details.size() - 1));
    this->setStructure(details);
}

int Matrix::getNumColsFromStr(const string &line) const {
    string temp = line;
    int count = 0;
    // Every two numbers in the matrix are separated by a comma
    while (!temp.empty()) {
        if (temp[0] == ',') {
            count++;
        }
        temp = temp.substr(1);
    }
    return (count + 1);
}

void Matrix::setStartingPos(const string &info) {
    // 0,0
    m_startR = stoi(info.substr(0, info.find(',')));
    m_startC = stoi(info.substr(info.find(',') + 1));
}

void Matrix::setFinishPos(const string &info) {
    // 36,36
    m_goalR = stoi(info.substr(0, info.find(',')));
    m_goalC = stoi(info.substr(info.find(',') + 1));
}

void Matrix::setStructure(const vector<string> &details) {
    // Creating one big continuous block of memory
    m_matrix = new State<Position> *[m_numRows * m_numCols];

    // Each cell in the matrix is a pointer to a State object
    for (int i = 0; i < m_numRows; i++) {
        for (int j = 0; j < m_numCols; j++) {
            m_matrix[i * m_numCols + j] = new State<Position>(new Position(i, j));
        }
    }

    int vecind = 0;
    // Setting the costs of all the cells in the matrix
    for (int i = 0; i < m_numRows; i++) {
        string curr = details.at(vecind);
        for (int j = 0; j < m_numCols; j++) {
            unsigned long index = curr.find(',');
            if (index > curr.length()) {
                index = curr.length();
            }
            double cost = stod(curr.substr(0, index));
            m_matrix[i * m_numCols + j]->setCost(cost);
            // If we reached the end of the string
            if (index == curr.length()) {
                break;
            }
            // Ignoring spaces
            if (curr[index + 1] == ' ') {
                curr = curr.substr(index + 2);
            } else {
                curr = curr.substr(index + 1);
            }
        }
        vecind++;
    }
}

State<Position> *Matrix::getInitialState() const {
    return m_matrix[m_startR * m_numCols + m_startC];
}

State<Position> *Matrix::getGoalState() const {
    return m_matrix[m_goalR * m_numCols + m_goalC];
}

vector<State<Position> *> Matrix::getAllPossibleStates(State<Position> *n) const {
    vector<State<Position> *> vec;
    Position *pos = n->getState();
    int currRow = pos->getX();
    int currCol = pos->getY();

    // Up neighbor
    if (currRow > 0) {
        vec.push_back(m_matrix[(currRow - 1) * m_numCols + currCol]);
    }
    // Down neighbor
    if (currRow < m_numRows-1) {
        vec.push_back(m_matrix[(currRow + 1) * m_numCols + currCol]);
    }
    // Left neighbor
    if (currCol > 0) {
        vec.push_back(m_matrix[currRow * m_numCols + (currCol - 1)]);
    }
    // Right neighbor
    if (currCol < m_numCols-1) {
        vec.push_back(m_matrix[currRow * m_numCols + (currCol + 1)]);
    }
    return vec;
}

void Matrix::setSizes(int rows, int cols) {
    m_numRows = rows;
    m_numCols = cols;
}

string Matrix::toString() {
    string final;
    for (int i = 0; i < m_numCols * m_numRows; i++) {
        final += to_string((int)m_matrix[i]->getCost()) + ",";
    }
    // Removing the last comma and adding a separator
    final.pop_back();
    final += "@";

    // Getting the entry and exit points
    final += to_string(m_startR) + "," + to_string(m_startC);
    final += "@";
    final += to_string(m_goalR) + "," + to_string(m_goalC);
    return final;
}

//int Matrix::getRows() const {
//    return m_numRows;
//}
//
//int Matrix::getCols() const {
//    return m_numCols;
//}