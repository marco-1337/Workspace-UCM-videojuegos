// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "Set.h"

using namespace std;

// función que resuelve el problema
// O(n*k) siendo n datos.size() y siendo k el numero de elementos menores a buscar
void resolver(const vector<int>& datos, const int& k, Set<int>& auxSet, int cont) {

    if (cont < datos.size()-1)
    {
        resolver(datos, k, auxSet, cont+1);
    }

    if(auxSet.size() < k)
    {
        auxSet.add(datos[cont]);
    }
    else if(*auxSet.getMax() > datos[cont] && !auxSet.contains(datos[cont]))
    {
        auxSet.removeMax();
        auxSet.add(datos[cont]);
    } 
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int nMenores, num;
    cin >> nMenores;

    if (nMenores == 0)
        return false;

    vector<int> datos;

    cin >> num;
    while(num != -1){
        datos.push_back(num);
        cin >> num;
    }
    
    Set<int> auxSet(nMenores);

    resolver(datos, nMenores, auxSet, 0);
    
    // escribir sol
    cout << auxSet << "\n";

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