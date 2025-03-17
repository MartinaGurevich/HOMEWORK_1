#include <iostream>
#include <fstream>
#include <array>
#include <string>
using namespace std;

//creo un archivo.  //dsp hago un switch.

enum leyendas { DEBUG=1, INFO, WARNING, ERROR, CRITICAL, MARTINA, SECURITY}; //AGREGO MARTINA DE MANERA HARDCODEADA

constexpr array<const char*,7> leyendasStrings = {
    "DEBUG",
    "INFO",
    "WARNING", 
    "ERROR", 
    "CRITICAL",
    "MARTINA",
    "SECURITY"

};

//que el usuario elija la opcion
void opciones_severidad(){
    //usuario elige el nivel de severidad
    cout<<"Opciones del NIvel de Severidad:" << "\n";
    for(size_t i=0; i<leyendasStrings.size(); i++){
        cout<< i+1 <<"-"<< leyendasStrings [i]<< "\n";
    }

}

void logMessage(const string& mensaje, int NivelSeveridad,const string& archivo="", int linea_error= -1 , const string& nombre_usuario=""){
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
        case MARTINA:
            nivel="MARTINA";
            break;
        case SECURITY:
            nivel="SECURITY";
            break;
        default:
        cerr<< "NO es valido este nivel de severidad";
            return;
    }
    logfile<<"[" <<nivel<< "]<"<< mensaje <<">"<<"\n";

    if(NivelSeveridad==4){
        logfile<< "<Archivo: "<< archivo << ", Linea: "<< linea_error<<">";
    }
    if(NivelSeveridad==7){
        logfile<< "< Nombre de usuario: "<< nombre_usuario<<">";
    }
    logfile<< "\n"; //
    logfile.close();
}

void log_message_error(string& mensaje, string& archivo, int& linea_codigo){
    
    cin.ignore(); //no hay problemas para la proxima entrada  /////////

    cout<<"ingrese su mensaje: ";
    getline(cin, mensaje);

    cout<<"ingrese el archivo donde ocurrio el error: ";
    getline(cin, archivo);

    cout<<"ingrese linea donde esta el error: ";
    cin >> linea_codigo;//es un int
    cin.ignore();
} 

//2c
void log_acceso_usuario(string& mensaje, string& nombre_usuario){
    cin.ignore();////////////////////////////////////////
    cout<< "ingrese su mensaje de acceso: "; //pongo ingrese su mensaje de acceso ?
    
    getline(cin, mensaje);

    cout<<"ingrese el nombre de usuario: ";
    getline(cin, nombre_usuario);
    
    //cin.ignore();
}

int main(){
    int seleccion;
    string mensaje, archivo, usuario;
    int linea_error;

    for(int i=0; i<leyendasStrings.size(); i++){
        opciones_severidad();

        cout<<"seleccione nivel de severidad ( para salir 0 ): "; //que pasa si vuelvo a elegir el mismo ?
        cin>> seleccion;

        if(seleccion==0)break;

        while(seleccion< 1 || seleccion> leyendasStrings.size()){
            cout<< "opcion invalida, intente denuevo:" ;
            cin>> seleccion;   
        }
        if (seleccion==4){
            log_message_error(mensaje, archivo, linea_error);
            logMessage(mensaje,seleccion, archivo, linea_error);
            continue;
        }
        if(seleccion== 7){
            log_acceso_usuario(mensaje, usuario);
            logMessage(mensaje, seleccion,"",-1, usuario); 
            continue;
        }
            else{
                
                cin.ignore();//
                cout<< "ingrese su mensaje: ";
                
                getline(cin,mensaje);
                logMessage(mensaje, seleccion);
            }
    }
    return 0;

}
