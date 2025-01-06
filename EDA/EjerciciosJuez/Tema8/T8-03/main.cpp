#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>

#include <unordered_map>
#include <map>

using namespace std;

using Estado = string;
using Partido = string;

struct DatosEstado
{
    int comp;
    string masVotadoNom;
    int maxVotos;
    unordered_map<Partido, int> votosTotales;
};

class ConteoVotos {

private:
    unordered_map<Estado, DatosEstado> mapEstados;

public:

    void nuevo_estado(const Estado &nombre, int num_compromisarios) 
    {
        auto estadoInsert = mapEstados.insert({nombre, {num_compromisarios, "", 0, unordered_map<Partido, int>()}});

        if (!estadoInsert.second)
            throw domain_error("Estado ya existente");
    }  
    
    void sumar_votos(const Estado &estado, const Partido &partido, int num_votos) 
    {
        auto it = mapEstados.find(estado);

        if (it == mapEstados.end())
            throw domain_error("Estado no encontrado");

        auto insercionVotos = it->second.votosTotales.insert({partido, num_votos});

        if (!insercionVotos.second)
            insercionVotos.first->second += num_votos;
        
        if(insercionVotos.first->second > it->second.maxVotos)
        {
            it->second.maxVotos = insercionVotos.first->second;
            it->second.masVotadoNom = insercionVotos.first->first;
        }
    }

    Partido ganador_en(const Estado &estado) const 
    {
        auto it = mapEstados.find(estado);

        if (it == mapEstados.end())
            throw domain_error("Estado no encontrado");

        return it->second.masVotadoNom;
    }

    vector<pair<Partido,int>> resultados() const 
    {
        map<Partido, int> partidosRelevantes;

        for (auto e : mapEstados)
        {
            auto [it, b] = partidosRelevantes.insert({e.second.masVotadoNom, e.second.comp});
            if (!b)
            {
                it->second += e.second.comp;
            }
        }

        vector<pair<Partido,int>> salida(partidosRelevantes.size());

        auto it = partidosRelevantes.begin();
        for (int i = 0; i < salida.size(); ++i)
        {
            salida[i] = *it;
            ++it;
        }

        return salida;
    }

}; 

bool resuelveCaso() {
    string comando;
    cin >> comando;
    if (!cin) return false;

    ConteoVotos elecciones;

    while (comando != "FIN") {
        try {
            if (comando == "nuevo_estado") {
                Estado estado;
                int num_compromisarios;
                cin >> estado >> num_compromisarios;
                elecciones.nuevo_estado(estado, num_compromisarios);
            } else if (comando == "sumar_votos") {
                Estado estado;
                Partido partido;
                int num_votos;
                cin >> estado >> partido >> num_votos;
                elecciones.sumar_votos(estado, partido, num_votos);
            } else if (comando == "ganador_en") {
                Estado estado;
                cin >> estado;
                Partido ganador  = elecciones.ganador_en(estado);
                cout << "Ganador en " << estado << ": " << ganador << "\n";
            } else if (comando == "resultados") {
                for (const auto &par : elecciones.resultados()) {
                    cout << par.first << " " << par.second << "\n";
                }
            }
        } catch (std::exception &e) {
            cout << e.what() << "\n";
        }
        cin >> comando;
    }

    cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); 
#endif

    while(resuelveCaso()) { }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
