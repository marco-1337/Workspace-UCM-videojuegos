// Plantilla para el ejercicio del Consultorio Médico

#include <iostream>
#include <iomanip>
#include <fstream>

#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>

#include <unordered_map>
#include <map>
#include <list>

#include <string>

using namespace std;

using medico = string;
using paciente = string;

class fecha
{
private:
    int d, h, m;
public:
    fecha(int d, int h, int m): d(d), h(h), m(m) {}

    bool operator<(const fecha& other) const
    {
        if (d == other.d)
        {
            if (h == other.h)
                return m < other.m;

            return h < other.h;
        }

        return d < other.d;
    }

    int getD() const {return d;}
    int getH() const {return h;}
    int getM() const {return m;}
};

class Consultorio
{
private:
    unordered_map<medico, map<int, map<fecha, paciente>>> datosMedicos;
    
public:

    void nuevoMedico(const medico& med)
    {
        datosMedicos.insert({med, map<int, map<fecha, paciente>>()});
    }

    void pideConsulta(const paciente& pac, const medico& med, const fecha& fec)
    {
        auto itMedico = datosMedicos.find(med);

        if (itMedico == datosMedicos.end())
            throw invalid_argument("Medico no existente");
        
        auto insercionDia = itMedico->second.insert({fec.getD(), map<fecha, paciente>()});

        if (insercionDia.second)
        {
            insercionDia.first->second[fec] = pac;
        }
        else
        {
            auto insercionFecha = insercionDia.first->second.insert({fec, pac});

            if (!insercionFecha.second)
                throw invalid_argument("Fecha ocupada");
        }
    }

    string siguientePaciente(const medico& med) const
    {
        auto itMedico = datosMedicos.find(med);

        if (itMedico == datosMedicos.end())
            throw invalid_argument("Medico no existente");
        
        if (itMedico->second.size() == 0)
            throw invalid_argument("No hay pacientes");

        return itMedico->second.begin()->second.begin()->second;
    }

    void atiendeConsulta(const medico& med)
    {
        auto itMedico = datosMedicos.find(med);

        if (itMedico == datosMedicos.end())
            throw invalid_argument("Medico no existente");
        
        auto dias = &itMedico->second;

        if (dias->size() == 0)
            throw invalid_argument("No hay pacientes");

        auto fechasPrimerDia = &dias->begin()->second;

        fechasPrimerDia->erase(fechasPrimerDia->begin());
        
        if (fechasPrimerDia->size() == 0)
            dias->erase(dias->begin());
    }

    list<pair<string, paciente>> listaPacientes(medico& med, int d)
    {
        list<pair<string, paciente>> salida;

        auto itMedico = datosMedicos.find(med);

        if (itMedico == datosMedicos.end())
            throw invalid_argument("Medico no existente");
        
        auto itDia = itMedico->second.find(d);

        if (itDia != itMedico->second.end())
        {
            for (auto [f, p] : itDia->second)
            {
                string h = to_string(f.getH()), m = to_string(f.getM());

                if (f.getH() < 10) h = "0"+h;
                if (f.getM() < 10) m = "0"+m;

                salida.push_back({h+":"+m, p});
            }
        }

        return salida;
    }
};

bool resuelve() {
   
   int N;
   cin >> N;
   if (!cin) return false;
   
   string inst; medico med; paciente pac; int d, h, m; char c;
   Consultorio con;
   
   for (int i = 0; i < N; ++i) {
      try {
         cin >> inst;
         if (inst == "nuevoMedico") {
            cin >> med;
            con.nuevoMedico(med);
         } else if (inst == "pideConsulta") {
            cin >> pac >> med >> d >> h >> c >> m;
            con.pideConsulta(pac, med, fecha(d,h,m));
         } else if (inst == "siguientePaciente") {
            cin >> med;
            pac = con.siguientePaciente(med);
            cout << "Siguiente paciente doctor " << med << '\n';
            cout << pac << '\n';
         } else if (inst == "atiendeConsulta") {
            cin >> med;
            con.atiendeConsulta(med);
         } else if (inst == "listaPacientes") {
            cin >> med >> d;
            auto vec = con.listaPacientes(med, d);
            cout << "Doctor " << med << " dia " << d << '\n';
            for (auto p : vec) {
               cout << p.second << ' ' << p.first << '\n';
            }
         } else
            assert(false);
      } catch (invalid_argument e) { cout << e.what() << '\n'; }
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
    
    
    while (resuelve());

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}