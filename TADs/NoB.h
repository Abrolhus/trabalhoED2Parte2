#include <iostream>

using namespace std;

class NoB
{
    private:
        int* values;
        NoB** childs;
        NoB* parent;

        int pos;
        int posChild;
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
        void insert( int val, NoB* no );

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