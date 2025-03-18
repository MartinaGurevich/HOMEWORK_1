#include <iostream>
#include<cstring>
#include <chrono>
using namespace std;

bool comparacion_recursiva(const char* palabra1,const char* palabra2){
    //caso base
    if(*palabra1=='\0' && *palabra2=='\0') {return true;} //si llego al final de ambas palabras, son iguales
    if(*palabra1!= *palabra2) {return false; }//si no tienen el mismo largo o si no tienen iguales caracteres
    
    //caso recursivo
    return comparacion_recursiva(palabra1 +1, palabra2 + 1);

}
//lo hago con str tmb 

int main ()
{
    char plabara1[]="hola como estas yo bien";
    char plabara2[]="hola como estas yo mal";

    if (comparacion_recursiva( plabara1, plabara2)){
        cout<<"las palabras : \""  <<plabara1<< "\" y \"" <<plabara2<< "\" son iguales. \n";
    }else{
        cout<<"las palabras : \""  <<plabara1<< "\" y \"" <<plabara2<< "\" son distintas. \n";
    }

    return 0;
}
