#include "Enrutador.h"
#include <iostream>
#include <algorithm>
using namespace std;

Enrutador::Enrutador(const string& n) : nombre(n) {}

string Enrutador::getNombre() const {
    return nombre;
}

void Enrutador::agregarVecino(const string& destino, int costo) {
    for (auto& v : vecinos) {
        if (v.getDestino() == destino) {
            v.setCosto(costo);
            return;
        }
    }
    vecinos.emplace_back(destino, costo);
}

void Enrutador::eliminarVecino(const string& destino) {
    vecinos.erase(remove_if(vecinos.begin(), vecinos.end(),
                            [&](const Enlace& e) { return e.getDestino() == destino; }),
                  vecinos.end());
}

const vector<Enlace>& Enrutador::getVecinos() const {
    return vecinos;
}

void Enrutador::actualizarTablaCostos(const string& destino, int costo, const string& siguienteSalto) {
    tablaCostos[destino] = costo;
    tablaRutas[destino] = siguienteSalto;
}

map<string, int> Enrutador::getTablaCostos() const {
    return tablaCostos;
}

void Enrutador::mostrarTablaCostos() const {
    cout << "\nTabla de costos del router " << nombre << ":\n";
    for (const auto& [dest, cost] : tablaCostos)
        cout << "  -> " << dest << " : " << cost << endl;
}

void Enrutador::mostrarVecinos() const {
    cout << "Vecinos de " << nombre << ":\n";
    for (const auto& v : vecinos)
        cout << "  - " << v.getDestino() << " (costo " << v.getCosto() << ")\n";
}
