#ifndef ARVOREB_H
#define ARVOREB_H

#include <iostream>
#include "NoB.h"
#include "../HashTable.h"
#include "auxiliar.h"
#include <fstream>

using namespace std;

class ArvoreB
{
    private:
        NoB* root;

        int size;

        void printAux( NoB* no, int& layer, bool& overflow );
        void clearAux( NoB* no );

        void overflow( int val, NoB* current, NoB* left, NoB* right );

        int AuxBusca( NoB*, int );

        HashTable* HashRef;

    public:
        ArvoreB( HashTable*, int );
        ~ArvoreB();

        bool Busca( int val );
        int BuscaCasos( int );

        void Insere( int val );

        void Print( bool overflow = false );
        void Limpar();
};

#endif