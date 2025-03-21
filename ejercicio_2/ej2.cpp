#include <iostream>
#include <fstream>
#include <array>
#include <string>
using namespace std;

/* 
    Este programa implementa un sistema de registro con diferentes niveles de severidad. Utilizo la sobrecarga de funciones.
    El usuario puede seleccionar su nivel de severidad, escribir un mensaje y este se guardara en el archivo "Log.txt".
    - en caso de ERROR, el usuario ingresa el mesaje de error, en que archivo ocurrio y en que linea del mismo
    - En caso de SECURITY se ingresa el nombre de usuario. 
    - Finalmente si se ingresa un nivel o argumento invalido, el programa maneja el error y pide que lo ingrese nuevamente. Si se selecciona TEST, este lanza un error en runtime.


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

// Funcion que registra errores enocntrados por el usuario
void logMessage(string& mensaje, string& archivo, int& linea_codigo){
    ofstream logfile("Log.txt", ios::app);
    if (!logfile){
        cerr<<"nos se puede abrir el archivo. \n";
        return;
    }
    cout<<"ingrese su mensaje de error: ";
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

    logfile<< "[" <<leyendasStrings[static_cast<leyendas>(ERROR) - 1]<< "] <" << mensaje << "> - <Archivo: "<< archivo << ", Linea: "<< to_string(linea_codigo) <<">" << endl;
    logfile.close();
}


// Funcion que permite registar mensaje de "Acceso de Usuario"
void logMessage(string& mensaje, string& nombre_usuario){
    ofstream logfile("Log.txt", ios::app);
    if (!logfile){
        cerr<<"nos se puede abrir el archivo. \n";
        return;
    }
    cout<< "ingrese su mensaje de acceso: ";
    cin.ignore(); //limpia bufer y permite que getline funcione bien 
    getline(cin, mensaje);

    cout<<"ingrese el nombre de usuario: ";
    getline(cin, nombre_usuario);

    logfile<< "[" << leyendasStrings[static_cast<leyendas>(SECURITY) - 1]<< "] <" << mensaje << "> - < Nombre de usuario: "<< nombre_usuario <<">" << endl;
    logfile.close();
}

//Funcion que maneja la entrada de mensajes 
void logMessage(string& mensaje, leyendas nivel) {
    ofstream logfile("Log.txt", ios::app);
    if (!logfile){
        cerr<<"nos se puede abrir el archivo. \n";
        return;
    }
    cout<< "ingrese su mensaje: ";
    cin.ignore(); //limpia bufer y permite que getline funcione bien 
    getline(cin, mensaje);

    logfile<<"[" <<leyendasStrings[nivel-1]<< "] <"<< mensaje <<">" << endl;
    logfile.close();
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
            
            switch (seleccion) {
                case ERROR:
                    logMessage(mensaje, archivo, linea_error);
                    break;
                case SECURITY:
                    logMessage(mensaje, usuario);
                    break;
                case TEST:
                    throw runtime_error(" Error CRITICAL en tiempo de ejecucion desde test."); //manejo de error en runtime.
                default:
                    logMessage(mensaje, static_cast<leyendas>(seleccion));
                    break;
            }
        }
        catch(runtime_error& e){
            ofstream logfile("Log.txt", ios::app);
            if (logfile){
                logfile<<"["<< leyendasStrings[CRITICAL -1]<<"] <"<<e.what()<<">"<< endl; //muestro el error en log 
                logfile.close();
           }
           cerr<< "ERROR CRITICO : " <<e.what()<< endl; //sale del programa
           return 1;
        }
        
    }
    return 0;
}



