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

    delete no;

    no = nullptr;
}

void ArvoreAVL::Insere( int key, int& comp )
{
    this->raiz = InsereAux( key, raiz, comp );
}

NoAVL* ArvoreAVL::InsereAux( int key, NoAVL* no, int& comp )
{
    if ( no == nullptr )
    {
        return new NoAVL( key );
    }

    Registro* reg_cur = &HashRef->at( no->get() );
    Registro* reg_new = &HashRef->at( key );

    // char decision = 'r';

    if( reg_new->getId() > reg_cur->getId() )
        no->setDir( InsereAux( key, no->dir(), comp));
        // decision = 'r';
    else if( reg_new->getId() < reg_cur->getId() )
        no->setEsq( InsereAux( key, no->esq(), comp));
        // decision = 'l';
    else if( stoi(reg_new->getData().substr(0,4)) > stoi( reg_cur->getData().substr(0,4) ) )
        no->setDir( InsereAux( key, no->dir(), comp));
        // decision = 'r';
    else if( stoi(reg_new->getData().substr(0,4)) < stoi( reg_cur->getData().substr(0,4) ) )
        no->setEsq( InsereAux( key, no->esq(), comp));
        // decision = 'l';
    else if( stoi(reg_new->getData().substr(5,2)) > stoi( reg_cur->getData().substr(5,2) ) )
        no->setDir( InsereAux( key, no->dir(), comp));
        // decision = 'r';
    else if( stoi(reg_new->getData().substr(5,2)) < stoi( reg_cur->getData().substr(5,2) ) )
        no->setEsq( InsereAux( key, no->esq(), comp));
        // decision = 'l';
    else if( stoi(reg_new->getData().substr(8,2)) > stoi(reg_cur->getData().substr(8,2)) )
        no->setDir( InsereAux( key, no->dir(), comp));
        // decision = 'r';
    else
        no->setEsq( InsereAux( key, no->esq(), comp ));
        // decision = 'l';
    comp++;

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
            no = rotSEsq( no );
        else if( fd == -1 )
            no = rotDEsq( no );
    }
    else if( no->getFc() == -2 )
    {
        if( fe == -1 || fe == 0 )
            no = rotSDir( no );
        else if( fe == 1 )
            no = rotDDir( no );
    }
    return no;
}

bool ArvoreAVL::Busca( int val )
{
    NoAVL* aux = raiz;
    Registro reg_cur = HashRef->at( val );
    Registro reg_aux;
    int comp;

    while( aux != nullptr )
    {
        if( aux->get() == val ) return true;

        reg_aux = HashRef->at( aux->get() );

        if( reg_aux.getId() > reg_cur.getId() )
            aux = aux->esq();
        else if( reg_aux.getId() < reg_cur.getId() )
            aux = aux->dir();
        else
        {
            int DataComp = DataCompare( reg_aux.getData(), reg_cur.getData() );
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
        // cerr << "Comparando " << val << " com " << atual << endl;
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

NoAVL* ArvoreAVL::rotSEsq( NoAVL* no )
{
    // salva endereço de no->dir
    // e cria novo nó substituto de "no"
    NoAVL* aux = no->dir();

    // aponta direita do no pra esquerda de aux
    // e ajusta o novo fc do no
    no->setDir( aux->esq() );
    no->fixFc();
    no->fixH();

    // aponta esquerda do aux para endereço do no substituto
    // e ajusta o novo fc do aux
    aux->setEsq( no );
    aux->fixFc();
    aux->fixH();

    return aux;
}
NoAVL* ArvoreAVL::rotSDir( NoAVL* no )
{
    NoAVL* aux = no->esq();

    no->setEsq( aux->dir() );
    no->fixFc();
    no->fixH();

    aux->setDir( no );
    aux->fixFc();
    aux->fixH();

    return aux;
}
NoAVL* ArvoreAVL::rotDEsq( NoAVL* no )
{
    no->setDir( rotSDir( no->dir() ) );
    return rotSEsq( no );
    // NoAVL* aux = no->dir();
    // NoAVL* aux2 = aux->esq();

    // no->setDir( aux2->esq() );
    // aux->setEsq( aux2->dir() );
    // aux2->setEsq( no );
    // aux2->setDir( aux );
}
NoAVL* ArvoreAVL::rotDDir( NoAVL* no )
{
    no->setEsq( rotSEsq( no->esq() ) );
    return rotSDir( no );
}

int ArvoreAVL::Count()
{
    return 0;
}