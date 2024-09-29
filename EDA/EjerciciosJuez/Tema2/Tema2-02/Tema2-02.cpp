// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// digitosIzquierda son el numero de digitos a la izquierda del ultimo dígito
// El coste sería O(n) siendo n digitosIzquierda + 1
int complementarios(int datos, int digitosIzquierda) {
    if (digitosIzquierda == 0) 
    {
        return 9 - datos;
    }
    else
    {
        return complementarios(datos/10, digitosIzquierda - 1) * 10 + (9 - (datos % 10));
    }
}

// multiplicadorDigito siempre es una potencia de 10
// equivale a 10^(k-1) siendo k el número de dígitos de datos 
// El coste sería O(k)
int complementariosInverso(int datos, int multiplicadorDigito)
{
    if (multiplicadorDigito == 1)
    {
        return 9 - datos;
    }
    else
    {
        return complementariosInverso(datos / 10, multiplicadorDigito / 10) 
            + (9 - (datos % 10)) * multiplicadorDigito;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int datos;
    cin >> datos;
    
    int aux = datos;
    int n = 0;
    int nInv = 1;
    while (aux > 9)
    {
        n++;
        nInv *= 10;
        aux /= 10;
    }

    int sol = complementarios(datos, n);
    int solInverso = complementariosInverso(datos, nInv);
    // escribir sol
    cout << sol << " " << solInverso << "\n";
    
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