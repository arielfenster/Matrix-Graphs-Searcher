//
// Created by daniel on 1/14/19.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H


#include "ClientHandler.h"
#include "../Algorithms/Solver.h"
#include "../CacheManager/CacheManager.h"

#define BUFFER_SIZE 256


template<class P, class S>
class MyTestClientHandler : public ClientHandler {
private:
    Solver<P, S> *_solver;
    CacheManager<P, S> *_manager;

public:

    MyTestClientHandler(Solver<P, S> *solver, CacheManager<P, S> *manager);

    virtual ~MyTestClientHandler() {}

    void handleClient(int socketId, bool *terminateSocket) override;

    bool endExists(string &line);

    string readFromSocket(int socketId, char *buffer, int size);

};

template<class P, class S>
MyTestClientHandler<P, S>::MyTestClientHandler(Solver<P, S> *solver, CacheManager<P, S> *manager) {
    _solver = solver;
    _manager = manager;
}

template<class P, class S>
void MyTestClientHandler<P, S>::handleClient(int socketId, bool *terminateSocket) {

    string line = "";
    string solutionFromFile;
    string *solutionFromSolve;

    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);
//    bool shouldStop = true;

    while (true) {
        //read from socket until you you get "end"
        line = readFromSocket(socketId, buffer, BUFFER_SIZE);
        if (endExists(line)) {
            *terminateSocket = true;
            return;
        }

        bzero(buffer, BUFFER_SIZE);
        this->removeStringEnd(line);

        if (_manager->isSolutionExists(&line)) {
            solutionFromFile = _manager->getSolution(line);
            this->copySolToBuffer(solutionFromFile, buffer);
        } else {
            string temp = line;
            solutionFromSolve = _solver->solve(&line);
            _manager->saveSolution(&temp, solutionFromSolve);
            this->copySolToBuffer(*solutionFromSolve, buffer);
        }
        write(socketId, buffer, line.size());
        write(socketId, "\n", 1);

        bzero(buffer, BUFFER_SIZE);
    }
}

template<class P, class S>
bool MyTestClientHandler<P, S>::endExists(string &line) {
    return line.find("end") != string::npos;
}

template<class P, class S>
string MyTestClientHandler<P, S>::readFromSocket(int socketId, char *buffer, int size) {

    string line;
    auto n = read(socketId, buffer, size);
    if (n < 0) {
        cout << strerror(errno);
    }
    line = buffer;
    return line;
}


#endif //EX4_MYTESTCLIENTHANDLER_H
