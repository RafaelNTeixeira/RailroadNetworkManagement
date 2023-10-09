#include "Station.h"

Station::Station() {
    name = "";
    district = "";
    municipality = "";
    township = "";
    line = "";
}

Station::Station(string name_, string district_, string municipality_, string township_, string line_) {
    name = name_;
    district = district_;
    municipality = municipality_;
    township = township_;
    line = line_;
}

string Station::getName() {
    return name;
}

string Station::getDistrict() {
    return district;
}

string Station::getMunicipality() {
    return municipality;
}

string Station::getTownship() {
    return township;
}

string Station::getLine() {
    return line;
}

void Station::setName(string name_) {
    name = name_;
}

void Station::setDistrict(string district_) {
    district = district_;
}

void Station::setMunicipality(string municipality_) {
    municipality = municipality_;
}

void Station::setTownship(string township_) {
    township = township_;
}

void Station::setLine(string line_) {
    line = line_;
}