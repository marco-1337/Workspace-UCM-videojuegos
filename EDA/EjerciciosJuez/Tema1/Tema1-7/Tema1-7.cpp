// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


// función que resuelve el problema
/*
    Básicamente usa el mismo código que el ejercicio 1-6 lo único que ordena ambas listas
    por lo tanto la complejidad asintótica en el caso peor sería:

    O(n log n + m log m) siendo n y m las dimensiones de las dos listas a comparar respectivamente
*/
void comparaListados(vector<string> const& eda, vector<string> const& tpv,
                     vector<string>& comunes, vector<string>& soloEda, vector<string>& soloTpv){

    vector<string> edaOrdenado = eda;
    vector<string> tpvOrdenado = tpv;

    sort(edaOrdenado.begin(), edaOrdenado.end());
    sort(tpvOrdenado.begin(), tpvOrdenado.end());

    int indexEda = 0, indexTpv = 0;

    while ( indexEda < edaOrdenado.size() && indexTpv < tpvOrdenado.size() ) 
    {
        if ( edaOrdenado[indexEda] == tpv[indexTpv]) 
        {
            comunes.push_back(edaOrdenado[indexEda]);     
            indexEda++;
            indexTpv++;
        }
        else if (edaOrdenado[indexEda] < tpvOrdenado[indexTpv])
        {
            soloEda.push_back(edaOrdenado[indexEda]);
            indexEda++;
        }
        else
        {
            soloTpv.push_back(tpvOrdenado[indexTpv]);
            indexTpv++;
        }
    }

    if (indexEda < edaOrdenado.size()) {
        soloEda.insert(soloEda.end(), edaOrdenado.begin() + indexEda, edaOrdenado.end());
    }
    else if (indexTpv < tpvOrdenado.size()) {
        soloTpv.insert(soloTpv.end(), tpvOrdenado.begin() + indexTpv, tpvOrdenado.end());
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;

    vector<string> comunes;
    vector<string> soloEda;
    vector<string> soloTpv;

    cin >> n;
    vector<string> eda(n);
    for (string& e : eda) cin >> e;

    cin >> n;
    vector<string> tpv(n);
    for (string& e : tpv) cin >> e;

    comparaListados(eda,tpv,comunes,soloEda,soloTpv);
    
    for (string& e : comunes) cout << e << " ";
    cout << endl;
    for (string& e : soloEda) cout << e << " ";
    cout << endl;
    for (string& e : soloTpv) cout << e << " ";
    cout << endl;
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