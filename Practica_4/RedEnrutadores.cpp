#include "RedEnrutadores.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <set>
#include <random>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <iomanip>  // para setw() y left()
using namespace std;

RedEnrutadores::~RedEnrutadores() {
    for (auto& [_, router] : routers)
        delete router;
}

void RedEnrutadores::cargarDesdeCSV(const string& archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error: no se pudo abrir el archivo " << archivo << endl;
        return;
    }

    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string origen, destino, costoStr;
        getline(ss, origen, ';');
        getline(ss, destino, ';');
        getline(ss, costoStr, ';');
        int costo = stoi(costoStr);

        if (routers.find(origen) == routers.end())
            routers[origen] = new Enrutador(origen);
        if (routers.find(destino) == routers.end())
            routers[destino] = new Enrutador(destino);

        routers[origen]->agregarVecino(destino, costo);
        routers[destino]->agregarVecino(origen, costo);
    }

    file.close();
    cout << "Red cargada desde el archivo: " << archivo << endl;

}

void RedEnrutadores::agregarRouter(const string& nombre) {
    if (routers.find(nombre) != routers.end()) {
        cout << "El router " << nombre << " ya existe." << endl;
        return;
    }
    routers[nombre] = new Enrutador(nombre);
    cout << "Router " << nombre << " agregado temporalmente (no se guarda en archivo)." << endl;


}

void RedEnrutadores::eliminarRouter(const string& nombre) {
    if (routers.find(nombre) == routers.end()) {
        cout << "El router " << nombre << " no existe." << endl;
        return;
    }

    delete routers[nombre];
    routers.erase(nombre);

    for (auto& [_, router] : routers)
        router->eliminarVecino(nombre);

    cout << "Router " << nombre << " eliminado (solo en ejecución)." << endl;
}

void RedEnrutadores::agregarEnlace(const string& origen, const string& destino, int costo) {
    if (routers.find(origen) == routers.end() || routers.find(destino) == routers.end()) {
        cout << "Alguno de los routers no existe." << endl;
        return;
    }
    routers[origen]->agregarVecino(destino, costo);
    routers[destino]->agregarVecino(origen, costo);

}


void RedEnrutadores::dijkstra(const string& origen, map<string, int>& distancias, map<string, string>& predecesores) {
    const int INF = numeric_limits<int>::max();
    distancias.clear();
    predecesores.clear();

    for (auto& [nombre, _] : routers)
        distancias[nombre] = INF;

    distancias[origen] = 0;
    set<pair<int, string>> cola;
    cola.insert({0, origen});

    while (!cola.empty()) {
        string actual = cola.begin()->second;
        cola.erase(cola.begin());

        for (auto& enlace : routers[actual]->getVecinos()) {
            string vecino = enlace.getDestino();
            int nuevoCosto = distancias[actual] + enlace.getCosto();

            if (nuevoCosto < distancias[vecino]) {
                cola.erase({distancias[vecino], vecino});
                distancias[vecino] = nuevoCosto;
                predecesores[vecino] = actual;
                cola.insert({nuevoCosto, vecino});
            }
        }
    }
}

void RedEnrutadores::mostrarCaminoMasCorto(const string& origen, const string& destino) {
    if (routers.find(origen) == routers.end() || routers.find(destino) == routers.end()) {
        cout << "Uno de los routers no existe." << endl;
        return;
    }

    map<string, int> distancias;
    map<string, string> predecesores;
    dijkstra(origen, distancias, predecesores);

    if (distancias[destino] == numeric_limits<int>::max()) {
        cout << "No hay camino entre " << origen << " y " << destino << endl;
        return;
    }

    vector<string> camino;
    for (string actual = destino; actual != origen; actual = predecesores[actual])
        camino.push_back(actual);
    camino.push_back(origen);
    reverse(camino.begin(), camino.end());

    cout << "\nCamino más corto de " << origen << " a " << destino << ":\n";
    for (size_t i = 0; i < camino.size(); i++) {
        cout << camino[i];
        if (i < camino.size() - 1) cout << " -> ";
    }
    cout << "\nCosto total: " << distancias[destino] << endl;
}

void RedEnrutadores::mostrarTodosLosRouters() const {
    cout << "\nRouters actuales en la red:\n";
    for (auto& [nombre, _] : routers)
        cout << "- " << nombre << endl;
}

void RedEnrutadores::mostrarTablaRouter(const string& nombre) {
    if (routers.find(nombre) == routers.end()) {
        cout << "Router no encontrado.\n";
        return;
    }
    routers[nombre]->mostrarTablaCostos();
}

void RedEnrutadores::mostrarVecinosRouter(const string& nombre) {
    if (routers.find(nombre) == routers.end()) {
        cout << "Router no encontrado.\n";
        return;
    }
    routers[nombre]->mostrarVecinos();
}

void RedEnrutadores::mostrarTablaDeCostos(const std::string& origen) {
    if (routers.find(origen) == routers.end()) {
        cout << "El enrutador " << origen << " no existe." << endl;
        return;
    }

    unordered_map<string, int> distancia;
    unordered_map<string, string> anterior;
    const int INF = numeric_limits<int>::max();

    for (auto& [nombre, _] : routers)
        distancia[nombre] = INF;
    distancia[origen] = 0;

    using P = pair<int, string>;
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, origen});

    while (!pq.empty()) {
        auto [dist, actual] = pq.top();
        pq.pop();
        if (dist > distancia[actual]) continue;

        // Relajación de Dijkstra
        for (const Enlace& enlace : routers[actual]->getVecinos()) {
            string vecino = enlace.getDestino();
            int nuevoCosto = dist + enlace.getCosto();

            if (nuevoCosto < distancia[vecino]) {
                distancia[vecino] = nuevoCosto;
                anterior[vecino] = actual;
                pq.push({nuevoCosto, vecino});
            }
        }
    }

    // Mostrar resultados
    cout << "\nTabla de costos desde el enrutador " << origen << ":\n";
    cout << "Destino\tCosto\tCamino\n";
    cout << "---------------------------------\n";

    for (auto& [destino, costo] : distancia) {
        if (destino == origen) continue;
        if (costo == INF) {
            cout << destino << "\tINF\tSin conexion\n";
        } else {
            vector<string> camino;
            string actual = destino;
            while (actual != origen) {
                camino.push_back(actual);
                actual = anterior[actual];
            }
            camino.push_back(origen);
            reverse(camino.begin(), camino.end());

            cout << destino << "\t" << costo << "\t";
            for (size_t i = 0; i < camino.size(); i++) {
                cout << camino[i];
                if (i < camino.size() - 1) cout << " -> ";
            }
            cout << "\n";
        }
    }
    cout << endl;
}

void RedEnrutadores::generarRedAleatoria() {
    routers.clear(); // limpiamos la red anterior
    int cantidad;
    cout << "Ingrese la cantidad de routers que desea crear: ";
    cin >> cantidad;

    if (cantidad <= 0) {
        cout << "Cantidad no válida.\n";
        return;
    }

    // Registrar los nombres de los routers
    vector<string> nombres;
    for (int i = 0; i < cantidad; ++i) {
        string nombre;
        cout << "Ingrese el nombre del router #" << (i + 1) << ": ";
        cin >> nombre;
        nombres.push_back(nombre);
        routers[nombre] = new Enrutador(nombre);
    }

    // Generador aleatorio de enlaces
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> costoDist(1, 20);   // costos entre 1 y 20
    uniform_real_distribution<> probDist(0.0, 1.0); // probabilidad de conexión

    cout << "\nGenerando conexiones aleatorias...\n";
    for (int i = 0; i < cantidad; ++i) {
        for (int j = i + 1; j < cantidad; ++j) {
            if (probDist(gen) < 0.5) { // 50% de probabilidad de crear un enlace
                int costo = costoDist(gen);
                routers[nombres[i]]->agregarVecino(nombres[j], costo);
                routers[nombres[j]]->agregarVecino(nombres[i], costo);
                cout << "Conectado " << nombres[i] << " <-> " << nombres[j] << " con costo " << costo << endl;
            }
        }
    }

    cout << "\nRed aleatoria generada exitosamente.\n";

}

void RedEnrutadores::mostrarTablaCompletaAleatoria()  {
    if (routers.empty()) {
        cout << "No hay routers cargados en la red aleatoria.\n";
        return;
    }
    cout << " -----------------  ";
    cout << "\n[ TABLA CONEXIONES ]\n";
    cout << " -----------------  \n";
    cout << left << setw(12) << "ORIGEN" << setw(12) << "DESTINO" << setw(8) << "COSTO" << endl;
    cout << string(30, '-') << endl;

    // Recorremos los routers y sus vecinos
    for (const auto& [nombre, router] : routers) {
        for (const auto& enlace : router->getVecinos()) {
            cout << left << setw(12) << nombre << setw(12) << enlace.getDestino() << setw(8)  << enlace.getCosto() << endl;
        }
    }
}
