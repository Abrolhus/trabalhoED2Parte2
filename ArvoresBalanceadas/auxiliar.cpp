#include "auxiliar.h"
#include <string>

/**
 * @param data01 Data principal
 * @param data02 Data a ser comparada
 * @return -1 Caso data02 < data01 | 1 Caso data02 > data01 | 0 Caso data02 = data01  
 */
int DataCompare( string data01, string data02 )
{
    return (
        stoi(data01.substr(0,4)) < stoi(data02.substr(0,4)) ?
            1:
            stoi(data01.substr(0,4)) > stoi(data02.substr(0,4)) ?
                -1:
                stoi(data01.substr(5,2)) < stoi(data02.substr(5,2)) ?
                    1:
                    stoi(data01.substr(5,2)) > stoi(data02.substr(5,2)) ?
                        -1:
                        stoi(data01.substr(8,2)) < stoi(data02.substr(8,2)) ?
                            1:
                            stoi(data01.substr(8,2)) > stoi(data02.substr(8,2)) ?
                                -1:
                                0
    );
}