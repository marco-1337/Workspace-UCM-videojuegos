#include <iostream>
#include <fstream>
#include <cctype>

#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

void resolver(string const& primerDeporte, unordered_map<string, int>& deportes){
    string deporte, alumno;
    deporte = primerDeporte;

    unordered_map<string, string> alumnos;

    while (deporte != "_FIN_") {
        
        auto sportsIt = deportes.insert({deporte, 0});

        cin >> alumno;
        while (!isupper(alumno[0]) && alumno != "_FIN_") {
            auto it = alumnos.find(alumno);
            if (it == alumnos.end())
            {
                alumnos[alumno] = deporte;
                ++sportsIt.first->second;
            }
            else
            {
                if (it->second != deporte && it->second != "nAn")
                {
                    --deportes[it->second];
                    it->second = "nAn";
                }
            }

            cin >> alumno;
        }
        deporte = alumno;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    string primerDeporte;
    cin >> primerDeporte;
    if (!cin) return false;

    unordered_map<string, int> deportes;

    resolver(primerDeporte, deportes);

    vector<pair<string, int>> deportesPorPeso(deportes.size());

    int i = 0;
    for (auto& e : deportes)
    {
        deportesPorPeso[i] = e;
        ++i;
    }

    sort(deportesPorPeso.begin(), deportesPorPeso.end(),
        [] (pair<string, int> a, pair<string, int> b)
        {
            if (a.second == b.second)
                return a.first < b.first;
            else
                return a.second > b.second;
        });

    for (auto& e : deportesPorPeso)
    {
        cout << e.first << " " << e.second << "\n"; 
    }

    cout << "---\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso())
        ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}