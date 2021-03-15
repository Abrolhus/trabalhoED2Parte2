#include "ArvoreB.h"

ArvoreB::ArvoreB( HashTable* Hash, int size )
{
    root = nullptr;
    this->size = size;
    HashRef = Hash;
}

ArvoreB::~ArvoreB()
{
    Limpar();
}

void ArvoreB::Limpar()
{
    root = nullptr;
    // clearAux( root );
}
void ArvoreB::clearAux( NoB* no )
{
    if( no == nullptr ) return;

    int i;
    for( i = 0; i < no->getPos(); i++ )
        clearAux( no->getChild(i) );
    clearAux( no->getChild(i) );
    
    delete no;
    no = nullptr;
}

bool ArvoreB::Busca( int val )
{
    NoB* aux = root;

    Registro* reg_cur = &HashRef->at( val );
    Registro* reg_aux;

    int comp;

    while( aux != nullptr )
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

int ArvoreB::BuscaCasos( int val, int& comp )
{
    cerr << "BUSCA NA ARVORE B PELO VALOR " << val << endl;
    return AuxBusca( root, val, comp );    
}
int ArvoreB::AuxBusca( NoB* no, int val, int& comp )
{
    if( no == nullptr )
    {
        cerr << "Folha" << endl;
        return 0;
    }

    NoB* aux = no;

    int soma = 0;
    int i = 0;
    for( i = 0; i < no->getPos(); i++ )
    {
        cerr << "Comparando " << val;
        int atual = HashRef->at( aux->get(i) ).getCode();
        cerr << " com " << atual << endl;
        comp++;
        if( atual > val )
        {
            return AuxBusca( no->getChild(i), val, comp );
        }
        else if( atual == val )
        {
            soma += HashRef->at( aux->get(i) ).getCasos();
            soma += AuxBusca( aux->getChild(i), val, comp );
        }
    }

    return soma + AuxBusca( aux->getChild(i), val, comp );
    // if( no == nullptr ) return 0;

    // int soma = 0;
    // int i;
    // for( i=0; i < size; i++ )
    // {
    //     if( no->get(i) > val ) break; // SE CODIGO MAIOR PODE SAIR
    //     if( no->get(i) == val ) 
    //     {
    //         if( !no->isLeaf() )
    //             soma += AuxBusca( no->getChild(i), val, comp );
    //         soma += HashRef->at( no->get(i) ).getCasos(); // SE CODIGO CORRESPONDE, SOMA NUMERO DE CASOS DOS FILHOS DA ESQUERDA E DOS DA DIREITA
    //     }
    //     comp++;
    //     // SE NO MENOR, CONTINUA BUSCA
    // }
    // comp++;

    // if( !no->isLeaf() )
    //     soma += AuxBusca( no->getChild(i), val, comp );

    // return soma;
}

void ArvoreB::Insere( Registro val, int& comp )
{
    if( root == nullptr )
    {
        root = new NoB(size);
        root->setLeaf(true);
        root->append( HashRef->getIndexOf( val.getCode(), val.getData() ) );
        root->appendChild(nullptr);
        return;
    }

    InsereAux( val, comp, root );
}
void ArvoreB::InsereAux( Registro val, int& comp, NoB* no )
{
    Registro atual;
    while( !no->isLeaf() )
    {
        int i = 0;
        for( i = 0; i < no->getPos(); i++ )
        {
            atual = HashRef->at( no->get(i) );
            if( (val.getCode() < atual.getCode()) || ( val.getCode() == atual.getCode() && DataCompare( val.getData(), atual.getData() ) == 1 ) )
            {
                InsereAux( val, comp, no->getChild(i) );
                return;
            }
        }
        InsereAux( val, comp, no->getChild(i) );
        return;
    }

    overflow( val, no, nullptr, nullptr, comp );
}

void ArvoreB::overflow( Registro val, NoB* current, NoB* left, NoB* right, int& comp )
{
    if( current == nullptr )
    {
        current = new NoB(size);
        current->setLeaf(false);
        current->append( HashRef->getIndexOf( val.getCode(), val.getData() ) );
        current->appendChild(left);
        current->appendChild(right);
        return;
    }

    Registro atual;

    int i = 0;
    for( i = 0; i < current->getPos(); i++ )
    {
        atual = HashRef->at( current->get( i ) );
        if( (val.getCode() < atual.getCode()) || ( val.getCode() == atual.getCode() && DataCompare( val.getData(), atual.getData() ) == 1 ) )
            break;
    }

    current->insert( HashRef->getIndexOf( val.getCode(), val.getData() ), i );
    current->insertChild( i+1, right );
    current->setChild( i, left );

    if( left != nullptr ) left->setParent( current );
    if( right != nullptr ) right->setParent( current );

    if( current->getPos() < size ) return;

    Registro subir = HashRef->at( current->get( current->getPos()/2 ) );
    NoB* novo = new NoB(size);
    novo->setLeaf(current->isLeaf());

    int j = 0;
    for( j = (current->getPos()/2)+1; j < current->getPos(); )
    {
        novo->append( current->get(j) );
        novo->appendChild( current->getChild(j) );

        current->pop(j);
        current->popChild(j);
    }
    current->popChild(j);
    current->pop(j-1);

    overflow( subir, current->getParent(), left, novo, comp );

}

void ArvoreB::Print( bool overflow )
{
    // if( root == nullptr ) return;
    // for( int i = 0; i < root->getPos(); i++ )
    //     cout << root->get(i) << endl;
    bool of = overflow;
    int layer = 0;
    printAux( root, layer, of );
}
void ArvoreB::printAux( NoB* no, int& layer, bool& overflow)
{   
    if( no == nullptr ) return;

    for( int j = 0; j < layer; j++ ) cout << "  ";
    
    int i;
    for( i = 0; i < no->getPos(); i++ )
    {
        int code = ( no->get(i) == 0 ? -1:HashRef->at(no->get(i)).getCode() );
        string data = ( no->get(i) == 0 ? "-1":HashRef->at(no->get(i)).getData() );
        cout << no->get( i ) << "[ " << code << "," << data << " ]" << ( i==no->getPos()-1 ? "":", ");

        if( no->getChild(i) != nullptr )
        {
            layer++;
            cout << endl;
            printAux( no->getChild(i), layer, overflow );
            cout << endl;
            layer--;
            for( int j = 0; j < layer; j++ ) cout << "  ";
        }

    }

    if( no->getChild(i) != nullptr )
    {
        layer++;
        cout << endl;
        printAux( no->getChild(i), layer, overflow );
        cout << endl;
        layer--;
    }
}

int ArvoreB::Count()
{
    return CountAux( root );
}
int ArvoreB::CountAux( NoB* no )
{
    if( no == nullptr ) return 0;

    int soma = 0;
    int i;
    for( i = 0; i < no->getPos(); i++ )
        soma += 1+CountAux( no->getChild(i) );

    return soma+CountAux( no->getChild(i) );  
}