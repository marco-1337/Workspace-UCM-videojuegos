// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30

#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"
using namespace std;


template <class T>
class queue_plus : public queue<T> {
    using Nodo = typename queue<T>::Nodo;

public:

    // O(n) siendo n la longitud de datos
    void cuela(const T& n, queue_plus<T>& datos){

        if(datos.size() > 0) 
        {
            Nodo* consulta = this->prim;
            bool encontrado = false;

            while (!encontrado && consulta != nullptr)
            {
                if (consulta->elem == n)
                    encontrado = true;
                else
                    consulta = consulta->sig;
            }

            if (encontrado)
            {
                datos.ult->sig = consulta->sig;
                consulta->sig = datos.prim;

                this->nelems += datos.nelems;
        
                datos.prim = nullptr;
                datos.ult = nullptr;
                datos.nelems = 0;
            }
        }
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, a;

    queue_plus<int> q;
    cin >> n;
    while (n != -1){
        q.push(n);
        cin >> n;
    }

    cin >> a;

    queue_plus<int> p;
    cin >> n;
    while (n != -1){
        p.push(n);
        cin >> n;
    }

    // escribir cola original (pero antes dar una vuelta para comprobar que la cola está bien formada)
    for (int i = 0; i < q.size(); ++i){
        n = q.front();
        cout << n << " ";
        q.pop();
        q.push(n);
    }

    cout << "\n";

    // llamada a metodo
    q.cuela(a,p);

    // Ahora imprimimos la cola y de paso la dejamos vacía
    while (!q.empty()){
        cout << q.front() << " ";
        q.pop();
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
