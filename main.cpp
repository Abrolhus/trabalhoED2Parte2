#include "TADs\ArvoreB.h"
#include "TADs\ArvoreAVL.h"
#include "TADs\interface.h"

int main( int argc, char** argv ){

    ArvoreAVL avlTree;
    ArvoreB bTree( 8 );

    interface( avlTree, bTree );

    return 0;
    
}
