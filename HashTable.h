#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <list>
#include <vector>
#include "Registro.h"

#define EMPTY 0
#define DELETE_ME 1
#define FULL 2


class Element{
    public:
    int key;
    Registro value;
    int flag;
    Element(int key, int flag){
        this->key = key;
        this->flag = flag;
        this->value = Registro();
    }
};

class HashTable{
    public:
        HashTable(int size);
        void insert(Registro);
        void remove(std::string cidade, std::string data);
        float getLoadFactor();
        int getSize();
        Registro& at(std::string cidade, std::string data);
        Registro& at(int id);
        void print();
    private:
        // std::list<Registro>
        std::vector<Element> table; // using std::list for now, I may implement a linked list container later.
        int size;
        long hashFunction(std::string cidade, std::string data, int i);
};


#endif
