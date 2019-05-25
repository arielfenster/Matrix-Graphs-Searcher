//
// Created by daniel on 1/8/19.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H


#include <fstream>
#include <unordered_map>
#include "CacheManager.h"

//
template<class P, class S>
class MatrixFileCacheManager : public CacheManager<P,S> {

    fstream m_stream;
    unordered_map<P, S> m_hash_map;
    string m_file_name;

public:

    MatrixFileCacheManager(string & fileName){

        this->m_file_name = fileName;
        if (!fileExists(m_file_name)) {
            this->m_stream.open(m_file_name, ios::out);
            this->m_stream.close();
        }
        loadFromFile();
    }

    ~MatrixFileCacheManager() override;

    bool isSolutionExists(P *problem) override;

    string getSolution(string &problem) override;

    void saveSolution(P *problem, S *solution) override;

    void loadFromFile() override;

    void writeToFile(P *problem, S *solution) override;

    bool fileExists(string & fileName);


};

#endif //EX4_FILECACHEMANAGER_H