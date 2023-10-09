#ifndef PROJECT_STATION_H
#define PROJECT_STATION_H

#include <string>
using namespace std;


class Station {
public:
    Station();
    Station(string name_, string district_, string municipality_, string township_, string line_);
    string getName();
    string getDistrict();
    string getMunicipality();
    string getTownship();
    string getLine();
    void setName(string name_);
    void setDistrict(string district_);
    void setMunicipality(string municipality_);
    void setTownship(string township_);
    void setLine(string line_);

private:
    string name;
    string district;
    string municipality;
    string township;
    string line;
};


#endif
