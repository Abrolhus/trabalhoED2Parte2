#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <list>
#include <vector>
#include "Registro.h"

class HashTable{
    public:
        HashTable(int size);
        void insert(Registro);
        void remove(std::string cidade, std::string data);
        float getLoadFactor();
        int getSize();
        Registro at(std::string cidade, std::string data);
        void print();
    private:
        // std::list<Registro>
        std::vector<std::list<Registro>*> table; // using std::list for now, I may implement a linked list container later.
        int size;
        int hashFunction(std::string cidade, std::string data);
};


#endif
