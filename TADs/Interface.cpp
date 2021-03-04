#include "Interface.h"
#include <iostream>

using namespace std;

void interface( ArvoreAVL& avlTree, ArvoreB& bTree )
{
    string args[10];
    char command;
    int argsI[10];

    printOptions:

    cout << "===== INTERFACE =====" << endl;
    cout << "i - Inserção de N registros" << endl;
    cout << "s - Fechar programa" << endl;
    cout << "=====================" << endl;

    readCommand:

    cin >> command;

    switch (command)
    {
        case 's':
            goto the_end;
        break;

        case 'i':
            cout << "Digite o valor de N: ";
            cin >> argsI[0];

            notUnderstoodTree:
            cout << "Qual estrutura de dados deseja usar ? ("
                << "quad," << "hash," << "avl," << "b" << ")"
                << endl;
            cin >> args[0];

            if( args[0].compare("quad") == 0 )
            {

            }
            else if( args[0].compare("hash") == 0 )
            {

            }
            else if( args[0].compare("avl") == 0 )
            {

            }
            else if( args[0].compare("b") == 0 )
            {

            }
            else
            {
                goto notUnderstoodTree;
            }

        break;
        
        default: 
            goto readCommand;
        break;
    }

    goto printOptions;

    the_end:

    return;
}