// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
//#include "stack_eda.h"
#include "LinkedListStack.h"
using namespace std;


// función externa que resuelve el problema sobre stack
// O(2n) siendo n el numero de elementos en s
void duplicar(stack<int>& s){
    stack<int> auxStack;

    while(!s.empty())
    {
        auxStack.push(s.top());
        s.pop();
    }

    while (!auxStack.empty())
    {
        s.push(auxStack.top());
        s.push(auxStack.top());
        auxStack.pop();
    }
}

// Clase extendida con operación interna duplicar que reaprovecha nodos existentes
template <class T>
class LinkedListStack_plus : public LinkedListStack<T> {
    using Nodo = typename LinkedListStack<T>::Nodo;

public:
    // O(n/2) siendo n el numero de elementos
    void duplicar() {
        if (this->nelems > 0)
        {
            Nodo* currentNodo = this->cima;

            while (currentNodo != nullptr)
            {
                Nodo* nodoDuplicado = new Nodo((*currentNodo).elem, (*currentNodo).sig);
                (*currentNodo).sig = nodoDuplicado;
                currentNodo = (*nodoDuplicado).sig;
            }
        }
    }
};



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int e;
    //stack<int> s;
    LinkedListStack_plus<int> s;
    cin >> e;
    if (!cin) return false;
    while (e != 0){
        s.push(e);
        cin >> e;
    }
    //duplicar(s);
    s.duplicar();

    // Ahora imprimimos la pila de cima a base y de paso la dejamos vacía
    while (!s.empty()){
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso())
        ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}