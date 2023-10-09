#include "FileManager.h"
#include "Station.h"
#include "Network.h"

/**
 * Abre um file com as estações, definindo-as como nodes de um grafo. \n
 * Time Complexity: O(n1*V); [n1 = número de estações a serem lidas]
 * @param file Uma "string" que corresponde ao nome do ficheiro de estações.
 * @param g Um grafo.
 * @return Grafo cujos nodes correspondem às estaçóes, sem edges definidos.
 */
Graph FileManager::readStations(string file, Graph g) {
    string name, district, municipality, township, line, skip;
    ifstream filename;
    filename.open("../Files/" + file);
    if (!filename.is_open()) cout << "File creation failed" << endl;
    else {
        if (!filename.eof()) { getline(filename, skip, ',');}
        if (!filename.eof()) { getline(filename, skip, ',');}
        if (!filename.eof()) { getline(filename, skip, ',');}
        if (!filename.eof()) { getline(filename, skip, ',');}
        if (!filename.eof()) { getline(filename, skip,  '\n');}

        while (!filename.eof()) {
            getline(filename, name, ',');
            getline(filename, district, ',');
            getline(filename, municipality, ',');
            getline(filename, township, ',');
            getline(filename, line, '\n');

            if (name[0] == '\n') {
                name.erase(0,1);
            }

            if (township[0] == '\"') {
                int pos = line.find('\"');
                township.erase(0, 1);
                township += ",";
                township += line.substr(0, pos);
                line.erase(0, pos + 2);
            }

            Station station = Station(name, district, municipality, township, line);
            g.addVertex(station);
        }
    }
    return g;
}

/**
 * Abre um file com as ligações de comboios, definindo-as como edges de um grafo. \n
 * Time Complexity: O(n2*V); [n2 = número de ligações de comboios a serem lidas]
 * @param file Uma "string" que corresponde ao nome do ficheiro da rede de estações.
 * @param g Um grafo.
 * @return Grafo cujas edges correspondem às ligações de comboios que podem ser feitas entre estações (nodes).
 */
Graph FileManager::readNetworks(string file, Graph g) {
    string stationA, stationB, capacity, service, skip;
    ifstream filename;
    filename.open("../Files/" + file);
    if (!filename.is_open()) cout << "File creation failed" << endl;
    else {
        if (!filename.eof()) { getline(filename, skip, ',');}
        if (!filename.eof()) { getline(filename, skip, ','); }
        if (!filename.eof()) { getline(filename, skip, ','); }
        if (!filename.eof()) { getline(filename, skip, '\n'); }

        while (!filename.eof()) {
            getline(filename, stationA, ',');
            getline(filename, stationB, ',');
            getline(filename, capacity, ',');
            getline(filename, service, '\n');

            if (stationA[0] == '\n') {
                stationA.erase(0,1);
            }

            Network network = Network(stationA, stationB, stod(capacity), service);
            g.addBidirectionalEdge(network); // O(V)
        }
    }
    return g;
}