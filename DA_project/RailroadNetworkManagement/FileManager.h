#ifndef PROJECT_FILEMANAGER_H
#define PROJECT_FILEMANAGER_H

#include <string>
#include <iostream>
#include <fstream>
#include "data_structures/Graph.h"
using namespace std;

class FileManager {
public:
    Graph readStations(string file, Graph g);
    Graph readNetworks(string file, Graph g);
};

#endif
