#include "HashTable.h"
HashTable::HashTable(int size){
    // inicialize all lists. TODO: verify if this is the correct procedure
    this->table  = std::vector<Element>();
    for (int i = 0; i < size; i++) {
        this->table.push_back(Element(i, EMPTY));
    }
    this->size = size;
}

void HashTable::insert(Registro reg){
    int i = 0;
    int index;
    do {
        index = this->hashFunction(reg.getCidade(), reg.getData(), i);
        i++;
    } while(this->table.at(index).flag == FULL && i != this->table.size());
    if(this->table.at(index).flag == FULL){ // TODO: tirar redundancia;
        std::cout << "couldnt insert" << std::endl;
        return;
    }
    this->table.at(index).value = reg;
    this->table.at(index).flag = FULL;
}

void HashTable::remove(std::string cidade, std::string data){
}

void HashTable::print(){
    int count = 0;
    for(int i = 0; i < this->table.size(); i++){
        if(this->table.at(i).flag == FULL){
            count++;
            std::cout << this->table.at(i).value.getCidade() << " (" << this->table.at(i).value.getData() << ") " << std::endl;
        }
    }
    std::cout << count << std::endl;
    std::cout << this->table.size() << std::endl;
}

long HashTable::hashFunction(std::string cidade, std::string data, int i){
    //simplest hashFunction for testing
    unsigned long hash = 5381;
    unsigned long hash2 = 0;
    std::string str = cidade + data;
    int c;
    int j = 0;

    while ( j < str.size()){
        c = (int)str[j];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        hash2 = c + (hash2 << 6) + (hash2 << 16) - hash2;
        j++;
    }
    return (hash + i*(hash2))%this->table.size();
    // return (int)(((int)cidade[0] + (int)(data[0]) + i )% this->getSize());
}
int HashTable::getSize(){
    return this->size;
}
Registro& HashTable::at(std::string cidade, std::string data){
    int index;
    int i = 0;
    while(i < this->getSize()){
        index = this->hashFunction(cidade, data, i);
        Element* element = &this->table.at(index);
        if(element->flag == FULL){
            if(element->value.getCidade() == cidade && element->value.getData() == data){
                return element->value;
            }
        }
        i++;
    }
    // if(this->table.at(index).flag == FULL || this->table.at(index).flag == DELETE_ME){ // TODO: tirar redundancia;
    // TODO: throw error;
    return this->table.at(index).value;
}
Registro& HashTable::at(int index){
    // TODO: throw exception
    return this->table.at(index).value;
}
int HashTable::getIndexOf(std::string cidade, std::string data){
    int i = 0;
    int index;
    while(i < this->getSize()){
        index = this->hashFunction(cidade, data, i);
        Element* element = &this->table.at(index);
        if(element->flag == FULL){
            if(element->value.getCidade() == cidade && element->value.getData() == data){
                return element->key;
            }
        }
        i++;
    }
    // if(this->table.at(index).flag == FULL || this->table.at(index).flag == DELETE_ME){ // TODO: tirar redundancia;
    // TODO: throw error;
    return -1;


}

