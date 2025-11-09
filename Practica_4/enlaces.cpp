#include "enlaces.h"

Enlace::Enlace(const string& dest, int c) : destino(dest), costo(c) {}

string Enlace::getDestino() const {
    return destino;
}

int Enlace::getCosto() const {
    return costo;
}

void Enlace::setCosto(int c) {
    costo = c;
}
