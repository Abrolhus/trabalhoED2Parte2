#include "NoB.h"

NoB::NoB( int n )
{
    size = n;
    pos = 0;
    posChild = 0;
    leaf = false;
    parent = nullptr;
    values = new int[n+1]; // RESERVA 1 SLOT PARA OVERFLOW
    childs = new NoB*[n+2];

    int i;
    for( i = 0; i < n+1; i++ )
    {
        values[i] = -1;
        childs[i] = nullptr;
    }
    childs[i] = nullptr;
}

NoB::~NoB()
{
    delete [] childs;
    delete [] values;
}

int NoB::get( int i )
{
    return values[i];
}

void NoB::set( int i, int val )
{
    values[i] = val;
}

NoB* NoB::getChild( int i )
{
    return childs[i];
}

void NoB::setChild( int i, NoB* no )
{
    childs[i] = no;
}

void NoB::appendChild( NoB* no )
{
    childs[posChild] = no;
    posChild++;
}

int NoB::getPos()
{
    return pos;
}
int NoB::getPosChild()
{
    return posChild;
}

void NoB::setPos( int val )
{
    pos = val;
}

void NoB::setPosChild( int val )
{
    posChild = val;
}

bool NoB::isLeaf()
{
    return leaf;
}

void NoB::setLeaf( bool x )
{
    leaf = x;
}

bool NoB::full()
{
    return ( pos >= size );
}

void NoB::setParent( NoB* no )
{
    parent = no;
}

NoB* NoB::getParent()
{
    return parent;
}

void NoB::append( int val )
{
    if( pos > size )
    {
        cout << "Não foi possível inserir valor " << val << " no nó ( overflow )" << endl;
        exit(1);
    }

    values[pos] = val;
    pos++;
}

void NoB::insert( int val )
{
    if( pos > size )
    {
        cout << "Não foi possível inserir valor " << val << " no nó ( overflow )" << endl;
        exit(1);
    }

    int i;

    for( i = 0; i < size; i++ )
    {
        if( values[i] == -1 )
        {
            values[i] = val;
            pos++;
            return;
        }
        else
        if( val < values[i] )
        {
            for( int k = size+1; k > i; k-- )
            {
                values[k] = values[k-1];
                childs[k+1] = childs[k];
            }
            // childs[i] = childs[i-1];
            values[i] = val;
            pos++;
            return;
        }
    }

    values[i] = val;
    pos++;
}

void NoB::insert( int val, int k )
{
    if( pos > size )
    {
        cout << "Não foi possível inserir valor " << val << " no nó ( overflow )" << endl;
        exit(1);
    }

    for( int i = size+1; i > k; i-- )
    {
        values[i] = values[i-1];
        childs[i+1] = childs[i];
    }
    // childs[k] = childs[k-1];
    values[k] = val;
    pos++;
}

void NoB::insert( int val, NoB* no )
{
    if( pos > size )
    {
        cout << "Não foi possível inserir valor " << val << " no nó ( overflow )" << endl;
        exit(1);
    }

    for( int i = 0; i < size; i++ )
    {
        if( val < values[i] )
        {
            for( int k = size+1; k > i; k-- )
            {
                values[k] = values[k-1];
                childs[k+1] = childs[k];
            }
            values[i] = val;
            childs[i] = no;
            pos++;
            posChild++;
            return;
        }
        else if( values[i] == -1 )
        {
            values[i] = val;
            childs[i] = no;
            pos++;
            posChild++;
            return;
        }
    }
}