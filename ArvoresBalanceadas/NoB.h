#ifndef NOB_H
#define NOB_H

#include <iostream>

using namespace std;

#include <vector>

class NoB
{
    private:
        vector<NoB*> childs;
        vector<int> values;

        NoB* parent;

        int size;

        bool leaf;

    public:
        NoB( int n );
        ~NoB();

        int get( int i );
        void set( int i, int val );
        void append( int val );
        void insert( int val );
        void insert( int val, int k );
        // void insert( int val, NoB* no );
        void pop( int );

        NoB* getChild( int i );
        void setChild( int i, NoB* no );
        void appendChild( NoB* no );

        int getPos();
        int getPosChild();
        void setPos( int val );
        void setPosChild( int val );

        bool isLeaf();
        void setLeaf( bool x = true );

        bool full();

        void setParent( NoB* no );
        NoB* getParent();
};

#endif