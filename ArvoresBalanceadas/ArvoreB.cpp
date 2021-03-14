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
    // clearAux( root );
    // delete root;
    root = nullptr;
    return;
}
void ArvoreB::clearAux( NoB* no )
{
    return;
//     if( no == nullptr ) return;

//     if( no->isLeaf() )
//     {
//         if( no->getParent() != nullptr ) no->getParent()->setLeaf();
//         delete no;
//         no = nullptr;
//         return;
//     }

//     for( int i = 0; i < size+2; i++ )
//         clearAux( no->getChild(i) );
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
    for( i = 0; i < size; i++ )
    {
        cerr << "Comparando " << val;
        int atual = ( aux->get(i) == -1 ? -1:HashRef->at( aux->get(i) ).getCode() );
        cerr << " com " << atual << endl;
        comp++;
        if( aux->get(i) == -1 || atual > val )
        {
            cerr << "Valor menor ou igual a -1" << endl;
            break;
        }
        else if( atual == val )
        {
            cerr << "Encontrado" << endl;
            soma += AuxBusca( aux->getChild(i), val, comp ) + HashRef->at( aux->get(i) ).getCasos();
        }
        cerr << "Seguindo em frente i:" << i << endl;
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
        root = new NoB(size);
        root->setLeaf();
    }

    NoB* aux = root;
    int i;

    Registro reg_cur;
    Registro reg_new = HashRef->at( val );

    for( i = 0; i < size; i++ )
    {
        comp++;
        // cerr << "Chave hash: " << aux->get(i) << endl;
        // cerr << "Comparando " << reg_new.getCode() << " com " << ( aux->get(i) == -1 ? -1:HashRef->at( aux->get(i) ).getCode() ) << endl;
        if( aux->get(i) == -1 ) // INSERE SE VAZIO
        {
            // cerr << "No vazio" << endl;
            if( aux->getChild(i) == nullptr ) // SE NÃO POSSUI VALORES A DIREITA DE AUX-1, INSERE
            {
                // cerr << "No folha, inserindo" << endl;
                aux->insert( val, i );
                return;
            }
            else
            {
                // cerr << "Não folha, indo para filho" << endl;
                aux = aux->getChild(i);
                // if( aux == nullptr ) cerr << "filho nulo" << endl;
                i = -1;
            }
        }
        else
        {
            // cerr << "Indice não nulo" << endl;
            reg_cur = HashRef->at( aux->get(i) );// BUSCA REGISTRO ASSOCIADO A CHAVE AUX[i]
            comp++;
            if( reg_cur.getCode() > reg_new.getCode() ) // INSERE SE ESTIVER ENTRE ALGUM VALOR
            {
                // cerr << "No " << reg_new.getCode() << " menor que " << reg_cur.getCode() << endl;
                if( aux->isLeaf() ) // SE NO FOLHA, OVERFLOW, SAI DO FOR
                {
                    // cerr << "No é folha, chamando overflow" << endl;
                    overflow( val, aux, nullptr, nullptr, comp );
                    return;
                }

                if( aux->getChild(i) != nullptr )
                {
                    // cerr << "No nao folha, entrando em filho" << endl;
                    aux = aux->getChild(i); // CASO NAO SEJA NO FOLHA, CONTINUA BUSCANDO LOCAL DE INSERCAO
                    i = -1;
                }
            }
            else if( reg_cur.getCode() == reg_new.getCode() )
            {
                // cerr << "Codigos iguais, comparando data" << endl;
                comp++;
                if( DataCompare( reg_cur.getData(), reg_new.getData() ) == -1 )
                {
                    // cerr << "Data menor" << endl;
                    if( aux->isLeaf() ) // SE NO FOLHA, OVERFLOW, SAI DO FOR
                    {
                        // cerr << "No é folha, chamando overflow" << endl;
                        overflow( val, aux, nullptr, nullptr, comp );
                        return;
                    }

                    if( aux->getChild(i) != nullptr )
                    {
                        // cerr << "No nao folha, entrando em filho" << endl;
                        aux = aux->getChild(i); // CASO NAO SEJA NO FOLHA, CONTINUA BUSCANDO LOCAL DE INSERCAO
                        i = -1;
                    }
                }
            }
        }
        // cerr << "Seguindo" << endl;
    }

    // cerr << "overflow" << endl;
    overflow( val, aux, nullptr, nullptr, comp );
}

void ArvoreB::overflow( int val, NoB* current, NoB* left, NoB* right, int& comp )
{
    if( current == nullptr )
    {
        root = new NoB(size);
        current = root;
        current->setLeaf(false);
    }

    Registro reg_cur = HashRef->at( val );
    Registro reg_aux;

    int i;
    for( i = 0; i < size; i++ ) // BUSCA POSICAO NA QUAL VAL SERA INSERIDO
    {
        if( current->get(i) != -1 )
            reg_aux = HashRef->at( current->get(i) );
        if( current->get(i) == -1 || reg_aux.getId() > reg_cur.getId() ) 
            break;
        else if( reg_aux.getId() == reg_cur.getId() )
        {
            comp++;
            if( DataCompare(reg_aux.getData(), reg_cur.getData()) == -1 )
                break;
        } 
        comp++;
    }
    comp++;

    current->insert( val, i );
    current->setChild( i, left );
    current->setChild( i+1, right );
    // current->setChild( (i == size ? i-1:i), left );
    // current->setChild( (i == size ? i:i+1), right );

    if( left != nullptr ) left->setParent( current );
    if( right != nullptr ) right->setParent( current );

    if( current->getPos() < size+1 ) return;

    int pivo = current->get( size/2 );
    NoB* newLeft = current;
    NoB* newRight = new NoB(size);

    current->set( size/2, -1 );
    int j;
    for( j = (size/2)+1; j < size+1; j++ )
    {
        newRight->append( current->get(j) );
        newRight->appendChild( current->getChild(j) );

        current->set( j, -1 );
        current->setChild( j, nullptr );
    }
    newRight->appendChild( current->getChild(j) );
    current->setChild( j, nullptr );
    newRight->setLeaf( current->isLeaf() ); // SE AUX E FOLHA, NO DA DIREITA TAMBEM SERA

    current->setPos( size/2 );

    overflow( pivo, current->getParent(), current, newRight, comp );

}

void ArvoreB::Print( bool overflow )
{
    bool of = overflow;
    int layer = 0;
    printAux( root, layer, of );
}
void ArvoreB::printAux( NoB* no, int& layer, bool& overflow)
{   
    if( no == nullptr ) return;

    for( int j = 0; j < layer; j++ ) cout << "  ";
    for( int i = 0; i < size+(overflow ? 1:0); i++ )
    {
        cout << no->get( i ) << "[ " << ( no->get(i) == -1 ? -1:HashRef->at(no->get(i)).getCode() ) << "," << ( no->get(i) == -1 ? "-1":HashRef->at(no->get(i)).getData() ) << " ]" << ( i==size-1+(overflow ? 1:0) ? "":", ");

        if( no->getChild(i) != nullptr )
        {
            layer++;
            cout << endl;
            printAux( no->getChild(i), layer, overflow );
            layer--;
        }

    }
    cout << endl;
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
    for( i = 0; i < size; i++ )
    {
        if( no->get(i) != -1 ) soma++; else break;
        soma += CountAux( no->getChild(i) );
    }

    return soma+CountAux( no->getChild(i) );  
}