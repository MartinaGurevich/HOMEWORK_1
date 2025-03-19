#include <iostream>
#include <fstream>
#include <array>
#include <string>
using namespace std;

//creo un archivo.  //dsp hago un switch.

enum leyendas { DEBUG=1, INFO, WARNING, ERROR, CRITICAL, TEST, SECURITY}; //AGREGO MARTINA DE MANERA HARDCODEADA

constexpr array<const char*,7> leyendasStrings = {
    "DEBUG",
    "INFO",
    "WARNING", 
    "ERROR", 
    "CRITICAL",
    "TEST",
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

void logMessage(const string& mensaje, int NivelSeveridad,const string& archivo="", int linea_error= -1,const string& nombre_usuario="" ){
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
        case TEST:
            nivel="TEST";
            break;
        case SECURITY:
            nivel="SECURITY";
            break;
        default:
        cerr<< "NO es valido este nivel de severidad";
            return;
    }
    logfile<<"[" <<nivel<< "]<"<< mensaje <<">" ;//<<"\n";

    if(NivelSeveridad==4){
        logfile<< " - <Archivo: "<< archivo << ", Linea: "<< linea_error<<">";
    }
    if(NivelSeveridad==7){
        logfile<< " - < Nombre de usuario: "<< nombre_usuario<<">";
    }
    logfile<< "\n"; //
    logfile.close();
}
//2b ii

void log_message_error(string& mensaje, string& archivo, int& linea_codigo){
    
    cout<<"ingrese su mensaje: ";
    cin.ignore(); //no hay problemas para la proxima entrada 
    getline(cin, mensaje);

    cout<<"ingrese el archivo donde ocurrio el error: ";
    getline(cin, archivo);

    cout<<"ingrese linea donde esta el error: ";
    cin >> linea_codigo;//es un int
    
    cin.ignore();
} 
//2c
void log_acceso_usuario(string& mensaje, string& nombre_usuario){
    cout<< "ingrese su mensaje de acceso: "; //pongo ingrese su mensaje de acceso ?
    cin.ignore();
    getline(cin, mensaje);

    cout<<"ingrese el nombre de usuario: ";
    getline(cin, nombre_usuario);
    
    //cin.ignore(); 
}

int main(){
    int seleccion;
    string mensaje, archivo, usuario;
    int linea_error;

    while(true){
        try{
            opciones_severidad();

            cout<<"seleccione nivel de severidad (para salir 0 ): "; //que pasa si vuelvo a elegir el mismo ?
            cin>> seleccion; 

            if(seleccion==0)break;

            while(seleccion< 1 || seleccion> leyendasStrings.size()){
                throw invalid_argument("opcion invalida, intente denuevo:");
            }

            if (seleccion==4){
                log_message_error(mensaje, archivo, linea_error);
                logMessage(mensaje,seleccion, archivo, linea_error);
                continue;
            }
            if(seleccion== 7){
                log_acceso_usuario(mensaje, usuario);
                logMessage(mensaje, seleccion,archivo,linea_error, usuario); 
                continue;//ESTA BIEN QUEPONGA TODOS LOS ARGUMNETSO ACA ?
            }

            else{
                cin.ignore();//
                cout<< "ingrese su mensaje: ";
                getline(cin,mensaje);
                logMessage(mensaje, seleccion); //ME PASA QUE LOS ARGUMENTOS DE LA FUNCION SON MAS Y NO ME LEE CUANDO POMGO NI EL 4
            }
        }
        catch(invalid_argument &e){
            cout << e.what();
            cin.clear();
        } 
    }
    return 0;
}

//me falta el ultimo punto



