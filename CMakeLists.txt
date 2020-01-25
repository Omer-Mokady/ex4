cmake_minimum_required(VERSION 3.15)
project(ex4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(ex4 main.cpp Server.h MySerialServer.cpp MySerialServer.h ClientHandler.h MyTestClientHandler.h Solver.h CacheManager.h StringReverser.cpp StringReverser.h State.h MyClientHandler.h Searchable.h MatrixProblem.cpp MatrixProblem.h Searcher.h ObjectAdapter.h BestFirstSearch.h DFSAlgo.h BFSAlgo.h MyParallelServer.h MyParallelServer.cpp AstarNew.h QueueComparator.h)