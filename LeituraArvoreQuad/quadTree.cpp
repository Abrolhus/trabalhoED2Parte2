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
    this->tam = 0;
    //this->pos = 0;
    //while( getline(file,line) )
    //    this->tam++;
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
        if (tam == 0)this->raiz = new folhaQuadTree(stateCode, cityCode, cidade, longitude, latitude, capital);
        else {
            folhaQuadTree *p = new folhaQuadTree(stateCode, cityCode, cidade, longitude, latitude, capital);
            inserir(raiz, p);
        }
        this->tam++;
    }
}

quadTree::~quadTree()
{
}

folhaQuadTree* quadTree::compara(folhaQuadTree *raiz, folhaQuadTree* i){
    if (i->getLatitude() < raiz->getLatitude()){
        if(i->getLongitude() < raiz->getLongitude()){
            return raiz->getSW();
        }
        else {
            return raiz->getNW();
        }
    }
    else {
        if(i->getLongitude() < raiz->getLongitude()){
            return raiz->getSE();
        }
        else{
            return raiz->getNE();
        }
    }
}

void quadTree::inserir(folhaQuadTree* raiz, folhaQuadTree* i){
    folhaQuadTree* quadrante = NULL;
    if(raiz == NULL){
        this->raiz = i;
    }
    else{
        while(raiz != NULL){
            folhaQuadTree* pai = raiz;
            quadrante = compara(pai, i);
            raiz = quadrante; 
        }
        if(raiz == NULL){
            quadrante = i;
        }
    }
}

bool quadTree::confereIntervalo(folhaQuadTree* r, float x0, float x1, float y0, float y1){
    /*if (x0 < x1 && y0 < y1){
        if(raiz->getLatitude() >= x0 && raiz->getLatitude()<=x1){
            if(raiz->getLongitude() >= y0 && raiz->getLongitude()<= y1){
                raiz->getCityCode(); //adicionar ao retorno
            }
        }
    }
    if(x0 > x1 && y0 > y1){
        if(raiz->getLatitude() <= x0 && raiz->getLatitude() >= x1){
            if(raiz->getLongitude() <= y0 && raiz->getLongitude() >= y1){
                raiz->getCityCode(); //adicionar ao retorno
            }
        }
    }
    if(x0 < x1 && y0 > y1){
        if(raiz->getLatitude() <= x0 && raiz->getLatitude() >= x1){
            if(raiz->getLongitude() <= y0 && raiz->getLongitude() >= y1){
                raiz->getCityCode(); //adicionar ao retorno
            }
        }
    }*/

    if (x0 == x1){
        if(raiz->getLatitude() == x0){
            if(y0 < y1){
                    if(raiz->getLongitude() >= y0 && raiz->getLongitude()<= y1){
                        raiz->getCityCode(); //adicionar ao retorno
                    }
                }
            else{
                if(raiz->getLongitude() <= y0 && raiz->getLongitude() >= y1){
                    raiz->getCityCode(); //adicionar ao retorno
                }
            }
        }
    }
    if (y0 == y1){
        if (raiz->getLongitude() == y0){
            if(x0<x1){
                if(raiz->getLatitude() >= x0 && raiz->getLatitude()<=x1){
                    raiz->getCityCode();
                }
            }
            else{
                if(raiz->getLatitude() <= x0 && raiz->getLatitude() >= x1){
                    raiz->getCityCode();
                }
            }
        }
    }

    if (x0 < x1){
        if(raiz->getLatitude() >= x0 && raiz->getLatitude()<=x1){
            if(y0 < y1){
                if(raiz->getLongitude() >= y0 && raiz->getLongitude()<= y1){
                    raiz->getCityCode(); //adicionar ao retorno
                }
            }
            else{
                if(raiz->getLongitude() <= y0 && raiz->getLongitude() >= y1){
                    raiz->getCityCode(); //adicionar ao retorno
                }
            }
        }
    }
    else{
        if(raiz->getLatitude() <= x0 && raiz->getLatitude() >= x1){
            if(y0 < y1){
                if(raiz->getLongitude() >= y0 && raiz->getLongitude()<= y1){
                    raiz->getCityCode(); //adicionar ao retorno
                }
            }
            else{
                if(raiz->getLongitude() <= y0 && raiz->getLongitude() >= y1){
                    raiz->getCityCode(); //adicionar ao retorno
                }
            }
        } 
    }
}

folhaQuadTree* quadTree::comparaComIntervalo(folhaQuadTree *r, float x0, float x1, float y0, float y1){
    if (x0 < r->getLatitude()){
        if(y0 < r->getLongitude()){
            return r->getSW();
        }
        else {
            return r->getNW();
        }
    }
    else {
        if(y0 < r->getLongitude()){
            return r->getSE();
        }
        else{
            return r->getNE();
        }
    }
}

void quadTree:: buscaIntervalo(folhaQuadTree* r, float x0, float x1, float y0, float y1){
    if(r != NULL){
        if(confereIntervalo(r, x0, x1, y0, y1)){
            if(r->getNE() != NULL) buscaIntervalo(r->getNE(), x0, x1, y0, y1);
            if(r->getSE() != NULL) buscaIntervalo(r->getSE(), x0, x1, y0, y1);
            if(r->getNW() != NULL) buscaIntervalo(r->getNW(), x0, x1, y0, y1);
            if(r->getSW() != NULL) buscaIntervalo(r->getSW(), x0, x1, y0, y1);
        }
        else{
            buscaIntervalo(comparaComIntervalo(r,x0,x1,y0,y1), x0, x1, y0, y1); //caso nao esteja no intervalo, determinar em qual quadrante o intervalo esta
        }
    }
}