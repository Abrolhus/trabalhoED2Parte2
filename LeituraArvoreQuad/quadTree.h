#ifndef QUADTREE_H
#define QUADTREE_H

#include <iostream>
#include "folhaQuadTree.h"
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

class quadTree
{
private:
    folhaQuadTree* raiz;
    int tam;
    int itera;
public:
    quadTree(vector<folhaQuadTree*> vet);
    ~quadTree();
    void inserir(folhaQuadTree *p);
    /*bool marcarComoRemovido();
    quadTree reconstruir();*/
    char compara(folhaQuadTree *r, folhaQuadTree* i);
    void buscaIntervalo(folhaQuadTree* r, double x0, double x1, double y0, double y1, vector<int>& s, int& comps);
    bool confereIntervalo(folhaQuadTree* r, double x0, double x1, double y0, double y1, vector<int>& s, int& comps);
    void buscaIntervaloAux(vector<int>& s, double x0, double x1, double y0, double y1);
    void imprimir();
    void imprimirAux(folhaQuadTree* r);
    int getTam(){return tam;};
    void desalocar(folhaQuadTree* r);
};

#endif