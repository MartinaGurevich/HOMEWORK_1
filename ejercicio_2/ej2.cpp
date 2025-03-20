#include <iostream>
#include <fstream>
#include <array>
#include <string>
using namespace std;

/* 
    Este programa implementa un sistema de registro con diferentes niveles de severidad.
    El usuario puede seleccionar su nivel de severidad, escribir un mensaje y este se guardara en el archivo "Log.txt".
    - en caso de ERROR, el usuario ingresa el mesaje de error, en que archivo ocurrio y en que linea del mismo
    - En caso de SECURITY se ingresa el nombre de usuario. 
    - Finalemnte si se ingresa un nivel invalido, el programa maneja el error y pide que lo ingrese nuevamente.

*/
enum leyendas { DEBUG=1, INFO, WARNING, ERROR, CRITICAL, TEST, SECURITY}; //defino los niveles de severidad con numero enteros y luego AGREGO TEST y SECURITY DE MANERA HARDCODEADA

constexpr array<const char*,7> leyendasStrings = { //me permite acceder a los nombres de los niveles.
    "DEBUG",
    "INFO",
    "WARNING", 
    "ERROR", 
    "CRITICAL",
    "TEST",
    "SECURITY"

};

//Funcion para que el usuario elija el nivel de severidad
void opciones_severidad(){
    cout<<"Opciones del Nivel de Severidad:" << "\n";
    for(size_t i=0; i<leyendasStrings.size(); i++){
        cout<< i+1 <<"-"<< leyendasStrings [i]<< "\n";
    }

}

void logMessage(const string& mensaje, int NivelSeveridad,const string& archivo="", int linea_error= -1,const string& nombre_usuario="" ){

    //El usuario selecciona opcion, ingresa mensaje y se agrega al archivo log("Log.txt").
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
    logfile<<"[" <<nivel<< "]<"<< mensaje <<">" ;

    if(NivelSeveridad==4){
        logfile<< " - <Archivo: "<< archivo << ", Linea: "<< linea_error<<">";
    }
    if(NivelSeveridad==7){
        logfile<< " - < Nombre de usuario: "<< nombre_usuario<<">";
    }
    logfile<< "\n"; 
    logfile.close();
}

// Funcion que registra errores enocntrados por el usuario
void log_message_error(string& mensaje, string& archivo, int& linea_codigo){
    
    cout<<"ingrese su mensaje: ";
    cin.ignore(); //no hay problemas para la proxima entrada 
    getline(cin, mensaje);

    cout<<"ingrese el archivo donde ocurrio el error: ";
    getline(cin, archivo);

    cout<<"ingrese linea donde esta el error: ";
    while (!(cin >> linea_codigo)){ //manejo error si no me ingresan un int
        cout<<"ERROR. Debe ingresar el numero de linea. Intente nuevamente: ";
        cin.clear();
        cin.ignore(10000,'\n');
    }
    
    cin.ignore();// limpia bufer
}


// Funcion que permite registar mensaje de "Acceso de Usuario"
void log_acceso_usuario(string& mensaje, string& nombre_usuario){
    cout<< "ingrese su mensaje de acceso: ";
    cin.ignore(); //limpia bufer y permite que getline funcione bien 
    getline(cin, mensaje);

    cout<<"ingrese el nombre de usuario: ";
    getline(cin, nombre_usuario);
    

}

int main(){
    int seleccion;
    string mensaje, archivo, usuario;
    int linea_error;

    while(true){
        try{ //manejo de errores
            opciones_severidad();

            while(true){ //MANEJO DE ENTRADAS INCORRECTAS
                cout<< "Seleccione nivel de severidad (para salir 0): ";
                if(cin>>seleccion){
                    if(seleccion >= 0 && seleccion <= leyendasStrings.size()){
                        break; // el numero es valido
                    } else{
                        cout<< "¡OPCION INVALIDA! Intente nuevamente.\n"; 
                    }
                }else{
                    cout<<"¡ENTRADA INVALIDA, Ingrese un numero.\n";//el usuario no ingreso un int
                    cin.clear(); //limpia estado de error.
                    cin.ignore(10000, '\n');
                }
            }


            if(seleccion==0)break;

            //while(seleccion< 1 || seleccion> leyendasStrings.size()){
            //    throw invalid_argument("¡OPCIÓN INVALIDA!. Intente nuevamente. \n"); //si el usuario no ingresa un int dentro del rango de las opciones, me marca un error.
           // }
            //casos ERROR y SECURITY.

            if (seleccion==4){
                log_message_error(mensaje, archivo, linea_error);
                logMessage(mensaje,seleccion, archivo, linea_error);
                continue;
            }
            if(seleccion== 7){
                log_acceso_usuario(mensaje, usuario);
                logMessage(mensaje, seleccion,archivo,linea_error, usuario); 
                continue;
            }

            else{ //para otro nivel de severidad, pido mensaje
                cin.ignore(); //limpio buffer antes de getline
                cout<< "ingrese su mensaje: ";
                getline(cin,mensaje);
                logMessage(mensaje, seleccion); 
            }
        }
        catch(const invalid_argument& e){
            cout << e.what(); //pido nuevamente la opcion debido al invalid_argument previo.
            cin.clear(); //limpia el estado de error de cin
            cin.ignore(10000, '\n'); //Descarta hasta 10.000 caracteres. Y no entra en loop infinito.
        } 
    }
    return 0;
}



