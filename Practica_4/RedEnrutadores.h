#ifndef REDENRUTADORES_H
#define REDENRUTADORES_H

#include <string>
#include <map>
#include "Enrutador.h"
using namespace std;

class RedEnrutadores {
private:
    map<string, Enrutador*> routers;
    void dijkstra(const string& origen, map<string, int>& distancias,  map<string, string>& predecesores);

public:
    ~RedEnrutadores();

    void cargarDesdeCSV(const string& archivo);
    void agregarRouter(const string& nombre);
    void eliminarRouter(const string& nombre);
    void agregarEnlace(const string& origen, const string& destino, int costo);

    void mostrarCaminoMasCorto(const string& origen, const string& destino);
    void mostrarTodosLosRouters() const;
    void mostrarTablaRouter(const string& nombre);
    void mostrarVecinosRouter(const string& nombre);
    void mostrarMatrizCostos() const;

    void generarRedAleatoria();
    void mostrarTablaDeCostos(const std::string& origen);
    void mostrarTablaCompletaAleatoria();

};


#endif // REDENRUTADORES_H
