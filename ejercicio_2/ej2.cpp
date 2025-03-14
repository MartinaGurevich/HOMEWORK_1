#include <iostream>
#include <fstream>
#include <array>
#include <string>
using namespace std;

//creo un archivo.  //dsp hago un switch.

enum leyendas { DEBUG=1, INFO, WARNING, ERROR, CRITICAL };

constexpr array<const char*,5> leyendasStrings = {
    "DEBUG",
    "INFO",
    "WARNING", 
    "ERROR", 
    "CRITICAL"
};

//que el usuario elija la opcion
void opciones_severidad(){
    //usuario elige el nivel de severidad
    cout<<"Opciones del NIvel de Severidad:" << "\n";
    for(size_t i=0; i<leyendasStrings.size(); i++){
        cout<< i+1 <<"-"<< leyendasStrings [i]<< "\n";
    }

}

void logMessage(string mensaje, int NivelSeveridad){
    //usuario elige la opcion
    //lo que se seleccione se agrega al archivo log
    ofstream logfile("Log.txt", ios::app);
    if (!logfile){
        cerr<<"nos se puede abrir el archivo. \n";
        return;
    }
    
    string nivel;
    switch (NivelSeveridad)
    {
        case DEBUG:
            nivel="DEBUG";
            break;
        case INFO:
            nivel="INFO";
            break;
        case WARNING:
            nivel="WARNING";
            break;
        case ERROR:
            nivel="ERROR";
            break;
        case CRITICAL:
            nivel="CRITICAL";
            break;
        default:
        cerr<< "NO es valido este nivel de severidad";
            return;
    }
    logfile<<"[" <<nivel<< "]<"<< mensaje <<">"<<"\n";
    logfile.close();
}

int main(){
    

    int seleccion;
    char mensaje[256];
    for(int i=0; i<5; i++){
        opciones_severidad();

        cout<<"seleccione nivel de severidad: "; //que pasa si vuelvo a elegir el mismo ?
        scanf("%d", &seleccion);

        while(seleccion< 1 || seleccion> 5){
            cout<< "opcion invalida, intente denuevo:" ;
            scanf("%d", &seleccion);
        }

        cout<< "ingrese su mensaje: ";
        scanf(" %[^\n]", mensaje);//

        logMessage(mensaje, seleccion); 
}
    return 0;
}


