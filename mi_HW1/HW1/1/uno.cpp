#include <iostream> 
#include <vector> 

using namespace std;

vector<vector<int>> get_matriz(int n, vector<vector<int>>& datos); // inicializo mis funciones.
void print(vector<vector<int>>& datos);
void printInd(vector<vector<int>>& datos);

int main() {

    vector<vector<int>> datos; // creo mi matriz vacia.
    int n;
    cout << "Ingrese el tamano de su matriz: "; 
    cin >> n;

    datos = get_matriz(n, datos); // llamo a mi funcion que crea la matriz.

    int op;
    cout << "Como prefiere ver sus datos?:\n1: En matriz\n2: Individualmente por ubicacion\n";
    cin >> op;

    if (op == 1) {
        print(datos);
    } else {
        printInd(datos);
    }

    return 0;
}

vector<vector<int>> get_matriz(int n, vector<vector<int>>& datos) { // creo mi funcion de tipo matriz, que la crea en solo un for, y la devuelve.
    int valor = 1;
    datos.resize(n, vector<int>(n)); 
    for (int k = 0; k < n * n; ++k) {
        int i = k / n; 
        int j = k % n;  
        datos[i][j] = valor++;
    }
    return datos;
}

void print(vector<vector<int>>& datos) { // incizo a), imprimo la matriz en forma de matriz.
    for (const auto& fila : datos) {
        for (int num : fila) {
            cout << num << " ";
        }
        cout << endl;
    }
}

void printInd(vector<vector<int>>& datos) {  
    int filas = datos.size();
    if (filas == 0) return; 

    int columnas = datos[0].size();
    for (int id = 0; id < filas * columnas; ++id) {
        int i = id / columnas; 
        int j = id % columnas;

        cout << "M[" << i + 1 << "][" << j + 1 << "] = " << datos[i][j] << " ";

        if (j == columnas - 1) cout << endl; 
    }
}
