#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <cstring>
#include <string_view>

using namespace std;
using namespace std::chrono;

// Función que compara en tiempo de compilación con la clase string_view
constexpr bool sonIguales(string_view f1, string_view f2) {
    return (f1.size() != f2.size()) ? false :
           (f1.empty()) ? true :
           (f1[0] != f2[0]) ? false :
           sonIguales(f1.substr(1), f2.substr(1));
}

// Función que es comparada en tiempo de ejecución con string
bool sonIguales(string f1, string f2) {
    if (f1.size() == 0) {
        return true;
    }
    if (f1[0] != f2[0]) {
        return false;
    }
    return sonIguales(f1.substr(1), f2.substr(1));
}

int main1() {  
    string f1;
    cout << "Ingrese la frase n1 que desea comparar: ";
    getline(cin, f1);
    string f2;
    cout << "Ingrese la frase n2 que desea comparar: ";
    getline(cin, f2);

    auto start = high_resolution_clock::now();  

    if (f1.size() == f2.size()) {
        if (sonIguales(f1, f2)) {
            cout << "Las frases son iguales" << endl;
        } else {
            cout << "Las frases son diferentes" << endl;
        }
    } else {
        cout << "Las frases son diferentes" << endl;
    }
    
    auto end = high_resolution_clock::now();  
    auto duracion = duration_cast<microseconds>(end - start);
    cout << "Tiempo de ejecución (función recursiva con string): " << duracion.count() << " microsegundos " << endl;

    return 0;
}

// Función que compara en tiempo de compilación con char
constexpr bool sonIgualesCompileTime(const char* f1, const char* f2, size_t idx = 0) {
    return (f1[idx] == f2[idx]) && (f1[idx] != '\0' ? sonIgualesCompileTime(f1, f2, idx + 1) : true);
}

// Función que es comparada en tiempo de ejecución con char
bool sonIguales(const char* f1, const char* f2) {
    if (strlen(f1) == 0) {  
        return true;
    }
    if (f1[0] != f2[0]) {  
        return false;
    }
    return sonIguales(f1 + 1, f2 + 1);  
}

int main2() {   
    char f1[64], f2[64];                                

    cout << "Ingrese la primera frase (máximo 63 caracteres): ";
    cin.getline(f1, 64);  

    cout << "Ingrese la segunda frase (máximo 63 caracteres): ";
    cin.getline(f2, 64);  

    auto start = high_resolution_clock::now(); 

    if (strlen(f1) != strlen(f2)) {
        cout << "Las cadenas son diferentes." << endl;
    } else {
        if (sonIguales(f1, f2)) {
            cout << "Las cadenas son iguales." << endl;
        } else {
            cout << "Las cadenas son diferentes." << endl;
        }
    }

    auto end = high_resolution_clock::now();  
    auto duracion = duration_cast<microseconds>(end - start);
    cout << "Tiempo de ejecución (función recursiva con char): " << duracion.count() << " microsegundos " << endl;

    return 0;
}

int main() {

    constexpr const char* f1_compile = "Hola soy sofi bottino y la rompi en la HW1";
    constexpr const char* f2_compile = "Hola soy sofi bottino y la rompi en la HW1";

    constexpr bool resultado_string = sonIguales("Hola soy sofi bottino y la rompi en la HW1"sv, "Hola soy sofi bottino y la rompi en la HW1"sv);
    constexpr bool resultado_char = sonIgualesCompileTime(f1_compile, f2_compile);

    static_assert(resultado_string, "Las frases con string_view deberían ser iguales");
    static_assert(resultado_char, "Las frases con char* deberían ser iguales");

    // Aca ya no mido el "tiempo de compilación" como tal, sino que solo valido las comparaciones
    // que pasan en tiempo de compilación
    cout << "Resultado de la comparación en tiempo de compilación con string_view: " 
         << (resultado_string ? "iguales" : "diferentes") << endl;

    cout << "Resultado de la comparación en tiempo de compilación con char*: " 
         << (resultado_char ? "iguales" : "diferentes") << endl;

    auto start_compile = high_resolution_clock::now();  

    // Solo mido el tiempo de ejecución de las comparaciones
    if (sonIgualesCompileTime(f1_compile, f2_compile)) {
        cout << "Las frases (char*) comparadas en tiempo de ejecución son iguales" << endl;
    } else {
        cout << "Las frases (char*) comparadas en tiempo de ejecución son diferentes" << endl;
    }

    if (sonIguales("Hola"sv, "Hola"sv)) {
        cout << "Las frases (string_view) comparadas en tiempo de ejecución son iguales" << endl;
    } else {
        cout << "Las frases (string_view) comparadas en tiempo de ejecución son diferentes" << endl;
    }

    auto end_compile = high_resolution_clock::now(); 
    auto duracion_compile = duration_cast<microseconds>(end_compile - start_compile);
    cout << "Tiempo de ejecución total: " << duracion_compile.count() << " microsegundos " << endl;

    cout << "Programa con string:\n";
    main1();
    cout << "Programa con char:\n";
    main2();

    return 0;
}


// Justificación del uso de string y char:
// Utilizo strings para simplificar la gestión de memoria y evitar la manipulación manual de buffers,
// ya que string maneja internamente la memoria dinámica. Sin embargo, al comparar las dos versiones,
// podemos ver que la implementación con char podría ser más eficiente en términos de uso de memoria.
// Al realizar la comparación en tiempo de compilación (usando `constexpr`), eliminamos la sobrecarga de tiempo
// de ejecución en el caso de cadenas constantes, ya que la evaluación es procesada por el compilador.
// Por lo tanto, la comparación de cadenas en tiempo de ejecución será más costosa que la comparación en tiempo de compilación.

