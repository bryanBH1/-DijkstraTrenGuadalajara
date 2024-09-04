//
//  Arista.hpp
//  GRAFO - ARCHIVOS
//
//  Created by Bryan Bautista on 18/03/23.
//

#ifndef Arista_hpp
#define Arista_hpp

#include <iostream>
using namespace std;
class Vertice; // Declaración adelantada de la clase B

class Arista{
private:
    int peso;
    Arista* sig;
    Vertice* dest;
    
    friend class Grafo; // permito el acceso a grafo
public:
    Arista(Vertice* destino,int peso);
};

#endif /* Arista_hpp */
