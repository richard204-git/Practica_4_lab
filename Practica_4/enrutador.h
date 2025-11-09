#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>
#include <vector>
#include "Enlaces.h"
using namespace std;

class Enrutador {
private:
    string nombre;
    map<string, int> tablaCostos;
    map<string, string> tablaRutas;
    vector<Enlace> vecinos;

public:
    Enrutador(const string& n);

    string getNombre() const;
    void agregarVecino(const string& destino, int costo);
    void eliminarVecino(const string& destino);
    const vector<Enlace>& getVecinos() const;

    void actualizarTablaCostos(const string& destino, int costo, const string& siguienteSalto);

    map<string, int> getTablaCostos() const;
    void mostrarTablaCostos() const;
    void mostrarVecinos() const;
};

#endif // ENRUTADOR_H
