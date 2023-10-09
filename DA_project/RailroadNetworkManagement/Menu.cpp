#include <sstream>
#include <list>
#include "Menu.h"
#include "Algorithms.h"

/**
 * Cria o menu principal e as funcionalidades do programa.
 * @return 0 Quando o programa acaba.
 */
int Menu::createMenu() {
    Graph g, temp, new_graph, clean;
    FileManager f;
    Algorithms algo;
    int number, choice, flow, maxFlow, option, k, cost, curr_cost, max_flow;
    string file1, file2;
    string source, target, vSource, vTarget, line;
    stringstream ss;
    list<pair<int, string>> mostTrains;
    pair<int,string> train;
    vector<string> path;
    vector<pair<pair<int, int>,vector<string>>> paths;
    vector<pair<int, string>> lastStations;
    pair<int,string> station;
    Station station_;
    Network network_;

    drawTrain();
    showheader();
    cout << "How many station networks do you want to analyse? " << endl;
    cout << "If you select only one network, we'll use the files \"stations.csv\" and \"network.csv\" on the directory Files!" << endl;
    number = checkValidInput();

    while (number > 0) {
        if (number == 1) {
            g = createGraph("stations.csv", "network.csv", g, f);
            break;
        }
        cout << "Insert the name of the stations file:" << endl;
        cin >> file1;
        cout << "Insert the name of the network file:" << endl;
        cin >> file2;
        g = createGraph(file1, file2, g, f);
        number--;
    }

    while (true) {
        printOptions();
        choice = checkValidInput();
        switch (choice) {
            case 0:
                drawTrain();
                showCredits();
                return 0;

            case 1:
                cout << "From which station do you wish to travel?" << endl;
                getline(cin, source);
                cout << "Which station do you wish to arrive?" << endl;
                getline(cin, target);
                temp = g;
                temp = algo.edmondsKarp(temp, source, target);
                maxFlow = algo.MaximumTrainsSimultaneously(temp, target);
                cout << endl;

                cout << "The maximum number of trains that can simultaneously travel between " <<
                source << " and " << target << " is " << maxFlow << "." << endl;

                cout << endl;
                source = "";
                target = "";
                temp = clean;
                break;

            case 2:
                maxFlow = INT16_MIN;
                temp = g;
                for (int i = 0; i < g.getVertexSet().size(); i++) {
                    vSource = g.getVertexSet()[i]->getName();
                    for (int j = i + 1; j < g.getVertexSet().size(); j++) {
                        vTarget = g.getVertexSet()[j]->getName();

                        temp = algo.edmondsKarp(temp, vSource, vTarget);
                        flow = algo.MaximumTrainsSimultaneously(temp, vTarget);
                        if (flow > maxFlow) {
                            maxFlow = flow;
                            source = vSource;
                            target = vTarget;
                            train.first = maxFlow;
                            train.second = source;
                            mostTrains.push_back(train);
                        }
                        temp = g;
                    }
                }

                for (auto it = mostTrains.begin(); it != mostTrains.end(); it++) {
                    if (it->first != maxFlow) {
                        it = mostTrains.erase(it);
                        it--;
                    }
                }

                for (auto it = mostTrains.begin(); it != mostTrains.end(); it++) {
                    cout << "The maximum amount of trains taking full advantage of the existing network go from " <<
                    it->second << " to " << target << " with a number of " << it->first << "." << endl;
                }
                cout << endl;
                mostTrains.clear();
                maxFlow = INT16_MIN;
                temp = clean;
                source = "";
                target = "";
                break;

            case 3:
                cout << "By:" << endl;
                cout << "1. Municipality" << endl;
                cout << "2. District" << endl;
                option = checkValidInput();
                cout << endl << endl;
                if (option == 1){
                    cout << "How many municipalities do you want to see?" << endl;
                    k = checkValidInput();
                    algo.largerBudgetsMunicipality(g, k);
                }
                else {
                    cout << "How many districts do you want to see?" << endl;
                    k = checkValidInput();
                    algo.largerBudgetsDistrict(g, k);
                }
                temp = clean;
                cout << endl;
                break;

            case 4:
                cout << "Which station do you want to define as the destination?" << endl;
                getline(cin, target);
                cout << endl;
                maxFlow = INT16_MIN;
                temp = g;

                for (auto v : g.getVertexSet()) {
                    source = v->getName();
                    if (source == target) continue;
                    temp = algo.edmondsKarp(temp, source, target);
                    flow = algo.MaximumTrainsSimultaneously(temp, target);
                    if (flow > maxFlow) maxFlow = flow;
                    temp = g;
                }
                cout << "The maximum number of trains that can simultaneously arrive at " <<
                        target << " is " << maxFlow << "." << endl;
                temp = clean;
                cout << endl;
                maxFlow = INT16_MIN;
                break;

            case 5:
                cout << "From which station do you wish to travel?" << endl;
                getline(cin, source);
                cout << "Which station do you wish to arrive?" << endl;
                getline(cin, target);
                temp = g;
                temp = algo.edmondsKarp(temp, source, target);
                for (auto v : temp.getVertexSet()) {
                    v->setVisited(false);
                }
                cost = 0;
                curr_cost = 0;
                max_flow = 0;
                algo.dfs(temp, source, target, path, paths, cost, curr_cost, max_flow);
                printPath(paths, source, target);
                temp = clean;
                path.clear();
                paths.clear();
                break;

            case 6:
                for (auto vertex : g.getVertexSet()){
                    station_.setName(vertex->getName());
                    station_.setDistrict(vertex->getDistrict());
                    station_.setLine(vertex->getLine());
                    station_.setMunicipality(vertex->getMunicipality());
                    station_.setTownship(vertex->getTowship());

                    temp.addVertex(station_);
                    for (auto edge: vertex->getAdj()){
                        network_.setService(edge->getService());
                        network_.setCapacity(edge->getWeight());
                        network_.setStationA(edge->getOrig()->getName());
                        network_.setStationB(edge->getDest()->getName());
                        temp.addBidirectionalEdge(network_);
                    }
                }

                cout << "Write the source station of the edge to remove:" << endl;
                getline(cin, source);
                cout << "Write the target station of the edge to remove:" << endl;
                getline(cin, target);

                while (true) {
                    temp = algo.newGraph(temp, source, target);
                    cout << "Do you want to remove more edges? [Yes/No]" << endl;
                    if (!checkYesOrNo()) break;
                    cout << "Write the source station of the edge to remove:" << endl;
                    getline(cin, source);
                    cout << "Write the target station of the edge to remove:" << endl;
                    getline(cin, target);
                }
                source = "";
                target = "";
                cout << "From which station do you wish to travel?" << endl;
                getline(cin, source);
                cout << "Which station do you wish to arrive?" << endl;
                getline(cin, target);

                temp = algo.edmondsKarp(temp, source, target);
                maxFlow = algo.MaximumTrainsSimultaneously(temp, target);

                cout << "The maximum number of trains that can simultaneously travel between " <<
                        source << " and " << target << " is " << maxFlow << "." << endl;
                cout << endl;
                source = "";
                target = "";
                temp = clean;
                cout << endl;
                break;

            case 7:
                for (auto vertex : g.getVertexSet()) {
                    station_.setName(vertex->getName());
                    station_.setDistrict(vertex->getDistrict());
                    station_.setLine(vertex->getLine());
                    station_.setMunicipality(vertex->getMunicipality());
                    station_.setTownship(vertex->getTowship());

                    new_graph.addVertex(station_);
                    for (auto edge: vertex->getAdj()) {
                        network_.setService(edge->getService());
                        network_.setCapacity(edge->getWeight());
                        network_.setStationA(edge->getOrig()->getName());
                        network_.setStationB(edge->getDest()->getName());
                        new_graph.addBidirectionalEdge(network_);
                    }
                }

                cout << "Write the source station of the edge to remove:" << endl;
                getline(cin, source);
                cout << "Write the target station of the edge to remove:" << endl;
                getline(cin, target);

                while (true) {
                    new_graph = algo.newGraph(new_graph, source, target);
                    cout << "Do you want to remove more edges? [Yes/No]" << endl;
                    if (!checkYesOrNo()) break;
                    cout << "Write the source station of the edge to remove:" << endl;
                    getline(cin, source);
                    cout << "Write the target station of the edge to remove:" << endl;
                    getline(cin, target);
                }
                cout << "How many stations do you want to see?" << endl;
                k = checkValidInput();
                algo.mostAffected(g, new_graph, k);
                new_graph = clean;
                cout << endl;
                break;

            default:
                cout << "Such feature doesn't exist. Try another one!" << endl;
                break;
        }
    }
}

/**
 * Recebe um primeiro file com as estações e um segundo com as ligações de comboios e cria um grafo. \n
 * Time Complexity: O((n1*V)+(n2*V)); [n1 = número de estações a ler, n2 = número de ligações de comboios a ler]
 * @param file1 Uma "string" que corresponde ao nome do ficheiro de estações.
 * @param file2 Uma "string" que corresponde ao nome do ficheiro da rede de comboios.
 * @param g Um grafo.
 * @param f Um objeto file manager.
 * @return Grafo cujos nodes correspondem aos valores atribuídos do file1 e cujos edges correspondem aos valores atribuídos do file2.
 */
Graph Menu::createGraph(string file1, string file2, Graph g, FileManager f) {
    g = f.readStations(file1, g);
    g = f.readNetworks(file2, g);
    return g;
}

/**
 * Faz print das features disponíveis.
 */
void Menu::printOptions() {
    showheader();
    cout << "Basic Service Metrics" << endl;
    cout << endl;
    cout << "1. Calculate the maximum number of trains that can simultaneously travel between two specific stations" << endl;
    cout << "2. Calculate, from all pairs of stations, the ones that require the highest amount of trains "
            "when taking full advantage of the existing network capacity" << endl;
    cout << "3. Top-k municipalities and districts, regarding their transportation needs" << endl;
    cout << "4. Calculate the maximum number of trains that can simultaneously arrive at a given station" << endl;
    cout << endl;
    cout << endl;
    cout << "Operation Cost Optimization" << endl;
    cout << endl;
    cout << "5. Calculate the maximum amount of trains that can simultaneously travel "
            "between two specific stations with minimum cost for the company" << endl;
    cout << endl;
    cout << endl;
    cout << "Reliability and Sensitivity to Line Failures" << endl;
    cout << endl;
    cout << "6. Calculate the maximum number of trains that can simultaneously travel between two specific stations, "
            "when you remove the edges from the network " << endl;
    cout << "7. Top-k most affected stations" << endl;
    cout << endl;
    cout << "0. Quit the program" << endl;
}

/**
 * Imprime o header do menu.
 */
void Menu::showheader(){
    cout << "============================================== Rail Road Management ==============================================" << endl;
    cout << endl;
}

/**
 * Verifica se é inserido como input um valor "yes" ou "no". Caso não se verifique,
 * é imprimida uma mensagem de erro até que seja inserido um valor válido.
 * @return True caso seja inserido como input um valor "yes" ou "no"
 */
bool Menu::checkYesOrNo() {
    while(true){
        string check;
        getline(cin, check);
        cout << endl;
        if(check == "No" || check == "no" || check == "NO") return false;
        else if (check == "Yes" || check == "yes" || check == "YES") return true;
        else cout << "ERROR: Invalid input. Please, answer 'Yes' or 'No': ";
    }
}

/**
 * Faz um pedido e verificação de input e retorna-o se estiver num formato válido. \n
 * Caso contrário, continua a fazer o pedido até que o utilizador forneça um valor adequado.
 * @return Inteiro correspondente à escolha do utilizador.
 */
int Menu::checkValidInput() {
    int choice;
    cin >> choice;

    while(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input. Please, enter a number:" << endl;
        cin >> choice;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout << endl;
    return choice;
}

/**
 * Imprime os créditos.
 */
void Menu::showCredits(){
    cout << "Software developed by:" << endl;
    cout << "Joao Sobral" << " - " << "Joao Costa" << " - " << "Rafael Teixeira" << endl;
    cout << "G12_5" << " - " << "2LEIC12" << " - " << "DA 2022/2023" << endl;
    cout << endl;
}

/**
 * Imprime os caminhos com menor custo e cujo número de comboios que se deslocam em simultâneo é maior \n
 * Time Complexity: O(P), [P = número de caminhos guardados no vetor paths]
 * @param paths Um vetor de pares de pares de "ints", um para o custo e o outro para o número máximo de comboios, e o caminho.
 * @param source Uma "string" que corresponde à estação inicial.
 * @param target Uma "string" que corresponde à estação final.
 */
void Menu::printPath(vector<pair<pair<int, int>,vector<string>>> paths, string source, string target) {
    int k = 0;

    while (true){
        if ((paths[k].first.first == paths[k+1].first.first) && (paths[k].first.second == paths[k+1].first.second)) k++;
        else break;
    }
    paths.erase(paths.begin()+1+k, paths.end());

    int check = 0;
    cout << endl;
    cout << "Minimal cost: " << paths[0].first.first << endl;
    cout << "The maximum number of trains that can simultaneously travel between " <<
    source << " and " << target << " is " << paths[0].first.second << "." << endl;
    for (int i = 0; i < paths.size(); i++) {
        for (auto ele: paths[i].second) {
            if (check == 0){
                cout << ele;
                check = 1;
                continue;
            }
            cout << " -> " << ele;
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * Desenha um comboio.
 */
void Menu::drawTrain() {
    cout << "                 _-====-__-======-__-========-_____-============-__\n"
            "               _(                                                 _)\n"
            "            OO(           _/_ _  _  _/_   _/_ _  _  _/_           )_\n"
            "           0  (_          (__(_)(_) (__   (__(_)(_) (__            _)\n"
            "         o0     (_                                                _)\n"
            "        o         '=-___-===-_____-========-___________-===-dwb-='\n"
            "      .o                                _________\n"
            "     . ______          ______________  |         |      _____\n"
            "   _()_||__|| ________ |            |  |_________|   __||___||__\n"
            "  (G12_5 2LC| |      | |            | __Y______00_| |_         _|\n"
            " /-OO----OO\"\"=\"OO--OO\"=\"OO--------OO\"=\"OO-------OO\"=\"OO-------OO\"=P\n"
            "##################################################################################################################" << endl;
    cout << endl;
}