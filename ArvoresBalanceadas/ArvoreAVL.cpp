#include "ArvoreAVL.h"

ArvoreAVL::ArvoreAVL( HashTable* Hash )
{
    HashRef = Hash;
    raiz = nullptr;
}

ArvoreAVL::~ArvoreAVL()
{
    Limpar();
}

void ArvoreAVL::Limpar()
{
    // delete raiz;
    // raiz = nullptr;
    // if( raiz == nullptr ) return;

    LimparAux(raiz);
    raiz = nullptr;
}
void ArvoreAVL::LimparAux( NoAVL* no )
{
    if( no == nullptr ) return;

    LimparAux(no->esq());
    LimparAux(no->dir());

    cerr << "Deletando " << no->get() << endl;

    delete no;

    no = nullptr;
}

void ArvoreAVL::Insere( int key, int& comp )
{
    if( raiz == nullptr )
    {
        raiz = new NoAVL( key );
    }
    else
        InsereAux( key, raiz, comp );
}
void ArvoreAVL::InsereAux( int key, NoAVL* no, int& comp )
{
    if( no == nullptr ) return;

    Registro* reg_cur = &HashRef->at( no->get() );
    Registro* reg_new = &HashRef->at( key );

    char decision = 'r';

    if( reg_new->getId() > reg_cur->getId() )
        decision = 'r';
    else if( reg_new->getId() < reg_cur->getId() )
        decision = 'l';
    else if( stoi(reg_new->getData().substr(0,4)) > stoi( reg_cur->getData().substr(0,4) ) )
        decision = 'r';
    else if( stoi(reg_new->getData().substr(0,4)) < stoi( reg_cur->getData().substr(0,4) ) )
        decision = 'l';
    else if( stoi(reg_new->getData().substr(5,2)) > stoi( reg_cur->getData().substr(5,2) ) )
        decision = 'r';
    else if( stoi(reg_new->getData().substr(5,2)) < stoi( reg_cur->getData().substr(5,2) ) )
        decision = 'l';
    else if( stoi(reg_new->getData().substr(8,2)) > stoi(reg_cur->getData().substr(8,2)) )
        decision = 'r';
    else
        decision = 'l';

    comp++;

    NoAVL* prox = ( decision == 'r' ? no->dir():no->esq() );
    
    if( prox == nullptr )
    {
        NoAVL* aux = new NoAVL( key );
        if( decision == 'r' )
            no->setDir(aux);
        else
            no->setEsq(aux);
    }

    InsereAux( key, prox, comp );

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
    Registro* reg_cur = &HashRef->at( val );
    Registro* reg_aux;
    int comp;

    while( aux != nullptr )
    {
        if( aux->get() == val ) return true;

        reg_aux = &HashRef->at( aux->get() );

        if( reg_aux->getId() > reg_cur->getId() )
            aux = aux->esq();
        else if( reg_aux->getId() < reg_cur->getId() )
            aux = aux->dir();
        else
        {
            int DataComp = DataCompare( reg_aux->getData(), reg_cur->getData(), comp );
            if( DataComp == -1 )
                aux = aux->esq();
            else if( DataComp == 1 )
                aux = aux->dir();
        }
    }

    return false;
}

int ArvoreAVL::BuscaCasos( int val, int& comp )
{
    NoAVL* aux = raiz;

    while( aux != nullptr )
    {
        int atual = HashRef->at( aux->get() ).getCode();
        cout << "Comparando " << val << " com " << atual << endl;
        if( atual > val )
            aux = aux->esq();
        else if( atual < val )
            aux = aux->dir();
        else
            return BuscaAux( aux, val, comp );
        comp++;
    }

    return 0;
}
int ArvoreAVL::BuscaAux( NoAVL* no, int val, int& comp )
{
    if( no == nullptr ) return 0;
    
    Registro atual = HashRef->at( no->get() );

    if( atual.getCode() != val )
        return 0;

    return BuscaAux( no->esq(), val, comp ) + BuscaAux( no->dir(), val, comp ) + atual.getCasos();
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

    (*bckp) = (*no);

    // aponta esquerda do aux para endereço do no substituto
    // e ajusta o novo fc do aux
    aux->setEsq( bckp );
    aux->fixFc();
    aux->fixH();

    (*no) = (*aux);

    delete aux;
    aux = nullptr;
}
void ArvoreAVL::rotSDir( NoAVL* no )
{
    NoAVL* aux = no->esq();
    NoAVL* bckp = new NoAVL();

    no->setEsq( aux->dir() );
    no->fixFc();
    no->fixH();

    (*bckp) = (*no);

    aux->setDir( bckp );
    aux->fixFc();
    aux->fixH();

    (*no) = (*aux);

    delete aux;
    aux = nullptr;
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