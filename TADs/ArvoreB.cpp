#include "ArvoreB.h"

ArvoreB::ArvoreB( int size )
{
    root = new NoB(size);
    root->setLeaf();
    this->size = size;
}

ArvoreB::~ArvoreB()
{

}

bool ArvoreB::Busca( int val )
{
    NoB* aux = root;

    while( aux != nullptr )
    {
        for( int i = 0; i < size; i++ )
        {
            if( aux->get(i) == val )
                return true;
            else if( aux->get(i) > val )
            {
                aux = aux->getChild( i );
                break;
            }
            else if( i == size-1 )
            {
                aux = aux->getChild(size);
                break;
            }
        }
    }

    return false;
}

void ArvoreB::Insere( int val )
{
    // if( root == nullptr )
    // {
    //     root = new NoB( size );
    //     root->setLeaf();
    // }

    // bool done = false;
    // int ov = -1;
    // NoB* oc = root;
    // NoB* on = root;
    // insereAux( val, root, done, ov, oc, on );
    // return;

    NoB* aux = root;
    int i;

    for( i = 0; i < size; i++ )
    {
        if( aux->get(i) == -1 ) // INSERE SE VAZIO
        {
            aux->insert( val, i );
            cout << "Inserido " << val << endl;
            return;
        }

        if( aux->get(i) > val ) // INSERE SE ESTIVER ENTRE ALGUM VALOR
        {
            // if( aux->full() ) // SE CHEIO, BUSCA NO FILHO OU COMEÇA OVERFLOW
            // {
                if( aux->isLeaf() ) // SE NO FOLHA, OVERFLOW, SAI DO FOR
                    break;

                aux = aux->getChild(i); // CASO NAO SEJA NO FOLHA, CONTINUA BUSCANDO LOCAL DE INSERCAO
                i = -1;
            // }
            // else
            // {
                // aux->insert( val );
                // cout << "Inserido " << val << endl;
                // return; // SE NÃO OVERFLOW, INSERIU COM SUCESSO DE MANEIRA ORDENADA
            // }
        }
    }

    cout << "Overflow" << endl;
    overflow( val, aux, nullptr, nullptr );
}

void ArvoreB::overflow( int val, NoB* current, NoB* left, NoB* right )
{
    if( current == nullptr )
    {
        root = new NoB(size);
        current = root;
    }

    int i;
    for( i = 0; i < size; i++ ) // BUSCA POSICAO NA QUAL VAL SERA INSERIDO
        if( current->get(i) > val || current->get(i) == -1 ) break;

    current->insert( val );
    current->setChild( i, left );
    current->setChild( i+1, right );

    cout << "Inserido " << val << endl;

    if( current->getPos() <= size ) return;

    int pivo = current->get( size/2 );
    NoB* newRight = new NoB(size);

    current->set( size/2, -1 );
    for( int j = (size/2)+1; j < size+1; j++ )
    {
        newRight->append( current->get(j) );
        newRight->appendChild( current->getChild(j) );

        current->set( j, -1 );
        current->setChild( j, nullptr );
    }
    newRight->appendChild( current->getChild(size) );

    newRight->setLeaf( current->isLeaf() ); // SE AUX E FOLHA, NO DA DIREITA TAMBEM SERA

    overflow( pivo, current->getParent(), current, newRight );

}

void ArvoreB::Print( bool overflow )
{
    bool of = overflow;
    int layer = 0;
    printAux( root, layer, of );
}
void ArvoreB::printAux( NoB* no, int& layer, bool& overflow )
{   
    if( no == nullptr ) return;

    for( int j = 0; j < layer; j++ ) cout << "  ";
    for( int i = 0; i < size+(overflow ? 1:0); i++ )
    {
        cout << no->get( i ) << ( i==size-1+(overflow ? 1:0) ? "":", ");

        if( no->getChild(i) != nullptr )
        {
            layer++;
            cout << endl;
            printAux( no->getChild(i), layer, overflow );
            layer--;
        }

    }
    cout << endl;
}