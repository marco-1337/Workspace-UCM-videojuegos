// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <stack>

using namespace std;

// función que resuelve el problema
// O(n) siendo n la longitud de datos
string resolver(string datos) {

    stack<char> pila;

    for(char ch: datos)
    {
        if (ch == '(' || ch == '[' || ch == '{')
            pila.push(ch);
        else if (ch == ')' || ch == ']' || ch == '}')
        {
            if(pila.empty())
            {
                return "NO";
            }
            else if (pila.top() == '(')
            {
                if (ch == ')')
                    pila.pop();
                else if (ch == ']' || ch == '}')
                    return "NO";
            }
            else if (pila.top() == '[')
            {
                if (ch == ']')
                    pila.pop();
                else if (ch == ')' || ch == '}')
                    return "NO";
            }
            else
            {
                if (ch == '}')
                    pila.pop();
                else if (ch == ')' || ch == ']')
                    return "NO";
            }
        }
    }

    if(pila.empty())
        return "SI";
    return "NO";
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    string datos;

    getline(cin, datos);

    if (! std::cin)
        return false;

    string sol = resolver(datos);
    
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