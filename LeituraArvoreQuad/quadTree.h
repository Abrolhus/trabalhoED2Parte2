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
    bool inserir(folhaQuadTree p);
    /*bool marcarComoRemovido();
    quadTree reconstruir();*/
    folhaQuadTree compara();
};


