// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>

using namespace std;

using TablaRefs = map<string, list<int>>;

// O(n) en tiempo y espacio siendo n el numero de letras en el texto. Lineal porque se recorren todas las letras 1 vez
// para hacerlas minúsculas. Se agrega el coste de la funcion hash de string por palabra (caso peor O(n + n/4).
void referencias(int numLineas, TablaRefs& refs){
    string palabra;
    char c;
    for (int numLinea = 1; numLinea <= numLineas; numLinea++) {
        cin.get(c);
        while (c != '\n'){
            cin.unget(); // Se vuelve a dejar c en cin (por si era la 1ª letra de la linea)

            cin >> palabra;

            std::transform(palabra.begin(), palabra.end(), palabra.begin(), 
                [](unsigned char c) {return std::tolower(c);}
            );

            if(palabra.size() > 2 && palabra.size() < 11)
            {
                auto it = refs.find(palabra);

                if (it != refs.end())
                {
                    if (it->second.empty() || it->second.back() != numLinea) 
                        refs[palabra].push_back(numLinea);
                }
                else refs[palabra].push_back(numLinea);
            }

            cin.get(c);
        }
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    char c;
    cin >> n;
    cin.get(c); // Me salto el \n de detrás del N
    if (n == 0)
        return false;

    TablaRefs refs;
    referencias(n,refs);

    // escribir sol
    for(auto& elem : refs)
    {
        cout << elem.first;
        for (const int& num : elem.second)
            cout << " " << num;
        cout << "\n";
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