// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include "list_eda.h"

using namespace std;

// función que resuelve el problema
// O(n) siendo n longitud de datos
void resolver(list<int>& datos) {

    list<int>::iterator it = datos.begin();
    list<int> salida;

    if(it != datos.end()) 
    {
        int numAnterior = *it;
        salida.push_back(numAnterior);

        ++it;

        while (it != datos.end())
        {
            if(*it >= numAnterior)
            {
                numAnterior = *it;
                salida.push_back(numAnterior);

            }
            
            ++it;
        }
    }

    datos = salida;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;

    cin >> n;

    list<int> datos;

    while (n != -1)
    {
        datos.push_back(n);
        cin >> n;
    }
    
    resolver(datos);
    // escribir sol
    
    for (auto i = datos.begin(); i != datos.end(); ++i)
    {
        cout << *i << " ";
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