#include <iostream>

using namespace std;

class folhaQuadTree
{
private:
    folhaQuadTree* NE;
    folhaQuadTree* SE;
    folhaQuadTree* NW;
    folhaQuadTree* SW;
public:
    folhaQuadTree(/* args */);
    ~folhaQuadTree();
    float getLatitude();
    float getLongitude();
    void setLatitude(float latitude);
    void setLongitude(float longitude);
    folhaQuadTree* getNE();
    folhaQuadTree* getSE();
    folhaQuadTree* getNW();
    folhaQuadTree* getSW();
};


