// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/* 
    En los casos base se comprueba si es par o impar y se suma a los contadores de pares de los
    niveles superiores, en los niveles superiores se compara el numero de pares para comprobar
    si esa seccion es caucasica y se comprueba tambien que las mitades de esa misma sección sea
    caucasica, además se suman los pares de ambas mitades (los pares totales de la sección) y se
    suma a los pares del nivel superior

    (a = 2, b = 2, k = 0) --> Complejidad de O(n)
*/
bool caucasico(vector<int> sec, int ini, int fin, int& pares)
{
    int n = fin - ini;
    if (n == 0) return true;
    if (n == 1) 
    {
        if(sec[ini] % 2 == 0)
            pares++;

        return true;
    }

    int medio = (ini + fin) / 2;

    int paresIzquierda = 0, paresDerecha = 0;

    bool izquierda = caucasico(sec, ini, medio, paresIzquierda);
    bool derecha = caucasico(sec, medio, fin, paresDerecha);

    pares += paresIzquierda + paresDerecha;

    return (izquierda && derecha && abs(paresIzquierda - paresDerecha) < 3);

}

//función carcasa
bool caucasico(vector<int> sec)
{
    int aux;
    return caucasico(sec, 0, sec.size(), aux);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n == 0) return false;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    cout << (caucasico(sec)? "SI" : "NO") << endl;
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
    //system("PAUSE");
#endif

    return 0;
}