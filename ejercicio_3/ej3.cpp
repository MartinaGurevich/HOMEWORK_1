#include <iostream>
#include <memory> //para el sharedptr
using namespace std;

struct nodo{
    int dato;
    shared_ptr<nodo> next;

    nodo(int valor) : dato(valor), next(nullptr) {}
};

//creo un nodo 
shared_ptr<nodo> crear_nodo(int valor){
    return make_shared<nodo>(valor);
}

//inserto nodo enfrente de la lista
void insertar_enfrente(shared_ptr<nodo>& head, int valor){
    shared_ptr<nodo> nuevo_nodo= crear_nodo(valor);
    nuevo_nodo->next= head;// cambio el puntero q apunte a la head anterior
    head= nuevo_nodo; 
}

//inserto nodo al final de la lista
void insertar_final(shared_ptr<nodo>& cola, int valor){
    shared_ptr<nodo> ultimo_nodo= crear_nodo(valor);
    
    if(!cola){
        cola=ultimo_nodo;
    }
    else{
        shared_ptr<nodo> temp= cola;
        while(temp->next){
            temp=temp->next;
        }
        temp->next= ultimo_nodo;
    }
}

void insertar(shared_ptr<nodo>& nodo_insertado,int valor, int posicion){
    shared_ptr<nodo> nuevo_nodo= crear_nodo(valor);

    if(posicion<=0){
        insertar_enfrente(nodo_insertado,valor);
    }

    //hago un contador para ver el largo de la lista
    shared_ptr<nodo> temp=nodo_insertado;
    int contador=0;

    while(temp && contador< posicion -1){
        temp= temp->next;
        contador++;
    }

    if(!temp){
        cout<<"posicion fuera del rango de la lista";
        insertar_final(nodo_insertado, valor);
        return;
    }

    //itero hasta encontar la posicion deseada
    nuevo_nodo-> next= temp->next;
    temp->next= nuevo_nodo;
}

void erase(shared_ptr<nodo>& head, int posicion){

    if(!head){
        cout<<"la lista esta vacia" ;
        return;}//si la lista esta vacia no hago nada
    
    if(posicion == 0){
        head=head->next;
        return;
    }
    shared_ptr<nodo> temp=head;
    int contador=0;

    while(temp->next && temp ->next->next &&  contador< posicion -1 ){
        temp= temp ->next;
        contador++;
    }

    if(!temp->next || !temp->next->next){//si no esta dentro del largo de la lista
        cout<<"¡Posicion fuera de rango, se elimina ultimo nodo!\n";
        temp->next= nullptr;
        return;
    }
   // if (!temp->next->next){
    //    temp->next=nullptr;
       // return;
   // }


    temp->next= temp->next ->next; //salto el nodo a eliminar y ajusto su puntero
    }


void print_list(shared_ptr<nodo>& head){
    shared_ptr<nodo> temp=head;

    while(temp){
        cout<< temp->dato<<"->";
        temp=temp->next;
    }
    cout<< " NULL"<<endl;
}

int main(){
    shared_ptr<nodo> head= nullptr; //litsa vacia

    insertar_final(head,10);
    insertar_final(head,25);
    insertar_final(head,60);
    insertar_final(head,2);
    insertar_final(head,14);

   cout<<"lista actual: \n";
   print_list(head);

   insertar_enfrente(head, 87);
   cout<<"lista actual, luego de insertar primero: \n";
   print_list(head);

   insertar(head, 105, 3);

   cout<<"lista actual, luego de insertar: \n";
   print_list(head);

   erase(head,3);

   cout<<"lista despues de borrar nodo: \n";
   print_list(head);

   insertar_final(head, 666);
   cout<<"lista actual, luego de insertar al final: \n";
   print_list(head);

   return 0;

}

