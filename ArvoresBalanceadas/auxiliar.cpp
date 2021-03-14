#include "auxiliar.h"
#include <string>

/**
 * @param data01 Data principal
 * @param data02 Data a ser comparada
 * @return -1 Caso data02 < data01 | 1 Caso data02 > data01 | 0 Caso data02 = data01  
 */
int DataCompare( string data01, string data02 )
{
    if( stoi(data01.substr(0,4)) < stoi(data02.substr(0,4)) )
        return 1;
    else if( stoi(data01.substr(0,4)) > stoi(data02.substr(0,4)) )
        return -1;
    else if( stoi(data01.substr(5,2)) < stoi(data02.substr(5,2)) )
        return 1;
    else if( stoi(data01.substr(5,2)) > stoi(data02.substr(5,2)) )
        return -1;
    else if( stoi(data01.substr(8,2)) < stoi(data02.substr(8,2)) )
        return 1;
    else if( stoi(data01.substr(8,2)) > stoi(data02.substr(8,2)) )
        return -1;
    else
        return 0;
}