#ifndef GRAFO_H
#define GRAFO_H

#include "nodo.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <queue>

class Grafo {
private:
    std::unordered_map<std::string, Nodo*> nodos;

public:
    Grafo();
    ~Grafo();

    Nodo* agregarNodo(std::string nombre);
    void agregarArista(std::string origen, std::string destino, std::string accion);
    void mostrarGrafo();

    bool caminoMasCorto(std::string inicio, std::string fin, std::vector<std::string>& camino);
    bool caminoBestFirst(std::string inicio, std::vector<std::string>& camino);

    struct NodoCola {
        Nodo* nodo;
        int h;
        std::vector<std::string> camino;

        bool operator<(const NodoCola& otro) const {
            return h > otro.h; // menor heurística tiene más prioridad
        }
    };

    static int Heuristica(std::string estado);
};

#endif
