#include "TADs\ArvoreB.h"

int main( int argc, char** argv ){

    ArvoreB arvore( 4 );

    arvore.Insere( 10 );
    arvore.Insere( 58 );
    arvore.Insere( 37 );
    arvore.Insere( 15 );
    arvore.Insere( 5 );
    arvore.Insere( 16 );
    arvore.Insere( 43 );
    arvore.Insere( 2 );
    arvore.Insere( 100 );
    arvore.Insere( 400 );
    arvore.Insere( 12 );

    arvore.Print(true);

    return 0;
}
