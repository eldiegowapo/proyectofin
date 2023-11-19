#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct Orden {
    int numeroTicket;
    string razonSocial;
    string nombreVendedor;
    string fecha;
    vector<string> articulos;
    vector<double> precios;
    vector<int> cantidades;
    double descuentos;
    double propina;
    double impuesto;
    double total;
    bool cancelada;
};

vector<Orden> ordenes;

void Alta();
void Modificar();
void Eliminar();
void ListaOrdenes();
void LimpiarPantalla();
void ArchivarOrdenes();
void GuardarOrdenesEnArchivo(const string& nombreArchivo);
void CargarOrdenesDesdeArchivo(const string& nombreArchivo);

int main() {
    CargarOrdenesDesdeArchivo("ordenes.txt");

    int opcion;
    do {
        cout << "---------------Menú de opciones:---------------" << endl;
        cout << "1. Alta de Ordenes" << endl;
        cout << "2. Modificar Orden" << endl;
        cout << "3. Eliminar o Cancelar Orden" << endl;
        cout << "4. Lista de Ordenes" << endl;
        cout << "5. Limpiar pantalla" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                Alta();
                break;
            case 2:
                Modificar();
                break;
            case 3:
                Eliminar();
                break;
            case 4:
                ListaOrdenes();
                break;
            case 5:
                LimpiarPantalla();
                break;
            case 6:
                ArchivarOrdenes();
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 6);

    return 0;
}

void Alta() {
    Orden nuevaOrden;
    cout << "Ingrese la razón social del restaurante: ";
    cin.ignore();
    getline(cin, nuevaOrden.razonSocial);
    cout << "Ingrese el número de ticket (no se puede repetir): ";
    cin >> nuevaOrden.numeroTicket;

    // Verificar si el número de ticket ya existe
    for (const Orden& orden : ordenes) {
        if (orden.numeroTicket == nuevaOrden.numeroTicket) {
            cout << "¡Error! El número de ticket ya existe. Intente de nuevo." << endl;
            return;
        }
    }

    cout << "Ingrese el nombre del vendedor: ";
    cin.ignore();
    getline(cin, nuevaOrden.nombreVendedor);
    cout << "Ingrese la fecha: ";
    getline(cin, nuevaOrden.fecha);

    // Ingresar artículos y precios
    int numArticulos;
    cout << "Ingrese el número de artículos: ";
    cin >> numArticulos;

    for (int i = 0; i < numArticulos; ++i) {
        string articulo;
        double precio;
        int cantidad;

        cout << "Ingrese el artículo " << i + 1 << ": ";
        cin.ignore();
        getline(cin, articulo);

        cout << "Ingrese el precio del artículo " << i + 1 << ": ";
        cin >> precio;

        cout << "Ingrese la cantidad del artículo " << i + 1 << ": ";
        cin >> cantidad;

        nuevaOrden.articulos.push_back(articulo);
        nuevaOrden.precios.push_back(precio);
        nuevaOrden.cantidades.push_back(cantidad);
    }

    cout << "Ingrese el descuento o promoción (%): ";
    cin >> nuevaOrden.descuentos;

    cout << "Ingrese la propina (10%, 15%, 20%): ";
    cin >> nuevaOrden.propina;

    cout << "Ingrese el impuesto: ";
    cin >> nuevaOrden.impuesto;

    // Calcular el total
    nuevaOrden.total = 0;
    for (size_t i = 0; i < nuevaOrden.articulos.size(); ++i) {
        nuevaOrden.total += nuevaOrden.precios[i] * nuevaOrden.cantidades[i];
    }

    nuevaOrden.total -= (nuevaOrden.total * nuevaOrden.descuentos) / 100;
    nuevaOrden.total += (nuevaOrden.total * nuevaOrden.propina) / 100;
    nuevaOrden.total += nuevaOrden.impuesto;

    nuevaOrden.cancelada = false;

    // Agregar la nueva orden al vector
    ordenes.push_back(nuevaOrden);

    cout << "Orden creada exitosamente." << endl;
}

void Modificar() {
    int numeroTicket;
    cout << "Ingrese el número de ticket de la orden que desea modificar: ";
    cin >> numeroTicket;

    bool encontrado = false;
    for (Orden& orden : ordenes) {
        if (orden.numeroTicket == numeroTicket && !orden.cancelada) {
            cout << "Orden encontrada. Modifique los campos necesarios:" << endl;

            cout << "Ingrese la nueva razón social del restaurante: ";
            cin.ignore();
            getline(cin, orden.razonSocial);

            cout << "Ingrese el nuevo nombre del vendedor: ";
            getline(cin, orden.nombreVendedor);

            cout << "Ingrese la nueva fecha: ";
            getline(cin, orden.fecha);

            // Modificar artículos y precios
            int numArticulos;
            cout << "Ingrese el nuevo número de artículos: ";
            cin >> numArticulos;

            orden.articulos.clear();
            orden.precios.clear();
            orden.cantidades.clear();

            for (int i = 0; i < numArticulos; ++i) {
                string articulo;
                double precio;
                int cantidad;

                cout << "Ingrese el nuevo artículo " << i + 1 << ": ";
                cin.ignore();
                getline(cin, articulo);

                cout << "Ingrese el nuevo precio del artículo " << i + 1 << ": ";
                cin >> precio;

                cout << "Ingrese la nueva cantidad del artículo " << i + 1 << ": ";
                cin >> cantidad;

                orden.articulos.push_back(articulo);
                orden.precios.push_back(precio);
                orden.cantidades.push_back(cantidad);
            }

            cout << "Ingrese el nuevo descuento o promoción (%): ";
            cin >> orden.descuentos;

            cout << "Ingrese la nueva propina (10%, 15%, 20%): ";
            cin >> orden.propina;

            cout << "Ingrese el nuevo impuesto: ";
            cin >> orden.impuesto;

            // Calcular el nuevo total
            orden.total = 0;
            for (size_t i = 0; i < orden.articulos.size(); ++i) {
                orden.total += orden.precios[i] * orden.cantidades[i];
            }

            orden.total -= (orden.total * orden.descuentos) / 100;
            orden.total += (orden.total * orden.propina) / 100;
            orden.total += orden.impuesto;

            cout << "Orden modificada exitosamente." << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "¡Error! Orden no encontrada o cancelada." << endl;
    }
}

void Eliminar() {
    int numeroTicket;
    cout << "Ingrese el número de ticket de la orden que desea eliminar o cancelar: ";
    cin >> numeroTicket;

    for (Orden& orden : ordenes) {
        if (orden.numeroTicket == numeroTicket && !orden.cancelada) {
            cout << "Orden encontrada. ¿Desea cancelarla? (1: Sí / 2: No): ";
            int opcion;
            cin >> opcion;

            if (opcion == 1) {
                orden.cancelada = true;
                cout << "Orden cancelada exitosamente." << endl;
            }

            return;
        }
    }

    cout << "¡Error! Orden no encontrada o ya cancelada." << endl;
}

void ListaOrdenes() {
    int opcion;
    cout << "Filtrar por:\n1. Número de ticket\n2. Mostrar todas" << endl;
    cout << "Seleccione una opción: ";
    cin >> opcion;

    cout << setw(10) << "Ticket" << setw(20) << "Razón Social" << setw(20) << "Vendedor"
         << setw(15) << "Fecha" << setw(15) << "Total" << setw(15) << "Estado" << endl;
    cout << string(95, '-') << endl;

    for (const Orden& orden : ordenes) {
        if ((opcion == 1 && orden.cancelada) || (opcion == 2)) {
            cout << setw(10) << orden.numeroTicket << setw(20) << orden.razonSocial
                 << setw(20) << orden.nombreVendedor << setw(15) << orden.fecha
                 << setw(15) << orden.total << setw(15) << (orden.cancelada ? "Cancelada" : "Activa") << endl;
        }
    }
}

void LimpiarPantalla() {
    system("cls");  // En Windows
    //system("clear");  // En sistemas tipo Unix/Linux
}

void ArchivarOrdenes() {
    GuardarOrdenesEnArchivo("ordenes.txt");
    cout << "¡Gracias por utilizar el punto de venta! Se han guardado las ordenes." << endl;
}

void GuardarOrdenesEnArchivo(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::binary);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para escribir." << endl;
        exit(EXIT_FAILURE);
    }

    for (const Orden& orden : ordenes) {
        archivo << orden.numeroTicket << "\n";
        archivo << orden.razonSocial << "\n";
        archivo << orden.nombreVendedor << "\n";
        archivo << orden.fecha << "\n";
        archivo << orden.articulos.size() << "\n";

        for (size_t i = 0; i < orden.articulos.size(); ++i) {
            archivo << orden.articulos[i] << "\n";
            archivo << orden.precios[i] << "\n";
            archivo << orden.cantidades[i] << "\n";
        }

        archivo << orden.descuentos << "\n";
        archivo << orden.propina << "\n";
        archivo << orden.impuesto << "\n";
        archivo << orden.total << "\n";
        archivo << orden.cancelada << "\n";
    }

    archivo.close();
}

void CargarOrdenesDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary);

    if (!archivo.is_open()) {
        cerr << "No se encontró el archivo de órdenes. Se creará uno nuevo." << endl;
        return;
    }

    ordenes.clear();

    while (!archivo.eof()) {
        Orden orden;
        int numArticulos;

        archivo >> orden.numeroTicket;
        archivo.ignore();

        getline(archivo, orden.razonSocial);
        getline(archivo, orden.nombreVendedor);
        getline(archivo, orden.fecha);

        archivo >> numArticulos;
        archivo.ignore();

        for (int i = 0; i < numArticulos; ++i) {
            string articulo;
            double precio;
            int cantidad;

            getline(archivo, articulo);
            archivo >> precio;
            archivo >> cantidad;
            archivo.ignore();

            orden.articulos.push_back(articulo);
            orden.precios.push_back(precio);
            orden.cantidades.push_back(cantidad);
        }

        archivo >> orden.descuentos;
        archivo >> orden.propina;
        archivo >> orden.impuesto;
        archivo >> orden.total;
        archivo >> orden.cancelada;
        archivo.ignore();

        ordenes.push_back(orden);
    }

    archivo.close();
}
