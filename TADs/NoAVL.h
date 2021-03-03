#include <iostream>

using namespace std;

class NoAVL
{
    private:
        NoAVL* noEsq;
        NoAVL* noDir;

        int fator;
        int valor;
        int h;

    public:
        NoAVL();
        NoAVL( int val );
        ~NoAVL();

        NoAVL* esq(){ return noEsq; }
        NoAVL* dir(){ return noDir; }

        void setEsq( NoAVL* no ){ noEsq = no; }
        void setDir( NoAVL* no ){ noDir = no; }

        int get(){ return valor; }
        void set( int val ){ valor = val; }

        int getFc(){ return fator; }
        void setFc( int val ){ fator = val; }

        int getH(){ return h; }
        void setH( int val ){ h = val; }

        void fixFc();
        void fixH();

        void print();
};