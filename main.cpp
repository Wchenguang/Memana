#include <iostream>
#include "Memana.h"

int main(){

    Memana memana;

    char *str = (char*)memana.allovate(10);
    memset(str,0,10);
    strcpy(str, "hello");

    std::cout<<str<<std::endl;

    return 0;
}