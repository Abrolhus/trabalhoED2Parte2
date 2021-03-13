#ifndef ARVOREB_H
#define ARVOREB_H

#include <iostream>
#include "NoB.h"
#include "../HashTable.h"
#include "auxiliar.h"
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

class ArvoreB
{
    private:
        NoB* root;

        int size;

        void printAux( NoB* no, int& layer, bool& overflow );
        void clearAux( NoB* no );

        void overflow( int val, NoB* current, NoB* left, NoB* right, int& );

        int AuxBusca( NoB*, int, int& );

        HashTable* HashRef;

    public:
        ArvoreB( HashTable*, int );
        ~ArvoreB();

        bool Busca( int val );
        int BuscaCasos( int, int& );

        void Insere( int val, int& );

        void Print( bool overflow = false );
        void Limpar();
};

#endif