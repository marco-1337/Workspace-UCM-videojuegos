#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cassert>
#include <stdexcept>

#include<unordered_map>
#include<map>
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

    unordered_map<cancion, int> playlist;
    map<int, cancion> playlistOrdered;

    int antiguedadPlaylist = 0;

    unordered_map<cancion, int> historial;
    map<int, cancion> historialOrdered;

    int antiguedadHistorial = 0;

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

        auto [itPlaylist, b] = playlist.insert({song, ++antiguedadPlaylist});

        if (b)
        {
            duracionPlaylist += it->second.duracion;
            playlistOrdered[antiguedadPlaylist] = song;
        }
    }

    cancion current()
    {
        if (playlist.size() == 0)
            throw invalid_argument("current");
        return playlistOrdered.begin()->second;
    }

    void play()
    {
        if (playlist.size() > 0)
        {
            auto songIt = playlistOrdered.begin();

            playlist.erase(songIt->second);
            duracionPlaylist -= canciones[songIt->second].duracion;
            
            int nuevaAntiguedad = ++antiguedadHistorial;

            auto [itHistorial, b] = historial.insert({songIt->second, nuevaAntiguedad});

            if (!b)
            {
                historialOrdered.erase(itHistorial->second);
                itHistorial->second = nuevaAntiguedad;
            }

            historialOrdered[nuevaAntiguedad] = songIt->second;

            playlistOrdered.erase(songIt);
        }
    }

    int totalTime()
    {
        return duracionPlaylist;
    }

    vector<cancion> recent(int n)
    {
        auto it = historialOrdered.end();
        if (it == historialOrdered.begin())
        {
            return vector<cancion>(0);
        }
        vector<cancion> salida(n);
        --it;
        bool notBegin = true;

        int i;
        for (i = 0; i < n && notBegin; ++i)
        {
            salida[i] = it->second;
            if (it != historialOrdered.begin())
            {
                --it;
            }
            else
            {
                notBegin = false;
            }
        }

        if (i < n)
            salida.resize(i);

        return salida;
    }

    void deleteSong(cancion song)
    {
        auto it = canciones.find(song);

        if (it != canciones.end())
        {
            auto itP = playlist.find(song);
            auto itH = historial.find(song);

            if (itP != playlist.end())
            {   
                duracionPlaylist -= it->second.duracion;
                playlistOrdered.erase(itP->second);
                playlist.erase(itP);
            }
            
            if (itH != historial.end())
            {
                historialOrdered.erase(itH->second);
                historial.erase(itH);
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