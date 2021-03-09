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
    this->NE = NULL;
    this->SE = NULL;
    this->SW = NULL;
    this->NW = NULL;
}

folhaQuadTree::~folhaQuadTree()
{
}