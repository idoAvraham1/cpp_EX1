cmake_minimum_required(VERSION 3.27)
project(cpp_ex1)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_ex1 main.cpp
        Graph.cpp
        Graph.hpp
        GraphProperties.hpp
        Algorithms.hpp
        Algorithms.cpp
        ShortestPath.cpp
        ShortestPath.hpp
        IsBipartite.cpp
        IsBipartite.hpp
        DetectCycle.cpp
        DetectCycle.hpp
        IsConnected.cpp
        IsConnected.hpp
        doctest.h
        Test.cpp
        TestCounter.cpp
        DetectNegativeCycle.cpp
        DetectNegativeCycle.hpp
        DetectNegativeCycle.hpp
)
