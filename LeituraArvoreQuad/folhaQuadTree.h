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
    /*void setCidade(string cidade);
    string getCidade();
    void setStateCode(string stateCode);
    string getStateCode();
    void setCityCode(string cityCode);
    string getCityCode();*/
};


