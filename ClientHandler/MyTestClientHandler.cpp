//
// Created by daniel on 1/8/19.
//

#include <strings.h>
#include <unistd.h>
#include <cstring>
#include "MyTestClientHandler.h"
#include "Matrix.h"
#include "Searchable.h"
#include "FileCacheManager.h"

#define BUFFER_SIZE 256



/*
 * read from socket
 * if the line has the word "end" - get out
 * else- check if there is solution
 * if there is a solution - write it
 * else- send to solver, get the solution and save in cache - manager, and write( daaa...)
 *
 */
void MyTestClientHandler::handleClient(int socketId) {
    string line;
    string solution;

    char buffer[BUFFER_SIZE];
//    bzero(buffer, BUFFER_SIZE);
    bool shouldStop = false;

    vector<string> vec;
    Searchable<Position> *matrix;

    while (!shouldStop) {
        //read from socket until you you get "end"
        if (getOut(vec)) {
            shouldStop = true;
            break;
        }
        vec = readFromSocket(buffer, BUFFER_SIZE, socketId);
        //convert char* to string
        //  line = createLine(buffer, BUFFER_SIZE);
    }
//    matrix = new Matrix();
//    matrix->initialize(vec);
//
//
//
//    if (_manager->isSolutionExists(matrix)) {
//        solution = _manager->getSolution(matrix);
//        write(socketId, &solution, BUFFER_SIZE);
//        bzero(buffer, BUFFER_SIZE);
//    } else {
//        _manager->saveSolution(matrix);
//        write(socketId, buffer, BUFFER_SIZE);
//        bzero(buffer, BUFFER_SIZE);
//    }
}

string MyTestClientHandler::createLine(char buffer[], int size) {

    string line;
    char *temp;

    for (int i = 0; i < size; i++) {
        if (buffer[i] == ' ') {
            continue;
        }
        if (buffer[i] == '\0' || buffer[i] == '\r' || buffer[i] == '\n') {
            break;
        }

        line += buffer[i];
    }
    return line;

}

bool MyTestClientHandler::getOut(vector<string> &line) {

    for (auto iter: line) {
        if (iter == "end") {
            return true;
        }
    }
    return false;
}

vector<string> MyTestClientHandler::readFromSocket(char *buffer, int size, int socketId) {
    vector<string> v;
    string line;
    bool getOutOfLoop = true;
    while (getOutOfLoop) {
        if (getOut(v)) {
            getOutOfLoop = false;
            break;
        }
        auto n = read(socketId, buffer, size);
        line = createLine(buffer, size);
        v.emplace_back(line);

    }
    return v;
}

MyTestClientHandler::MyTestClientHandler() { }

MyTestClientHandler::~MyTestClientHandler() { }