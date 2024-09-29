// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void calcularPolidivisible(long long raiz, int digitosRaiz, int maxDigitos, int incremento)
{
    if(digitosRaiz > maxDigitos) 
        return;

    if (raiz % digitosRaiz == 0) 
    {
        cout << raiz << "\n";

        long long nuevaRaiz = (raiz * 10);

        calcularPolidivisible(nuevaRaiz, digitosRaiz + 1, maxDigitos, 1);
    }
    if((raiz + incremento)% 10 != 0)
    {
        calcularPolidivisible(raiz + 1, digitosRaiz, maxDigitos, 1);
    }
}

// función carcasa
void escribePolidivisibles(long long raiz, int maxDigitos) {
    int digitosPrevios;

    if(raiz == 0) 
    {
        digitosPrevios = 1;
    }
    else 
    {
        long long rAux = raiz;
        digitosPrevios = 0;
        while (rAux > 0) 
        {
            rAux /= 10;
            digitosPrevios++;
        }
    }
    calcularPolidivisible(raiz, digitosPrevios, maxDigitos, (raiz % 10)*-1);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    long long numeroBase;
    int n;

    cin >> numeroBase >> n; 

    if (! std::cin)
        return false;
    
    escribePolidivisibles(numeroBase, n);
    
    cout << "---" << "\n"; 

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