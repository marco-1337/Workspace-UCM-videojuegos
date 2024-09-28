// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// función que resuelve el problema
// función que resuelve el problema
void comparaListados(vector<string> const& eda, vector<string> const& tpv,
                     vector<string>& comunes, vector<string>& soloEda, vector<string>& soloTpv){
    
    int indexEda = 0, indexTpv = 0;

    while ( indexEda < eda.size() && indexTpv < tpv.size() ) 
    {
        if ( eda[indexEda] == tpv[indexTpv]) 
        {
            comunes.push_back(eda[indexEda]);     
            indexEda++;
            indexTpv++;
        }
        else if (eda[indexEda] < tpv[indexTpv])
        {
            soloEda.push_back(eda[indexEda]);
            indexEda++;
        }
        else
        {
            soloTpv.push_back(tpv[indexTpv]);
            indexTpv++;
        }
    }

    if (indexEda < eda.size()) {
        soloEda.insert(soloEda.end(), eda.begin() + indexEda, eda.end());
    }
    else if (indexTpv < tpv.size()) {
        soloTpv.insert(soloTpv.end(), tpv.begin() + indexTpv, tpv.end());
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