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
    this->itera = 0;
    this->raiz = NULL;
    while( getline(file,line) ){
        string line_aux = line;

        string stateCode = line_aux.substr(0, line_aux.find(','));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        string cityCode = line_aux.substr(0, line_aux.find(','));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        string cidade = line_aux.substr(0, line_aux.find(','));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        double latitude = stof(line_aux.substr(0, line_aux.find(',')));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        double longitude = stof(line_aux.substr(0, line_aux.find(',')));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        string capital = line_aux.substr(0, line_aux.find(','));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        //vet.push_back( new No(data,estado,cidade,codigo,casos,mortes) );
        /*if (tam == 0){
            this->raiz = new folhaQuadTree(stateCode, cityCode, cidade, longitude, latitude, capital);
            this->tam++;
        }*/
        folhaQuadTree *p = new folhaQuadTree(stateCode, cityCode, cidade, longitude, latitude, capital);
        inserir(p);
        this->tam++;
    }
}

quadTree::~quadTree()
{
}

char quadTree::compara(folhaQuadTree *r, folhaQuadTree* i){
    if (i->getLatitude() < r->getLatitude()){
        if(i->getLongitude() < r->getLongitude()){
            return r->getSudoeste();
        }
        else {
            return r->getNoroeste();
        }
    }
    else {
        if(i->getLongitude() < r->getLongitude()){
            return r->getSudoeste();
        }
        else{
            return r->getNordeste();
        }
    }
}

void quadTree::inserir(folhaQuadTree* i){
    folhaQuadTree* r = raiz;
    if(this->raiz == NULL){
        this->raiz = i;
        return;
    }
    else{
        while(r != NULL){
            folhaQuadTree* pai = r;
            char quadrante = compara(pai, i);
            r = pai->getFilho(quadrante); 
            if(r == NULL){
                pai->setFilho(quadrante, i);
            }
            this-> itera++;
        }
        
    }
}

bool quadTree::confereIntervalo(folhaQuadTree* r, double x0, double x1, double y0, double y1, vector<string>& s){
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
        if(r->getLatitude() == x0){
                if(r->getLongitude() >= y0 && r->getLongitude()<= y1){
                    s.push_back(r->getCityCode());
                    return true; //adicionar ao retorno
                }
        }
    }
    if (y0 == y1){
        if (r->getLongitude() == y0){
            if(r->getLatitude() >= x0 && r->getLatitude()<=x1){
                s.push_back(r->getCityCode());
                return true;
            }
        }
    }
    cout<< "chegou4" << endl;
    //cout << r->getLatitude()<< r->getLongitude()<< endl;
    if(r->getLatitude() >= x0 && r->getLatitude()<=x1){
        if(r->getLongitude() >= y0 && r->getLongitude()<= y1){
            s.push_back(r->getCityCode());
            return true; //adicionar ao retorno
        }
    }

    return false;
    
    /*else{
        if(r->getLatitude() <= x0 && r->getLatitude() >= x1){
            if(y0 < y1){
                if(r->getLongitude() >= y0 && r->getLongitude()<= y1){
                    r->getCityCode(); //adicionar ao retorno
                }
            }
            else{
                if(r->getLongitude() <= y0 && r->getLongitude() >= y1){
                    r->getCityCode(); //adicionar ao retorno
                }
            }
        } 
    }*/
}


void quadTree:: buscaIntervalo(folhaQuadTree* r, double x0, double x1, double y0, double y1, vector<string>& s){
    
    if(r != NULL){
        if(confereIntervalo(r, x0, x1, y0, y1, s)){
            if(r->getNE() != NULL) buscaIntervalo(r->getNE(), x0, x1, y0, y1, s);
            if(r->getSE() != NULL) buscaIntervalo(r->getSE(), x0, x1, y0, y1, s);
            if(r->getNW() != NULL) buscaIntervalo(r->getNW(), x0, x1, y0, y1, s);
            if(r->getSW() != NULL) buscaIntervalo(r->getSW(), x0, x1, y0, y1, s);
        }
        else{
            if(r->getLatitude() > x0 && r->getLatitude() > x1){
                if (r->getLongitude() > y0 && r->getLongitude() > y1){
                    if(r->getSW() != NULL) buscaIntervalo(r->getSW(), x0, x1, y0, y1, s);
                }
                if (r->getLongitude() > y0 && r->getLongitude() < y1){
                    if(r->getSW() != NULL) buscaIntervalo(r->getSW(), x0, x1, y0, y1, s);
                    if(r->getNW() != NULL) buscaIntervalo(r->getNW(), x0, x1, y0, y1, s);
                }
                if(r->getLongitude() < y0 && r->getLongitude() < y1){
                    if(r->getNW() != NULL) buscaIntervalo(r->getNW(), x0, x1, y0, y1, s);
                }
            }
            if(r->getLatitude() > x0 && r->getLongitude() < x1){
                if (r->getLongitude() > y0 && r->getLongitude() > y1){
                    if(r->getSW() != NULL) buscaIntervalo(r->getSW(), x0, x1, y0, y1, s);
                    if(r->getSE() != NULL) buscaIntervalo(r->getSE(), x0, x1, y0, y1, s);
                }
                if(r->getLongitude() < y0 && r->getLongitude() < y1){
                    if(r->getNW() != NULL) buscaIntervalo(r->getNW(), x0, x1, y0, y1, s);
                    if(r->getNE() != NULL) buscaIntervalo(r->getNE(), x0, x1, y0, y1, s);
                }
            }
            if(r->getLatitude() < x0 && r->getLatitude() < x1){
                if (r->getLongitude() > y0 && r->getLongitude() > y1){
                    if(r->getSE() != NULL) buscaIntervalo(r->getSE(), x0, x1, y0, y1, s);
                }
                if (r->getLongitude() > y0 && r->getLongitude() < y1){
                    if(r->getSE() != NULL) buscaIntervalo(r->getSE(), x0, x1, y0, y1, s);
                    if(r->getNE() != NULL) buscaIntervalo(r->getNE(), x0, x1, y0, y1, s);
                }
                if(r->getLongitude() < y0 && r->getLongitude() < y1){
                    if(r->getNE() != NULL) buscaIntervalo(r->getNE(), x0, x1, y0, y1, s);
                }
            }
        }
    }
}

void quadTree::buscaIntervaloAux(vector<string>& s, double x0, double x1, double y0, double y1){
    if(x1 < x0){
        double aux = 0;
        aux  = x0;
        x0 = x1;
        x1 = aux;
    } 
    if(y1 < y0){
        double aux = 0;
        aux = y0;
        y0 = y1;
        y1 = aux;
    }
    folhaQuadTree* r = raiz;
    buscaIntervalo(r, x0, x1, y0, y1, s);
}


void quadTree:: imprimir(){
    imprimirAux(raiz);
}

void quadTree::imprimirAux(folhaQuadTree* r){
    if(r !=NULL){
        cout << r->getCidade() << r->getLongitude() << r->getLatitude() << endl;
        if (r->getNE() != NULL) imprimirAux(r->getNE());
        if (r->getSE() != NULL) imprimirAux(r->getSE());
        if (r->getNW() != NULL) imprimirAux(r->getNW());
        if (r->getSW() != NULL) imprimirAux(r->getSW());
    } 
}