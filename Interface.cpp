#include "Interface.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>


using namespace std;

// void interface( ArvoreAVL& avlTree, ArvoreB& bTree, HashTable& hash, vector<Registro>& regs )
void interface( ArvoreAVL& avlTree, ArvoreB& bTree, quadTree& quad, HashTable& hash, vector<Registro>& regs, vector<folhaQuadTree*> vet)
{
    string args[10];
    char command;
    int argsI[10];
    streambuf* bckpbuf = cout.rdbuf();
    ofstream otpbuf;
    vector<int> randoms;
    int compsB=0;
    vector<int> chavesRegiao;
    int somaAvl = 0;
    int somaB = 0;
    int compsAvl = 0;

    ArvoreB bTree2( &hash, 200);

    chrono::high_resolution_clock::time_point start,end;

    unsigned char selectedTree = 'a';

    printOptions:

    cout << "========= INTERFACE =========" << endl;
    cout << "ETAPA 05" << endl;
    cout << "5 - Realizar etapa 05" << endl;
    cout << "n - Preencher N aleatorios" << endl;
    cout << "c - Obter total de casos" << endl;
    cout << "x - Estabelecer area geografica de busca" << endl;
    cout << "f - Preencher tabela hash" << endl << endl;
    cout << "Selecionado [ " << ( selectedTree == 'a' ? "Arvore AVL": selectedTree == 'b' ? "Arvore B": selectedTree == 'c' ? "Arvore QUAD": selectedTree == 'd' ? "Tabela Hash":"" ) << " ]" << " - (\\) para mudar" << endl;
    cout << "p - Printar" << endl;
    cout << "i - Inserção de N registros" << endl;
    cout << "l - Limpar a estrutura" << endl;
    cout << "t - Tamanho" << endl;
    cout << "s - Fechar programa" << endl << endl;
    cout << "OUTROS" << endl;
    cout << "h - Printar da hash" << endl;
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
            argsI[9] = 0;

            if( argsI[0] > 20 )
            {
                otpbuf.open("saida.txt",ofstream::app);
                cout.rdbuf( otpbuf.rdbuf() );
            }
            
            if( selectedTree == 'a' )
            {
                for( int i = 0; i < argsI[0]; i++ )
                    avlTree.Insere( hash.getIndexOf(regs[i].getCode(),regs[i].getData()), argsI[9] );
                avlTree.Print();
            }
            else if( selectedTree == 'b' )
            {
                for( int i = 0; i < argsI[0]; i++ )
                {
                    bTree.Insere( hash.getIndexOf(regs[i].getCode(),regs[i].getData()), argsI[9] );
                    bTree2.Insere( hash.getIndexOf(regs[i].getCode(),regs[i].getData()), argsI[9] );
                }
                bTree.Print();
            }
            else if( selectedTree == 'c' )
            {
                auto ts = chrono::high_resolution_clock::now();
                for(int i=0; i< argsI[0]; i++){
                    quad.inserir(vet[i]);
                }
                auto te = chrono::high_resolution_clock::now();
                double duration = chrono::duration_cast<chrono::milliseconds>(te-ts).count();
                cout<< "<<<< QuadTree >>>>" << endl;
                cout << "Tempo de insercao: " << duration << endl;
                quad.imprimir();
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
            cout << "Limpando B[20]..." << endl;
            bTree.Limpar();
            cout << "Limpando B[200]..." << endl;
            bTree2.Limpar();

            cout << "Gerando " << argsI[0] << " valores" << endl;
            randoms = hash.getNRandomHashCodes( argsI[0] );
            
            // for( int i = 0; i < randoms.size(); i++ ) cout << randoms[i] << (i == randoms.size()-1 ? "": " - ");
            // cout << endl;

            argsI[1] = 0;
            argsI[2] = 0;
            argsI[3] = 0;

            otpbuf.open("resultado.txt", ostream::app);
            cout.rdbuf( otpbuf.rdbuf() );

            cout << "Inserindo " << argsI[0] << " valores (AVL)..." << endl;
            start = chrono::high_resolution_clock::now();
            for( int i = 0; i < randoms.size(); i++ )
            {
                cerr << "Inserindo " << randoms[i] << " em AVL" << endl;
                avlTree.Insere( randoms[i], argsI[1] );
            }
            end = chrono::high_resolution_clock::now();
            cout << "Duração da inserção (AVL): " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << "ns" << endl;
            cout << "Número de comparações (AVL): " << argsI[1] << endl;
            cout << endl;

            cout << "Inserindo " << argsI[0] << " valores (B[20])..." << endl;
            start = chrono::high_resolution_clock::now();
            for( int i = 0; i < randoms.size(); i++ )
            {
                cerr << "Inserindo " << randoms[i] << " em B[20]" << endl;
                bTree.Insere( randoms[i], argsI[2] );
            }
            end = chrono::high_resolution_clock::now();
            cout << "Duração da inserção (B[20]): " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << "ns" << endl;
            cout << "Número de comparações (B[20]): " << argsI[2] << endl;
            cout << endl;

            cout << "Inserindo " << argsI[0] << " valores (B[200])..." << endl;
            start = chrono::high_resolution_clock::now();
            for( int i = 0; i < randoms.size(); i++ )
            {
                cerr << "Inserindo " << randoms[i] << " em B[200]" << endl;
                bTree2.Insere( randoms[i], argsI[3] );
            }
            end = chrono::high_resolution_clock::now();
            cout << "Duração da inserção (B[200]): " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << "ns" << endl;
            cout << "Número de comparações (B[200]): " << argsI[3] << endl;
            cout << endl;

            cout.rdbuf( bckpbuf );
            otpbuf.close();

        break;

        case 'c':
            cout << "Digite o código da cidade: " << endl;
            cin >> argsI[0];

            argsI[1] = argsI[2] = 0;

            otpbuf.open("resultado.txt", ostream::app);
            cout.rdbuf( otpbuf.rdbuf() );

            cout << "Buscando na AVL..." << endl;
            start = chrono::high_resolution_clock::now();
            argsI[1] = avlTree.BuscaCasos( argsI[0], argsI[2] );
            end = chrono::high_resolution_clock::now();
            cout << "Duração da comparação (AVL): " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << "ns" << endl;
            cout << "Número de comparações (AVL): " << argsI[2] << endl;
            cout << "Número de casos (AVL): " << argsI[1] << endl;
            cout << endl;

            argsI[2] = 0;

            cout << "Buscando na B[20]..." << endl;
            start = chrono::high_resolution_clock::now();
            argsI[1] = bTree.BuscaCasos( argsI[0], argsI[2] );
            end = chrono::high_resolution_clock::now();
            cout << "Duração da comparação (B[20]): " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << "ns" << endl;
            cout << "Número de comparações (B[20]): " << argsI[2] << endl;
            cout << "Número de casos (B[20]): " << argsI[1] << endl;
            cout << endl;

            argsI[2] = 0;

            cout << "Buscando na B[200]..." << endl;
            start = chrono::high_resolution_clock::now();
            argsI[1] = bTree2.BuscaCasos( argsI[0], argsI[2] );
            end = chrono::high_resolution_clock::now();
            cout << "Duração da comparação (B[200]): " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << "ns" << endl;
            cout << "Número de comparações (B[200]): " << argsI[2] << endl;
            cout << "Número de casos (B)[200]: " << argsI[1] << endl;
            cout << endl;

            cout.rdbuf( bckpbuf );
            otpbuf.close();

        break;

        case 'l':
            if( selectedTree == 'a' ) avlTree.Limpar();
            else if( selectedTree == 'b' ) { bTree.Limpar(); bTree2.Limpar(); }
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

        case 't':
            if( selectedTree == 'a' ) cout << avlTree.Count();
            else if( selectedTree == 'b' ) cout << bTree.Count();
            // else if( selectedTree == 'd' ) hash.Count();

            cout << endl;
        break;

        case 'h':
            cout << "Digite o codigo hash:" << endl;
            cin >> argsI[0];

            cout << "Cidade: " << hash.at( argsI[0] ).getCidade() << endl
                 << "Codigo: " << hash.at( argsI[0] ).getCode() << endl
                 << "Casos: " << hash.at( argsI[0] ).getCasos() << endl
                 << "Data: " << hash.at( argsI[0] ).getData() << endl;
        break;

        case 'x':
            cout<< "Digite os valores de (x0, y0) e (x1,y1) " << endl;
            double x0, y0, x1, y1;
            cin >> x0 >> y0 >> x1 >> y1;
            somaB= 0;
            somaAvl = 0;
            compsB = 0;
            compsAvl = 0;
            for(int i = 0; i < vet.size(); i++){
                quad.inserir(vet[i]);
            }
            quad.buscaIntervaloAux(chavesRegiao, x0, x1, y0, y1);
            
            for(int i = 0; i < chavesRegiao.size(); i++){
                somaAvl += avlTree.BuscaCasos(chavesRegiao[i], compsAvl);
                somaB += bTree.BuscaCasos(chavesRegiao[i], compsB);
            }

            cout << "Casos pela arvore AVL: " << somaAvl << endl;
            cout << "Casos pela arvore B: " << somaB << endl;
            
        break;
        
        default: 
            goto readCommand;
        break;
    }

    goto printOptions;

    the_end:

    return;
}