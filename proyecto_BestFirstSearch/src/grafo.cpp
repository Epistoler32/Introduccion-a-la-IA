#include "grafo.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <sstream>

Grafo::Grafo() {}

Grafo::~Grafo() {
    for (std::pair<const std::string, Nodo*>& par : nodos) {
        delete par.second;
    }
}

Nodo* Grafo::agregarNodo(std::string estado) {
    if (nodos.find(estado) == nodos.end()) {
        nodos[estado] = new Nodo(estado);
    }
    return nodos[estado];
}

void Grafo::agregarArista(std::string origen, std::string destino, std::string accion) {
    Nodo* nodoOrigen = agregarNodo(origen);
    Nodo* nodoDestino = agregarNodo(destino);
    nodoOrigen->agregarAdyacente(nodoDestino, accion);
}

void Grafo::mostrarGrafo() {
    for (std::pair<const std::string, Nodo*>& par : nodos) {
        std::cout << par.first << " -> ";
        for (const std::pair<Nodo*, std::string>& ady : par.second->getAdyacentes()) {
            std::cout << ady.first->getNombre();
        }
        std::cout << std::endl;
    }
}

int Grafo::Heuristica(std::string estado) {
    int a, b;
    char par1, coma, par2;
    std::stringstream ss(estado);
    ss >> par1 >> a >> coma >> b >> par2;
    int ab = 0; // cantidad que se puede transferir de 4L -> 5L
    int ba = 0; // cantidad que se puede transferir de 5L -> 4L
    int dif=0;
    if (a > 0 && b < 5) {
        ab = std::min(a, 5 - b);
        if (b > 0 && a < 4) {
            ba = std::min(b, 4 - a);
            dif = std::min(abs((b+ab)-2), abs((b-ba)-2));
            return std::min(dif, abs(b-2));
        }
        return std::min(abs((b+ab)-2), abs(b-2));
    }else if (b > 0 && a < 4) {
            ba = std::min(b, 4 - a);
            if (a > 0 && b < 5) {
                ab = std::min(a, 5 - b);
                dif = std::min(abs((b+ab)-2), abs((b-ba)-2));
                return std::min(dif, abs(b-2));
            }
        return std::min(abs((b-ba)-2), abs(b-2));
    }
    return abs(b-2);
}


bool Grafo::caminoBestFirst(std::string inicio, std::vector<std::string>& camino) {
    if (nodos.find(inicio) == nodos.end()) {
        return false;
    }

    std::priority_queue<NodoCola> pq;
    std::unordered_map<std::string, bool> visitado;

    NodoCola ini{nodos[inicio], Heuristica(inicio), {inicio}};
    pq.push(ini);
    visitado[inicio] = true;

    while (!pq.empty()) {
        NodoCola act = pq.top();
        pq.pop();

        int a, b;
        char par1, coma, par2;
        std::stringstream ss(act.nodo->getNombre());
        ss >> par1 >> a >> coma >> b >> par2;

        if (b == 2) {
            camino = act.camino;
            return true;
        }

        for (const std::pair<Nodo*, std::string>& par : act.nodo->getAdyacentes()) {
            Nodo* vecino = par.first;
            const std::string& accion = par.second;

            std::string estadoVecino = vecino->getNombre();
            if (!visitado[estadoVecino]) {
                visitado[estadoVecino] = true;
                NodoCola nuevo{vecino, Heuristica(estadoVecino), act.camino};
                nuevo.camino.push_back(estadoVecino + " <- " + accion);
                pq.push(nuevo);
            }
        }

    }

    return false;
}
