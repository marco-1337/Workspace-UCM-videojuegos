#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cassert>
#include <stdexcept>

#include<unordered_map>
#include <list>
#include <vector>

using namespace std;

using cancion = std::string;
using artista = std::string;

struct datos_cancion
{
    string art;
    int duracion;
};

class iPud
{
private:
    unordered_map<cancion, datos_cancion> canciones;

    unordered_map<cancion, pair<int, list<cancion>::iterator>> cancionesEnPlaylist;
    list<cancion> playlist;

    unordered_map<cancion, list<cancion>::iterator> cancionesEnHistorial;
    list<cancion> historial;

    int duracionPlaylist = 0;

public:
    void addSong(cancion song, artista aut, int dur)
    {
        auto [it, b] = canciones.insert({song,{aut, dur}});

        if (!b)
            throw invalid_argument("addSong");
    }

    void addToPlaylist(cancion song)
    {
        auto it = canciones.find(song);

        if (it == canciones.end())
            throw invalid_argument("addToPlaylist");

        playlist.push_back(song);
        auto [itPlaylist, b] = cancionesEnPlaylist.insert({song, {it->second.duracion, --playlist.end()}});

        if (!b)
        {
            playlist.erase(itPlaylist->second.second);
            itPlaylist->second.second = --playlist.end();
        }
        else
            duracionPlaylist += it->second.duracion;
    }

    cancion current()
    {
        if (playlist.size() == 0)
            throw invalid_argument("current");
        return playlist.front();
    }

    void play()
    {
        if (playlist.size() > 0)
        {
            cancion c = playlist.front();
            auto itPlaylist = cancionesEnPlaylist.find(c); 
            cancionesEnPlaylist.erase(itPlaylist);
            playlist.pop_front();

            duracionPlaylist -= itPlaylist->second.first;

            historial.push_back(c);
            auto [itHistorial, b] = cancionesEnHistorial.insert({c, --historial.end()});

            if (!b)
            {
                historial.erase(itHistorial->second);
                itHistorial->second = --historial.end();
            }
        }
    }

    int totalTime()
    {
        return duracionPlaylist;
    }

    vector<cancion> recent(int n)
    {
        vector<cancion> salida(n);
        
        auto it = historial.begin();
        for (int i = n-1; i >= 0 && it != historial.end(); --i)
        {
            salida[i] = *it;
            ++it;
        }

        return salida;
    }

    void deleteSong(cancion song)
    {
        auto it = canciones.find(song);

        if (it != canciones.end())
        {
            auto itP = cancionesEnPlaylist.find(song);
            auto itH = cancionesEnHistorial.find(song);

            if (itP != cancionesEnPlaylist.end())
            {
                playlist.erase(itP->second.second);
                cancionesEnPlaylist.erase(itP);
            }
            else if (itH != cancionesEnHistorial.end())
            {
                historial.erase(itH->second);
                cancionesEnHistorial.erase(itH);
            }
            canciones.erase(it);
        }
    }

};

bool resuelve() {
    string operacion;
    cin >> operacion;
    if (!cin)
        return false;
    cancion tit; artista aut; int dur;
    iPud ipud;
    while (operacion != "FIN") {
        try {
            if (operacion == "addSong") {
                cin >> tit >> aut >> dur;
                ipud.addSong(tit, aut, dur);
            } else if (operacion == "addToPlaylist") {
                cin >> tit;
                ipud.addToPlaylist(tit);
            } else if (operacion == "current") {
                tit = ipud.current(); // aunque no se hace nada, puede producir error
            } else if (operacion == "play") {
                try {
                    string tocando = ipud.current(); // para saber si la lista es vacía
                    ipud.play();
                    cout << "Sonando " << tocando << '\n';
                } catch (invalid_argument e) {
                    cout << "No hay canciones en la lista\n";
                }
            } else if (operacion == "totalTime") {
                cout << "Tiempo total " << ipud.totalTime() << '\n';
            } else if (operacion == "recent") {
                int N;
                cin >> N;
                auto lista = ipud.recent(N);
                if (lista.empty())
                    cout << "No hay canciones recientes\n";
                else {
                    cout << "Las " << lista.size() << " mas recientes\n";
                    for (auto const& s : lista)
                        cout << "    " << s << '\n';
                }
            } else if (operacion == "deleteSong") {
                cin >> tit;
                ipud.deleteSong(tit);
            } else { // operacion desconocida
                assert(false);
            }
        } catch (invalid_argument e) {
            cout << "ERROR " << e.what() << '\n';
        }
        cin >> operacion;
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