#include "HashTable.h"
HashTable::HashTable(int size){
    // inicialize all lists. TODO: verify if this is the correct procedure
    for (int i = 0; i < size; i++) {
        this->table.push_back(new std::list<Registro>);
    }
    this->size = size;
}

void HashTable::insert(Registro reg){
    int index = this->hashFunction(reg.getCidade(), reg.getData());
    this->table[index]->push_back(reg);
}

void HashTable::remove(std::string cidade, std::string data){
    int index = hashFunction(cidade, data);
    for(auto it = this->table[index]->begin(); it != this->table[index]->end(); ++it){ // TODO: substitute this->table[index] for a more readable pointer.
        if(it->getCidade() == cidade && it->getData() == cidade){
            this->table[index]->erase(it); //
            return;
        }
    }
}

void HashTable::print(){
    for(auto* lista : this->table){
        std::cout << "nLista:" << std::endl;
        for(auto reg : *lista){
            std::cout << reg.getCidade() << " (" << reg.getData() << ") " << std::endl;
        }
        std::cout << std::endl;
    }
}

int HashTable::hashFunction(std::string cidade, std::string data){
    //simplest hashFunction for testing
    return (int)(((int)cidade[0] + (int)(data[0]) )% this->getSize());
}
int HashTable::getSize(){
    return this->size;
}

