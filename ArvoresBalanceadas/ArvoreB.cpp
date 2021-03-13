#include "ArvoreB.h"

#include <string>
#include <stdio.h>

ArvoreB::ArvoreB( HashTable* Hash, int size )
{
    root = NULL;
    this->size = size;
    HashRef = Hash;
}

ArvoreB::~ArvoreB()
{
    Limpar();
}

void ArvoreB::Limpar()
{
    if( root == NULL ) return;

    clearAux( root );

    root = NULL;
}
void ArvoreB::clearAux( NoB* no )
{
    if( no == NULL ) return;

    int i;
    for( i=0; i < size; i++ )
    {
        clearAux( no->getChild(i) );
    }
    clearAux( no->getChild(i) );

    delete no;
}

bool ArvoreB::Busca( int val )
{
    NoB* aux = root;

    Registro* reg_cur = &HashRef->at( val );
    Registro* reg_aux;

    while( aux != NULL )
    {
        for( int i = 0; i < size; i++ )
        {
            if( aux->get(i) == val )
                return true;
            else
            {
                reg_aux = &HashRef->at( aux->get(i) );

                if( reg_aux->getId() > reg_cur->getId() )
                {
                    aux = aux->getChild( i );
                    break;
                }
                else if( DataCompare( reg_aux->getData(), reg_cur->getData() ) == -1 )
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
    }

    return false;
}

void ArvoreB::Insere( int val )
{
    if( root == NULL )
    {
        root = new NoB(size);
        root->setLeaf();
    }

    NoB* aux = root;
    int i;

    Registro* reg_cur;
    Registro* reg_new = &HashRef->at( val );

    for( i = 0; i < size; i++ )
    {
        if( aux->get(i) != -1 )
            reg_cur = &HashRef->at( aux->get(i) ); // BUSCA REGISTRO ASSOCIADO A CHAVE AUX[i]
        if( aux->get(i) == -1 ) // INSERE SE VAZIO
        {
            if( aux->getChild(i) == NULL ) // SE NÃO POSSUI VALORES A DIREITA DE AUX-1, INSERE
            {
                aux->insert( val, i );
                return;
            }
            else
            {
                aux = aux->getChild(i);
                i = -1;
            }
        }
        else
        if( reg_cur->getId() > reg_new->getId() || DataCompare( reg_cur->getData(), reg_new->getData() ) == -1 ) // INSERE SE ESTIVER ENTRE ALGUM VALOR
        {
            if( aux->isLeaf() ) // SE NO FOLHA, OVERFLOW, SAI DO FOR
            {
                overflow( val, aux, NULL, NULL );
                return;
            }

            if( aux->getChild(i) != NULL )
            {
                aux = aux->getChild(i); // CASO NAO SEJA NO FOLHA, CONTINUA BUSCANDO LOCAL DE INSERCAO
                i = -1;
            }
        }
    }

    overflow( val, aux, NULL, NULL );
}

void ArvoreB::overflow( int val, NoB* current, NoB* left, NoB* right )
{
    if( current == NULL )
    {
        root = new NoB(size);
        current = root;
    }

    Registro* reg_cur = &HashRef->at( val );
    Registro* reg_aux;

    int i;
    for( i = 0; i < size; i++ ) // BUSCA POSICAO NA QUAL VAL SERA INSERIDO
    {
        if( current->get(i) != -1 )
            reg_aux = &HashRef->at( current->get(i) );
        if( reg_aux->getId() > reg_cur->getId() || DataCompare(reg_aux->getData(), reg_cur->getData()) == -1 || current->get(i) == -1 ) break;
    }

    current->insert( val, i );
    current->setChild( (i == size ? i-1:i), left );
    current->setChild( (i == size ? i:i+1), right );

    if( left != NULL ) left->setParent( current );
    if( right != NULL ) right->setParent( current );

    if( current->getPos() < size+1 ) return;

    int pivo = current->get( size/2 );
    NoB* newRight = new NoB(size);

    current->set( size/2, -1 );
    for( int j = (size/2)+1; j < size+1; j++ )
    {
        newRight->append( current->get(j) );
        newRight->appendChild( current->getChild(j) );

        current->set( j, -1 );
        current->setChild( j, NULL );
    }
    newRight->appendChild( current->getChild(size) );
    newRight->setLeaf( current->isLeaf() ); // SE AUX E FOLHA, NO DA DIREITA TAMBEM SERA

    current->setPos( size/2 );

    overflow( pivo, current->getParent(), current, newRight );

}

void ArvoreB::Print( bool overflow )
{
    bool of = overflow;
    int layer = 0;
    printAux( root, layer, of );
}
void ArvoreB::printAux( NoB* no, int& layer, bool& overflow)
{   
    if( no == NULL ) return;

    for( int j = 0; j < layer; j++ ) cout << "  ";
    for( int i = 0; i < size+(overflow ? 1:0); i++ )
    {
        cout << no->get( i ) << ( i==size-1+(overflow ? 1:0) ? "":", ");

        if( no->getChild(i) != NULL )
        {
            layer++;
            cout << endl;
            printAux( no->getChild(i), layer, overflow );
            layer--;
        }

    }
    cout << endl;
}