#ifndef PROJECT_NETWORK_H
#define PROJECT_NETWORK_H

#include <string>

using namespace std;

class Network {
public:
    Network();
    Network(string stationA_, string stationB_, double capacity_, string service_);
    string getStationA();
    string getStationB();
    double getCapacity();
    string getService();
    void setStationA(string stationA_);
    void setStationB(string stationB_);
    void setCapacity(double capacity_);
    void setService(string service_);

private:
    string stationA;
    string stationB;
    double capacity;
    string service;
};


#endif
