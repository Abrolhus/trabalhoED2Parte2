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
    string cityCode;
    string cidade;
    float longitude;
    float latitude;
    string capital;
public:
    folhaQuadTree(string stateCode, string cityCode, string cidade, float longitude, float latitude, string capital);
    ~folhaQuadTree();
    float getLatitude() {return latitude;};
    float getLongitude(){return longitude;};
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
    string getCityCode(){return cityCode;};
};

#endif