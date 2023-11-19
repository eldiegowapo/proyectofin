#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Articulo {
    string nombre;
    int cantidad;
    double precioUnitario;
};

struct Ticket {
    string razonSocial;
    int numeroTicket;
    string nombreVendedor;
    string fecha;
    vector<Articulo> listaArticulos;
    double precioArticulos;
    double descuentos;
    double propina;
    double impuesto;
    double total;
};

int main() {
    Ticket ticket;

    // Capturar datos generales del restaurante
    cout << "Ingrese la raz�n social del restaurante: ";
    getline(cin, ticket.razonSocial);

    // Capturar n�mero de ticket (no se puede repetir)
    cout << "Ingrese el n�mero de ticket: ";
    cin >> ticket.numeroTicket;

    // Limpiar el buffer del teclado despu�s de leer un n�mero
    cin.ignore();

    // Capturar nombre del vendedor
    cout << "Ingrese el nombre del vendedor: ";
    getline(cin, ticket.nombreVendedor);

    // Capturar fecha
    cout << "Ingrese la fecha: ";
    getline(cin, ticket.fecha);

    // Capturar lista de art�culos
    cout << "Ingrese los art�culos (nombre cantidad precioUnitario): " << endl;
    while (true) {
        Articulo articulo;
        string nombre;
        int cantidad;
        double precioUnitario;

        cin >> nombre;
        if (nombre == "fin") {
            break;
        }

        cin >> cantidad >> precioUnitario;
        cin.ignore();

        articulo.nombre = nombre;
        articulo.cantidad = cantidad;
        articulo.precioUnitario = precioUnitario;

        ticket.listaArticulos.push_back(articulo);
        ticket.precioArticulos += cantidad * precioUnitario;
    }

    // Capturar descuentos o promociones
    cout << "Ingrese descuentos o promociones (si no hay, ingrese 0): ";
    cin >> ticket.descuentos;

    // Calcular propina
    cout << "Seleccione la propina (10%, 15%, 20%): ";
    int opcionPropina;
    cin >> opcionPropina;
    switch (opcionPropina) {
    case 10:
        ticket.propina = 0.1 * ticket.precioArticulos;
        break;
    case 15:
        ticket.propina = 0.15 * ticket.precioArticulos;
        break;
    case 20:
        ticket.propina = 0.2 * ticket.precioArticulos;
        break;
    default:
        cout << "Opci�n de propina inv�lida. No se aplicar� propina." << endl;
        ticket.propina = 0;
    }

    // Capturar impuesto
    cout << "Ingrese el impuesto: ";
    cin >> ticket.impuesto;

    // Calcular total
    ticket.total = ticket.precioArticulos - ticket.descuentos + ticket.propina + ticket.impuesto;

    // Mostrar el resumen del ticket
    cout << "\n--- Resumen del Ticket ---\n";
    cout << "Raz�n Social: " << ticket.razonSocial << endl;
    cout << "N�mero de Ticket: " << ticket.numeroTicket << endl;
    cout << "Nombre del Vendedor: " << ticket.nombreVendedor << endl;
    cout << "Fecha: " << ticket.fecha << endl;
    cout << "Art�culos:\n";
    for (const auto& articulo : ticket.listaArticulos) {
        std::cout << "- " << articulo.nombre << ": " << articulo.cantidad << " x $" << articulo.precioUnitario << std::endl;
    }
    cout << "Precio de los Art�culos: $" << ticket.precioArticulos << endl;
    cout << "Descuentos: $" << ticket.descuentos << endl;
    cout << "Propina: $" << ticket.propina << endl;
    cout << "Impuesto: $" << ticket.impuesto << endl;
    cout << "Total a Pagar: $" << ticket.total << endl;

    return 0;
}
