#include "HashTable.h"
int main(){
    HashTable ht = HashTable(5);
    ht.insert({"Belo Horizonte", "MG", 11});
    ht.insert({"Betin", "MG", 21});
    ht.insert({"Juiz de Fora", "MG", 31});
    ht.insert({"Rio de Janeiro", "RJ", 71});
    ht.insert({"Sao Paulo", "SP", 13});
    ht.print();
    return 0;



}
