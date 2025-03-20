#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

void printline(string archivo);
void logMessage(string archivo, string mensaje, string usuario); 
void logMessage(string archivo, string mensaje); 
void handleError(string archivo, string error);
void logMessage(string archivo, string error, int linea = 0); 
int main() {
    string nombre;
    int op;

    cout << "Ingrese el nombre del archivo log: ";
    cin >> nombre;

    cout << "Que desea hacer con el archivo\n1) Solo lectura\n2) Escribir log Messages\n3) Log de Acceso\n";
    cin >> op;

    if (op == 2) {
        int op2;
        int op3;
        cout << "Seleccione el log Message que desea mostrar en su archivo\n1) 'No se pudo establecer conexion con el servidor.'\n2) 'Permiso denegado al intentar acceder al archivo.'\n3) 'Archivo de configuracion no encontrado.'\n";
        cin >> op2;
        cout << "Desea especificar en que linea de código?\n1) Si\n2) No\n";
        cin >> op3;

        string error;
        int linea = 0; 

        if (op3 == 1) {                                // inciso b) ii)
            cout << "Ingrese la linea del log: ";
            cin >> linea;
        }

        if (op2 == 1) {
            error = "ERROR: No se pudo establecer conexion con el servidor.";
        }
        if (op2 == 2) {
            error = "ERROR: Permiso denegado al intentar acceder al archivo.";
        }
        if (op2 == 3) {
            error = "ERROR: Archivo de configuracion no encontrado.";
        }
        logMessage(nombre, error, linea);  // Llamo a la version con linea
    } else if (op == 1) {
        printline(nombre);
    } else if (op == 3) {               // inciso b) iii)
        string mensaje, usuario;
        cout << "Ingrese el mensaje de acceso (ej. 'Access Granted', 'Access Denied'): ";
        cin.ignore(); // Limpio el buffer
        getline(cin, mensaje);
        cout << "Ingrese el nombre de usuario: ";
        getline(cin, usuario);
        logMessage(nombre, mensaje, usuario);  // Llamo a la version de log de acceso
    } else {
        cout << "Opción no valida.\n";
    }

    // Simulo un error de ejecucion // inciso b) iv)
    try {
        // Aca simulo una operacion que falla
        throw runtime_error("Error en la ejecucion del programa.");
    } catch (const runtime_error& e) {
        handleError(nombre, e.what());
        return 1;  // Termino el programa con un codigo de error
    }

    return 0;
}

void printline(string archivo) {
    ifstream archivolectura(archivo);
    if (!archivolectura) {
        cerr << "ERROR AL ABRIR EL LOG\n";
        return;
    }
    string linea;
    while (getline(archivolectura, linea)) {
        cout << "Leido: " << linea << "\n";
    }
    archivolectura.close();
}

// Sobrecarga para log de error con línea
void logMessage(string archivo, string error, int linea) {
    ofstream archivoescritura(archivo, ios::app);
    if (!archivoescritura) {
        cerr << "ERROR AL ABRIR EL LOG\n";
        return;
    }
    archivoescritura << error << " en la linea: " << linea << '\n';
    cout << "Error emitido.\n";
    archivoescritura.close();
}

// Sobrecarga para log de acceso
void logMessage(string archivo, string mensaje, string usuario) {
    ofstream archivoescritura(archivo, ios::app);
    if (!archivoescritura) {
        cerr << "ERROR AL ABRIR EL LOG\n";
        return;
    }
    archivoescritura << "[SECURITY] " << mensaje << " para el usuario: " << usuario << '\n';
    cout << "Mensaje de acceso emitido.\n";
    archivoescritura.close();
}

// Sobrecarga para log de mensaje simple
void logMessage(string archivo, string mensaje) {
    ofstream archivoescritura(archivo, ios::app);
    if (!archivoescritura) {
        cerr << "ERROR AL ABRIR EL LOG\n";
        return;
    }
    archivoescritura << mensaje << '\n';
    cout << "Mensaje registrado en el log.\n";
    archivoescritura.close();
}

void handleError(string archivo, string error) {
    ofstream archivoescritura(archivo, ios::app);
    if (!archivoescritura) {
        cerr << "ERROR AL ABRIR EL LOG\n";
        return;
    }
    archivoescritura << "[ERROR] " << error << '\n';
    cout << "Error registrado en el log.\n";
    archivoescritura.close();
}
