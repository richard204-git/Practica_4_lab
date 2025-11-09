#ifndef ENLACES_H
#define ENLACES_H


#include <string>
using namespace std;

class Enlace {
private:
    string destino;
    int costo;

public:
    Enlace(const string& dest, int c);
    string getDestino() const;
    int getCosto() const;
    void setCosto(int c);
};

#endif // ENLACES_H
