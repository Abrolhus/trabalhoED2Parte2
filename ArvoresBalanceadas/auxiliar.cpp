#include "auxiliar.h"
#include <string>

/**
 * @param data01 Data principal
 * @param data02 Data a ser comparada
 * @return -1 Caso data02 < data01 | 1 Caso data02 > data01 | 0 Caso data02 = data01  
 */
int DataCompare( string data01, string data02, int& comp )
{
    if( stoi(data01.substr(0,4)) < stoi(data02.substr(0,4)) )
    {
        comp++;
        return 1;
    }
    else if( stoi(data01.substr(0,4)) > stoi(data02.substr(0,4)) )
    {
        comp+=2;
        return -1;
    }
    else if( stoi(data01.substr(5,2)) < stoi(data02.substr(5,2)) )
    {
        comp+=3;
        return 1;
    }
    else if( stoi(data01.substr(5,2)) > stoi(data02.substr(5,2)) )
    {
        comp+=4;
        return -1;
    }
    else if( stoi(data01.substr(8,2)) < stoi(data02.substr(8,2)) )
    {
        comp+=5;
        return 1;
    }
    else if( stoi(data01.substr(8,2)) > stoi(data02.substr(8,2)) )
    {
        comp+=6;
        return -1;
    }
    else
    {
        comp+=7;
        return 0;
    }
}