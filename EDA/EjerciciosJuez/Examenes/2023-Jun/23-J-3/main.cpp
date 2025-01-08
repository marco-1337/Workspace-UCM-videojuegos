/*
Nombre completo:
DNI:
Usuario del juez:
Puesto de laboratorio:
Qué has conseguido hacer y qué no: 
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

#include <unordered_map>
#include <map>
#include <queue>

using namespace std;


class Fecha {
    int _dia, _mes, _anio;

public:
    Fecha(int d = 0, int m = 0, int a = 0) : _dia(d), _mes(m), _anio(a) {}
    int dia() const { return _dia; }
    int mes() const { return _mes; }
    int anio() const { return _anio; }
    bool operator<(Fecha const& other) const {
        return _anio < other._anio ||
               (_anio == other._anio && _mes < other._mes) ||
               (_anio == other._anio && _mes == other._mes && _dia < other._dia);
    }
};

inline std::istream& operator>>(std::istream & entrada, Fecha & h) {
    int d,m,a; char c;
    std::cin >> d >> c >> m >> c >> a;
    h = Fecha(d, m, a);
    return entrada;
}

inline std::ostream& operator<<(std::ostream & salida, Fecha const& f) {
    salida << std::setfill('0') << std::setw(2) << f.dia() << '/';
    salida << std::setfill('0') << std::setw(2) << f.mes() << '/';
    salida << std::setfill('0') << std::setw(2) << f.anio();
    return salida;
}

using Codigo = string;
using Cliente = string;

struct ProductoDatos
{
    int existencias = 0;
    map<Fecha, int> adquisiciones;
};

class Tienda {
private:
    unordered_map<Codigo, ProductoDatos> almacen;
    unordered_map<Codigo, queue<Cliente>> listaEspera;
public:
    vector<Cliente> adquirir(Codigo const& cod, Fecha const& f, int cant) {
        
        auto it = listaEspera.find(cod);

        vector<Cliente> salida;

        if (it != listaEspera.end())
        {
            salida = vector<Cliente>(it->second.size());

            int n = it->second.size();
            int i = 0;
            while(!it->second.empty() && cant > 0)
            {
                salida[i] = it->second.front();
                it->second.pop();
                --cant;
                ++i;
            }
        }

        if (cant > 0)
        {
            auto it = almacen.find(cod);
            if (it == almacen.end())
            {
                map<Fecha, int> insertMap;
                insertMap[f] = cant;
                almacen[cod] = {cant, insertMap};
            }
            else
            {
                it->second.existencias += cant;
                it->second.adquisiciones[f] = cant;
            }
        }

        return salida;
    }

    pair<bool,Fecha> vender(Codigo const& cod, Cliente const& cli) {

        auto it = almacen.find(cod);

        if (it == almacen.end() || it->second.adquisiciones.empty())
        {
            listaEspera[cod].push(cli);
            return {false, Fecha()};
        }
        else
        {
            --it->second.adquisiciones.begin()->second;
            --it->second.existencias;
            Fecha f = it->second.adquisiciones.begin()->first;
            if (it->second.adquisiciones.begin()->second == 0)
                it->second.adquisiciones.erase(it->second.adquisiciones.begin());
            return {true, f};
        }
    }

    int cuantos(Codigo const& cod) const {
        auto it = almacen.find(cod);

        if (it == almacen.end())
            return 0;

        return it->second.existencias;
    }

    bool hay_esperando(Codigo const& cod) const {

        auto it = listaEspera.find(cod);

        if (it == listaEspera.end())
            return false;

        return !it->second.empty();
    }
};

bool resuelveCaso() {
    std::string operacion, cod, cli;
    Fecha f;
    int cant;
    std::cin >> operacion;
    if (!std::cin)
        return false;

    Tienda tienda;

    while (operacion != "FIN") {
        if (operacion == "adquirir") {
            cin >> cod >> f >> cant;
            vector<Cliente> clientes = tienda.adquirir(cod, f, cant);
            cout << "PRODUCTO ADQUIRIDO";
            for (auto c : clientes)
                cout << ' ' << c;
            cout << '\n';
        } else if (operacion == "vender") {
            cin >> cod >> cli;
            pair<bool,Fecha> venta = tienda.vender(cod, cli);
            if (venta.first) {
                cout << "VENDIDO " << venta.second << '\n';
            } else
                cout << "EN ESPERA\n";
        } else if (operacion == "cuantos") {
            cin >> cod;
            cout << tienda.cuantos(cod) << '\n';
        } else if (operacion == "hay_esperando") {
            cin >> cod;
            if (tienda.hay_esperando(cod))
                cout << "SI\n";
            else
                cout << "NO\n";
        }

        std::cin >> operacion;
    }
    std::cout << "---\n";
    return true;
}


//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input3.txt");
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