#ifndef REGISTRO_H
#define REGISTRO_H
#include <iostream>
class Registro {
    private:
        std::string estado;
        std::string data;
        int codigo;
        std::string cidade;
        int casos;
        int mortes;
    public:
        Registro(std::string data, std::string estado, std::string cidade, int codigo, int casos, int mortes);
        Registro();
        std::string getData(){ return this->data; }
        std::string getCidade(){ return this->cidade; }
        int getId(){ return this->codigo; }
        int getCasos(){ return this->casos; }
        int getCode(){ return this->codigo;}
};
#endif
