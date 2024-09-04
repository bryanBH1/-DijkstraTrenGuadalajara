//
//  Vertice.cpp
//  GRAFO - ARCHIVOS
//
//  Created by Bryan Bautista on 18/03/23.
//

#include "Vertice.hpp"

Vertice::Vertice(Estacion* estacion){
    this->estacion = estacion;
    this->sig = nullptr;
    this->ari = nullptr;
}
