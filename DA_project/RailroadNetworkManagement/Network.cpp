#include "Network.h"

Network::Network() {
    stationA = "";
    stationB = "";
    capacity = 0.0;
    service = "";
}

Network::Network(string stationA_, string stationB_, double capacity_, string service_) {
    stationA = stationA_;
    stationB = stationB_;
    capacity = capacity_;
    service = service_;
}

string Network::getStationA() {
    return stationA;
}

string Network::getStationB() {
    return stationB;
}

double Network::getCapacity() {
    return capacity;
}

string Network::getService() {
    return service;
}

void Network::setStationA(string stationA_) {
    stationA = stationA_;
}

void Network::setStationB(string stationB_) {
    stationB = stationB_;
}

void Network::setCapacity(double capacity_) {
    capacity = capacity_;
}

void Network::setService(string service_) {
    service = service_;
}