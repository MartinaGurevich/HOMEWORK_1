#include <iostream>
#include <vector>
using namespace std;

/* 

    Texto introductorio del archivo: 
        -Incluyo la biblioteca <vector> para representar la matriz. 
        - <vector> es util porque es un contenedor dinamico, es decir que su tamaño se puede modificar en tiempo de ejecucion.
        - Este programa genera una matriz cuadrada de n x n. 
        - La matriz se inicializa con valores secuenciales desde 1. 
        - Finalmente se muestra el contenido de la matriz en orden descendente.
    
    */

vector<vector<int>> matrix(int n){
    if(n<=0){
        cout <<"no se puede hacer una matriz con este n" << endl;
        return {};
    }
    int filas= n ;
    int columnas= n;

    vector<vector<int>> matriz(filas, vector<int>(columnas,1)); //creo matriz de nxn incializando valores en 1
    int contador = 1;  //contador que aumenta a medida que me muevo por la matriz.
    for (int i=0; i< filas; i++){ 
        for (int j=0; j<columnas; j++){
            matriz[i][j]= contador; //se guardan los valores secuenciales.
            contador++;
        }
    }
    return matriz;
}

//1_b)
void mayor_a_menor(vector<vector<int>> &matriz, int n){
    for (int i= n*n-1; i>=0 ; i--){ //recorro la matriz desde el ultimo valor al primero
        int fila=i/n; // me indica en que fila se encuentra el numero
        int columna=i % n; // me da la posicion dentro de la fila
        
        cout<< "M"<<n<<"["<<fila <<"]["<< columna <<"] = " <<matriz[fila][columna]<< endl;
    } 
}

int main(){
    int n;
    cout<<"ingrese tamaño de n: ";
    cin >> n;

    vector<vector<int >> matriz= matrix(n); 
    mayor_a_menor(matriz,n);

    return 0;
}