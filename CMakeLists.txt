cmake_minimum_required(VERSION 3.13)
project(ex4)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(ex4 main.cpp Algorithms/AStar.h Communication/Server.h CacheManager/CacheManager.h
        CacheManager/MatrixFileCacheManager.cpp CacheManager/MatrixFileCacheManager.h
        ClientHandler/ClientHandler.h Communication/MySerialServer.cpp Communication/MySerialServer.h
        ClientHandler/MyClientHandler.h Solvable/StringReverser.h Algorithms/Solver.h Utils/State.h
        Utils/Position.h Solvable/Matrix.cpp Solvable/Matrix.h Solvable/Searchable.h SearchSolution.cpp SearchSolution.h
        Algorithms/BFS.h Algorithms/BFS.cpp Algorithms/DFS.h Algorithms/BestFirstSearch.h Algorithms/Searcher.h Utils/CostComparator.h
        CacheManager/FileCacheManager.h Communication/MyParallelServer.cpp Communication/MyParallelServer.h
        Utils/Heuristic.h Utils/ManhattanDistance.h Solvable/TestMatrices.h)