//
// Created by daniel on 1/8/19.
//

#include "MatrixFileCacheManager.h"


template<class P, class S>
MatrixFileCacheManager<P, S>::~MatrixFileCacheManager() {
}

template<class P, class S>
bool MatrixFileCacheManager<P, S>::isSolutionExists(P *problem) {
    if (m_hash_map.count(*problem) != 0) {
        return true;
    } else {
        return false;
    }
}

template<class P, class S>
string MatrixFileCacheManager<P, S>::getSolution(string &problem) {
    if (isSolutionExists(&problem)) {
        return (m_hash_map.find(problem))->first;
    } else {
        return "";
    }
}

template<class P, class S>
void MatrixFileCacheManager<P, S>::saveSolution(P *problem, S *solution) {
    m_hash_map.insert(pair<P, S>(*problem, *solution));
    writeToFile(problem, solution);
}

template<class P, class S>
void MatrixFileCacheManager<P, S>::loadFromFile() {
    string prob = "";
    string solution = "";
    string line;
    this->m_stream.open(this->m_file_name, ios::app);
    if (this->m_stream.eof()) {
        throw invalid_argument("the file is empty");
    }
    size_t position;
    bool problemFound = false;
    while (getline(this->m_stream, line)) {
        if (!problemFound) {
            prob += line;
            position = line.find("end");
            if (position != string::npos)
                problemFound = true;
        } else {
            position = line.find("&");
            if (position != string::npos) {
                this->m_hash_map[prob] = solution;
                problemFound = false;
            } else {
                solution += line;
            }
        }
    }
    this->m_stream.close();
}

template<class P, class S>
void MatrixFileCacheManager<P, S>::writeToFile(P *problem, S *solution) {

    this->m_stream.open(this->_fileName, ios::app);
    this->m_stream.app(problem);
    this->m_stream.app(solution);
    this->m_stream.app("&");
    this->m_stream.close();

}

template<class P, class S>
bool MatrixFileCacheManager<P, S>::fileExists(string &fileName) {
    ifstream isfile(fileName);
    return (bool) isfile;
}

