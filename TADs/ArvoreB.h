#ifndef ARVOREB_H
#define ARVOREB_H

#include <iostream>
#include "NoB.h"

using namespace std;

class ArvoreB
{
    private:
        NoB* root;

        int size;

        void printAux( NoB* no, int& layer, bool& overflow );

        void overflow( int val, NoB* current, NoB* left, NoB* right );

    public:
        ArvoreB( int size );
        ~ArvoreB();

        bool Busca( int val );

        void Insere( int val );

        void Print( bool overflow = false );
};

#endif