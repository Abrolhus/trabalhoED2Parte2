#ifndef FOLHAQUAD_H
#define FOLHAQUAD_H

#include <iostream>

using namespace std;

class folhaQuadTree
{
private:
    folhaQuadTree* NE;
    folhaQuadTree* SE;
    folhaQuadTree* NW;
    folhaQuadTree* SW;
    string stateCode;
    int cityCode;
    string cidade;
    double longitude;
    double latitude;
    string capital;
    char Nordeste;
    char Sudeste;
    char Noroeste;
    char Sudoeste;
public:
    folhaQuadTree(string stateCode, int cityCode, string cidade, double longitude, double latitude, string capital);
    ~folhaQuadTree();
    double getLatitude() {return latitude;};
    double getLongitude(){return longitude;};
    //void setLatitude(float latitude);
    //void setLongitude(float longitude);
    folhaQuadTree* getNE() {return NE;};
    folhaQuadTree* getSE() {return SE;};
    folhaQuadTree* getNW() {return NW;};
    folhaQuadTree* getSW() {return SW;};
    //void setCidade(string cidade);
    string getCidade() {return cidade;};
    //void setStateCode(string stateCode);
    string getStateCode() {return stateCode;};
    //void setCityCode(string cityCode);
    int getCityCode(){return cityCode;};
    void setFilho(char val, folhaQuadTree* valor);
    folhaQuadTree* getFilho(char val);
    char getNoroeste(){return Noroeste;};
    char getNordeste(){return Nordeste;};
    char getSudeste(){return Sudeste;};
    char getSudoeste(){return Sudoeste;};
};

#endif