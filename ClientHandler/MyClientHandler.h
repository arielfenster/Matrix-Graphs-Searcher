//
// Created by daniel on 1/8/19.
//

#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H


#include <vector>
#include <sstream>
#include "../ClientHandler/ClientHandler.h"
#include "../Algorithms/Searcher.h"
#include "../CacheManager/CacheManager.h"
#include <strings.h>
#include <unistd.h>
#include <cstring>
#include "../ClientHandler/MyClientHandler.h"
#include "../Solvable/Matrix.h"
#include "../Solvable/Searchable.h"
#include "../CacheManager/MatrixFileCacheManager.h"

#define BUFFER_SIZE 256

template<class T>
class MyClientHandler : public ClientHandler {
    Searcher<T> *m_searcher;
    CacheManager<string, string> *_manager;
    bool toStop;

public:
    MyClientHandler(Searcher<T> *searcher, CacheManager<string, string> *manager);

    virtual ~MyClientHandler() {}

    bool getOut(const string &line);

    void handleClient(int socketId) override;

    vector<string> readFromSocket(int socketId);
};

template<class T>
MyClientHandler<T>::MyClientHandler(Searcher<T> *searcher, CacheManager<string, string> *manager) {
    this->_manager = manager;
    this->m_searcher = searcher;
    this->toStop = true;
}

template<class T>
void MyClientHandler<T>::handleClient(int socketId) {
    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);
    vector<string> vec;
    while (this->toStop) {
        vec = readFromSocket(socketId);
    }
    this->toStop = true;
    Searchable<T> *matrix = new Matrix();
    matrix->initialize(vec);
    string matString = matrix->toString();

    string solution;

    if (_manager->isSolutionExists(&matString)) {
        solution = _manager->getSolution(matString);
    } else {
        vector<State<T> *> nodes = m_searcher->search(matrix);
        SearchSolution *sv = new SearchSolution();
        sv->setSolution(nodes);
        solution = sv->getSolution();
        _manager->saveSolution(&matString, &solution);
        delete sv;
    }
    this->copySolToBuffer(solution, buffer);
    write(socketId, buffer, solution.size());
    write(socketId, "\n", 1);
    bzero(buffer, BUFFER_SIZE);
}

template<class T>
bool MyClientHandler<T>::getOut(const string &line) {
    if (line.substr(0).find("end") < line.size()) {
        this->toStop = false;
        return true;

    } else {
        return false;
    }
}

template<class T>
vector<string> MyClientHandler<T>::readFromSocket(int socketId) {
    vector<string> v;
    std::string lineData;
    std::stringstream ss;
    char buffer[256];
    while (true) {
        bzero(buffer, 256);
        read(socketId, buffer, 255);
        ss << buffer;
        if (this->getOut(ss.str())) {
            break;
        }
    }
    while (std::getline(ss,lineData)) {
        v.push_back(lineData);
    }
    v.pop_back();
    return v;
}


#endif //EX4_MYCLIENTHANDLER_H