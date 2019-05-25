#include "Communication/Server.h"
#include "Solvable/Searchable.h"
#include "Solvable/StringReverser.h"
#include "CacheManager/FileCacheManager.h"
#include "ClientHandler/MyTestClientHandler.h"
#include "Communication/MySerialServer.h"
#include "Communication/MyParallelServer.h"
#include <iostream>
#include <chrono>
#include "ClientHandler/MyClientHandler.h"
#include "Algorithms/BestFirstSearch.h"
#include "Algorithms/AStar.h"
#include "Utils/ManhattanDistance.h"
#include "Algorithms/BFS.h"
#include "Algorithms/DFS.h"
#include "Utils/Heuristic.h"
#include <string>
#include <vector>

#define FILENAME "fileCacheManager.txt"

using namespace std;
using namespace server_side;



int main(int argc, char **argv) {
    int port = stoi(argv[1]);
    auto *serv = new MyParallelServer();
    Heuristic<Position>* h = new ManhattanDistance();
    Searcher<Position> *searcher = new AStar<Position>(h);

    string fileName = FILENAME;
    auto *fcm = new FileCacheManager<string, string>(fileName);
    auto *s = new MyClientHandler<Position>(searcher, fcm);
    serv->open(port, s);
    serv->stop(port);
    delete serv;
    delete fcm;
    delete s;

    return 0;
}


