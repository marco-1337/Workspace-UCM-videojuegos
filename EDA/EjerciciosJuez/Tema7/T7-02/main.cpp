#include <iostream>
#include <fstream>
#include <string>

#include <unordered_map>
#include <set>

using namespace std;

using Diccionario = unordered_map<string, int>;

void leerDiccionario(Diccionario& diccionario){
    char c;
    string clave;
    int valor;
    cin.get(c);
    while (c != '\n'){
        cin.unget();
        cin >> clave >> valor;
        diccionario[clave] = valor;
        cin.get(c);
    }
}

void resuelveCaso(){
    
    Diccionario antiguo;
    Diccionario nuevo;
    leerDiccionario(antiguo);
    leerDiccionario(nuevo);
    
    set<string> borrados;
    set<string> añadidos;
    set<string> modificados;

    for (auto e : nuevo)
    {
        auto it = antiguo.find(e.first);
        if (it == antiguo.end())
        {
            añadidos.insert(e.first);
        }
        else
        {
            if (it->second != e.second )
                modificados.insert(e.first);

            antiguo.erase(it);
        }
    }

    for (auto e : antiguo)
    {
        borrados.insert(e.first);
    }

    if (añadidos.empty() && borrados.empty() && modificados.empty())
    {
        cout << "Sin cambios\n";
    }
    else
    {
        if (!añadidos.empty())
        {
            cout << "+ ";
            for (string e : añadidos)
            {
                cout << e << " ";
            }
            cout << "\n";
        }
        if (!borrados.empty())
        {
            cout << "- ";
            for (string e : borrados)
            {
                cout << e << " ";
            }
            cout << "\n";
        }
        if (!modificados.empty())
        {
            cout << "* ";
            for (string e : modificados)
            {
                cout << e << " ";
            }
            cout << "\n";
        }
    }
    cout << "---\n";
}


int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos; char c;
    std::cin >> numCasos;
    cin.get(c);
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
