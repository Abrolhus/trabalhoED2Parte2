#include "HashTable.h"
#include "Registro.h"
#include <iostream>
#include <fstream>
#include "ArvoresBalanceadas\ArvoreB.h"
#include "ArvoresBalanceadas\ArvoreAVL.h"
#include "LeituraArvoreQuad\quadTree.h"
#include "interface.h"
#include <vector>
#include "math.h"

using namespace std;

vector<Registro> lerRegistrosParaHashTable( std::ifstream&, HashTable& );

int main( int argc, char** argv ){

    string filename_covid = "brazil_covid19_cities_processado.csv";
    string filename_coords = "brazil_cities_coordinates.csv";

    if( argc == 2 )
    {
        filename_covid = argv[1]+("/"+filename_covid);
        filename_coords = argv[1]+("/"+filename_coords);
    }        

    ifstream file_covid(filename_covid);
    ifstream file_coords(filename_coords);
    
    HashTable ht = HashTable( (int)pow(2,22) );
    cout << "Hashtable Criada" << endl;
    ArvoreAVL avlTree( &ht );
    cout << "AVL Criada" << endl;
    // quadTree qTree(file_coords);
    ArvoreB bTree( &ht , 8 );
    cout << "B Criada" << endl;

    vector<Registro> registros = lerRegistrosParaHashTable(file_covid, ht);
    cout << "Registros lidos" << endl;

    // int chave;
    // for( int i = 0; i < registros.size(); i++ )
    // {
    //     chave = ht.getIndexOf( registros[i].getCidade(), registros[i].getData() );
    //     avlTree.Insere( chave );
    //     bTree.Insere( chave );
    // }
    // cout << "AVL e B Carregadas" << endl;
    // interface( avlTree, bTree, qTree, ht, registros );
    interface( avlTree, bTree, ht, registros );

    return 0;

}
vector<Registro> lerRegistrosParaHashTable(std::ifstream& file, HashTable& ht){
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
     * SEPARA VETOR
     */
    vector<Registro> regs;

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
        Registro reg(data, estado, cidade, int(codigo), casos, mortes);
        regs.push_back( reg );
    }

    return regs;

}
