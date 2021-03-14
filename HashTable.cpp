#include "HashTable.h"
#include <math.h>
HashTable::HashTable(int size){
    /* inicialize the Hash Table's vector with all elements flagged as EMPTY.
     * Uses the defaut Registro's constructor to inicialize the so called 'empty' Registro
     */
    // inicialize all lists. TODO: verify if this is the correct procedure
    this->table  = std::vector<Element>();
    for (int i = 0; i < size; i++) {
        this->table.push_back(Element(i, EMPTY));
    }
    this->size = size;


    // for testing hash function
    this->numeroDePares = 0;
    this->numeroDeImpares = 0;
    this->nConfitos = 0;
    this->sondagens = 0;
}

void HashTable::insert(Registro reg){
    /* Inserts Registro */
    int i = 0;
    int index;
    do {
    if(i >10)
        std::cout << i << " " ;
        index = this->hashFunction(reg.getCode(), reg.getData(), i);
        i++;
    } while(this->table.at(index).flag == FULL && i != this->table.size());
    if(this->table.at(index).flag == FULL){ // TODO: tirar redundancia;
        std::cout << "couldnt insert" << std::endl;
        return;
    }
    this->nConfitos += i -1+1;

    this->table.at(index).value = reg;
    this->table.at(index).flag = FULL;
}

void HashTable::remove(int codigoCidade, std::string data){
    /* removes element */
}

void HashTable::print(){
    /* Print out the table for debugging.
     */
    int count = 0;
    for(int i = 0; i < this->table.size(); i++){
        if(this->table.at(i).flag == FULL){
            count++;
            // std::cout << this->table.at(i).value.getCidade() << " (" << this->table.at(i).value.getData() << ") " << std::endl;
            std::cout << table.at(i).value.getCode() << std::endl;
            if(i != table.at(i).key)
                std::cout << "ERROR";
        }
    }
    std::cout << count << std::endl;
    std::cout << "acessos: " << nConfitos/(float)1431490 << std::endl;
    std::cout << this->table.size() << std::endl;
}

long HashTable::hashFunction(int codigoCidade, std::string data, int i){
    /* Hash Function expecific for double hashing.
     * (h(x, i) = h1(x) + i*h2(x)) mod m
     * m: size of hash table
     * h1: djb2
     * h2: sdbm
     * both djb2 and sdbm are avaliable at http://www.cse.yorku.ca/~oz/hash.html
     */
    unsigned long hash = 5381;
    unsigned long hash2 = 0;
    std::string str = data + std::to_string(codigoCidade);
    // int numData = data[0]*pow(10, 7) +data[1]*pow(10, 6) + data[3]*pow(10, 5) + data[4]*pow(10, 4)  + data[6]*pow(10, 3) +data[7]*pow(10, 2) + data[8]*pow(10, 1) + data[9]*pow(10, 0);
    // std::cout << data;
    int c;
    int j = 0;

    while ( j < str.size()){
        c = (int)str[j];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        hash2 = c + (hash2 << 6) + (hash2 << 16) - hash2;
        j++;
    }
    return (hash + i*(hash2))%this->table.size();
}

int HashTable::getSize(){
    return this->size;
}

Registro& HashTable::at(int codigoCidade, std::string data){
    /* returns reference to Registro at given key (codigoCidade, data)
     */
    int index;
    int i = 0;
    while(i < this->getSize()){
        index = this->hashFunction(codigoCidade, data, i);
        Element* element = &this->table.at(index);
        if(element->flag == FULL){
            if(element->value.getCode() == codigoCidade && element->value.getData() == data){
                return element->value;
            }
        }
        i++;
    }
    // if(this->table.at(index).flag == FULL || this->table.at(index).flag == DELETE_ME){ // TODO: tirar redundancia;
    // TODO: throw exception;
    return this->table.at(index).value;
}
Registro& HashTable::at(int index){
    /* returns reference to Registro at given index / hashCode */
    // TODO: throw exception
    return this->table.at(index).value;
}
int HashTable::getIndexOf(int codigoCidade, std::string data){
    /* returns index of Registro corresponding to both given city code and date
     */
    int i = 0;
    int index;
    while(i < this->getSize()){
        index = this->hashFunction(codigoCidade, data, i);
        Element* element = &this->table.at(index);
        if(element->flag == FULL){
            if(element->value.getCode() == codigoCidade && element->value.getData() == data){
                return element->key;
            }
        }
        i++;
    }
    // if(this->table.at(index).flag == FULL || this->table.at(index).flag == DELETE_ME){ // TODO: tirar redundancia;
    // TODO: throw error;
    return -1;


}
void HashTable::clear(){
    /* Erases all elements.
     * It actually doesn't, only marks all of them as free space
     */
    for(auto& element : this->table){
        element.flag = EMPTY;
    }// the elements are not erased, so if you are willing to store some heavy elements, this solution may not be suitable;
}
std::vector<int> HashTable::getNRandomHashCodes(int n){
    /* returns index of N different random elements
     */
    std::vector<int> hashCodes;
    std::vector<int> nRandomHashCodes;
    for(auto element : this->table){
        if(element.flag == FULL){
            hashCodes.push_back(element.key);
        }
    } // copies all hashCodes to this vector
    int index;
    int aux;
    for(int i = 0; i < n; i++){ // based on Fisher–Yates shuffle
        index = rand()%(hashCodes.size() - i) + i;
        nRandomHashCodes.push_back(hashCodes.at(index));
        hashCodes.at(index) = hashCodes.at(i);
    }
    std::cout << "\n" << nRandomHashCodes.size() << std::endl;
    return nRandomHashCodes;
}



