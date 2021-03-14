#ifndef INTERFACE_H
#define INTERFACE_H

#include "ArvoresBalanceadas/ArvoreAVL.h"
#include "ArvoresBalanceadas/ArvoreB.h"
#include "LeituraArvoreQuad/quadTree.h"
#include "HashTable.h"
#include <vector>
#include "Registro.h"

// void interface( ArvoreAVL&, ArvoreB&, HashTable&, vector<Registro>& );
void interface( ArvoreAVL&, ArvoreB&, quadTree&, HashTable&, vector<Registro>& );

#endif