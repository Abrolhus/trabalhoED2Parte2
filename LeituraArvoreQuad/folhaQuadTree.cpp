#include <iostream>
#include "folhaQuadTree.h"


using namespace std;


folhaQuadTree::folhaQuadTree(string stateCode, string cityCode, string cidade, float longitude, float latitude, string capital )
{
    this->stateCode = stateCode;
    this->cityCode = cityCode;
    this->cidade = cidade;
    this->longitude = longitude;
    this->latitude = latitude;
    this->capital = capital;
    this->NE = nullptr;
    this->SE = nullptr;
    this->SW = nullptr;
    this->NW = nullptr;
}

folhaQuadTree::~folhaQuadTree()
{
}