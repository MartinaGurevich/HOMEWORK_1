#include <iostream>
#include<cstring>
#include <chrono>
#include <ej4>
using namespace std;

int miProcesoAMedir(){

}

int main(){
    auto startTime = std::chrono::high_resolution_clock::now();
    miProcesoAMedir();
    auto endTime = chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(
    endTime - startTime);
    cout << "A miProcesoAMedir le tomó: " << elapsedTime.count() <<"nanosegundos "<< endl;
}