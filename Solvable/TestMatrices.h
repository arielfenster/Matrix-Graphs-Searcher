//
// Created by ariel on 16/01/19.
//

#ifndef EX4_TESTMATRICES_H
#define EX4_TESTMATRICES_H
#include <string>
#include <queue>
#include <iostream>
#include <fstream>
#include "Matrix.h"

using namespace std;

class TestMatrices {

    queue<string> readMatrix(string &fileName) {
        ifstream stream(fileName);
        queue<string> vec;
        string line;

        while (getline(stream,line)) {
            if (!line.empty()) {
                vec.push(line);
            }
        }
        stream.close();
        return vec;
    }
    void test() {
        string file = "graphs.txt";
        queue<string> q = this->readMatrix(file);
        Matrix** arr = new Matrix*[10];
        ofstream outstream("solution.txt");

        for (int i=0;i<10;i++) {
            arr[i] = new Matrix();
        };
        
        
        
        outstream.close();
    }
};


#endif //EX4_TESTMATRICES_H
