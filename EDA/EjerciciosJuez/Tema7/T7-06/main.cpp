// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

#include "list"
#include "unordered_map"

using namespace std;

using Pelicula = string;
using Actor = string;

using Reparto = list<pair<string, int>>;
using RepartosPeliculas = unordered_map<string, Reparto>;

/*
    Complejidad en tiempo:

    O(n*m) siendo n el numero de peliculas y m el numero de actores únicos
    ya que por cada pelicula se podría hacer una inserción potencial de todos los actores

    Complejidad en espacio

    Igual que la temporal por la misma razón

    Lo nuevo
    P = nº de pliculas, A = nª max de actores en una pelicula

    O(P*A)
*/
void leerRepartos(int numPeliculas, RepartosPeliculas& peliculas){
    Pelicula peli; int numActores;
    Actor actor; int minutos;
    for (int i = 0; i < numPeliculas; ++i){
        cin >> peli; 
        cin >> numActores;
        
        // Esto no estaba en la original, hacia la busqueda dentro de cada iteracion del for (mal)
        peliculas[peli] = list<pair<string, int>>();

        Reparto* peliculaActual = &peliculas[peli];
        for (int j = 0; j < numActores; ++j){
            cin >> actor >> minutos;
            peliculaActual->push_back({actor, minutos});
        }
    }
}


/*
    Complejidad en tiempo:

    O(n(log n) + m) siendo n el numero de actores total y siendo m el numero de peliculas.
    sobre n es n(log n) porque se hace una ordenacion final para mostrarlos alfabeticamente
    sobre m es lineal porque se recorren las peliculas emitidas para insercion en el map

    Complejidad en espacio:

    O(n + m) siendo n el numero total de peliculas únicas y m el número total de actores únicos
    Ya que solo guardaremos las peliculas y actores con sus iteraciones/tiempo de emisión, no se repiten 
*/
void procesarEmisiones(RepartosPeliculas const& repartos, vector<string> const& secEmisiones)
{
    unordered_map<string, int> peliculasEmitidas;
    unordered_map<string, int> actoresEmitidos;
    pair<string, int> masEmitida = {"", 0};

    int tActorMasVisto = 0;
    vector <string> actoresMasVistos;

    // E long secuencia emisiones, A num maximo de actores en una peli (actores unicos)
    // O (E)
    for(const string& pelicula : secEmisiones)
    {
        int& emisionesP = ++peliculasEmitidas[pelicula];

        if(emisionesP >= masEmitida.second)
            masEmitida = {pelicula, emisionesP};

        Reparto reparto = repartos.at(pelicula);
    }

    for (auto [pelicula, reps] : peliculasEmitidas)
    {
        for(auto [act, tiempo] : repartos.at(pelicula))
        {
            int& minutosA = actoresEmitidos[act] += tiempo * reps;
            if (minutosA > tActorMasVisto) {tActorMasVisto = minutosA; actoresMasVistos.clear();}
            if (minutosA == tActorMasVisto) actoresMasVistos.push_back(act);
        }
    }

    std::sort(actoresMasVistos.begin(), actoresMasVistos.end());

    std::cout << masEmitida.second << " " << masEmitida.first << "\n";
    std::cout << tActorMasVisto;
    for (const string& actor: actoresMasVistos)
    {
        std::cout << " " << actor;
    }
    std::cout << "\n";
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int numPelis, numEmisiones;
    cin >> numPelis;
    if (numPelis == 0)
        return false;

    // Lectura de los repartos de las peliculas
    RepartosPeliculas repartos;
    leerRepartos(numPelis, repartos);

    // Lectura de la secuencia de peliculas emitidas en vector<string>
    cin >> numEmisiones;
    vector<string> secEmisiones(numEmisiones);
    for (string& s : secEmisiones) cin >> s;

    procesarEmisiones(repartos, secEmisiones);

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