#include <iostream>
#include <memory> //para el sharedptr
using namespace std;

/*
    Este programa implementa una lista enlazada, con nodos con valor y una direccion de memoria.
    Uso smartpointers , especificamente sharedptr por el motivo de que se destruyen solos al salir del scope.
    Se implementaron funciones para el manejo de la lista. 
    Pongo ejemplos para verificar el funcionamiento requerido.
*/

struct nodo{
    int dato;
    shared_ptr<nodo> next;

    nodo(int valor) : dato(valor), next(nullptr) {}
};

//creo un nodo 
shared_ptr<nodo> crear_nodo(int valor){
    return make_shared<nodo>(valor);
}

//inserto nodo delante de la lista
void insertar_alfrente(shared_ptr<nodo>& head, int valor){
    shared_ptr<nodo> nuevo_nodo= crear_nodo(valor);
    nuevo_nodo->next= head;// cambio el puntero q apunte a la head anterior
    head= nuevo_nodo; 
}

//inserto nodo al final de la lista
void insertar_final(shared_ptr<nodo>& cola, int valor){
    shared_ptr<nodo> ultimo_nodo= crear_nodo(valor);
    
    if(!cola){
        cola=ultimo_nodo; //si esta vacia agrego el nodo
    }
    else{
        shared_ptr<nodo> temp= cola;
        while(temp->next){
            temp=temp->next;  
        }
        temp->next= ultimo_nodo; //agrego ultimo nodo con puntero a null
    }
}

//inserta un nodo en la posición que se le pase a la función
void insertar(shared_ptr<nodo>& nodo_insertado,int valor, int posicion){
    shared_ptr<nodo> nuevo_nodo= crear_nodo(valor);

    if(posicion<=0){
        insertar_alfrente(nodo_insertado,valor); //primer posicion
    }

    //hago un contador para ver el largo de la lista
    shared_ptr<nodo> temp=nodo_insertado;
    int contador=0;

    while(temp && contador< posicion -1){
        temp= temp->next; //itero sobre la lista
        contador++;
    }

    if(!temp){ //si se le pasa posicion mayor al largo de la lista, lo agrego ultimo
        cout<<"posicion fuera del rango de la lista. ¡Se agrega como ultima posicion! \n";
        insertar_final(nodo_insertado, valor); //inserto ultimo
        return;
    }

    //itero hasta encontar la posicion deseada
    nuevo_nodo-> next= temp->next;
    temp->next= nuevo_nodo;
}

//borra un nodo en la posición que se le pase a la función.
void erase(shared_ptr<nodo>& head, int posicion){

    if(!head){
        cout<<"la lista esta vacia" ;
        return;}//si la lista esta vacia no hago nada
    
    if(posicion == 0){
        head=head->next; //borro el primero
        return;
    }
    shared_ptr<nodo> temp=head;
    int contador=0;

    while(temp->next && temp ->next->next &&  contador< posicion -1 ){
        temp= temp ->next; //itero hasta q llegue al final de la lista
        contador++;
    }

    if(!temp->next || !temp->next->next){//si no esta dentro del largo de la lista
        cout<<"¡Posicion fuera de rango, se elimina ultimo nodo!\n";
        temp->next= nullptr;
        return;
    }

    temp->next= temp->next ->next; //salto el nodo a eliminar y ajusto su puntero
    }

//imprimo lista completa
void print_list(shared_ptr<nodo>& head){
    shared_ptr<nodo> temp=head;

    while(temp){
        cout<< temp->dato<<"->";
        temp=temp->next;
    }
    cout<< " NULL"<<endl;
}

int main(){ //ejemplos para corroborar funcionamiento.
    shared_ptr<nodo> head= nullptr; //lista vacia 

    insertar_final(head,10);
    insertar_final(head,25);
    insertar_final(head,60);
    insertar_final(head,2);
    insertar_final(head,14);

   cout<<"lista actual: \n";
   print_list(head);

   insertar_alfrente(head, 87);
   cout<<"lista actual, luego de insertar primero: \n";
   print_list(head);

   insertar(head, 105, 3);

   cout<<"lista actual, luego de insertar: \n";
   print_list(head);

   insertar(head, 200, 55);

   cout<<"lista actual, luego de insertar: \n";
   print_list(head);

   erase(head,3);

   cout<<"lista despues de borrar nodo: \n";
   print_list(head);

   
   erase(head,40);

   cout<<"lista despues de borrar nodo: \n";
   print_list(head);

   insertar_final(head, 666);
   cout<<"lista actual, luego de insertar al final: \n";
   print_list(head);

   return 0;

}

