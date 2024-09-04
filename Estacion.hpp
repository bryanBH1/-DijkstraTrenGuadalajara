//
//  Estacion.hpp
//  GRAFO - ARCHIVOS
//
//  Created by Bryan Bautista on 19/05/23.
//

#ifndef Estacion_hpp
#define Estacion_hpp

#include <iostream>
using namespace std;

class Estacion{
private:
    string linea;
    string nombre;
    
    friend class Grafo;
    
public:
    Estacion(string nombre, string linea);
    Estacion(string nombre);
    Estacion();
    
};

#endif /* Estacion_hpp */
