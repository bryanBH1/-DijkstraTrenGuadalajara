//
//  Vertice.hpp
//  GRAFO - ARCHIVOS
//
//  Created by Bryan Bautista on 18/03/23.
//

#ifndef Vertice_hpp
#define Vertice_hpp

#include <iostream>
using namespace std;
#include "Estacion.hpp"

class Arista; // Declaración adelantada de la clase

class Vertice{
private:
    Estacion* estacion;
    Vertice* sig;
    Arista* ari;
    
    friend class Grafo; // permito el acceso a grafo
public:
    Vertice(Estacion* estacion);
};


#endif /* Vertice_hpp */
