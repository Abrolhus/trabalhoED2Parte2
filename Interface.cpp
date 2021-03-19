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
    int compsB20=0;
    int compsB200=0;
    vector<int> chavesRegiao;
    int somaAvl = 0;
    int somaB20 = 0;
    int somaB200 = 0;
    int compsAVL = 0;
    //int somaB = 0;
    //in/t compsAvl = 0;
    long int times[5];

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
    cout << "y - S2: Casos em cidades de um intervalo geografico (Parcialmente automatizada)" << endl;
    cout << "z - S2: Casos em cidades de um intervalo geografico (100\% automatico Viniccius 13)" << endl;
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
                    avlTree.Insere( hash.at(regs[i].getCode(),regs[i].getData()), argsI[9] );
                avlTree.Print();
            }
            else if( selectedTree == 'b' )
            {
                for( int i = 0; i < argsI[0]; i++ )
                {
                    bTree.Insere( regs[i], argsI[9] );
                    argsI[9] = 0;
                    bTree2.Insere( regs[i], argsI[9] );
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
                avlTree.Insere( hash.at(randoms[i]), argsI[1] );
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
                bTree.Insere( hash.at( randoms[i] ), argsI[2] );
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
                bTree2.Insere( hash.at( randoms[i] ), argsI[3] );
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
        {
            int n;
            cout << "Digite quantos valores aleatorios em cada arvore: " << endl;
            cin >> n;
            cout<< "Digite os valores de (x0, y0) e (x1,y1) " << endl;
            double x0, y0, x1, y1;
            cin >> x0 >> y0 >> x1 >> y1;
            somaB20 = 0;
            somaB200 = 0;
            somaAvl = 0;
            compsB20 = 0;
            compsB200 = 0;
            compsAVL = 0;
            chrono::high_resolution_clock::time_point start, end;
            for(int i = 0; i < vet.size(); i++){
                quad.inserir(vet[i]);
            }
            hash.clear();
            for( int i = 0; i < regs.size(); i++ ){
                hash.insert( regs[i] );
            }
            auto nAleatorios = hash.getNRandomHashCodes(n);
            for(auto hashCode : nAleatorios){
                avlTree.Insere(hashCode, argsI[9]);
                bTree.Insere(hash.at(hashCode), argsI[9]);
            }// ou seja, ambas estruturas com o mesmo numero de elementos;
            quad.buscaIntervaloAux(chavesRegiao, x0, x1, y0, y1);

            start = chrono::high_resolution_clock::now();
            for(int i = 0; i < chavesRegiao.size(); i++){
              somaAvl += avlTree.BuscaCasos(chavesRegiao[i], compsAVL);
            }
            end = chrono::high_resolution_clock::now();
            int duracaoAVL = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
            start = chrono::high_resolution_clock::now();
            for(int i = 0; i < chavesRegiao.size(); i++){
                somaB20 += bTree.BuscaCasos(chavesRegiao[i], compsB20);
            }
            end = chrono::high_resolution_clock::now();
            int duracaoB20 = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
            for(int i = 0; i < chavesRegiao.size(); i++){
                somaB200 += bTree2.BuscaCasos(chavesRegiao[i], compsB200);
            }
            end = chrono::high_resolution_clock::now();
            int duracaoB200 = chrono::duration_cast<chrono::nanoseconds>(end-start).count();


            cout << "Casos pela arvore AVL: " << somaAvl << endl;
            cout << "nComparacoes AVL: " << compsAVL << endl;
            cout << "Duração da Busca (AVL): " << duracaoAVL << "ns" << endl;
            cout << "Casos pela arvore B(20): " << somaB20 << endl;
            cout << "nComparacoes B(20): " << compsB20 << endl;
            cout << "Duração da Busca (B(20)): " << duracaoB20<< "ns" << endl;
            cout << "Casos pela arvore B(200): " << somaB200 << endl;
            cout << "nComparacoes B(200): " << compsB200 << endl;
            cout << "Duração da Busca (B(200)): " << duracaoB200<< "ns" << endl;
        }
        case 'y':
        {
            int m, n;
            float mediaCompsAVL = 0, mediaCompsB20 = 0, mediaCompsB200 = 0,
                mediaDuracaoAVL = 0, mediaDuracaoB20 = 0, mediaDuracaoB200 = 0,
                mediaCasosAVL = 0, mediaCasosB20 = 0, mediaCasosB200 = 0;
            cout << "Quantas iteracoes (M)? ";
            cin >> m;
            cout << "Digite quantos valores aleatorios em cada arvore: " << endl;
            cin >> n;
            cout<< "Digite os valores de (x0, y0) e (x1,y1) " << endl;
            double x0, y0, x1, y1;
            cin >> x0 >> y0 >> x1 >> y1;
            chrono::high_resolution_clock::time_point start, end;
            for(int i = 0; i < vet.size(); i++){
                quad.inserir(vet[i]);
            }
            hash.clear();
            for( int i = 0; i < regs.size(); i++ ){
                hash.insert( regs[i] );
            }
            for(int i = 0; i < m; i++){
                // mediaCompsAVL = 0, mediaCompsB20 = 0, mediaCompsB200 = 0,
                // mediaDuracaoAVL = 0, mediaDuracaoB20 = 0, mediaDuracaoB200 = 0,
                // mediaCasosAVL = 0, mediaCasosB20 = 0, mediaCasosB200 = 0;
                somaB20 = 0;
                somaB200 = 0;
                somaAvl = 0;
                compsB20 = 0;
                compsB200 = 0;
                compsAVL = 0;
                auto nAleatorios = hash.getNRandomHashCodes(n);
                avlTree.Limpar();
                bTree.Limpar();
                for(auto hashCode : nAleatorios){
                    avlTree.Insere(hashCode, argsI[9]);
                    bTree.Insere(hash.at(hashCode), argsI[9]);
                }// ou seja, ambas estruturas com o mesmo numero de elementos;
                quad.buscaIntervaloAux(chavesRegiao, x0, x1, y0, y1);

                start = chrono::high_resolution_clock::now();
                for(int i = 0; i < chavesRegiao.size(); i++){
                  somaAvl += avlTree.BuscaCasos(chavesRegiao[i], compsAVL);
                }
                end = chrono::high_resolution_clock::now();
                int duracaoAVL = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
                start = chrono::high_resolution_clock::now();
                for(int i = 0; i < chavesRegiao.size(); i++){
                    somaB20 += bTree.BuscaCasos(chavesRegiao[i], compsB20);
                }
                end = chrono::high_resolution_clock::now();
                int duracaoB20 = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
                for(int i = 0; i < chavesRegiao.size(); i++){
                    somaB200 += bTree2.BuscaCasos(chavesRegiao[i], compsB200);
                }
                end = chrono::high_resolution_clock::now();
                int duracaoB200 = chrono::duration_cast<chrono::nanoseconds>(end-start).count();

                mediaDuracaoAVL += duracaoAVL;
                mediaDuracaoB20 += duracaoB20;
                mediaDuracaoB200 += duracaoB200;
                mediaCasosAVL += somaAvl;
                mediaCasosB20 += somaB20;
                mediaCasosB200 += somaB200;
                mediaCompsAVL += compsAVL;
                mediaCompsB20 += compsB20;
                mediaCompsB200 += compsB200;


                cout << endl;
                cout << " ----------- RODADA "<< i <<" ----------- " << endl;
                cout << "Casos pela arvore AVL: " << somaAvl << endl;
                cout << "nComparacoes AVL: " << compsAVL << endl;
                cout << "Duração da Busca (AVL): " << duracaoAVL << "ns" << endl;
                cout << "Casos pela arvore B(20): " << somaB20 << endl;
                cout << "nComparacoes B(20): " << compsB20 << endl;
                cout << "Duração da Busca (B(20)): " << duracaoB20<< "ns" << endl;
                cout << "Casos pela arvore B(200): " << somaB200 << endl;
                cout << "nComparacoes B(200): " << compsB200 << endl;
                cout << "Duração da Busca (B(200)): " << duracaoB200<< "ns" << endl;
            }
            cout << " ||||||||||| RESULTADOS |||||||||| " << endl;
            cout << "Media de Casos AVL: " << mediaCasosAVL/m << endl;
            cout << "Media de Casos B20: " << mediaCasosB20/m << endl;
            cout << "Media de Casos B200: " << mediaCasosB200/m << endl;
            cout << "Media de Duracao AVL: " << mediaDuracaoAVL/m << endl;
            cout << "Media de Duracao B20: " << mediaDuracaoB20/m << endl;
            cout << "Media de Duracao B200: " << mediaDuracaoB200/m << endl;
            cout << "Media de Comps AVL: " << mediaCompsAVL/m << endl;
            cout << "Media de Comps B20: " << mediaCompsB20/m << endl;
            cout << "Media de Comps B200: " << mediaCompsB200/m << endl;


        }
        case 'z':
        {
            int m, n;
            float mediaCompsAVL = 0, mediaCompsB20 = 0, mediaCompsB200 = 0,
                mediaDuracaoAVL = 0, mediaDuracaoB20 = 0, mediaDuracaoB200 = 0,
                mediaCasosAVL = 0, mediaCasosB20 = 0, mediaCasosB200 = 0;
            chrono::high_resolution_clock::time_point start, end;
            double x0, y0, x1, y1;

            // Inicializa estruturas 'estaticas' (hashtable e quadTree
            for(int i = 0; i < vet.size(); i++){
                quad.inserir(vet[i]);
            }
            hash.clear();
            for( int i = 0; i < regs.size(); i++ ){
                hash.insert( regs[i] );
            }

            // inputs;
            cout << "Quantas iteracoes (M)? ";
            cin >> m;
            cout<< "Digite os valores de (x0, y0) e (x1,y1) " << endl;
            cin >> x0 >> y0 >> x1 >> y1;
            vector<float> valoresAleatorios{1e4, 5e4, 1e5, 5e5, 1e6};

            quad.buscaIntervaloAux(chavesRegiao, x0, x1, y0, y1); // A mesma regiao para todos
            for(float val : valoresAleatorios){
                float mediaCompsAVL = 0, mediaCompsB20 = 0, mediaCompsB200 = 0,
                    mediaDuracaoAVL = 0, mediaDuracaoB20 = 0, mediaDuracaoB200 = 0,
                    mediaCasosAVL = 0, mediaCasosB20 = 0, mediaCasosB200 = 0;
                    n = (int) val;
                for(int i = 0; i < m; i++){
                    // mediaCompsAVL = 0, mediaCompsB20 = 0, mediaCompsB200 = 0,
                    // mediaDuracaoAVL = 0, mediaDuracaoB20 = 0, mediaDuracaoB200 = 0,
                    // mediaCasosAVL = 0, mediaCasosB20 = 0, mediaCasosB200 = 0;
                    somaB20 = 0;
                    somaB200 = 0;
                    somaAvl = 0;
                    compsB20 = 0;
                    compsB200 = 0;
                    compsAVL = 0;
                    auto nAleatorios = hash.getNRandomHashCodes(n);
                    avlTree.Limpar();
                    bTree.Limpar();
                    for(auto hashCode : nAleatorios){
                        avlTree.Insere(hashCode, argsI[9]);
                        // bTree.Insere(hash.at(hashCode), argsI[9]);
                    }// ou seja, ambas estruturas com o mesmo numero de elementos;

                    start = chrono::high_resolution_clock::now();
                    for(int i = 0; i < chavesRegiao.size(); i++){
                      somaAvl += avlTree.BuscaCasos(chavesRegiao[i], compsAVL);
                    }
                    end = chrono::high_resolution_clock::now();
                    int duracaoAVL = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
                    start = chrono::high_resolution_clock::now();
                    for(int i = 0; i < chavesRegiao.size(); i++){
                        // somaB20 += bTree.BuscaCasos(chavesRegiao[i], compsB20);
                    }
                    end = chrono::high_resolution_clock::now();
                    int duracaoB20 = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
                    for(int i = 0; i < chavesRegiao.size(); i++){
                        // somaB200 += bTree2.BuscaCasos(chavesRegiao[i], compsB200);
                    }
                    end = chrono::high_resolution_clock::now();
                    int duracaoB200 = chrono::duration_cast<chrono::nanoseconds>(end-start).count();

                    mediaDuracaoAVL += duracaoAVL;
                    // mediaDuracaoB20 += duracaoB20;
                    // mediaDuracaoB200 += duracaoB200;
                    mediaCasosAVL += somaAvl;
                    mediaCasosB20 += somaB20;
                    mediaCasosB200 += somaB200;
                    mediaCompsAVL += compsAVL;
                    mediaCompsB20 += compsB20;
                    mediaCompsB200 += compsB200;
                    duracaoB200 = 0;
                    duracaoB20 = 0;


                    cout << endl;
                    cout << " ----------- RODADA "<< i+1 <<" ----------- " << endl;
                    cout << "Casos pela arvore AVL: " << somaAvl << endl;
                    cout << "nComparacoes AVL: " << compsAVL << endl;
                    cout << "Duração da Busca (AVL): " << duracaoAVL << "ns" << endl;
                    cout << "Casos pela arvore B(20): " << somaB20 << endl;
                    cout << "nComparacoes B(20): " << compsB20 << endl;
                    // cout << "Duração da Busca (B(20)): " << duracaoB20<< "ns" << endl;
                    cout << "Casos pela arvore B(200): " << somaB200 << endl;
                    cout << "nComparacoes B(200): " << compsB200 << endl;
                    // cout << "Duração da Busca (B(200)): " << duracaoB200<< "ns" << endl;
                }
                cout << " ||||||||||| RESULTADOS (" << (int)val << ") |||||||||| " << endl;
                cout << "Media de Casos AVL: " << mediaCasosAVL/m << endl;
                cout << "Media de Casos B20: " << mediaCasosB20/m << endl;
                cout << "Media de Casos B200: " << mediaCasosB200/m << endl;
                cout << "Media de Duracao AVL: " << mediaDuracaoAVL/m << endl;
                cout << "Media de Duracao B20: " << mediaDuracaoB20/m << endl;
                cout << "Media de Duracao B200: " << mediaDuracaoB200/m << endl;
                cout << "Media de Comps AVL: " << mediaCompsAVL/m << endl;
                cout << "Media de Comps B20: " << mediaCompsB20/m << endl;
                cout << "Media de Comps B200: " << mediaCompsB200/m << endl;



            }


            break;
        }
        default:
            goto readCommand;
        break;
    }

    goto printOptions;

    the_end:

    return;
}
