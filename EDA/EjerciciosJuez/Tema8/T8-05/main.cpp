
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <unordered_map>
#include <algorithm>

#include <list>

using namespace std;

struct GrupoPuntos
{
    int maxAntiguedad = 0;
    unordered_map<string, int> registroAntiguedades;
};

class carnet_puntos
{
private:
    unordered_map<string, int> conductoresPuntos;
    vector<GrupoPuntos> porPuntos;

public:

    carnet_puntos(){
        porPuntos = vector<GrupoPuntos>(16);
    }

    void nuevo(string dni)
    {
        auto [it, b] = conductoresPuntos.insert({dni, 15});


        if (!b)
            throw domain_error("Conductor duplicado");
        
        porPuntos[15].registroAntiguedades[dni] = ++porPuntos[15].maxAntiguedad;
    }

    void quitar(string dni, int puntos)
    {
        auto it = conductoresPuntos.find(dni);

        if (it == conductoresPuntos.end())
            throw domain_error("Conductor inexistente");

        int prev = it->second;
        it->second = clamp(it->second - puntos, 0, 15);
        int current = it->second;
        
        if (prev != current)
        {
            porPuntos[prev].registroAntiguedades.erase(dni);
            porPuntos[current].registroAntiguedades[dni] = ++porPuntos[current].maxAntiguedad;
        }
    }

    void recuperar(string dni, int puntos)
    {
        auto it = conductoresPuntos.find(dni);

        if (it == conductoresPuntos.end())
            throw domain_error("Conductor inexistente");

        int prev = it->second;
        it->second = clamp(it->second + puntos, 0, 15);
        int current = it->second;
        
        if (prev != current)
        {
            porPuntos[prev].registroAntiguedades.erase(dni);
            porPuntos[current].registroAntiguedades[dni] = ++porPuntos[current].maxAntiguedad;
        }
    }

    int consultar(string dni)
    {
        auto it = conductoresPuntos.find(dni);

        if (it == conductoresPuntos.end())
            throw domain_error("Conductor inexistente");

        return it->second;
    }

    int cuantos_con_puntos(int puntos)
    {
        if (puntos < 0 || puntos > 15)
            throw domain_error("Puntos no validos");

        return porPuntos[puntos].registroAntiguedades.size();
    }

    list<string> lista_por_puntos(int puntos)
    {
        if (puntos < 0 || puntos > 15)
            throw domain_error("Puntos no validos");

        vector<pair<int,string>> outUnordered(porPuntos[puntos].registroAntiguedades.size());

        int i = 0;
        for (auto& e : porPuntos[puntos].registroAntiguedades)
        {
            outUnordered[i] = {e.second, e.first};
            ++i;
        }

        sort(outUnordered.begin(), outUnordered.end());

        list<string> out;
        for (auto& e : outUnordered)
        {
            out.push_front(e.second);
        }
        
        return out;
    }
};

bool resuelveCaso() {
    std::string orden, dni;
    int punt;
    std::cin >> orden;
    if (!std::cin)
        return false;
    
    carnet_puntos dgt;
    
    while (orden != "FIN") {
        try {
            if (orden == "nuevo") {
                cin >> dni;
                dgt.nuevo(dni);
            } else if (orden == "quitar") {
                cin >> dni >> punt;
                dgt.quitar(dni, punt);
            } else if (orden == "recuperar") {
                cin >> dni >> punt;
                dgt.recuperar(dni, punt);
            } else if (orden == "consultar") {
                cin >> dni;
                punt = dgt.consultar(dni);
                cout << "Puntos de " << dni << ": " << punt << '\n';
            } else if (orden == "cuantos_con_puntos") {
                cin >> punt;
                int cuantos = dgt.cuantos_con_puntos(punt);
                cout << "Con " << punt << " puntos hay " << cuantos << '\n';
            } else if (orden == "lista_por_puntos") {
                cin >> punt;
                auto const& lista = dgt.lista_por_puntos(punt);
                cout << "Tienen " << punt << " puntos:";
                for (auto const& dni : lista)
                    cout << ' ' << dni;
                cout << '\n';
            } else
                cout << "OPERACION DESCONOCIDA\n";
        } catch (std::domain_error e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}

int main() {
    
    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());
    
    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("pause");
#endif
    return 0;
}
