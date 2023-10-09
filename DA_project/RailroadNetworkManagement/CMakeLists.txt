cmake_minimum_required(VERSION 3.23)
project(Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project main.cpp
        Station.cpp
        Station.h
        Network.cpp
        Network.h
        data_structures/Graph.cpp
        data_structures/Graph.h
        data_structures/Heap.cpp
        data_structures/Heap.h
        data_structures/UFDS.cpp
        data_structures/UFDS.cpp
        data_structures/VertexEdge.cpp
        data_structures/VertexEdge.h
        FileManager.cpp
        FileManager.h
        Files/stations.csv
        Files/network.csv
        Menu.cpp
        Menu.h
        Algorithms.cpp
        Algorithms.h)

