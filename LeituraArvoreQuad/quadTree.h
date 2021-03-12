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
    void buscaIntervalo(folhaQuadTree* r, float x0, float x1, float y0, float y1);
    bool confereIntervalo(folhaQuadTree* r, float x0, float x1, float y0, float y1);
    folhaQuadTree* comparaComIntervalo(folhaQuadTree *r, float x0, float x1, float y0, float y1);
};

#endif