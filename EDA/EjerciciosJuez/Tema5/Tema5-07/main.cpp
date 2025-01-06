// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30

#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"

using namespace std;

template <class T>
class list_plus : public list<T> {
    using Nodo = typename list<T>::Nodo;

public:

    // O(n) siendo n la longitud de datos
    void elimina(const T& n){

        Nodo* actual = this->fantasma->sig;

        Nodo* next;

        while(actual != this->fantasma)
        {
            next = actual->sig;

            if (actual->elem == n)
            {
                this->borra_elem(actual);
            }

            actual = next;
        }
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, a;

    list_plus<int> l;
    cin >> n;
    while (n != -1){
        l.push_back(n);
        cin >> n;
    }

    cin >> a;

    // imprimir y dar una vuelta para comprobar que la cola está bien formada
    for (int i = 0; i < l.size(); ++i){
        n = l.front();
        cout << n << " "; 
        l.pop_front();
        l.push_back(n);
    }

    cout << "\n";

    l.elimina(a);

    // Ahora imprimimos la cola y de paso la dejamos vacía
    while (!l.empty()){
        cout << l.front() << " ";
        l.pop_front();
    }

    cout << "\n";
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
