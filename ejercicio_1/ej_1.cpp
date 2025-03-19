#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> matrix(int n){
    if(n<=0){
        cout <<"no se puede hacer una matriz con este n" << endl;
        return {};
    }
    int filas= n ;
    int columnas= n;

    vector<vector<int>> matriz(filas, vector<int>(columnas,1)); //creo matriz de nxn incializando valores en 0
    int contador= 1;  
    for (int i=0; i< filas; i++){
        for (int j=0; j<columnas; j++){
            matriz[i][j]= contador;
            contador++;
        }
    }
    return matriz;
}

//1_b)
void mayor_a_menor(vector<vector<int>> &matriz, int n){
    for (int i= n*n-1; i>=0 ; i--){
        int fila=i/n;
        int columna=i % n;
        
        cout<< "M"<<n<<"["<<fila <<"]["<< columna <<"] = " <<matriz[fila][columna]<< endl;
    } 
}

int main(){
    int n;
    cout<<"ingrese tamaño de n: ";
    cin >> n;

    vector<vector<int >> matriz= matrix(n); 
    
    for (const auto& fila : matriz){ 
        for(int elemento: fila){
            cout << elemento << " ";
        }
        cout<< endl;
    }
    mayor_a_menor(matriz,n);

    return 0;
}