#include "ArvoreB.h"

#include <string>

ArvoreB::ArvoreB( HashTable* Hash, int size )
{
    root = new NoB(size);
    root->setLeaf();
    this->size = size;
    HashRef = Hash;
}

ArvoreB::~ArvoreB()
{

}

bool ArvoreB::Busca( int val )
{
    NoB* aux = root;

    Registro* reg_cur = HashRef->get( val );
    Registro* reg_aux;

    while( aux != nullptr )
    {
        for( int i = 0; i < size; i++ )
        {
            if( aux->get(i) == val )
                return true;
            else
            {
                reg_aux = HashRef->get( aux->get(i) );

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
    NoB* aux = root;
    int i;

    Registro* reg_cur;
    Registro* reg_new = HashRef->get( val );

    for( i = 0; i < size; i++ )
    {
        reg_cur = HashRef->get( aux->get(i) ); // BUSCA REGISTRO ASSOCIADO A CHAVE AUX[i]

        if( aux->get(i) == -1 ) // INSERE SE VAZIO
        {
            if( aux->getChild(i) == nullptr ) // SE NÃO POSSUI VALORES A DIREITA DE AUX-1, INSERE
            {
                aux->insert( val, i );
                cout << "Inserido " << val << endl;
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
                overflow( val, aux, nullptr, nullptr );
                return;
            }

            if( aux->getChild(i) != nullptr )
            {
                aux = aux->getChild(i); // CASO NAO SEJA NO FOLHA, CONTINUA BUSCANDO LOCAL DE INSERCAO
                i = -1;
            }
        }
    }

    overflow( val, aux, nullptr, nullptr );
    // cout << "ERROR: O vetor foi percorrido e nada aconteceu" << endl;
}

void ArvoreB::overflow( int val, NoB* current, NoB* left, NoB* right )
{
    if( current == nullptr )
    {
        root = new NoB(size);
        current = root;
    }

    Registro* reg_cur = HashRef->get( val );
    Registro* reg_aux;

    int i;
    for( i = 0; i < size; i++ ) // BUSCA POSICAO NA QUAL VAL SERA INSERIDO
    {
        reg_aux = HashRef->get( current->get(i) );
        if( reg_aux->getId() > reg_cur->getId() || DataCompare(reg_aux->getData(), reg_cur->getData()) == -1 || current->get(i) == -1 ) break;
    }

    current->insert( val, i );
    current->setChild( (i == size ? i-1:i), left );
    current->setChild( (i == size ? i:i+1), right );

    if( left != nullptr ) left->setParent( current );
    if( right != nullptr ) right->setParent( current );

    cout << "Inserido " << val << endl;
    // Print(true);
    // cout << "pos: " << current->getPos() << endl;
    if( current->getPos() < size+1 ) return;

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

    current->setPos( size/2 );

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

/**
 * @param data01 Data principal
 * @param data02 Data a ser comparada
 * @return -1 Caso data02 < data01 | 1 Caso data02 > data01 | 0 Caso data02 = data01  
 */
int DataCompare( string data01, string data02 )
{
    return (
        stoi(data01.substr(0,4)) < stoi(data02.substr(0,4)) ?
            1:
            stoi(data01.substr(0,4)) > stoi(data02.substr(0,4)) ?
                -1:
                stoi(data01.substr(5,2)) < stoi(data02.substr(5,2)) ?
                    1:
                    stoi(data01.substr(5,2)) > stoi(data02.substr(5,2)) ?
                        -1:
                        stoi(data01.substr(8,2)) < stoi(data02.substr(8,2)) ?
                            1:
                            stoi(data01.substr(8,2)) > stoi(data02.substr(8,2)) ?
                                -1:
                                0
    );
}