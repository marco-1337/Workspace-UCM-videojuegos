// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include "queue_eda.h"

using namespace std;

template <class T>
class queue_plus : public queue<T>
{
private:
    using Nodo = typename queue<T>::Nodo;
public:
    // Temporal: O(n) siendo n el numero de elementos en la cola
    // Espacial: O(1)
    void cuela(const T& a, const T& b)
    {
        Nodo* nod = this->prim;

        Nodo* nA = nullptr;
        Nodo* nPreB = nullptr;

        while (nod != nullptr && nA == nullptr )
        {
            if (nod->elem == a)
                nA = nod;
            else
                nod = nod->sig;
        }

        if (nA != nullptr)
        {
            while (nod != this->ult && nPreB == nullptr )
            {
                if (nod->sig->elem == b)
                    nPreB = nod;
                nod = nod->sig;
            }

            if (nPreB != nullptr && nA != nPreB)
            {
                Nodo* sigA = nA->sig;
                Nodo* sigB = nPreB->sig->sig;
                nA->sig = nPreB->sig;
                nA->sig->sig = sigA;
                nPreB->sig = sigB;

                if (sigB == nullptr)
                {
                    this->ult = nPreB;
                }
            }
        }
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    queue_plus<int> cola;
    int n;

    cin >> n;

    if (! std::cin)
        return false;
    
    while (n != -1)
    {
        cola.push(n);
        cin >> n;
    }

    int a, b;
    cin >> a >> b;

    cola.cuela(a, b);
    
    // escribir sol
    
    while (!cola.empty())
    {
        cout << cola.front() << " ";
        cola.pop();
    }
    cout << "\n";
    
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    while (resuelveCaso());

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}