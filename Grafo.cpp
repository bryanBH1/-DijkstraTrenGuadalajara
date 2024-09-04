//
//  Grafo.cpp
//  GRAFO - ARCHIVOS
//
//  Created by Bryan Bautista on 18/03/23.
//

#include "Grafo.hpp"
#include "Vertice.hpp"
#include <iostream>
using namespace std;

#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <map>
#include <stack>

Grafo::Grafo(){
    this->raiz = nullptr;
    this->tamaño = 0;
}

bool Grafo::isEmpty(){
    
    return this->raiz==nullptr;
}

int Grafo::obtenerTamano()
{
    return tamaño;
}

Vertice* Grafo::obtenerVertice(Estacion* estacion){
    Vertice* aux = this->raiz;
    while(aux!=nullptr){
        if(aux->estacion->nombre == estacion->nombre) return aux;
        aux=aux->sig;
    }
    return nullptr;
}
void Grafo::insetarVertice(Estacion* estacion){
    if(obtenerVertice(estacion)) cout<<"Ya existe la estacion"<<endl;
    else{
        Vertice* nuevo = new Vertice(estacion); //creo un objeto de vertice
        if(isEmpty()) this->raiz = nuevo;
        else{
            Vertice* aux = this->raiz;
            while(aux->sig!=nullptr) aux=aux->sig;
            aux->sig = nuevo;
        }
        tamaño++;
    }
}
void Grafo::insertarArista(Estacion* origen, Estacion* destino, int peso){
    if(isEmpty()) cout<<"El grafo esta vacio";
    else{
        Vertice* ori = obtenerVertice(origen);
        Vertice* dest = obtenerVertice(destino);
        if(ori==nullptr) cout<<"No existe la estacion origen"<<endl;
        if(dest==nullptr) cout<<"No existe la estacion destino"<<endl;
        
        if(ori!=nullptr && dest!=nullptr){ //si las vertices existen
            Arista* nueva = new Arista(dest,peso); //agrego el destino y peso
            
            if(ori->ari==nullptr){ //cuando la verice no tiene aristas
                ori->ari = nueva;
            }else{
                Arista* aux = ori->ari; //cuando la vertice si tiene vertices se posiciona al final
                while(aux->sig!=nullptr){
                    aux=aux->sig;
                }
                aux->sig = nueva; //se agrega la arista
            }
        }
    }
}
void Grafo::mostrarListaDeAdyacencia(){
    if(isEmpty()) cout<<"El sistema de tren esta vacio"<<endl;
    else{
        Vertice* aux = this->raiz;
        while(aux!=nullptr){
            Arista* ari = aux->ari;
            while (ari!=nullptr) {
                cout<<aux->estacion->nombre<<" ->"<<ari->peso<<"-> "<<ari->dest->estacion->nombre<<", ";
                ari=ari->sig;
            }
            cout<<endl;
            aux=aux->sig;
        }
    }
}

void Grafo::eliminarAristas(Vertice* vertice){
    if(vertice==nullptr) return;
    else{
        Arista* i = vertice->ari; //indico la primera arista de la lista de aristas de la vertice
        while (vertice->ari!=nullptr) {//si la vertice tiene arista o aristas
            i=vertice->ari; //obtengo la arista
            vertice->ari = vertice->ari->sig; //dejo de apuntar a la arista
            cout<<"Conexion "<<vertice->estacion->nombre<<"->"<<i->dest->estacion->nombre<<" eliminado"<<endl;
            delete (i);
        }
    }
}
bool Grafo::existe(Estacion* estacion){
    Vertice* aux = this->raiz;
    while(aux!=nullptr){
        if(aux->estacion->nombre==estacion->nombre) return true;
        aux=aux->sig;
    }
    return false;
}

void Grafo::eliminarAristasDestino(Estacion* estacion){
    Vertice* i = this->raiz;
    
    while(i!=nullptr){
        if(i->estacion->nombre == estacion->nombre || i->ari==nullptr) {
            i = i->sig;
            continue;
        }
        if(i->ari->dest->estacion->nombre == estacion->nombre){ //cuando la primera vertice conecta con la vertice a eliminar
            Arista* j = i->ari;
            i->ari = i->ari->sig;
            cout<<"Conexion "<<i->estacion->nombre<<"->"<<j->dest->estacion->nombre<<" eliminado"<<endl;
            delete(j);
        }
        else{
            Arista* x = i->ari; //obtengo la lista de aristas de la vertice a eliminar
            Arista* y = x->sig; //me situo al principio de la lista
            //hago mi recorrido buscando la coincidencia usando 2 iteradores, 1 para saber la posicion del valor
            while (y!=nullptr) { //ya no es necesario indicar el nodo siguiente ya que y = x->sig
                if(y->dest->estacion->nombre==estacion->nombre){ //se busca la coincidencia con
                    x->sig = y->sig; //se hace la reconeccion
                    cout<<"Conexion "<<i->estacion->nombre<<"->"<<y->dest->estacion->nombre<<" eliminado"<<endl;
                    delete (y);//Se elimina la arista
                }
                x=y;
                y=y->sig;
            }
        }
        i=i->sig;
    }
}
void Grafo::eliminarVertice(Estacion* estacion){
    
    if(isEmpty()) cout<<"El sistema de tren esta vacio"<<endl;
    else if(!existe(estacion)) cout<<"La estacion no existe"<<endl;
    else{
        if(this->raiz->estacion->nombre == estacion->nombre){ //busco la coincidencia en la primera vertice
            Vertice* aux = this->raiz; //me posiciono en el primer nodo
            this->raiz = this->raiz->sig; //dejo de apuntar al primer nodo
            eliminarAristas(aux); //elimino todas las aristas de la vertice
            eliminarAristasDestino(aux->estacion);//elimina las aristas que conectan con esta vertice
            cout<<"Estacion "<<estacion->nombre<<" de la linea "<<estacion->linea<<" fue eliminado"<<endl;
            delete (aux); //finalmente elimino el nodo
            tamaño--;
        }else{
            Vertice* i = this->raiz;
            Vertice* j = i->sig;
            
            while (i!=nullptr) {
                if (j->estacion->nombre!=estacion->nombre) {
                    i->sig = j->sig;
                    eliminarAristas(j);
                    eliminarAristasDestino(j->estacion);//elimina las aristas que conectan con esta vertice
                    cout<<"Estacion "<<estacion->nombre<<" de la linea "<<estacion->linea<<" fue eliminado"<<endl;
                    delete (j);
                    tamaño--;
                    break;
                }
                i = j;
                j = j->sig;
            }
        }
    }
}
void Grafo::eliminarArista(Estacion* origen, Estacion* destino){
    if(isEmpty()) cout<<"El sistema de tren esta vacio"<<endl;
    else{
        Vertice* ori = obtenerVertice(origen);
        Vertice* dest = obtenerVertice(destino);
        if(ori==nullptr) cout<<"No existe la estacion origen"<<endl;
        if(dest==nullptr) cout<<"No existe la estacion destino"<<endl;
        
        if(ori!=nullptr && dest!=nullptr){ //si las vertices existen
            if(ori->ari->dest==dest){ //si es la primera arista la que se va a a eliminar
                Arista* i = ori->ari; //para que no se pierda la direccion de la arista a eliminar
                ori->ari = ori->ari->sig; //se reconecta
                cout<<"Conexion "<<ori->estacion->nombre<<"->"<<dest->estacion->nombre<<" eliminado"<<endl; //puedo utilizar los strings
                delete (i);
            }
        }
            else{
                Arista* i = ori->ari; //obtengo la lista de aristas de la vertice
                Arista* j = i->sig; //me posiciono al principio
                while (j!=nullptr) { //ya no es necesario indicar el nodo siguiente ya que y = x->sig
                    if(j->dest==dest){ //se busca la coincidencia con
                        i->sig = j->sig; //se hace la reconeccion
                        cout<<"Conexion "<<ori->estacion->nombre<<"->"<<dest->estacion->nombre<<" eliminado"<<endl; //puedo usar los strings
                        delete (j);//Se elimina la arista
                        break; //sirve para que ya no reorra
                    }
                    i=j;
                    j=j->sig;
                }
                
            }
    }
}
void Grafo::eliminarTodo(){
    if(isEmpty()) cout<<"El sistema de tren esta vacio"<<endl;
    else{
        Vertice* aux = this->raiz;
        
        while (this->raiz!=nullptr) {
            aux = this->raiz;
            this->raiz = this->raiz->sig;
            eliminarAristas(aux);
            cout<<"Estacion "<<aux->estacion->nombre<<" fue eliminado"<<endl;
            delete (aux);
            tamaño--;
        }
    }
}


void Grafo::guardarGrafo() {
    ofstream archivo("/Users/bryanbautista/Documents/INGENIERIA EN INFORMATICA/TERCER SEMESTRE/ALGORITMIA/PROGRAMAS/GRAFO - TRENES - DIJKSTRA/GRAFO - ARCHIVOS/Sistema de trenes.txt");
    // Escribir vértices y aristas
    Vertice* v = raiz;
    while (v != nullptr) {
        // Escribir nombre del vértice
        archivo << v->estacion->nombre << "|";

        // Escribir aristas del vértice
        Arista* a = v->ari;
        while (a != nullptr) {
            archivo << a->dest->estacion->nombre << "|" << a->peso;
            if (a->sig != nullptr) {
                archivo << "|";
            }
            a = a->sig;
        }
        archivo << "*" << endl;
        v = v->sig;
    }
    archivo.close();
}


void Grafo::cargarGrafo(){
    ifstream archivo("/Users/bryanbautista/Documents/INGENIERIA EN INFORMATICA/TERCER SEMESTRE/ALGORITMIA/PROGRAMAS/GRAFO - TRENES - DIJKSTRA/GRAFO - ARCHIVOS/Sistema de trenes.txt"); // se abre el archivo
    if(archivo.is_open()){ // si el archivo se abrio correctamente
        string line;
        while(getline(archivo,line)){ // se lee cada linea del archivo
            stringstream ss(line);
            string nombre;
            getline(ss, nombre, '|'); // se lee el nombre del vértice hasta el delimitador |
            cout<<"Estacion origen: "<<nombre<<endl;
            Estacion* Eorigen = new Estacion();
            Eorigen->nombre = nombre;
            Vertice* vertice = obtenerVertice(Eorigen);
            
            if(vertice==nullptr){ // si el vertice no existe se crea
                insetarVertice(Eorigen);
                vertice = obtenerVertice(Eorigen);
            }
            
            string aristas;
            getline(ss, aristas, '*'); // se lee todas las aristas del vértice hasta el delimitador *
            stringstream ss_aristas(aristas);
            cout<<"conexiones: "<<aristas<<endl;
            
            string arista;
            while(getline(ss_aristas, arista, '|')) { // se lee cada arista de la cadena de aristas hasta el delimitador |
                string destino = arista;
                cout<<"Estacion: "<<destino<<endl;
                Estacion* Edestino = new Estacion();
                Edestino->nombre = destino;
                insetarVertice(Edestino);
                getline(ss_aristas, arista, '|'); // se lee el peso de la arista
                int peso = stoi(arista);
                cout<<"Peso: "<<peso<<endl;
                insertarArista(Eorigen, Edestino, peso);
            }
        }
        archivo.close(); // se cierra el archivo
        cout<<"El sistema de tren se ha cargado exitosamente desde Sistema de trenes.txt"<<endl;
    }else{
        cout<<"No se pudo abrir el archivo"<<endl;
    }
}

 void Grafo::dijkstra(Estacion* origen, Estacion* destino) {
     if (isEmpty()) {
         cout << "El grafo está vacío" << endl;
         return;
     }

     Vertice* ori = obtenerVertice(origen);
     Vertice* dest = obtenerVertice(destino);

     if (ori == nullptr) {
         cout << "No existe la estación origen" << endl;
         return;
     }

     if (dest == nullptr) {
         cout << "No existe la estación destino" << endl;
         return;
     }

     // Inicializar las distancias mínimas y los nodos visitados
     map<Vertice*, int> distancias;
     map<Vertice*, Vertice*> previo;
     priority_queue<pair<int, Vertice*>, vector<pair<int, Vertice*>>, greater<pair<int, Vertice*>>> cola;

     // Inicializar todas las distancias en infinito excepto la del nodo de origen que es 0
     for (Vertice* v = raiz; v != nullptr; v = v->sig) {
         if (v == ori)
             distancias[v] = 0;
         else
             distancias[v] = INT_MAX;
         previo[v] = nullptr;
         cola.push(make_pair(distancias[v], v));
     }

     // Ejecutar el algoritmo de Dijkstra
     while (!cola.empty()) {
         Vertice* actual = cola.top().second;
         cola.pop();

         // Si se llega al nodo de destino, terminar el algoritmo
         if (actual == dest)
             break;

         // Explorar las aristas adyacentes al nodo actual
         Arista* arista = actual->ari;
         while (arista != nullptr) {
             Vertice* vecino = arista->dest;

             // Calcular la distancia provisional desde el nodo de origen hasta el vecino
             int distancia_provisional = distancias[actual] + arista->peso;

             // Actualizar la distancia mínima y el nodo previo si se encuentra una distancia más corta
             if (distancia_provisional < distancias[vecino]) {
                 distancias[vecino] = distancia_provisional;
                 previo[vecino] = actual;
                 cola.push(make_pair(distancias[vecino], vecino));
             }

             arista = arista->sig;
         }
     }

     // Comprobar si se encontró un camino hasta el nodo de destino
     if (previo[dest] == nullptr) {
         cout << "No se encontró un camino entre las estaciones" << endl;
         return;
     }
     // Calcular la distancia recorrida en el camino mínimo
         int distancia_recorrida = distancias[dest];

     // Reconstruir el camino mínimo desde el nodo de origen hasta el nodo de destino
     stack<Estacion*> camino;
     Vertice* v = dest;
     while (v != nullptr) {
         camino.push(v->estacion);
         v = previo[v];
     }

     // Mostrar el camino mínimo
     cout << "Camino mínimo desde " << origen->nombre << " hasta " << destino->nombre << ":" << endl;
     while (!camino.empty()) {
         cout << camino.top()->nombre;
         camino.pop();
         if (!camino.empty()) {
             cout << " -> ";
         }
     }
     cout << endl;
     cout << "Distancia recorrida:" << distancia_recorrida << " Kilometros"<<endl;
 }




                       
