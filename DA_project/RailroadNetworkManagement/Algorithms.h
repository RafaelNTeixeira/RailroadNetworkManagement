#ifndef PROJECT_ALGORITHMS_H
#define PROJECT_ALGORITHMS_H

#include "data_structures/VertexEdge.h"
#include "data_structures/Graph.h"

class Algorithms {
public:
    void augmentFlowAlongPath(Vertex *s, Vertex *t, double f);
    double findMinResidualAlongPath(Vertex *s, Vertex *t);
    bool findAugmentingPath(Graph g, Vertex *s, Vertex *t);
    void testAndVisit(queue< Vertex*> &q, Edge *e, Vertex *w, double residual);
    Graph edmondsKarp(Graph g, string source, string target);

    void largerBudgetsMunicipality(Graph graph, int k);
    void largerBudgetsDistrict(Graph graph, int k);

    int MaximumTrainsSimultaneously(Graph g, string target);

    Graph newGraph(Graph new_graph, string source, string target);
    void mostAffected(Graph g, Graph new_graph, int k);

    void dfs(Graph g, string source, string target, vector<string> &path, vector<pair<pair<int, int>,vector<string>>> &paths, int cost, int curr_cost, int maxFlow);

};


#endif //PROJECT_ALGORITHMS_H
