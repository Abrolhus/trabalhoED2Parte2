#include "ArvoreAVL.h"

ArvoreAVL::ArvoreAVL()
{
    raiz = nullptr;
}

ArvoreAVL::~ArvoreAVL()
{

}

void ArvoreAVL::Insere( int val )
{
    if( raiz == nullptr )
    {
        raiz = new NoAVL(val);
        raiz->setEsq(nullptr);
        raiz->setDir(nullptr);
    }
    else
        InsereAux( val, raiz );
}
void ArvoreAVL::InsereAux( int val, NoAVL* no )
{
    if( no == nullptr ) return;

    NoAVL* prox = ( no->get() > val ? no->esq():no->dir() );
    
    if( prox == nullptr )
    {
        NoAVL* aux = new NoAVL(val);
        aux->setDir(nullptr);
        aux->setEsq(nullptr);
        if( no->get() > val )
            no->setEsq(aux);
        else
            no->setDir(aux);
    }

    InsereAux( val, prox );

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
    while( aux != nullptr )
        if( aux->get() > val )
            aux = aux->esq();
        else if( aux->get() < val )
            aux = aux->dir();
        else
            return true;
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