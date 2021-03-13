#include <iostream>
#include "folhaQuadTree.h"


using namespace std;


folhaQuadTree::folhaQuadTree(string stateCode, string cityCode, string cidade, double longitude, double latitude, string capital )
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
    this->Nordeste = 'A';
    this->Noroeste = 'B';
    this->Sudeste = 'C';
    this->Sudoeste = 'D';
}

folhaQuadTree::~folhaQuadTree()
{
}

void folhaQuadTree:: setFilho(char val, folhaQuadTree* i){
    if (val == 'A') this->NE = i;
    if (val == 'B') this->NW = i;
    if (val == 'C') this->SE = i;
    if (val == 'D') this->SW = i;
}

folhaQuadTree* folhaQuadTree:: getFilho(char val){
    if (val == 'A') return NE;
    if (val == 'B') return NW;
    if (val == 'C') return SE;
    if (val == 'D') return SW;
    return NULL;
}