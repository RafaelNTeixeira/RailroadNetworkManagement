#ifndef PROJECT_MENU_H
#define PROJECT_MENU_H

#include <string>
#include "data_structures/Graph.h"
#include "FileManager.h"

using namespace std;

class Menu {
public:
    int createMenu();
    Graph createGraph(string file1, string file2, Graph g, FileManager f);
    int checkValidInput();
    void printOptions();
    bool checkYesOrNo();
    void showheader();
    void showCredits();
    void printPath(vector<pair<pair<int, int>, vector<string>>> paths, string source, string target);

    void drawTrain();
};


#endif
