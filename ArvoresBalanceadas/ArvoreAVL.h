#ifndef ARVOREAVL_H
#define ARVOREAVL_H

#include <iostream>
#include "NoAVL.h"
#include "../HashTable/HashTable.h"
#include "auxiliar.h"

using namespace std;

class ArvoreAVL
{
    private:
        NoAVL* raiz;

        void balanceamento();

        NoAVL* InsereAux( Registro, NoAVL*, int& );
        void PrintAux( NoAVL* );

        NoAVL* rotSEsq( NoAVL* );
        NoAVL* rotSDir( NoAVL* );
        NoAVL* rotDEsq( NoAVL* );
        NoAVL* rotDDir( NoAVL* );

        void LimparAux( NoAVL* );

        int BuscaAux( NoAVL*, int, int& );

        HashTable* HashRef;

    public:
        ArvoreAVL( HashTable* Hash );
        ~ArvoreAVL();

        void Insere( Registro, int& );

        bool Busca( int val );
        int BuscaCasos( int val, int& );

        void Print();
        void Limpar();

        int Count();
};

#endif
