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

void ArvoreB::Insere( int val, int& comp )
{
    if( root == nullptr )
    {
        NoB* no = new NoB(size);
        no->setLeaf(true);
        no->append( val );
        no->appendChild( nullptr );
        no->appendChild( nullptr );

        root = no;

        cerr << "Gerada raiz" << endl;
        cerr << "Inserido " << val << endl;
        return;
    }

    cerr << "Inserindo " << val << endl;
    InsereAux( val, comp, root );

}
void ArvoreB::InsereAux( int val, int& comp, NoB* no )
{
    Registro reg_cur;
    Registro reg_new = HashRef->at( val );
    
    cerr << "No " << (no->isLeaf() ? "é":"não") << " é folha" << endl;
    while( !no->isLeaf() )
    {
        cerr << "Iterando um no" << endl;
        int i;
        for( i = 0; i < no->getPos(); i++ )
        {
            reg_cur = HashRef->at( no->get(i) );
            comp++;
            cerr << "Comparando com posicao " << i << " ( " << reg_new.getCode() << "-" << reg_new.getData() << " ) com ( " << reg_cur.getCode() << "-" << reg_cur.getData() << " )" << endl;
            if( reg_new.getCode() < reg_cur.getCode() )
            {
                cerr << reg_new.getCode() << " menor que " << reg_cur.getCode() << endl;
                InsereAux( val, comp, no->getChild(i) );
                return;
            }
            else
            {
                if( reg_new.getCode() == reg_cur.getCode() )
                {
                    comp++;
                    if( DataCompare( reg_new.getData(), reg_cur.getData() ) == 1 )
                    {
                        cerr << reg_new.getData() << " menor que " << reg_cur.getData() << endl;
                        InsereAux( val,comp, no->getChild(i) );
                        return;
                    }
                }
            }
        }
        cerr << "Chegou ao final" << endl;
        InsereAux( val,comp, no->getChild(i) );
        return;
    }

    cerr << "Chamando overflow" << endl;
    overflow( val, no, nullptr, nullptr, comp );

    // int i;
    // for( i = 0; i < no->getPos(); i++ )
    // {
    //     comp++;
    //     reg_cur = HashRef->at( no->get(i) );
    //     cerr << "Comparando " << reg_new.getCode() << " com " << reg_cur.getCode() << endl;
    //     if( reg_new.getCode() < reg_cur.getCode() )
    //     {
    //         if( no->isLeaf() )
    //         {
    //             cerr << "No folha" << endl;
    //             if( no->full() )
    //             {
    //                 cerr << "No cheio, overflow" << endl;
    //                 overflow( val, no, nullptr, nullptr, comp );
    //             }
    //             else
    //             {
    //                 cerr << "Inserindo em " << i << endl;
    //                 no->insert( i, val );
    //                 cerr << "Inserido " << val << endl;
    //                 return;
    //             }
    //         }
    //         else
    //         {
    //             cerr << "No nao folha, recursividade" << endl;
    //             InsereAux( val, comp, no->getChild(i) );
    //             return;
    //         }
    //     }
    //     else if( reg_new.getCode() == reg_cur.getCode() && DataCompare( reg_new.getData(), reg_cur.getData() ) == 1 )
    //     {
    //         cerr << "Comparando por data" << endl;
    //         if( no->isLeaf() )
    //         {
    //             cerr << "No folha" << endl;
    //             if( no->full() )
    //             {
    //                 cerr << "No cheio, overflow" << endl;
    //                 overflow( val, no, nullptr, nullptr, comp );
    //             }
    //             else
    //             {
    //                 cerr << "Inserindo em " << i << endl;
    //                 no->insert( i, val );
    //                 cerr << "Inserido " << val << endl;
    //                 return;
    //             }
    //         }
    //         else
    //         {
    //             cerr << "No nao folha, recursividade" << endl;
    //             InsereAux( val, comp, no->getChild(i) );
    //             return;
    //         }
    //     }
    // }

    // cerr << "Chegou ao fim" << endl;
    // if( no->full() )
    // {
    //     cerr << "No cheio" << endl;
    //     if( no->isLeaf() )
    //     {
    //         cerr << "No folha, overflow" << endl;
    //         overflow( val, no, nullptr, nullptr, comp );
    //     }
    //     else
    //     {
    //         cerr << "No nao folha, recursivo" << endl;
    //         InsereAux( val, comp, no->getChild(i) );
    //     }
    // }
    // else
    // {
    //     if( no->isLeaf() )
    //     {
    //         cerr << "Inserido " << val << endl;
    //         no->append( val );
    //     }
    //     else
    //     {
    //         cerr << "No nao folha, recursividade" << endl;
    //         InsereAux(val, comp, no->getChild(i));
    //     }
    // }
}

void ArvoreB::overflow( int val, NoB* current, NoB* left, NoB* right, int& comp )
{
    if( current == nullptr )
    {
        current = new NoB(size);
        current->setLeaf(false);
        root = current;
        cerr << "Nova raiz" << endl;
    }

    Registro reg_new = HashRef->at( val );
    Registro reg_cur;

    int i;
    for( i = 0; i < current->getPos(); i++ ) // BUSCA POSICAO NA QUAL VAL SERA INSERIDO
    {
        if( current->get(i) != -1 )
            reg_cur = HashRef->at( current->get(i) );

        if( reg_cur.getId() > reg_new.getId() ) 
            break;
        else if( reg_cur.getId() == reg_cur.getId() )
        {
            comp++;
            if( DataCompare(reg_cur.getData(), reg_new.getData()) == -1 )
                break;
        } 
        comp++;
    }
    comp++;

    cerr << "Inserido " << val << " na posição " << i << endl;

    current->insert( val, i );
    if( i == 0 )
    {
        cerr << "Setando filho esq em " << i << endl;
        current->insertChild( i, left );
    }
    cerr << "Novo filho dir em " << i+1 << endl;
    current->insertChild( i+1, right );

    // cerr << "Setando filho esq em " << i << endl;

    // current->setChild( i, left )

    // current->setChild( (i == size ? i-1:i), left );
    // current->setChild( (i == size ? i:i+1), right );

    // if( left != nullptr ) left->setParent( current );
    if( right != nullptr ) right->setParent( current );

    if( current->getPos() < size+1 ) return;

    cerr << "Explosao de tamanho: " << current->getPos() << endl;

    int pivo = current->get( current->getPos()/2 );
    NoB* newLeft = current;
    NoB* newRight = new NoB(size);

    int iPivo = current->getPos()/2;
    int j;
    // for( j = (current->getPos()/2)+1, k=(current->getPos()/2)+1, l=0; j < current->getPos(); k++,l++)
    // {
    //     cerr << "jogando pra la " << endl;
    //     newRight->append( current->get(j) );
    //     newRight->setChild( l, current->getChild(k) );

    //     current->pop( j );
    //     current->setChild( k, nullptr );
    // }
    for( j = (current->getPos()/2)+1; j < current->getPos(); j++ )
    {
        newRight->append( current->get(j) );
        newRight->appendChild( current->getChild(j) );
    }
    newRight->appendChild( current->getChild(j) );

    for( j = (current->getPos()/2)+1; j < current->getPos(); )
    {
        current->pop( j );
        current->popChild( j );
    }
    current->popChild( j );

    // newRight->setChild( l,current->getChild(k) );
    // current->setChild( k, nullptr );

    newRight->setLeaf( current->isLeaf() ); // SE AUX E FOLHA, NO DA DIREITA TAMBEM SERA

    current->pop( iPivo );

    cerr << current->getPos() << " POS CURR" << endl;

    cerr << "Novo no esq: " << endl;
    for( int i = 0; i < current->getPos(); i++ )
        cerr << HashRef->at( current->get(i) ).getCode() << (i==current->getPos()-1 ? "\n":",");
    cerr << "Novo no dir: " << endl;
    for( int i = 0; i < newRight->getPos(); i++ )
        cerr << HashRef->at( newRight->get(i) ).getCode() << (i==newRight->getPos()-1 ? "\n":",");
    
    overflow( pivo, current->getParent(), newLeft, newRight, comp );
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