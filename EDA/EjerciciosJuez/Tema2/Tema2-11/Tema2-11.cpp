
/*
Nombre completo: Marco González Campo
DNI: 47554443B
Usuario del juez: EDA-GDV30
Puesto de laboratorio: Hecho en portatil
Qué has conseguido hacer y qué no: En clase he conseguido hacer todo excepto que funcione 
    en los casos que no está en primero o el último.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema

// Siendo que hay 1 subproblema (a = 1), los datos se dividen en 2 (b = 2) y no hay trabajo adicional (k = 0)
// Podemos determinar que el algoritmo pertenece a O(log n) siendo n la cantidad de caracteres en el vector "sec"
char resolver(const vector<char>& sec, int prim, int ini, int fin) {
    int n = (fin - ini);

    int mitad = (fin + ini)/2;
    char esperado = prim + (mitad - ini);
    if (n == 1) {
        if (sec[mitad] != esperado) {
            return (esperado); 
        }
        else {
            return (esperado + 1);
        }
    }

    if ( sec[mitad] != esperado)
    {
        return resolver(sec, prim, ini, mitad);
    }
    else 
    {
        return resolver(sec, esperado, mitad, fin);
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    char prim, ult, n;
    cin >> prim >> ult;
    n = ult-prim;
    vector<char> sec(n);
    for (char& e : sec) cin >> e;
    cout << resolver(sec, prim, 0, sec.size()) << endl;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input2.txt");
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