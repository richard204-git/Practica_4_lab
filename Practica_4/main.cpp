#include <iostream>
#include "RedEnrutadores.h"
using namespace std;

int main() {
    RedEnrutadores red;
    string archivo = "Routers.csv"; // archivo base
    red.cargarDesdeCSV(archivo);

    int opcion;
    do {
        cout << "\n=== [ MENUN ] ===\n";
        cout << "1. Mostrar routers\n";
        cout << "2. Agregar router\n";
        cout << "3. Eliminar router\n";
        cout << "4. Agregar enlace entre routers\n";
        cout << "5. Mostrar camino mas corto\n";
        cout << "6. Mostrar vecinos de un router\n";
        cout << "7. Mostrar tabla de costo a todo destino\n";
        cout << "8. Generar red aleatoria\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            red.mostrarTodosLosRouters();
        }
        else if (opcion == 2) {
            string nombre;
            cout << "Ingrese el nombre del nuevo router: ";
            cin >> nombre;
            red.agregarRouter(nombre);
        }
        else if (opcion == 3) {
            string nombre;
            cout << "Ingrese el nombre del router a eliminar: ";
            cin >> nombre;
            red.eliminarRouter(nombre);
        }
        else if (opcion == 4) {
            string origen, destino;
            int costo;
            cout << "Ingrese router origen: ";
            cin >> origen;
            cout << "Ingrese router destino: ";
            cin >> destino;
            cout << "Ingrese costo del enlace: ";
            cin >> costo;
            red.agregarEnlace(origen, destino, costo);
        }
        else if (opcion == 5) {
            string origen, destino;
            cout << "Ingrese router origen: ";
            cin >> origen;
            cout << "Ingrese router destino: ";
            cin >> destino;
            red.mostrarCaminoMasCorto(origen, destino);
        }
        else if (opcion == 6) {
            string nombre;
            cout << "Ingrese el nombre del router: ";
            cin >> nombre;
            red.mostrarVecinosRouter(nombre);
        }
        else if (opcion == 7) {
            string router;
            cout << "Ingrese el router a mostrar la tabla de costos: ";
            cin >> router;
            red.mostrarTablaDeCostos(router);
        }
        else if (opcion == 8) {
            // Aquí empieza el menú de red aleatoria
            RedEnrutadores redAleatoria;
            redAleatoria.generarRedAleatoria();

            int subopcion;
            do {
                cout << "\n===== [] MENU RED ALEATORIA ] =====\n";
                cout << "1. Mostrar routers generados\n";
                cout << "2. Mostrar vecinos de un router\n";
                cout << "3. Mostrar tabla de costos de un router\n";
                cout << "4. Mostrar camino más corto\n";
                cout << "5. Mostrar tabla completa de conexiones\n";
                cout << "0. Volver al menú principal\n";
                cout << "Seleccione una opción: ";
                cin >> subopcion;

                if (subopcion == 1) {
                    redAleatoria.mostrarTodosLosRouters();
                }
                else if (subopcion == 2) {
                    string nombre;
                    cout << "Ingrese el nombre del router: ";
                    cin >> nombre;
                    cout <<endl;
                    redAleatoria.mostrarVecinosRouter(nombre);
                }
                else if (subopcion == 3) {
                    string router;
                    cout << "Ingrese el router: ";
                    cin >> router;
                    cout <<endl;
                    redAleatoria.mostrarTablaDeCostos(router);
                }
                else if (subopcion == 4) {
                    string origen, destino;
                    cout << "Ingrese router origen: ";
                    cin >> origen;
                    cout <<endl;
                    cout << "Ingrese router destino: ";
                    cin >> destino;
                    cout <<endl;
                    redAleatoria.mostrarCaminoMasCorto(origen, destino);
                }
                else if (subopcion == 5) {
                    redAleatoria.mostrarTablaCompletaAleatoria();
                    cout <<endl;
                }

            } while (subopcion != 0);
        }

    } while (opcion != 0);

    cout << "Saliendo del simulador...\n";
    return 0;
}

