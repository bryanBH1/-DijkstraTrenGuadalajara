//
//  Grafo.hpp
//  GRAFO - ARCHIVOS
//
//  Created by Bryan Bautista on 18/03/23.
//

#ifndef Grafo_hpp
#define Grafo_hpp

#include "Vertice.hpp"
#include "Arista.hpp"
#include "Estacion.hpp"

using namespace std;

class Grafo{
private:
    Vertice* raiz;
    int tamaño;
    
public:
    Grafo();
    bool isEmpty();
    int obtenerTamano();
    Vertice* obtenerVertice(Estacion* estacion);
    void insetarVertice(Estacion* estaciono); //
    void insertarArista(Estacion* origen, Estacion* destino, int peso);//
    void mostrarListaDeAdyacencia(); //
    void eliminarVertice(Estacion* estacion); //
    void eliminarArista(Estacion* origen, Estacion* destino); //
    void eliminarTodo(); //
    void eliminarAristas(Vertice* vertice); //
    bool existe(Estacion* estacion); //
    void eliminarAristasDestino(Estacion* estacion);//
    void guardarGrafo(); //
    void cargarGrafo(); //
    void dijkstra(Estacion* origen, Estacion* destino);

};

#endif /* Grafo_hpp */
