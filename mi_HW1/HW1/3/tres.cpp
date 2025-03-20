#include <iostream>
#include <memory>

using namespace std;

struct Node {
    int value;
    shared_ptr<Node> next;
    weak_ptr<Node> prev; // Uso un weak asi evito ciclos.
};

struct List {
    shared_ptr<Node> head;
    shared_ptr<Node> tail;
};

shared_ptr<Node> createNode(int v) {
    auto newNode = make_shared<Node>();
    newNode->value = v;
    newNode->next = nullptr;
    newNode->prev.reset();
    return newNode;
}

List createList() {
    return List{nullptr, nullptr};
}

void push_front(List& lista, int v) {
    auto nuevoNodo = createNode(v);
    nuevoNodo->next = lista.head;

    if (lista.head) {
        lista.head->prev = nuevoNodo;
    } else {
        lista.tail = nuevoNodo;
    }

    lista.head = nuevoNodo;
}

void push_back(List& lista, int v) {
    auto nuevoNodo = createNode(v);
    nuevoNodo->prev = lista.tail;

    if (lista.tail) {
        lista.tail->next = nuevoNodo;
    } else {
        lista.head = nuevoNodo;
    }

    lista.tail = nuevoNodo;
}

void insert_at(List& lista, int v, int i) {
    if (!lista.head || i == 0) {
        push_front(lista, v);
        return;
    }

    auto nuevoNodo = createNode(v);
    auto temp = lista.head;
    int index = 0;

    while (temp->next && index < i - 1) {
        temp = temp->next;
        index++;
    }

    if (!temp->next) {
        cout << "Posición mayor que el tamaño de la lista, insertando al final.\n";
        push_back(lista, v);
        return;
    }

    nuevoNodo->next = temp->next;
    nuevoNodo->prev = temp;
    temp->next->prev = nuevoNodo;
    temp->next = nuevoNodo;
}

void erase(List& lista, int pos) {
    if (!lista.head) return;

    if (pos == 0) {
        lista.head = lista.head->next;
        if (lista.head) {
            lista.head->prev.reset();
        } else {
            lista.tail.reset();
        }
        return;
    }

    auto temp = lista.head;
    int index = 0;

    while (temp->next && index < pos) {
        temp = temp->next;
        index++;
    }

    if (!temp->next) {
        cout << "Posición mayor que el tamaño de la lista, eliminando el último nodo.\n";
        lista.tail = temp->prev.lock();
        if (lista.tail) {
            lista.tail->next.reset();
        } else {
            lista.head.reset();
        }
        return;
    }

    auto prevNode = temp->prev.lock();
    auto nextNode = temp->next;

    if (prevNode) {
        prevNode->next = nextNode;
    } else {
        lista.head = nextNode;
    }

    if (nextNode) {
        nextNode->prev = prevNode;
    } else {
        lista.tail = prevNode;
    }
}

void print(const List& lista) {
    auto temp = lista.head;
    while (temp) {
        cout << temp->value << " <-> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

int main() {
    int op;
    auto nuevaLista = createList();

    while (true) {
        cout << "¿Qué desea hacer?\n"
             << "1) Insertar un nodo al principio\n"
             << "2) Insertar un nodo al final\n"
             << "3) Insertar un nodo en una posición\n"
             << "4) Borrar un nodo en una posición\n"
             << "5) Imprimir la lista\n"
             << "6) Salir\n"
             << "Opción: ";
        cin >> op;

        if (op == 1) {
            int valor;
            cout << "Ingrese el valor: ";
            cin >> valor;
            push_front(nuevaLista, valor);
        } else if (op == 2) {
            int valor;
            cout << "Ingrese el valor: ";
            cin >> valor;
            push_back(nuevaLista, valor);
        } else if (op == 3) {
            int valor, indice;
            cout << "Ingrese el valor: ";
            cin >> valor;
            cout << "Ingrese la posición: ";
            cin >> indice;
            insert_at(nuevaLista, valor, indice);
        } else if (op == 4) {
            int indice;
            cout << "Ingrese la posición a borrar: ";
            cin >> indice;
            erase(nuevaLista, indice);
        } else if (op == 5) {
            print(nuevaLista);
        } else if (op == 6) {
            break;
        } else {
            cout << "Opción no válida.\n";
        }
    }

    return 0;
}

// Los incizos se ven aclarados en las opciones del main.