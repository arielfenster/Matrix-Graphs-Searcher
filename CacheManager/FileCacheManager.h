//
// Created by daniel on 1/14/19.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

#include "CacheManager.h"


template<class P, class S>
class FileCacheManager : public CacheManager<P, S> {
    fstream m_stream;
    unordered_map<P, S> m_hash_map;
    string m_file_name;

public:


    FileCacheManager(string &fileName) {
        this->m_file_name = fileName;
        if (!fileExists(m_file_name)) {
            this->m_stream.open(m_file_name, ios::out);
            this->m_stream.close();
        }
        loadFromFile();
    }

    ~FileCacheManager() override;

    bool isSolutionExists(P *problem) override;

    string getSolution(string &problem) override;

    void saveSolution(P *problem, S *solution) override;

    void loadFromFile() override;

    void writeToFile(P *problem, S *solution) override;

    bool fileExists(string &filename);


};


template<class P, class S>
FileCacheManager<P, S>::~FileCacheManager() {}

template<class P, class S>
bool FileCacheManager<P, S>::isSolutionExists(P *problem) {
    if (m_hash_map.empty()) {
        this->loadFromFile();
    }
    if (m_hash_map.count(*problem) != 0) {
        return true;
    } else {
        return false;
    }
}

template<class P, class S>
string FileCacheManager<P, S>::getSolution(string &problem) {
    if (isSolutionExists(&problem)) {
        return (m_hash_map.find(problem))->second;
    } else {
        return "";
    }
}

template<class P, class S>
void FileCacheManager<P, S>::saveSolution(P *problem, S *solution) {
    m_hash_map.insert(pair<P, S>(*problem, *solution));
    writeToFile(problem, solution);
}


template<class P, class S>
void FileCacheManager<P, S>::loadFromFile() {
    this->m_stream.open(this->m_file_name);
    if (m_stream.eof()) {
        m_stream.close();
        return;
    }

    string line;
    while (getline(m_stream, line)) {
        unsigned long dollar = line.find('$');
        unsigned long umper = line.find('&');
        if (dollar > line.size() || umper > line.size()) {
            break;
        }
        string prob = line.substr(0, dollar);
        line = line.substr(dollar+1);
        string sol = line.substr(0, line.size()-1);
        this->m_hash_map[prob] = sol;
    }
    this->m_stream.close();
}

template<class P, class S>
void FileCacheManager<P, S>::writeToFile(P *problem, S *solution) {
    this->m_stream.open(this->m_file_name, ios::app);
    this->m_stream << (*problem) << "$" << (*solution) << "&" << endl;
    this->m_stream.close();
}

template<class P, class S>
bool FileCacheManager<P, S>::fileExists(string &filename) {
    ifstream isfile(filename);
    return (bool) isfile;
}

#endif //EX4_FILECACHEMANAGER_H
