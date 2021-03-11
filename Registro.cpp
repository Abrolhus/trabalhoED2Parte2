#include "Registro.h"
Registro::Registro(std::string data, std::string estado, std::string cidade, int codigo, int casos, int mortes){
    this->data = data;
    this->estado = estado;
    this->cidade = cidade;
    this->codigo = codigo;
    this->casos = casos;
    this->mortes = mortes;
}
Registro::Registro(){
    this->data = "";
    this->estado = "";
    this->cidade = "";
    this->codigo = 0;
    this->casos = 0;
    this->mortes = 0;

}
