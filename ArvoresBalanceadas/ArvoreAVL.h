#ifndef ARVOREAVL_H
#define ARVOREAVL_H

#include <iostream>
#include "NoAVL.h"
#include "../HashTable.h"
#include "auxiliar.h"

using namespace std;

class ArvoreAVL
{
    private:
        NoAVL* raiz;

        void balanceamento();

        void InsereAux( int, NoAVL* );
        void PrintAux( NoAVL* );

        void rotSEsq( NoAVL* );
        void rotSDir( NoAVL* );
        void rotDEsq( NoAVL* );
        void rotDDir( NoAVL* );

        void LimparAux( NoAVL* );

        HashTable* HashRef;

    public:
        ArvoreAVL( HashTable* Hash );
        ~ArvoreAVL();

        void Insere( int );

        bool Busca( int val );

        void Print();
        void Limpar();
};

#endif