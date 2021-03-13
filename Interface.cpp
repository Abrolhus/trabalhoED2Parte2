#include "Interface.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void interface( ArvoreAVL& avlTree, ArvoreB& bTree, HashTable& hash, vector<Registro>& regs )
// void interface( ArvoreAVL& avlTree, ArvoreB& bTree, quadTree& quad, HashTable& hash, vector<Registro>& regs )
{
    string args[10];
    char command;
    int argsI[10];
    streambuf* bckpbuf = cout.rdbuf();
    ofstream otpbuf;
    vector<int> randoms;

    unsigned char selectedTree = 'a';

    printOptions:

    cout << "========= INTERFACE =========" << endl;
    cout << "ETAPA 05" << endl;
    cout << "5 - Realizar etapa 05" << endl;
    cout << "c - Obter total de casos" << endl;
    cout << "f - Preencher tabela hash" << endl << endl;
    cout << "Selecionado [ " << ( selectedTree == 'a' ? "Arvore AVL": selectedTree == 'b' ? "Arvore B": selectedTree == 'c' ? "Arvore QUAD": selectedTree == 'd' ? "Tabela Hash":"" ) << " ]" << " - (\\) para mudar" << endl;
    cout << "p - Printar" << endl;
    cout << "n - Preencher N aleatorios" << endl;
    cout << "i - Inserção de N registros" << endl;
    cout << "l - Limpar a estrutura" << endl;
    cout << "s - Fechar programa" << endl;
    cout << "=============================" << endl;

    readCommand:

    cin >> command;

    switch (command)
    {
        case 's':
            goto the_end;
        break;

        case 'i':
            cout << "Digite o valor de N: ";
            cin >> argsI[0];

            if( argsI[0] > 20 )
            {
                otpbuf.open("saida.txt",ofstream::app);
                cout.rdbuf( otpbuf.rdbuf() );
            }
            
            if( selectedTree == 'a' )
            {
                for( int i = 0; i < argsI[0]; i++ )
                    avlTree.Insere( hash.getIndexOf(regs[i].getCode(),regs[i].getData()) );
                avlTree.Print();
            }
            else if( selectedTree == 'b' )
            {
                for( int i = 0; i < argsI[0]; i++ )
                    bTree.Insere( hash.getIndexOf(regs[i].getCode(),regs[i].getData()) );
                bTree.Print();
            }
            else if( selectedTree == 'c' )
            {
                
            }
            else if( selectedTree == 'd' )
            {
                for( int i = 0; i < argsI[0]; i++ )
                    hash.insert( regs[i] );
                hash.print();
            }

            if( argsI[0] > 20 )
                otpbuf.close();
            cout.rdbuf( bckpbuf );

        break;

        case 'f':
            hash.clear();
            for( int i = 0; i < regs.size(); i++ )
                hash.insert( regs[i] );
        break;

        case 'n':
            cout << "Digite um valor de N:" << endl;
            cin >> argsI[0];

            cout << "Limpando Hash..." << endl;
            hash.clear();
            cout << "Preenchendo Hash..." << endl;
            for( int i = 0; i < regs.size(); i++ )
                hash.insert( regs[i] );

            cout << "Limpando AVL..." << endl;
            avlTree.Limpar();
            cout << "Limpando B..." << endl;
            bTree.Limpar();

            cout << "Gerando " << argsI[0] << " valores" << endl;
            randoms = hash.getNRandomHashCodes( argsI[0] );
            
            for( int i = 0; i < randoms.size(); i++ ) cout << randoms[i] << (i == randoms.size()-1 ? "": " - ");
            cout << endl;

            cout << "Inserindo " << argsI[0] << " valores..." << endl;
            for( int i = 0; i < randoms.size(); i++ )
            {
                cout << "Inserindo " << randoms[i] << " em AVL" << endl;
                avlTree.Insere( randoms[i] );
                cout << "Inserindo " << randoms[i] << " em B" << endl;
                bTree.Insere( randoms[i] );
            }

        break;

        case 'c':
            cout << "Digite o código da cidade: " << endl;
            cin >> argsI[0];

            argsI[1] = avlTree.BuscaCasos( argsI[0] );
            argsI[2] = bTree.BuscaCasos( argsI[0] );

            cout << "Número de casos (AVL): " << argsI[1] << endl;
            cout << "Número de casos (B): " << argsI[2] << endl;
            
        break;

        case 'l':
            if( selectedTree == 'a' ) avlTree.Limpar();
            else if( selectedTree == 'b' ) bTree.Limpar();
            else if( selectedTree == 'd' ) hash.clear();
            // else if( selectedTree == 'd' ) avlTree.Limpar();
        break;

        case '\\':
            selectedTree++;
            if( selectedTree == 'e' ) selectedTree = 'a';
        break;

        case 'p':
            if( selectedTree == 'a' ) avlTree.Print();
            else if( selectedTree == 'b' ) bTree.Print();
            else if( selectedTree == 'd' ) hash.print();
            // else if( selectedTree == 'b' ) bTree.Print();
        break;
        
        default: 
            goto readCommand;
        break;
    }

    goto printOptions;

    the_end:

    return;
}