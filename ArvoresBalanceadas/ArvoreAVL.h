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

        void InsereAux( int, NoAVL*, int& );
        void PrintAux( NoAVL* );

        void rotSEsq( NoAVL* );
        void rotSDir( NoAVL* );
        void rotDEsq( NoAVL* );
        void rotDDir( NoAVL* );

        void LimparAux( NoAVL* );

        int BuscaAux( NoAVL*, int, int& );

        HashTable* HashRef;

    public:
        ArvoreAVL( HashTable* Hash );
        ~ArvoreAVL();

        void Insere( int, int& );

        bool Busca( int val );
        int BuscaCasos( int val, int& );

        void Print();
        void Limpar();
};

#endif