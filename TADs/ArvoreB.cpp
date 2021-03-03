#include "ArvoreB.h"

ArvoreB::ArvoreB( int size )
{
    root = nullptr;
    this->size = size;
}

ArvoreB::~ArvoreB()
{

}

bool ArvoreB::Busca( int val )
{
    NoB* aux = root;

    while( aux != nullptr )
    {
        for( int i = 0; i < size; i++ )
        {
            if( aux->get(i) == val )
                return true;
            else if( aux->get(i) > val )
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

    return false;
}

void ArvoreB::Insere( int val )
{
    if( root == nullptr )
    {
        root = new NoB( size );
        root->setLeaf();
    }

    bool done = false;
    int ov = -1;
    NoB* oc = root;
    NoB* on = root;
    insereAux( val, root, done, ov, oc, on );
    return;

    if( root == nullptr )
    {
        root = new NoB( size );
        root->setLeaf();
    }

    NoB* it = root;

    for( int i = 0; i < size; i++ )
    {
        if( it->get(i) == -1 )
        {
            it->append( val );
            return;
        }
        else if( it->get(i) > val )
        {
            if( it->full() )
            {
                if( it->isLeaf() )
                {
                    NoB* newNode = new NoB( size );
                    newNode->setLeaf();
                    newNode->setParent( it->getParent() );

                    // INSERE O OVERFLOW
                    it->insert( val, i );

                    // BUSCA CHAVE DO MEIO
                    int middle = it->get(size/2);

                    // REPOPULAR SEGUNDO NÓ COM size/2 ELEMENTOS
                    // DO PRIMEIRO
                    for( int j = (size/2)+1; j < size+1; j++ )
                    {
                        newNode->append( it->get(j) );
                        newNode->appendChild( it->getChild(j) );
                        it->setChild( j, nullptr );
                        it->set( j, -1 );
                    }
                    it->setPos( size/2 );

                    NoB* aux = it->getParent();

                    // INSERE O OVERFLOW
                    aux->insert( middle );

                    val = middle;

                    it = it->getParent();
                    i = -1;
                }
                else
                {
                    it = it->getChild( i );
                    i = -1;
                }
            }
            else
            {
                // INSERE ORDENADO
                it->insert( val, i );
                return;
            }
        }
    }
}

void ArvoreB::insereAux( int val, NoB* no, bool& done, int& overflowValue, NoB*& overflowChild, NoB*& overflowNode )
{
    cout << "rec" << endl;
    if( no == nullptr ) return;

    for( int i = 0; i < size; i++ )
    {
        if( no->get(i) == -1 )
        {
            no->set( i, val );
            no->setPos( no->getPos() + 1 );
            cout << "Inserido " << val << endl;
            done = true;
            return;
        }
        else if( val < no->get(i) )
        {
            insereAux( val, no->getChild( i ), done, overflowValue, overflowChild, overflowNode );
            break;
        }
        else if( i == size )
        {
            insereAux( val, no->getChild( i+1 ), done, overflowValue, overflowChild, overflowNode );
            break;
        }
    }

    if( done ) return;

    if( no->isLeaf() )
    {
        no->insert( val );
        cout << "Inserido " << val << endl;
    }
    else
    {
        no->insert( overflowValue, overflowChild );
        for( int i = 0; i < size+1; i++ )
        {
            if( no->get(i) == overflowValue )
                no->setChild( i+1, overflowNode );
        }
    }

    if( no->full() )
    {
        cout << "overflow" << endl;
        overflowValue = no->get( size/2 );
        overflowChild = no;
        overflowNode = new NoB( size );
        overflowNode->setLeaf( no->isLeaf() );
        overflowNode->setParent( no->getParent() );

        int i;
        for( i = (size/2)+1; i < size+1; i++ )
        {
            overflowNode->append( no->get( i ) );
            overflowNode->appendChild( no->getChild( i ) );
            no->set( i, -1 );
            no->setChild( i, nullptr );
            no->setPos( no->getPos()-1 );
            no->setPosChild( no->getPosChild()-1 );
        }
        overflowNode->appendChild( no->getChild( i+1 ) );

        no->setPos( size/2 );

        if( no == root )
        {
            NoB* parent = new NoB( size );
            
            parent->append( val );
            parent->appendChild( overflowChild );
            parent->appendChild( overflowNode );

            no->setParent( parent );
            overflowNode->setParent( parent );

            root = parent;
        }

        return;
    }

    done = true;
}

void ArvoreB::overflow( int val, NoB* no, NoB* newNo )
{
    NoB* aux = no->getParent();

    if( aux == nullptr )
    {
        aux = new NoB( size );
        root = aux;
        no->setParent( root );
    }

    if( aux->full() )
    {
        aux->insert( val, newNo );
        // overflow( aux->get( size/2 ), aux->getChild() )
        return;
    }

    aux->insert( val, newNo );
}

void ArvoreB::Print()
{
    int layer = 0;
    printAux( root, layer );
}
void ArvoreB::printAux( NoB* no, int& layer )
{   
    for( int i = 0; i < size; i++ )
    {
        if( no->getChild(i) != nullptr )
        {
            layer++;
            printAux( no->getChild(i), layer );
            layer--;
        }
        cout << "Layer: " << layer << endl;

        if( layer > 0 )
        {
            cout << "|";
            for( int j = 0; j < layer; j++ ) cout << "-";
        }
        cout << " " << no->get( i ) << ( i==size-1 ? "\n":", ");
    }
}