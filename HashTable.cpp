#include "HashTable.h"
HashTable::HashTable(int size){
    // inicialize all lists. TODO: verify if this is the correct procedure
    for (int i = 0; i < size; i++) {
        this->table.push_back(new std::list<Registro>);
    }
    this->size = size;
}

void HashTable::insert(Registro reg){
    int index = this->hashFunction(reg.estado, reg.cidade);
    this->table[index]->push_back(reg);
}

void HashTable::remove(std::string estado, std::string cidade){
    int index = hashFunction(estado, cidade);
    for(auto it = this->table[index]->begin(); it != this->table[index]->end(); ++it){ // TODO: substitute this->table[index] for a more readable pointer.
        if(it->estado == estado && it->cidade == cidade){
            this->table[index]->erase(it); //
            return;
        }
    }
}

void HashTable::print(){
    for(auto* lista : this->table){
        std::cout << "nLista:" << std::endl;
        for(auto reg : *lista){
            std::cout << reg.cidade << " (" << reg.estado << ") " << reg.nCasos << std::endl;
        }
        std::cout << std::endl;
    }
}

int HashTable::hashFunction(std::string estado, std::string cidade){
    //simplest hashFunction for testing
    return (int)(((int)estado[0] + (int)(cidade[0]) )% this->getSize());
}
int HashTable::getSize(){
    return this->size;
}

