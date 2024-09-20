// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

bool medirDalton(const vector<int>& alturas)
{
    // Comprobar si estan de chiko a grande
    bool menosAMas = true;

    int i = 0;
    while(menosAMas && i < alturas.size()-1)
    {
        if (alturas[i]+1 != alturas[i+1])
            menosAMas = false;

        i++;
    }
    
    // Comprobar si estan de grande a chiko
    bool masAMenos;
    
    if (!menosAMas)
    {
        masAMenos = true;

        int i = 0;
        while(masAMenos && i < alturas.size()-1)
        {
            if (alturas[i]-1 != alturas[i+1])
                masAMenos = false;

            i++;
        } 
    }

    return menosAMas || masAMenos;
}

// función que resuelve el problema
string resolver(const vector<int>& datos) {
    if(datos.size() < 2 || datos.size() > 100000)
        return "DESCONOCIDOS";

    if (medirDalton(datos))
    {
        return "DALTON";
    }
    else
    {
        return "DESCONOCIDOS";
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int cantidad;
    cin >> cantidad;

    if (cantidad == 0)
        return false;
    
    vector<int> personajes(cantidad);

    for(int i = 0; i < cantidad; i++)
    {
        cin >> personajes[i];
    }

    string sol = resolver(personajes);
    
    // escribir sol
    cout << sol << "\n";

    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    while (resuelveCaso());

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}
