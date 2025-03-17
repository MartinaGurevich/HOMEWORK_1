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
        temp->next= cola;
    }