#include <iostream>
#include "NoAVL.h"

using namespace std;

class ArvoreAVL
{
    private:
        NoAVL* raiz;

        void balanceamento();

        void InsereAux( int val, NoAVL* no );
        void PrintAux( NoAVL* no );

        void rotSEsq( NoAVL* no );
        void rotSDir( NoAVL* no );
        void rotDEsq( NoAVL* no );
        void rotDDir( NoAVL* no );

    public:
        ArvoreAVL();
        ~ArvoreAVL();

        void Insere( int val );

        bool Busca( int val );

        void Print();
};