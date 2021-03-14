#include "NoB.h"

NoB::NoB( int n )
{
    size = n;
    leaf = false;
    parent = nullptr;
}

NoB::~NoB()
{
    // for( int i=0; i < size+2; i++ )
    // {
    //     delete childs[i];
    //     childs[i] = nullptr;
    // }
    // delete [] childs;
    // delete [] values;
}

int NoB::get( int i ){ return values[i]; }
void NoB::set( int i, int val ){ values[i] = val; }
NoB* NoB::getChild( int i ){ return childs[i]; }
void NoB::setChild( int i, NoB* no ){ childs[i] = no; }
void NoB::appendChild( NoB* no ){ childs.push_back(no); }
int NoB::getPos(){ return values.size(); }
int NoB::getPosChild(){ return childs.size(); }

bool NoB::isLeaf(){ return leaf; }
void NoB::setLeaf( bool x ){ leaf = x; }
bool NoB::full(){ return values.size() == size; }
void NoB::setParent( NoB* no ){ parent = no; }
NoB* NoB::getParent(){ return parent;}
void NoB::append( int val ){ values.push_back(val); }
void NoB::insert( int x )
{
    int size = values.size();
    for( int i = 0; i < size; i++ )
    {
        if( values[i] > x )
        {
            values.insert( values.begin()+i, x );
            return;
        }
    }

    values.push_back( x );
}
void NoB::pop( int pos ){ values.erase( values.begin()+pos ); }
void NoB::popChild( int pos ){ childs.erase( childs.begin()+pos ); }

void NoB::insert( int val, int k ){ values.insert( values.begin()+k, 1, val ); }
void NoB::insertChild( int pos, NoB* no ){ childs.insert( childs.begin()+pos, 1, no ); }