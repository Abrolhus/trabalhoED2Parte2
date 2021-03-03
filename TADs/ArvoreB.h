#include <iostream>
#include "NoB.h"

using namespace std;

class ArvoreB
{
    private:
        NoB* root;

        int size;

        void printAux( NoB* no, int& layer );

        void overflow( int val, NoB* no, NoB* newNo );

        void insereAux( int val, NoB* no, bool& done, int& overflowValue, NoB*& overflowChild, NoB*& overflowNode );

    public:
        ArvoreB( int size );
        ~ArvoreB();

        bool Busca( int val );

        void Insere( int val );

        void Print();
};