//
//  IndexPQ.h
//
//  Implementación de colas con prioridad mediante montículos.
//  Los elementos son enteros de 0 a N-1 que tienen asociada una prioridad
//  dentro de la cola. La prioridad de cualquier elemento puede ser
//  modificada con coste en O(log N).
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020 Alberto Verdejo
//

#ifndef INDEXPQ_H_
#define INDEXPQ_H_

#include <iostream>
#include <stdexcept>
#include <vector>
#include <unordered_map>

template <typename T, typename U>
struct ComparadorNulo {
    bool operator()(T const&, T const&, U const&, U const&) const {
        return false;
    }
};

// T es el tipo de las prioridades
// Comparator dice cuándo un valor de tipo T es más prioritario que otro
template <typename T, typename U, typename Comparator = std::less<U>, typename KeyComparator = ComparadorNulo<T,U>>
class IndexPQ {
public:
   // registro para las parejas < elem, prioridad >
   struct Par {
      T elem;
      U prioridad;
   };
   
private:
   // vector que contiene los datos (pares < elem, prio >)
   std::vector<Par> array;     // primer elemento en la posición 1
   
   // mapa que contiene las posiciones en array de los elementos
   std::unordered_map<T,int> posiciones;
   
   /* Objeto función que sabe comparar prioridades.
    antes(a,b) es cierto si a es más prioritario que b */
   Comparator antes;
   KeyComparator antesKey;

   bool compruebaAntes(const Par& a, const Par& b) {
      return antes(a.prioridad, b.prioridad) || antesKey(a.elem, b.elem, a.prioridad, b.prioridad); 
   }
   
public:
   IndexPQ(Comparator c = Comparator()) :
       array(1), posiciones(), antes(c), antesKey(KeyComparator()) {}
   
   IndexPQ(IndexPQ<T,U,Comparator,KeyComparator> const&) = default;

   IndexPQ<T,U,Comparator,KeyComparator>& operator=(IndexPQ<T,U,Comparator,KeyComparator> const&) = default;
   
   ~IndexPQ() = default;
   
   // e debe ser uno de los posibles elementos
   void push(T const& e, U const& p) {
      if (posiciones.find(e) != posiciones.end())
         throw std::invalid_argument("No se pueden insertar elementos repetidos.");
      else {
         array.push_back({e, p});
         posiciones[e] = size();
         flotar(size());
      }
   }
   
   void update(T const& e, U const& p) {
      if (posiciones.find(e) == posiciones.end()) // el elemento e se inserta por primera vez
         push(e, p);
      else {
         int i = posiciones.at(e);
         array[i].prioridad = p;
         if (i != 1 && compruebaAntes(array[i], array[i/2]))
            flotar(i);
         else // puede hacer falta hundir a e
            hundir(i);
      }
   }
   
   int size() const {
      return int(array.size()) - 1;
   }
   
   bool empty() const {
      return size() == 0;
   }
   
   Par const& top() const {
      if (size() == 0)
         throw std::domain_error("No se puede consultar el primero de una cola vacia");
      else return array[1];
   }
   
   void pop() {
      if (size() == 0) throw std::domain_error("No se puede eliminar el primero de una cola vacía.");
      else {
         posiciones.erase(array[1].elem); // para indicar que no está
         if (size() > 1) {
            array[1] = std::move(array.back());
            posiciones[array[1].elem] = 1;
            array.pop_back();
            hundir(1);
         } else
            array.pop_back();
      }
   }

   U const& priority(T const& e) const {
      auto it = posiciones.find(e);
      if (it == posiciones.end())
         throw std::domain_error("No se puede consultar la prioridad de un elemento que no ha sido insertado aún.");
      return array[it->second].prioridad;
   }

   bool contains(T const& e) const {
      if (posiciones.find(e) == posiciones.end()) return false;
      return true;
   }

private:
   
   void flotar(int i) {
      Par parmov = std::move(array[i]);
      int hueco = i;
      while (hueco != 1 && compruebaAntes(parmov, array[hueco/2])) {
         array[hueco] = std::move(array[hueco/2]); posiciones[array[hueco].elem] = hueco;
         hueco /= 2;
      }
      array[hueco] = std::move(parmov); posiciones[array[hueco].elem] = hueco;
   }
   
   void hundir(int i) {
      Par parmov = std::move(array[i]);
      int hueco = i;
      int hijo = 2*hueco; // hijo izquierdo, si existe
      while (hijo <= size())  {
         // cambiar al hijo derecho de i si existe y va antes que el izquierdo
         if (hijo < size() && compruebaAntes(array[hijo + 1], array[hijo]))
            ++hijo;
         // flotar el hijo si va antes que el elemento hundiéndose
         if (compruebaAntes(array[hijo], parmov)) {
            array[hueco] = std::move(array[hijo]); posiciones[array[hueco].elem] = hueco;
            hueco = hijo; hijo = 2*hueco;
         }
         else break;
      }
      array[hueco] = std::move(parmov); posiciones[array[hueco].elem] = hueco;
   }
   
};

#endif /* INDEXPQ_H_ */

/*
#include <iostream>
#include <string>
using namespace std;

int main() {
   
   IndexPQ<string, int> cola;
   cola.push("Pedro", 50);
   cola.push("Marta", 100);
   cola.push("Luis", 40);
   cola.update("Pedro", 30);
   cola.push("Eva", 60);
   cout << cola.top().elem << '\n';  // debe salir Pedro
   cola.pop();
   cola.update("Marta", 10);
   cout << cola.top().elem << '\n';  // debe salir Marta
   cola.update("Marta", 70);
   cout << cola.top().elem << '\n';  // debe salir Luis

}
*/