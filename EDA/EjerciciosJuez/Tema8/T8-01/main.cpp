
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <unordered_map>
#include <algorithm>

using namespace std;

class carnet_puntos
{
private:
    unordered_map<string, int> conductoresPuntos;
    int puntosTotales[16] = {0};
public:

    void nuevo(string dni)
    {
        auto res = conductoresPuntos.insert({dni, 15});
        if (!res.second)
            throw domain_error("Conductor duplicado");
        ++puntosTotales[15];
    }

    void quitar(string dni, int puntos)
    {
        auto it = conductoresPuntos.find(dni);

        if (it == conductoresPuntos.end())
            throw domain_error("Conductor inexistente");

        --puntosTotales[it->second];
        it->second = clamp(it->second - puntos, 0, 15);
        ++puntosTotales[it->second];
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

        return puntosTotales[puntos];
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
            } else if (orden == "consultar") {
                cin >> dni;
                punt = dgt.consultar(dni);
                cout << "Puntos de " << dni << ": " << punt << '\n';
            } else if (orden == "cuantos_con_puntos") {
                cin >> punt;
                int cuantos = dgt.cuantos_con_puntos(punt);
                cout << "Con " << punt << " puntos hay " << cuantos << '\n';
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
