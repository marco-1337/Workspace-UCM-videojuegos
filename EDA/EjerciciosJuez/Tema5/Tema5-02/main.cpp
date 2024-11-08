// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30

#include <iostream>
#include <iomanip>
#include <fstream>

#include <queue>
#include <deque>
#include <stack>

using namespace std;

// O(n) siendo n el tamaño de datos (O(2*n))
void resolver(queue<int>& datos) {
    
    deque<int> aux;
    
    while (!datos.empty())
    {
        if (datos.front() < 0)
            aux.emplace_back(datos.front());
        else
            aux.emplace_front(datos.front());

        datos.pop();
    }

    while (!aux.empty())
    {
        datos.push(aux.front());
        aux.pop_front();
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() 
{
    // leer los datos de la entrada
    
    int n;
    cin >> n; 

    if (n == 0)
        return false;
    
    queue<int> cola;
    int elem;

    for (int i = 0; i < n; i++)
    {
        cin >> elem;
        cola.push(elem);
    }

    resolver(cola);

    // escribir sol
    stack<int> salida;
    for (int i = 0; i < n; i++)
    {
        salida.push(cola.front());
        cola.push(cola.front());
        cola.pop();
    }

    while (!salida.empty()) 
    {
        cout << salida.top() << " ";
        salida.pop();
    }
    cout << endl;

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
     //system("PAUSE");
     #endif
    
    return 0;
}