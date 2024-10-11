// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

class Horas
{
private:
    int horas;
    int minutos;
    int segundos;
public:
    Horas();
    Horas(int horas, int minutos, int segundos);
    bool operator<(const Horas& otra) const;
    bool operator<=(const Horas& otra) const;
    friend ostream& operator<<(ostream& out, const Horas& horas);
    friend istream& operator>>(istream& in, Horas& horas);
};

Horas::Horas(): horas(0), minutos(0), segundos(0){}

Horas::Horas(int horas, int minutos, int segundos): horas(horas), minutos(minutos), segundos(segundos)
{
    bool error = false;

    if (horas < 0 || horas > 23)
        error = true;
    else if(minutos < 0 || minutos > 59)
        error = true;
    else if(segundos < 0 || segundos > 59)
        error = true;

    if(error)
        throw invalid_argument("ERROR");
}

bool Horas::operator<(const Horas& otra) const
{
    return (
        horas < otra.horas || 
        (horas == otra.horas && minutos < otra.minutos) || 
        (horas == otra.horas && minutos == otra.minutos && segundos < otra.segundos));
}

bool Horas::operator<=(const Horas& otra) const
{
    return (this->operator<(otra) || (horas == otra.horas && minutos == otra.minutos && segundos == otra.segundos));
}

ostream& operator<<(ostream& out, const Horas& horas)
{
    if(horas.horas < 10)
        out << 0;
    out << horas.horas << ":";
    if(horas.minutos < 10)
        out << 0;
    out << horas.minutos << ":";
    if(horas.segundos < 10)
        out << 0;
    out << horas.segundos;

    return out;
}

istream& operator>>(istream& in, Horas& horas)
{
    char aux;
    int h, m, s;

    in >> h >> aux >> m >> aux >> s;

    horas = Horas(h, m, s);

    return in;
}

void compruebaTrenSiguiente(const vector<Horas>& horarios, const Horas& consulta, int ini, int fin)
{
    int n = fin - ini;

    if (n == 0)
        cout << "NO";
    else if (n == 1)
    {
        if (consulta <= horarios[ini])
            cout << horarios[ini];
        else
            cout << "NO";
    }
    else 
    {
        int mitad = (ini + fin) / 2;

        if(consulta <= horarios[mitad-1])
            compruebaTrenSiguiente(horarios, consulta, ini, mitad);
        else
            compruebaTrenSiguiente(horarios, consulta, mitad, fin);
    }
}

void resolver(const vector<Horas>& horarios, const Horas& consulta)
{
    compruebaTrenSiguiente(horarios, consulta, 0, horarios.size());
}

// función que resuelve el problema

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int trenes;
    int horas;
    
    cin >> trenes;
    cin >> horas;

    if (trenes == 0 && horas == 0)
        return false;

    vector<Horas> horariosTrenes(trenes);
    
    for(Horas& h : horariosTrenes)
    {
        cin >> h;
    }

    vector<Horas> horasConsultadas(horas);
    
    for(Horas& h : horasConsultadas)
    {
        try
        {
            cin >> h;
            resolver(horariosTrenes, h);
        }
        catch (exception& e)
        {
            cout << e.what();
        }
        cout << "\n";
    }
    
    // escribir sol
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
    
    
    while (resuelveCaso());

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}