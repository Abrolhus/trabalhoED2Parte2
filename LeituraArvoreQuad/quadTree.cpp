#include <iostream>
#include "quadTree.h"


using namespace std;

quadTree::quadTree()
{
    this->tam = 0;
    this->itera = 0;
    this->raiz = NULL;
    //cout << tam;
}

quadTree::~quadTree()
{
    desalocar(raiz);
}

void quadTree:: desalocar(folhaQuadTree* r){
    if (r->getNE() != NULL) desalocar(r->getNE());
    if (r->getSE() != NULL) desalocar(r->getSE());
    if (r->getNW() != NULL) desalocar(r->getNW());
    if (r->getSW() != NULL) desalocar(r->getSW());
    delete r;
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
            //this-> itera++;
        }
        
    }
}

bool quadTree::confereIntervalo(folhaQuadTree* r, double x0, double x1, double y0, double y1, vector<int>& s, int& comps){
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
                    comps = comps+4;
                    return true; //adicionar ao retorno
                }
        }
    }
    if (y0 == y1){
        if (r->getLongitude() == y0){
            if(r->getLatitude() >= x0 && r->getLatitude()<=x1){
                s.push_back(r->getCityCode());
                comps = comps+4;
                return true;
            }
        }
    }
    if(r->getLatitude() >= x0 && r->getLatitude()<=x1){
        if(r->getLongitude() >= y0 && r->getLongitude()<= y1){
            s.push_back(r->getCityCode());
            comps = comps+4;
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


void quadTree:: buscaIntervalo(folhaQuadTree* r, double x0, double x1, double y0, double y1, vector<int>& s, int& comps){
    
    if(r != NULL){
        if(confereIntervalo(r, x0, x1, y0, y1, s, comps)){
            if(r->getNE() != NULL) buscaIntervalo(r->getNE(), x0, x1, y0, y1, s, comps);
            if(r->getSE() != NULL) buscaIntervalo(r->getSE(), x0, x1, y0, y1, s, comps);
            if(r->getNW() != NULL) buscaIntervalo(r->getNW(), x0, x1, y0, y1, s, comps);
            if(r->getSW() != NULL) buscaIntervalo(r->getSW(), x0, x1, y0, y1, s, comps);
        }
        else{
            if(r->getLatitude() > x0 && r->getLatitude() > x1){
                if (r->getLongitude() > y0 && r->getLongitude() > y1){
                    comps = comps+2;
                    if(r->getSW() != NULL) buscaIntervalo(r->getSW(), x0, x1, y0, y1, s, comps);
                }
                if (r->getLongitude() > y0 && r->getLongitude() < y1){
                    comps = comps+2;
                    if(r->getSW() != NULL) buscaIntervalo(r->getSW(), x0, x1, y0, y1, s, comps);
                    if(r->getNW() != NULL) buscaIntervalo(r->getNW(), x0, x1, y0, y1, s, comps);
                }
                if(r->getLongitude() < y0 && r->getLongitude() < y1){
                    comps = comps+2;
                    if(r->getNW() != NULL) buscaIntervalo(r->getNW(), x0, x1, y0, y1, s, comps);
                }
            }
            if(r->getLatitude() > x0 && r->getLongitude() < x1){
                if (r->getLongitude() > y0 && r->getLongitude() > y1){
                    comps = comps+2;
                    if(r->getSW() != NULL) buscaIntervalo(r->getSW(), x0, x1, y0, y1, s, comps);
                    if(r->getSE() != NULL) buscaIntervalo(r->getSE(), x0, x1, y0, y1, s, comps);
                }
                if(r->getLongitude() < y0 && r->getLongitude() < y1){
                    comps = comps+2;
                    if(r->getNW() != NULL) buscaIntervalo(r->getNW(), x0, x1, y0, y1, s, comps);
                    if(r->getNE() != NULL) buscaIntervalo(r->getNE(), x0, x1, y0, y1, s, comps);
                }
            }
            if(r->getLatitude() < x0 && r->getLatitude() < x1){
                if (r->getLongitude() > y0 && r->getLongitude() > y1){
                    comps = comps+2;
                    if(r->getSE() != NULL) buscaIntervalo(r->getSE(), x0, x1, y0, y1, s, comps);
                }
                if (r->getLongitude() > y0 && r->getLongitude() < y1){
                    comps = comps+2;
                    if(r->getSE() != NULL) buscaIntervalo(r->getSE(), x0, x1, y0, y1, s, comps);
                    if(r->getNE() != NULL) buscaIntervalo(r->getNE(), x0, x1, y0, y1, s, comps);
                }
                if(r->getLongitude() < y0 && r->getLongitude() < y1){
                    comps = comps+2;
                    if(r->getNE() != NULL) buscaIntervalo(r->getNE(), x0, x1, y0, y1, s, comps);
                }
            }
        }
    }
}

void quadTree::buscaIntervaloAux(vector<int>& s, double x0, double x1, double y0, double y1){
    auto ts = chrono::high_resolution_clock::now();
    int comps=0;
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
    buscaIntervalo(r, x0, x1, y0, y1, s, comps);
    for (int i = 0; i < s.size(); i++){
        s[i] = s[i]/10;
    }
    if (s.size() == 0){
        cout<< "Nenhuma cidade encontrada no intervalo" << endl;
        return;
    } 
    auto te = chrono::high_resolution_clock::now();
    double duration = chrono::duration_cast<chrono::milliseconds>(te-ts).count();
    cout<< "<<<< QuadTree >>>>" << endl;
    cout << "Tempo de busca do intervalo: " << duration << endl;
    cout << "Comparacoes: " << comps << endl;
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