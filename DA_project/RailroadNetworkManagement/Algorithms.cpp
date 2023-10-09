#include <list>
#include <stack>
#include "Algorithms.h"
#include "data_structures/Graph.h"

/**
 * Atualiza as augmenting paths de um grafo. \n
 * Time Complexity: O(V)
 * @param source Um apontador para um vértice que corresponde à estação inicial.
 * @param target Um apontador para um vértice que corresponde à estação final.
 * @param f Um "double" que corresponde ao flow.
 */
void Algorithms::augmentFlowAlongPath(Vertex *source, Vertex *target, double f) {
    for (auto v = target; v != source; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

/**
 * Faz a busca do caminho residual mais pequeno no grafo. \n
 * Time Complexity: O(V)
 * @param source Um apontador para um vértice que corresponde à estação inicial.
 * @param target Um apontador para um vértice que corresponde à estação final.
 * @return Valor double do caminho residual mais curto.
 */
double Algorithms::findMinResidualAlongPath(Vertex *source, Vertex *target) {
    double f = INF;

    for (auto v = target; v != source; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

/**
 * Determina o fluxo máximo de uma rede de fluxos fornecida
 * entre um node source e um node target. \n
 * Time Complexity: O(V*E^2)
 * @param graph Um grafo.
 * @param source Uma "string" que corresponde à estação inicial.
 * @param target Uma "string" que corresponde à estação final.
 * @return Grafo com o fluxo máximo determinado.
 */
Graph Algorithms::edmondsKarp(Graph graph, string source, string target) {
    Vertex* s = graph.findVertex(source);
    Vertex* t = graph.findVertex(target);
    if (s == nullptr || t == nullptr || s == t) {
        throw logic_error("Invalid source and/or target station");
    }

    for (auto v : graph.getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }

    while (findAugmentingPath(graph, s, t)) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
    return graph;
}

/**
 * Fornecendo um node source e um node target, procura
 * na network augmenting paths disponíveis. \n
 * Time Complexity: O(V)
 * @param graph Um grafo.
 * @param source Um apontador para um vértice que corresponde à estação inicial.
 * @param target Um apontador para um vértice que corresponde à estação final.
 * @return True caso exista um augmenting path e falso caso não exista.
 */
bool Algorithms::findAugmentingPath(Graph graph, Vertex *source, Vertex *target) {
    for (auto v : graph.getVertexSet()) {
        v->setVisited(false);
    }
    source->setVisited(true);
    queue<Vertex *> q;
    q.push(source);

    while (!q.empty() && !target->isVisited()) {
        auto v = q.front();
        q.pop();
        for (auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
        for (auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
    return target->isVisited();
}

/**
 * Esta função verifica se o vértice ainda não foi visitado ou ainda tem "flow". \n
 * Time Complexity: O(1)
 * @param q Uma fila de apontadores de vértices.
 * @param e Um apontador para um "edge".
 * @param w Um apontador para um vértice.
 * @param residual Um "double" que corresponde ao flow.
 */
void Algorithms::testAndVisit(queue<Vertex *> &q, Edge *e, Vertex *w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

/**
 * Organiza um vetor de pares de "ints" e "strings" por ordem decrescente. \n
 * Time Complexity: O(1)
 * @param p1 Um par de "ints" e "strings".
 * @param p2 Um par de "ints" e "strings".
 * @return Verdade se o "int" em p1 é maior que o "int" em p2, falso se acontecer o contrário.
 */
bool sort_vec_int(pair<int, string> &p1, pair<int, string> &p2){
    return p1.first > p2.first;
}

/**
 * Faz a soma de todas as linhas disponíveis em cada município,
 * guardando-a num vetor. \n
 * Time Complexity: O(V*M*E), [M = número de municípios]
 * @param graph Um grafo.
 * @param k Um valor inteiro.
 */
void Algorithms::largerBudgetsMunicipality(Graph graph, int k) {
    vector<pair<int, string>> municipalities;

    for (auto vertex : graph.getVertexSet()){
        bool already_exists = false;

        for (auto &municipality : municipalities){
            if (vertex->getMunicipality() == municipality.second){

                for (auto edge : vertex->getAdj()){
                    municipality.first += edge->getWeight();
                }
                already_exists = true;
                break;
            }
        }
        if (!already_exists){
            int sum = 0;
            for (auto edge: vertex->getAdj()){
                sum += edge->getWeight();
            }
            municipalities.push_back({sum, vertex->getMunicipality()});
        }
    }

    sort(municipalities.begin(), municipalities.end(), sort_vec_int);

    cout << "Municipalities that need larger budgets:" <<endl;

    if (k > municipalities.size()) k = municipalities.size();
    for (int i = 0; i < k; i++){
        cout << municipalities[i].second << " with " << municipalities[i].first << " lines to maintain" << endl;
    }
}

/**
 * Faz a soma de todas as linhas disponíveis em cada distrito,
 * guardando-a num vetor. \n
 * Time Complexity: O(V*D*E), [D = número de distritos]
 * @param graph Um grafo.
 * @param k Um valor inteiro.
 */
void Algorithms::largerBudgetsDistrict(Graph graph, int k) {
    vector<pair<int, string>> districts;

    for (auto vertex : graph.getVertexSet()){
        bool already_exists = false;

        for (auto &district : districts){
            if (vertex->getDistrict() == district.second){

                for (auto edge : vertex->getAdj()){
                    district.first += edge->getWeight();
                }

                already_exists = true;
                break;
            }
        }
        if (!already_exists){
            int sum = 0;
            for (auto edge: vertex->getAdj()){
                sum += edge->getWeight();
            }
            districts.push_back({sum, vertex->getDistrict()});
        }
    }

    sort(districts.begin(), districts.end(), sort_vec_int);

    cout << "Districts that need larger budgets:" << endl;

    if (k > districts.size()) k = districts.size();
    for (int i = 0; i < k; i++){
        cout << districts[i].second << " with " << districts[i].first << " lines to maintain" << endl;
    }
}

/**
 * Faz a soma total dos fluxos dos incoming edges. \n
 * Time Complexity: O(E)
 * @param g Um grafo.
 * @param target Uma "string" que corresponde à estação final.
 * @return Fluxo máximo de um node target.
 */
int Algorithms::MaximumTrainsSimultaneously(Graph g, string target) {
    int flow = 0;
    auto vTarget = g.findVertex(target);
    for (auto e : vTarget->getIncoming()) {
        flow += e->getFlow();
    }
    return flow;
}

/**
 * Faz a remoção dos edges que partem do node source até ao node target. \n
 * Time Complexity: O(V)
 * @param g Um grafo.
 * @param source Uma "string" que corresponde à estação inicial.
 * @param target Uma "string" que corresponde à estação final.
 * @return Grafo com os edges entre a estação source e target removidos no
 * caso de ser fornecido um par válido. Caso contrário é retornado um grafo
 * sem alterações feitas.
 */
Graph Algorithms::newGraph(Graph g, string source, string target){
    Vertex* vertex_source = g.findVertex(source);
    if (vertex_source == nullptr){
        cout << "Vertex not found" << endl;
        return g;
    }
    if (!vertex_source->removeEdge(target)){
        cout << "Edge not found" << endl;
    }
    return g;
}

/**
 * Organiza um vetor de pares de "ints" e "strings" por ordem decrescente. \n
 * Time Complexity: O(1)
 * @param p1 Um par de "ints" e "strings".
 * @param p2 Um par de "ints" e "strings".
 * @return Verdade se o "string" em p1 é maior que o "string" em p2, falso se acontecer o contrário.
 */
bool sort_vec_stations(pair<int, string> &p1, pair<int, string> &p2) {
    return p1.second > p2.second;
}

/**
 * Faz a busca dos casos em que há diferença de flows entre dois grafos,
 * guardando-os num vetor e ordenando-os por ordem decrescente
 * de diferença de fluxo. Conclui fazendo prints das k primeiro casos. \n
 * Time Complexity: O(V^2 * log(V) * E^3)*2
 * @param g Um grafo.
 * @param new_graph Um grafo com os "edges" escolhidos removidos.
 * @param k Um valor inteiro.
 */
void Algorithms::mostAffected(Graph g, Graph new_graph, int k){
    int flow, flowNew, diffFlow;
    string source, target, vSource, vTarget;
    Graph temp, tempNew;
    vector<pair<int, string>> mostAffectedStationsTemp;
    vector<pair<int, string>> mostAffectedStations;
    pair<int,string> train;
    temp = g;
    tempNew = new_graph;

    for (int i = 0; i < g.getVertexSet().size(); i++) {
        vSource = g.getVertexSet()[i]->getName();
        for (int j = i + 1; j < g.getVertexSet().size(); j++) {
            vTarget = g.getVertexSet()[j]->getName();

            temp = edmondsKarp(temp, vSource, vTarget);
            flow = MaximumTrainsSimultaneously(temp, vTarget);

            tempNew = edmondsKarp(tempNew, vSource, vTarget);
            flowNew = MaximumTrainsSimultaneously(tempNew, vTarget);

            diffFlow = flow - flowNew;

            if (diffFlow > 0) {
                train.first = diffFlow;
                train.second = vSource;
                mostAffectedStationsTemp.push_back(train);

                if (j == g.getVertexSet().size() - 1) {
                    train.first = diffFlow;
                    train.second = vTarget;
                    mostAffectedStationsTemp.push_back(train);
                }
            }
            temp = g;
            tempNew = new_graph;
        }
    }

    sort(mostAffectedStationsTemp.begin(), mostAffectedStationsTemp.end(), sort_vec_stations);

    int sum = 0;
    for (int i = 0; i < mostAffectedStationsTemp.size(); i++){
        if (mostAffectedStationsTemp[i].second == mostAffectedStationsTemp[i+1].second){
            sum += mostAffectedStationsTemp[i].first;
            continue;
        }
        sum += mostAffectedStationsTemp[i].first;
        mostAffectedStations.push_back({sum, mostAffectedStationsTemp[i].second});
        sum = 0;
    }

    sort(mostAffectedStations.begin(), mostAffectedStations.end(), sort_vec_int);

    if (k > mostAffectedStations.size()) {
        k = mostAffectedStations.size();
        cout << "The maximum number of affected stations is " << k << endl;
    }

    for (int i = 0; i < k; i++) {
        cout << mostAffectedStations[i].second << " -> Affected trains: " << mostAffectedStations[i].first << endl;
    }
}


/**
 * Guarda os caminhos com maior número de comboios a deslocar-se em simultâneo
 * e com um menor custa para a companhia. \n
 * Time Complexity: O(V + E)
 * @param g Um grafo.
 * @param source Uma "string" que corresponde à estação inicial.
 * @param target Uma "string" que corresponde à estação final.
 * @param path Um vetor de "strings" que corresponde a um caminho.
 * @param paths Um vetor de pares de pares de "ints", um para o custo e o outro para o número máximo de comboios, e o caminho.
 * @param cost Um inteiro que corresponde ao custo de um caminho.
 * @param curr_cost Um inteiro que corresponde ao custo atual de um caminho.
 * @param maxFlow Um inteiro que corresponde ao "flow" máximo.
 */
void Algorithms::dfs(Graph g, string source, string target, vector<string> &path, vector<pair<pair<int, int>,vector<string>>> &paths, int cost, int curr_cost, int maxFlow) {
    auto s = g.findVertex(source);
    auto t = g.findVertex(target);
    s->setVisited(true);
    path.push_back(s->getName());

    if (s == t) {
        if (paths.empty()) paths.push_back({{cost, maxFlow}, path});
        else if (cost == paths[0].first.first) {
            if (maxFlow <= paths[0].first.second) {
                paths.insert(paths.begin(), {{cost, maxFlow}, path});
            }
        }
        else if (cost < paths[0].first.first) paths.insert(paths.begin(), {{cost, maxFlow}, path});

        maxFlow = 0;
    }
    else {
        for (auto e : s->getAdj()) {
            auto w = e->getDest();
            if (!w->isVisited() && e->getFlow() > 0) {
                if (e->getService() == "STANDARD") {
                    curr_cost = e->getFlow() * 2;
                }
                else if (e->getService() == "ALFA PENDULAR") {
                    curr_cost = e->getFlow() * 4;
                }
                if (e->getFlow() > maxFlow) maxFlow = e->getFlow();

                cost += curr_cost;
                dfs(g, w->getName(), target, path, paths, cost, curr_cost, maxFlow);
            }
        }
    }
    cost -= curr_cost;
    path.pop_back();
    s->setVisited(false);
}

