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
    // cerr << "BUSCA NA ARVORE B PELO VALOR " << val << endl;
    return AuxBusca( root, val, comp );    
}
int ArvoreB::AuxBusca( NoB* no, int val, int& comp )
{
    if( no == nullptr ) return 0;

    int soma = 0;
    int i = 0;
    for( i = 0; i < no->getPos(); i++ )
    {
        Registro atual = HashRef->at( no->get(i) );
        comp++;
        if( atual.getCode() > val )
            break;
        else if( atual.getCode() == val )
        {
            soma += atual.getCasos();
            soma += AuxBusca( no->getChild(i), val, comp );
        }
    }

    return soma + AuxBusca( no->getChild(i), val, comp );
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
        root->append( HashRef->getIndexOf(val.getCode(), val.getData() ) );
        root->appendChild(nullptr);
        root->appendChild(nullptr);
        root->setLeaf(true);
        return;
    }

    InsereAux( val, comp, root );
    // if( root == nullptr )
    // {
    //     NoB* no = new NoB(size);
    //     no->setLeaf(true);
    //     no->append( HashRef->getIndexOf(val.getCode(), val.getData()) );
    //     no->appendChild( nullptr );
    //     no->appendChild( nullptr );

    //     root = no;

    //     // cerr << "Gerada raiz" << endl;
    //     // cerr << "Inserido " << val << endl;
    //     return;
    // }

    // // cerr << "Inserindo " << val << endl;
    // InsereAux( val, comp, root );

}
void ArvoreB::InsereAux( Registro val, int& comp, NoB* no )
{
    if( no == nullptr ) return;

    while( !no->isLeaf() )
    {
        Registro atual;
        int i = 0;
        for( i = 0; i < no->getPos(); i++ )
        {
            atual = HashRef->at( no->get(i) );
            comp++;
            if( val.getCode() < atual.getCode() )
            {
                InsereAux( val, comp, no->getChild(i) );
                return;
            }
            else
            if( ( val.getCode() == atual.getCode() && DataCompare( val.getData(), atual.getData() ) == 1 ) )
            {
                comp++;
                InsereAux( val, comp, no->getChild(i) );
                return;
            }
        }
        // cout << "no " << (no->isLeaf() ? "folha":"nao folha") << endl;
        // cout << "i " << i << endl;
        InsereAux( val, comp, no->getChild(i) );
        return;
    }

    overflow( val, no, nullptr, nullptr, comp );
}

void ArvoreB::overflow( Registro val, NoB* current, NoB* left, NoB* right, int& comp )
{
    if( current == nullptr )
    {
        // cout << "nullnode" << endl;
        current = new NoB(size);
        root = current;
        root->setLeaf(false);
        root->append( HashRef->getIndexOf( val.getCode(),val.getData() ) );
        root->appendChild(left);
        root->appendChild(right);
        if( left != nullptr ) left->setParent(current);
        if( right != nullptr ) right->setParent(current);
        return;
    }

    Registro atual;

    int i = 0;
    for( i = 0; i < current->getPos(); i++ )
    {
        atual = HashRef->at( current->get(i) );
        comp++;
        if( val.getCode() < atual.getCode() || ( val.getCode() == atual.getCode() && DataCompare( val.getData(), atual.getData() ) == 1 ) )
            break;
    }

    // cout << "Inserindo " << val << " em " << i << endl;

    // cout << "tams v " << current->getPos() << endl;
    // cout << "tams c " << current->getPosChild() << endl;
    current->insert( HashRef->getIndexOf( val.getCode(), val.getData() ), i );
    current->setChild(i, left);
    current->insertChild( i+1, right );
    // cout << "tams f v" << current->getPos() << endl;
    // cout << "tams f c" << current->getPosChild() << endl;
    
    if( current->getPos() < size ) return;

    NoB* newNode = new NoB(size);
    newNode->setLeaf( current->isLeaf() );
    newNode->setParent( current->getParent() );

    i = current->getPos()/2;
    Registro save = HashRef->at( current->get( i ) );
    // cout << "pivo " << save << endl;
    // cout << "numero de childs " << current->getPosChild() << endl;

    for( int j=i+1 ; j < current->getPos(); )
    {
        // cout << "jogando pra la " << current->get(j) << endl;
        newNode->append( current->get(j) );
        newNode->appendChild( current->getChild(j) );

        current->pop(j);
        current->popChild(j);
    }
    newNode->appendChild( current->getChild(i+1) );
    current->popChild(i+1);
    current->pop( i );

    left = current;
    // cout << "chamando ov " << endl;
    overflow( save, current->getParent(), left, newNode, comp );

    for( int i = 0; i < newNode->getPosChild(); i++ )
        if( newNode->getChild(i) != nullptr )
        {
            newNode->getChild(i)->setParent(newNode);
        }
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
    int i = 0;
    for( i = 0; i < no->getPos(); i++ )
        soma += 1+CountAux( no->getChild(i) );

    return soma+CountAux( no->getChild(i) );  
}