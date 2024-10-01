// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// Pertenece a O(log n) siendo n la cantidad de elementos en v
bool existeElemento(const vector<int>& v, int ini, int fin, int busqueda)
{
    int n = fin - ini;
    if(n == 0) return false;
    if(n == 1) return(v[ini] == busqueda);
    
    int medio = (ini + fin) / 2;

    if(v[ini] > v[medio])
    {
        if(busqueda >= v[medio] && busqueda <= v[fin-1]) 
            return existeElemento(v, medio, fin, busqueda);
        else 
            return existeElemento(v, ini, medio, busqueda);
    }    
    else 
    {
        if(busqueda >= v[ini] && busqueda < v[medio])
            return existeElemento(v, ini, medio, busqueda);
        else
            return existeElemento(v, medio, fin, busqueda);
    }
}

// función que resuelve el problema
bool resolver(const vector<int>& datos, int busqueda) {
    return existeElemento(datos, 0, datos.size(), busqueda);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int n, busqueda;
    cin >> n;

    if (n == -1)
        return false;

    cin >> busqueda;

    vector<int> datos(n);

    for (int& e : datos) 
    {
        cin >> e;
    }
    
    // escribir sol
    cout << (resolver(datos, busqueda) ? "SI" : "NO") << "\n";
    
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