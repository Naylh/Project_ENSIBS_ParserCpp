cmake_minimum_required(VERSION 3.22)
project(projetcpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(projetcpp main.cpp sources/utils/node/Position.cpp sources/utils/node/Node.cpp sources/parsing/Parser.cpp sources/utils/analyze/Analyzer.cpp test/TestNode.cpp test/TestParser.cpp test/TestDijkstra.cpp)