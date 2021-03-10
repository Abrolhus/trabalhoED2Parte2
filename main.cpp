#include "HashTable.h"
#include "Registro.h"
#include <iostream>
#include <fstream>
#include "TADs\ArvoreB.h"
#include "TADs\ArvoreAVL.h"
#include "TADs\interface.h"

using namespace std;
int main(){
    void lerRegistrosParaHashTable(std::ifstream& file, HashTable& ht);
    HashTable ht = HashTable(40);
    string fname = "brazil_covid19_cities_processado.csv";
    ifstream file(fname);
    lerRegistrosParaHashTable(file, ht);
    // ht.print();

    ArvoreAVL avlTree( &ht );
    ArvoreB bTree( &ht , 8 );

    interface( avlTree, bTree );

    return 0;

}
void lerRegistrosParaHashTable(std::ifstream& file, HashTable& ht){
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
    int size = 0;
    while( getline(file,line) )
        size++;
    file.clear(ios_base::goodbit);
    file.seekg(0, file.beg);

    /**
     * REALIZA A LEITURA DOS DADOS SALVANDO EM FORMA DE NÓS
     * ESSES NÓS SÃO OBJETOS QUE ARMAZENAM OS DADOS DE CADA CIDADE
    **/
    getline(file,line); // ( LÊ E JOGA A PRIMEIRA LINHA FORA )

    while( getline(file,line) ){
        string line_aux = line;

        string data = line_aux.substr(0, line_aux.find(','));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        string estado = line_aux.substr(0, line_aux.find(','));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        string cidade = line_aux.substr(0, line_aux.find(','));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        float codigo = stof(line_aux.substr(0, line_aux.find(',')));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        int casos = stof(line_aux.substr(0, line_aux.find(',')));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        int mortes = stoi(line_aux.substr(0, line_aux.find(',')));

        //vet.push_back( new No(data,estado,cidade,codigo,casos,mortes) );
        ht.insert(Registro(data, estado, cidade, int(codigo), casos, mortes));
    }

}
