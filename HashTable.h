#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <list>
#include <vector>

typedef struct{
    std::string cidade;
    std::string estado;
    int nCasos;
} Registro;
class HashTable{
    public:
        HashTable(int size);
        void insert(Registro);
        void remove(std::string estado, std::string cidade);
        float getLoadFactor();
        int getSize();
        Registro at(std::string estado, std::string cidade);
        void print();
    private:
        // std::list<Registro>
        std::vector<std::list<Registro>*> table; // using std::list for now, I may implement a linked list container later.
        int size;
        int hashFunction(std::string estado, std::string cidade);
};


#endif
