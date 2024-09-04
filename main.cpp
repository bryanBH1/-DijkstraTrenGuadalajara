//
//  main.cpp
//  GRAFO - ARCHIVOS
//
//  Created by Bryan Bautista on 18/03/23.
//

#include <iostream>
#include "Grafo.hpp"
#include "Estacion.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
    Grafo* grafo = new Grafo();
    int opcion,peso,tamaño;
    string nombre, linea, origen, destino;
    
    do{
        cout<<"MENU"<<endl;
        cout<<"1.-Insertar estacion"<<endl;
        cout<<"2.-Insertar conexion"<<endl;
        cout<<"3.-Obtener cantdad de conexiones"<<endl;
        cout<<"4.-Mostrar lista de adyacencia"<<endl;
        cout<<"5.-Eliminar estacion"<<endl;
        cout<<"6.-Eliminar conexion"<<endl;
        cout<<"7.-Eliminar todo"<<endl;
        cout<<"8.-Guardar sistema"<<endl;
        cout<<"9.-Cargar sistema"<<endl;
        cout<<"10.- Mostrar el camino mas corto"<<endl;
        cout<<"11.-Salir"<<endl;
        cout<<"Ingresa una opcion: ";
        cin>>opcion;
        
        switch (opcion) {
            case 1:{
                cout<<endl;
                cin.ignore();
                cout<<"INGRESANDO ESTACION"<<endl<<endl;
                cout<<"Estacion: ";
                getline(cin, nombre);
                cout<<"Linea: ";
                cin>>linea;

                
                Estacion* estacion1 = new Estacion(nombre,linea);
                grafo->insetarVertice(estacion1);
                
                break;
            }
            case 2:{
                cout<<endl;
                cin.ignore();
                cout<<"INGRESANDO CONEXION"<<endl<<endl;
                cout<<"Oigen: ";
                getline(cin, origen);
                cout<<"Destino: ";
                getline(cin, destino);
                cout<<"Kilometros: ";
                cin>>peso;
                Estacion* estacion1 = new Estacion(origen);
                Estacion* estacion2 = new Estacion(destino);
                grafo->insertarArista(estacion1, estacion2, peso);
                break;
            }
            case 3:
                tamaño = grafo->obtenerTamano();
                cout<<endl;
                cout<<"Hay "<<tamaño<<" estaciones";
                break;
            case 4:
                grafo->mostrarListaDeAdyacencia();
                break;
            case 5:{
                cout<<endl;
                cout<<"ELIMINADO ESTACION"<<endl<<endl;
                cout<<"Ingresa el nombre de la estacion: ";
                getline(cin, nombre);
                Estacion* estacion1 = new Estacion(nombre);
                grafo->eliminarVertice(estacion1);
                break;
            }
            case 6:{
                cout<<endl;
                cout<<"ELIMINADO CONEXION"<<endl<<endl;
                cout<<"Ingresa la estacion origen: ";
                getline(cin, origen);
                cout<<"Ingresa la estacion destino: ";
                getline(cin, destino);
                
                Estacion* estacion1 = new Estacion(origen);
                Estacion* estacion2 = new Estacion(destino);
                
                grafo->eliminarArista(estacion1, estacion2);
                break;
            }
            case 7:
                grafo->eliminarTodo();
                break;
            case 8:
                grafo->guardarGrafo();
                break;
            case 9:
               grafo->cargarGrafo();
                break;
            case 10:{
                cout<<endl;
                cin.ignore();
                cout<<"BUSQUEDA DEL CAMINO MAS CORTO"<<endl<<endl;
                cout<<"Origen: ";
                getline(cin, origen);
                cout<<"Destino: ";
                getline(cin, destino);
                
                Estacion* estacion1 = new Estacion(origen);
                Estacion* estacion2 = new Estacion(destino);
                
                grafo->dijkstra(estacion1, estacion2);
            }
                break;
            default:
                break;
        }
        cout<<endl<<endl;
    }while(opcion != 11);
    
    return 0;
}
