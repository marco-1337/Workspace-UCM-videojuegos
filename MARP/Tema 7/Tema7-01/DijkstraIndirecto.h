#pragma once

#include "IndexPQ.h"
#include "GrafoValorado.h"

#include <list>
#include <limits>

template <typename Valor>
using Camino = std::list<Valor>;

template <typename Valor>
class DijkstraIndirecto {
public:

    DijkstraIndirecto(GrafoValorado<Valor> const& g, int orig) 
    : origen(orig), dist(g.V(), INF), ulti(g.V()), pq() {

        dist[origen] = 0;
        pq.push(origen, 0);

        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a, v);
        }
    }

    bool hayCamino(int v) const { return dist[v] != INF; }
    Valor distancia(int v) const { return dist[v]; }

    Camino<Valor> camino(int v) const {

        Camino<Valor> cam;

        // recuperamos el camino retrocediendo
        int a;

        cam.push_front(v);
        
        for (a = v; a != origen; a = ulti[a])
            cam.push_front(ulti[a]);

        return cam;
    }

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    std::vector<int> ulti;
    IndexPQ<int, Valor> pq;

    void relajar(Arista<Valor> a, int v) {
        int w = a.otro(v);

        if (dist[w] > dist[v] + a.valor()) { 
            dist[w] = dist[v] + a.valor(); ulti[w] = v;
            pq.update(w, dist[w]);
        }
    }
};