//
//  Arista.cpp
//  GRAFO - ARCHIVOS
//
//  Created by Bryan Bautista on 18/03/23.
//

#include "Arista.hpp"

Arista::Arista(Vertice* destino, int peso){
    this->peso = peso;
    this->dest = destino;
    this->sig = nullptr;
}
