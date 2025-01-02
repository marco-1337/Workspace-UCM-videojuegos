// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

const int NUM_MONEDAS = 8;
const int valores[NUM_MONEDAS] = {1,2,5,10,20,50,100,200};

// El mismo fichero ha sido entregado tanto en el 3.14 como en el 3.15

// función que resuelve el problema
/*
    Tupla solución: 
    
    (X_0, X_1, ..., X_7) siendo X_k la cantidad de monedas del elemento k-ésimo

    Poda:

    Se considera la estimación optimista como el total de monedas restantes + las monedas recolectadas
    en ese nivel. Si la estimación optimista no super la mejor solución se descarta.

    También se descarta profundizar sobre monedas que sumando solo una daría un caso incorrecto,
    es decir, cuando sumar una del siguiente nivel se pase del precio
*/
void resolver(vector<int>& soluc, int n, int k, int monedas[NUM_MONEDAS],
    int precio, int recolectado, int valor, int& mejorValor, vector<int>& mejorSoluc,
    int aproxOptimista)
{

    if (k < NUM_MONEDAS )
    {
        for(int i = monedas[k]; i >= 0; --i)
        {
            soluc[k] = i;
            valor += i;
            recolectado += i * valores[k];

            if (recolectado <= precio) // esValida
            {
                if (recolectado == precio) // esSolucion
                {
                    if (valor > mejorValor) // esMejor
                    {
                        mejorValor = valor;
                        mejorSoluc = soluc;
                    }
                }
                // pseudopoda, previene considerar casos en los que solo usar una moneda de las siguientes supera el precio
                else if (k < n-1 && valor + valores[k+1] <= precio)
                {
                    aproxOptimista -= (monedas[k] - i); // calculo de la poda (se calcula con la diferencia restante y se propaga)
                    if (mejorValor < aproxOptimista)
                    {
                        resolver(soluc, n, k+1, monedas, precio, recolectado, valor, mejorValor, mejorSoluc, aproxOptimista);
                    }
                    aproxOptimista += (monedas[k] - i);
                }
            }

            valor -= i;
            recolectado -= i * valores[k];
        }
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int precio;
    int monedas[NUM_MONEDAS];
    cin >> precio;

    int aproxOptimista = 0;

    for (int i = 0; i < NUM_MONEDAS; ++i)
    {   
        cin >> monedas[i];
        aproxOptimista += monedas[i];
    }
    vector<int> soluc(NUM_MONEDAS);
    vector<int> mejorSoluc(NUM_MONEDAS);

    int mejorValor = -1;

    resolver(soluc, NUM_MONEDAS, 0, monedas, precio, 0, 0, mejorValor, mejorSoluc, aproxOptimista);
    
    // Mostrar salida
    if (mejorValor == -1) 
    {
        cout << "IMPOSIBLE\n";
    }
    else cout << mejorValor << "\n";
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input1.txt");
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