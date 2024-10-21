// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>
#include <algorithm>

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
    Horas operator+(const Horas& otra) const;

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

Horas Horas::operator+(const Horas& otra) const
{
    int h = 0, m = 0, s;

    s = segundos + otra.segundos;
    
    m = s / 60;
    s = s % 60;

    m += minutos + otra.minutos;

    h = m / 60;
    m = m % 60;

    h += horas + otra.horas;

    if (h > 23)
        throw out_of_range("ERROR: Resultado superior a 23:59:59");

    return Horas(h, m, s);
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

class Pelicula
{
private:
    Horas horaInicio;
    Horas horaFin;
    string nombre;
public:
    Pelicula();
    Pelicula(string nom, Horas ini, Horas duracion);
    bool operator<(const Pelicula& otra) const;
    Horas getFin() const;
    string getNombre() const;
};

Pelicula::Pelicula(){}

Pelicula::Pelicula(string nom, Horas ini, Horas duracion): nombre(nom), horaInicio(ini)
{
    horaFin = horaInicio + duracion;
}

bool Pelicula::operator<(const Pelicula& otra) const
{
    if (horaFin < otra.horaFin)
    {
        return true;
    }
    else
    {
        return (horaFin <= otra.horaFin && nombre < otra.nombre);
    }
}

Horas Pelicula::getFin() const
{
    return horaFin;
}

string Pelicula::getNombre() const
{
    return nombre;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int n;
    cin >> n;

    if (n < 1)
        return false;
    
    Horas auxStartTime, auxDuration;
    string auxString;

    vector<Pelicula> listaPeliculas(n);

    for (Pelicula& p : listaPeliculas)
    {
        cin >> auxStartTime >> auxDuration;
        cin.ignore();
        getline(cin, auxString);

        p = Pelicula(auxString, auxStartTime, auxDuration);
    }
    
    sort(listaPeliculas.begin(), listaPeliculas.end());
    
    // escribir sol

    for (const Pelicula& p : listaPeliculas) 
    {
        cout << p.getFin() << " " << p.getNombre() << "\n";
    }
    
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
