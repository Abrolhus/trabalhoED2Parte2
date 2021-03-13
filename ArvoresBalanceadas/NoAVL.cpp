#include "NoAVL.h"

NoAVL::NoAVL(){
    fator = 0; 
    h = 0;
    noDir = nullptr;
    noEsq = nullptr;
}

NoAVL::NoAVL( int val ){
    valor = val; 
    fator = 0; 
    h = 0;
    noDir = nullptr;
    noEsq = nullptr;
}

NoAVL::~NoAVL(){
    // delete noDir;
    // delete noEsq;
    // noDir = nullptr;
    // noEsq = nullptr;
}

void NoAVL::fixFc()
{
    int hd,he;
    hd = he = -1;
    if( noDir != nullptr )
        hd = noDir->getH();
    if( noEsq != nullptr )
        he = noEsq->getH();
    fator = hd-he;
}

void NoAVL::fixH(){ 
    int hd,he;
    hd = he = -1;
    if( noDir != nullptr )
        hd = noDir->getH();
    if( noEsq != nullptr )
        he = noEsq->getH();
    h = ( he > hd ? he:hd )+1;
}

void NoAVL::print(){ 
    cout << ( noEsq != nullptr ? noEsq->get():-1 )
    << "(h:"
    << ( noEsq != nullptr ? noEsq->getH():-1 )
    << ",f:"
    << ( noEsq != nullptr ? noEsq->getFc():-1 )
    << ")"
    << " <- "
    << valor
    << "(h:"
    << h
    << ",f:"
    << fator
    << ")"
    << " -> "
    << ( noDir != nullptr ? noDir->get():-1 )
    << "(h:"
    << ( noDir != nullptr ? noDir->getH():-1 )
    << ",f:"
    << ( noDir != nullptr ? noDir->getFc():-1 )
    << ")"
    << endl; 
}