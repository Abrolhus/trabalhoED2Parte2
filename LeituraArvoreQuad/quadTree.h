#include <iostream>
#include "folhaQuadTree.h"

using namespace std;

class quadTree
{
private:
    folhaQuadTree* raiz;
public:
    quadTree();
    ~quadTree();
    bool inserir(folhaQuadTree p);
    /*bool marcarComoRemovido();
    quadTree reconstruir();*/
    folhaQuadTree compara();
};


