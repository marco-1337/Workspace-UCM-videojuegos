// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include "list_eda.h"

using namespace std;

template <class T>
class list_plus: public list<T>
{
private:
    using Nodo = typename deque<T>::Nodo;
public:
    void desplazaSegmento(int pos, int lon, int k)
    {
        if (pos + lon > this->nelems)
            lon = this->nelems - pos;

        if (lon != 0 && k != 0 && pos - k >= 0 && pos < this->nelems)
        {
            Nodo* nod = this->fantasma->sig;

            for (int i = 0; i < pos - k; ++i)
            {
                nod = nod->sig;
            }

            Nodo* inicioSustitucion = nod;

            for (int i = 0; i < k; ++i)
            {
                nod = nod->sig;
            }

            Nodo* inicioSegmento = nod;

            Nodo* finalSustitucion = inicioSegmento->ant;

            for (int i = 0; i < lon-1; ++i)
            {
                nod = nod->sig;
            }

            Nodo* finalSegmento = nod;


            finalSegmento->sig->ant = finalSustitucion;
            finalSustitucion->sig = finalSegmento->sig;

            inicioSustitucion->ant->sig = inicioSegmento;
            inicioSegmento->ant = inicioSustitucion->ant;

            finalSegmento->sig = inicioSustitucion;
            inicioSustitucion->ant = finalSegmento;
        }
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    list_plus<char> lista;

    int n, pos, lon, k;

    cin >> n >> pos >> lon >> k;

    char e;
    for (int i = 0; i < n; ++i)
    {
        cin >> e;
        lista.push_back(e);
    }
    
    lista.desplazaSegmento(pos, lon, k);
    // escribir sol
    for (char c : lista)
    {
        cout << c << " ";
    }

    cout << "\n";
    
}

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
     system("PAUSE");
     #endif
    
    return 0;
}