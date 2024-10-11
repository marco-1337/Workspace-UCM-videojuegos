// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>


using namespace std;

bool monomialLesserThan(const pair<int, int>& mA, const pair<int, int>& mB) 
{
    return mA.second < mB.second;
}

class Polinomio
{
private:
    int grado;
    // 1 coeficiente, 2 exponente
    vector<pair<int, int>> listaMonomios;
public:
    Polinomio(): grado(0){}

    // O(log n) siendo n = listaMonomios.size()
    void addMonomio(int coeficiente, int exponente)
    {
        if(coeficiente != 0)
        {
            pair<int, int> elem = {coeficiente, exponente};

            vector<pair<int, int>>::iterator it = 
                lower_bound(listaMonomios.begin(), listaMonomios.end(), elem, monomialLesserThan);

            if (it == listaMonomios.end() || (*it).second != exponente) 
            {
                listaMonomios.insert(it, elem);
                if(exponente > grado)
                    grado = exponente;
            }
            else
                (*it).first += coeficiente;
        }
    }

    // O(n) siendo n = listaMonomios.size()
    int calcularParaX(int x) const
    {
        int sol = 0;
        for(const pair<int, int>& e : listaMonomios)
        {
            sol += e.first * pow(x, e.second);
        }
        return sol;
    }
};

// función que resuelve el problema
void resolver(const Polinomio& datos, vector<int> evaluar) {
    
    for(const int& v : evaluar)
    {
        cout << datos.calcularParaX(v) << " ";
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta

bool resuelveCaso() {
    // leer los datos de la entrada
    
    int coeficiente, exponente, nVal;

    cin >> coeficiente;

    if (! std::cin)
        return false;

    cin >> exponente;

    Polinomio datos;

    while(coeficiente != 0 || exponente != 0)
    {
        datos.addMonomio(coeficiente, exponente);
        cin >> coeficiente >> exponente;
    }
    
    cin >> nVal;

    vector<int> valores(nVal);

    for (int& v : valores)
    {
        cin >> v;
    }
    
    // escribir sol
    resolver(datos, valores);
    
    cout << "\n";

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