#include "ArvoreAVL.h"

#include <string>

ArvoreAVL::ArvoreAVL( HashTable* Hash )
{
    HashRef = Hash;
    raiz = nullptr;
}

ArvoreAVL::~ArvoreAVL()
{

}

void ArvoreAVL::Insere( int key )
{
    if( raiz == nullptr )
    {
        raiz = new NoAVL( key );
        raiz->setEsq(nullptr);
        raiz->setDir(nullptr);
    }
    else
        InsereAux( key, raiz );
}
void ArvoreAVL::InsereAux( int key, NoAVL* no )
{
    if( no == nullptr ) return;

    Registro* reg_cur = HashRef->get( no->get() );
    Registro* reg_new = HashRef->get( key );

    char decision = 'r';

    decision = ( 
        reg_new->getId() > reg_cur->getId() ? // COMPARA NO DE ID MAIOR
            'r':
            reg_new->getId() < reg_cur->getId() ?
                'l':
                stoi(reg_new->getData().substr(0,4)) > stoi( reg_cur->getData().substr(0,4) ) ? // COMPARA O ANO
                    'r':
                    stoi(reg_new->getData().substr(0,4)) < stoi( reg_cur->getData().substr(0,4) ) ?
                        'l':
                        stoi(reg_new->getData().substr(5,2)) > stoi( reg_cur->getData().substr(5,2) ) ? // COMPARA O MES
                            'r':
                            stoi(reg_new->getData().substr(5,2)) < stoi( reg_cur->getData().substr(5,2) ) ?
                                'l':
                                stoi(reg_new->getData().substr(8,2)) > stoi(reg_cur->getData().substr(8,2)) ? // COMPARA O DIA
                                    'r':
                                    'l'
    );

    NoAVL* prox = ( decision == 'r' ? no->dir():no->esq() );
    
    if( prox == nullptr )
    {
        NoAVL* aux = new NoAVL( key );
        aux->setDir(nullptr);
        aux->setEsq(nullptr);
        if( decision == 'r' )
            no->setDir(aux);
        else
            no->setEsq(aux);
    }

    InsereAux( key, prox );

    int fd,fe;
    fd = fe = 0;
    if( no->dir() != nullptr )
        fd = no->dir()->getFc();
    if( no->esq() != nullptr )
        fe = no->esq()->getFc();

    no->fixH();
    no->fixFc();

    if( no->getFc() == 2 )
    {
        if( fd == 1 || fd == 0 )
            rotSEsq( no );
        else if( fd == -1 )
            rotDEsq( no );
    }
    else if( no->getFc() == -2 )
    {
        if( fe == -1 || fe == 0 )
            rotSDir( no );
        else if( fe == 1 )
            rotDDir( no );
    }

}

bool ArvoreAVL::Busca( int val )
{
    NoAVL* aux = raiz;
    Registro* reg_cur = HashRef->get( val );
    Registro* reg_aux;

    while( aux != nullptr )
    {
        if( aux->get() == val ) return true;

        reg_aux = HashRef->get( aux->get() );

        if( reg_aux->getId() > reg_cur->getId() )
            aux = aux->esq();
        else if( reg_aux->getId() < reg_cur->getId() )
            aux = aux->dir();
        else
        {
            int DataComp = DataCompare( reg_aux->getData(), reg_cur->getData() );
            if( DataComp == -1 )
                aux = aux->esq();
            else if( DataComp == 1 )
                aux = aux->dir();
        }
    }

    return false;
}

void ArvoreAVL::Print()
{
    PrintAux( raiz );
}

void ArvoreAVL::PrintAux( NoAVL* no )
{
    if( no == nullptr ) return;

    // cout << no->get() << " -> fc = " << no->getFc() << " h = " << no->getH() << endl;
    no->print();

    // cout << "e: ";
    PrintAux( no->esq() );
    // cout << "d: ";
    PrintAux( no->dir() );
}

void ArvoreAVL::rotSEsq( NoAVL* no )
{
    // salva endereço de no->dir
    // e cria novo nó substituto de "no"
    NoAVL* aux = no->dir();
    NoAVL* bckp = new NoAVL();

    // aponta direita do no pra esquerda de aux
    // e ajusta o novo fc do no
    no->setDir( aux->esq() );
    no->fixFc();
    no->fixH();

    // atribui conteudo de no ao conteudo
    // do no substituto
    *( bckp ) = *( no );

    // aponta esquerda do aux para endereço do no substituto
    // e ajusta o novo fc do aux
    aux->setEsq( bckp );
    aux->fixFc();
    aux->fixH();

    // muda o conteudo do no atual para conteudo de aux
    // para que o endereço atual continue o mesmo
    // porem seu conteudo seja outro
    *( no ) = *( aux );

    // aux já não é mais util
    // pois foi clonado e seu clone substituiu no
    delete aux;
}
void ArvoreAVL::rotSDir( NoAVL* no )
{
    NoAVL* aux = no->esq();
    NoAVL* bckp = new NoAVL();

    no->setEsq( aux->dir() );
    no->fixFc();
    no->fixH();

    *( bckp ) = *( no );

    aux->setDir( bckp );
    aux->fixFc();
    aux->fixH();

    *( no ) = *( aux );
}
void ArvoreAVL::rotDEsq( NoAVL* no )
{
    rotSDir( no->dir() );
    rotSEsq( no );
    // NoAVL* aux = no->dir();
    // NoAVL* aux2 = aux->esq();

    // no->setDir( aux2->esq() );
    // aux->setEsq( aux2->dir() );
    // aux2->setEsq( no );
    // aux2->setDir( aux );
}
void ArvoreAVL::rotDDir( NoAVL* no )
{
    rotSEsq( no->esq() );
    rotSDir( no );
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