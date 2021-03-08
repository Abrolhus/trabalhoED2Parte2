#include <iostream>
#include "quadTree.h"


using namespace std;

quadTree::quadTree(ifstream& file)
{
    srand(time(NULL));

    /**
     * VERIFICA SE ARQUIVO FOI ABERTO CORRETAMENTE
     * CASO NAO TENHA SIDO, FECHA O PROGRAMA COM CODIGO DE ERRO
    **/
    if( !file.is_open() ){
        cout << "Não foi possível ler o arquivo" << endl;
        exit(0);
    }

    /**
     * INICIA AS VARIAVEIS DA CLASSE
    **/
    string line;
    this->tam = -1;
    //this->pos = 0;
    while( getline(file,line) )
        this->tam++;
    //this->raiz = new folhaQuadTree[this->tam];
    file.clear(ios_base::goodbit);
    file.seekg(0, file.beg);

    /**
     * REALIZA A LEITURA DOS DADOS SALVANDO EM FORMA DE NÓS
     * ESSES NÓS SÃO OBJETOS QUE ARMAZENAM OS DADOS DE CADA CIDADE
    **/
    getline(file,line); // ( LÊ E JOGA A PRIMEIRA LINHA FORA )

    while( getline(file,line) ){
        string line_aux = line;

        string stateCode = line_aux.substr(0, line_aux.find(','));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        string cityCode = line_aux.substr(0, line_aux.find(','));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        string cidade = line_aux.substr(0, line_aux.find(','));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        float latitude = stof(line_aux.substr(0, line_aux.find(',')));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        float longitude = stof(line_aux.substr(0, line_aux.find(',')));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        string capital = line_aux.substr(0, line_aux.find(','));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        //vet.push_back( new No(data,estado,cidade,codigo,casos,mortes) );
        this->raiz = &folhaQuadTree(stateCode, cityCode, cidade, longitude, latitude, capital);

        //this->pos++;
    }
}

quadTree::~quadTree()
{
}