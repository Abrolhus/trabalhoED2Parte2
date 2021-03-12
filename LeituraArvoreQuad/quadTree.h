#ifndef QUADTREE_H
#define QUADTREE_H

#include <iostream>
#include "folhaQuadTree.h"
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class quadTree
{
private:
    folhaQuadTree* raiz;
    int tam;
public:
    quadTree(ifstream &arquivo);
    ~quadTree();
    void inserir(folhaQuadTree* raiz,folhaQuadTree *p);
    /*bool marcarComoRemovido();
    quadTree reconstruir();*/
    folhaQuadTree* compara(folhaQuadTree *r, folhaQuadTree* i);
};

#endif