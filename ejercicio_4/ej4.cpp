#include <iostream>
#include<cstring>
#include <chrono>
using namespace std;

//comparacion recursiva usando char* DEJO ESTE O LO BORRO ?
bool comparacion_recursiva_c(const char* texto1,const char* texto2){
    //caso base
    if(*texto1=='\0' && *texto2=='\0') {return true;} //si llego al final de ambas palabras, son iguales
    if(*texto1!= *texto2) {return false; }//si no tienen el mismo largo o si no tienen iguales caracteres
    
    //caso recursivo
    return comparacion_recursiva_c(texto1 +1, texto2 + 1);

}

//comparacion recursiva usando string
bool comparacion_recursiva_s(const string& texto1,const string& texto2, int indice=0){
    //caso base
    if(indice==texto1.length() && indice==texto2.length()) {return true;} //llego al  final de ambas, y son iguales 
    if(indice>= texto1.length() ||indice>= texto2.length() || texto1[indice] != texto2[indice]) {return false; }//si no tienen el mismo largo o si no tienen iguales caracteres
    
    //caso recursivo
    return comparacion_recursiva_s(texto1, texto2, indice +1);
}


//modifico el 4.1 , comparacion recursiva en tiempo de compilacion  ----------------------------------------------- DEJO EL DE CHAR TAMBIEN ? 

constexpr bool comparacion_recursiva_char(const char* texto1,const char* texto2){
    //caso base
    if(*texto1=='\0' && *texto2=='\0') {return true;} //si llego al final de ambas palabras, son iguales
    if(*texto1!= *texto2) {return false; }//si no tienen el mismo largo o si no tienen iguales caracteres
    
    //caso recursivo
    return comparacion_recursiva_char(texto1 +1, texto2 + 1);

}

long long tiempo_ejecucion_char(const char* texto1,const char* texto2){
    
    auto startTime = chrono::high_resolution_clock::now();
    comparacion_recursiva_c( texto1, texto2);
    auto endTime = chrono::high_resolution_clock::now();
    auto elapsedTime = chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    return elapsedTime.count();

}

long long tiempo_ejecucion_str(const string& texto1,const string& texto2, int indice=0){
        
    auto startTime = chrono::high_resolution_clock::now();
    comparacion_recursiva_s( texto1, texto2);
    auto endTime = chrono::high_resolution_clock::now();
    auto elapsedTime = chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    return elapsedTime.count();

}



int main ()
{
    constexpr const char texto1_c[]="hola como estas yo mal , esta frase tiene al menos 64 caracteres para ver si es igual que la otra";
    constexpr const char texto2_c[]="hola como estas yo bien , esta frase tiene al menos 64 caracteres para ver si es igual que la otra";

    constexpr bool resultado_char_compilacion= comparacion_recursiva_char (texto1_c,texto2_c);
    
    string texto1_s= texto1_c;
    string texto2_s= texto2_c;
    //long long tiempo_str= tiempo_ejecucion_str(texto1_s,texto2_s);

    // COMPARARCION CON char*
    //bool resultado_char= comparacion_recursiva_c(texto1_c, texto2_c); ERA CUADNO ESTABA USANDO LA FUNCION DE CHAR SOLO 
    //long long tiempo_char= tiempo_ejecucion_char(texto1_c,texto2_c);

    cout<<"COMPARACION EN TIEMPO DE COMPILACION CON CHAR: \n" ;
    if (resultado_char_compilacion){
        cout<<"- Los textos son iguales. \n";
    }else{
        cout<<"- Los textos son distintos. \n";
    }
    cout<< "No hay tiempo de ejecucion, el calculo se realiza en la compilacion del programa \n";
    //cout<< "tiempo de ejecucion con char: ["<< tiempo_char <<"] nanosegundos\n"<< endl;

    auto startTime = chrono::high_resolution_clock::now();
    comparacion_recursiva_s( texto1_s, texto2_s);
    auto endTime = chrono::high_resolution_clock::now();
    auto elapsedTime = chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    int tiempo = elapsedTime.count();
    cout << "string " << tiempo << endl;

    startTime = chrono::high_resolution_clock::now();
    comparacion_recursiva_c( texto1_c, texto2_c);
    endTime = chrono::high_resolution_clock::now();
    elapsedTime = chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    tiempo = elapsedTime.count();
    cout << "char " << tiempo << endl;


    startTime = chrono::high_resolution_clock::now();
    cout << "Tiempo en compilacion ";
    endTime = chrono::high_resolution_clock::now();
    elapsedTime = chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    tiempo = elapsedTime.count();
    cout << "comp " << tiempo << endl;


    // COMPARARCION CON string
    bool resultado_str= comparacion_recursiva_s(texto1_s, texto2_s);
    //long long tiempo_str= tiempo_ejecucion_str(texto1_s,texto2_s);
    cout<<"------------------------------------------\n" ;
    cout<<"COMPARACION EN TIEMPO DE EJECUCION CON STRING: \n" ;
    if (resultado_str){
        cout<<"- Los textos son iguales. \n";
    }else{
        cout<<"- Los textos son distintos. \n";
    }
    //cout<< "Tiempo de ejecucion con string: ["<< tiempo_str <<"] nanosegundos\n"<< endl;


    return 0;
}


/* En primer lugar, tome la desicion de elegir ambos tipos (char* y str) para demostrar que el tiempo de 
ejecucion de ambos difiere. El tiempo de ejecucion de la funcion tipo char* siempre es mejor al tiempo de la funcion
de tipo str. Esto sucede porque char* no tiene administarcion de memoria adicional ni metodos internos. 

Como string es una clase, no se puede usar como contexpr. Entonces para modifiacar el codigo en tiempo de compilacion solo se puede usar char. 
*/