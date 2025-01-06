
#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <algorithm>

#include<unordered_map>

using namespace std;

struct ResultadosConcursante
{
    string nombre;
    int aciertos;
    int tiempo;

    bool operator<(const ResultadosConcursante& other)
    {
        if (aciertos == other.aciertos)
        {
            if (tiempo == other.tiempo)
            {
                return nombre < other.nombre;
            }

            return tiempo < other.tiempo;
        }

        return aciertos > other.aciertos;
    }
};

using ResultadoEjercicio = pair<int, bool>;
using Ejercicios = unordered_map<string, ResultadoEjercicio>;
using DatosConcursantes = unordered_map<string,Ejercicios>;

void procesaEnvios(vector<ResultadosConcursante>& resultados){
    string equipo, problema, veredicto;
    int minuto;

    DatosConcursantes datosConcursantes;

    cin >> equipo;

    while (equipo != "FIN") {

        auto equipoTup = datosConcursantes.insert({equipo, Ejercicios()});

        auto teamIt = equipoTup.first;
        Ejercicios* problemData = &teamIt->second;

        cin >> problema >> minuto >> veredicto;

        bool v = (veredicto == "AC") ? true : false;

        auto problemaTup = problemData->insert({problema, {1, v}});
        
        auto problemaIt = problemaTup.first;
        bool problemaExistia = !(problemaTup.second);

        if (problemaExistia)
        {
            if (!problemaIt->second.second)
            {
                if (veredicto == "AC")
                {
                    problemaIt->second.first = problemaIt->second.first*20 + minuto;
                    problemaIt->second.second = true;
                }
                else 
                {
                    ++problemaIt->second.first;
                }
            }
        }
        else if (v)
        {
            problemaIt->second.first = minuto;
        }
        
        cin >> equipo;
    }


    resultados.resize(datosConcursantes.size());
    auto it = datosConcursantes.begin();
    for (int i = 0; i < datosConcursantes.size(); ++i)
    {
        resultados[i] = {it->first, 0, 0};
        for (auto [ex, res] : it->second)
        {
            if (res.second)
            {
                ++resultados[i].aciertos;
                resultados[i].tiempo += res.first;
            }
        }
        ++it;
    }

    sort(resultados.begin(), resultados.end());
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    vector<ResultadosConcursante> resultados;
    procesaEnvios(resultados);

    // Se imprime la salida
    
    for (ResultadosConcursante& e : resultados)
    {
        cout << e.nombre << " " << e.aciertos << " " << e.tiempo << "\n";
    }

    cout << "---\n";
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input.txt");
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