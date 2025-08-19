#include <queue>
#include <set>
#include <string>
#include <iostream>
#include <vector>
#include "grafo.h"

struct Movimiento {
    std::pair<int,int> estado;
    std::string accion;
};


std::string estadoToStr(int a, int b) {
    return "(" + std::to_string(a) + "," + std::to_string(b) + ")";
}


std::pair<int,int> llenarJarra(int a, int b, int jarra, bool tipojarra) {
    if (tipojarra) return {jarra, b};   // Llenar jarra de 4L
    else return {a, jarra};           // Llenar jarra de 5L
}

std::pair<int,int> vaciarJarra(int a, int b, bool tipojarra) {
    if (tipojarra) return {0, b};  // Vaciar jarra de 4L
    else return {a, 0};           // Vaciar jarra de 5L
}

std::pair<int,int> transferir(int a, int b, int jarra4, int jarra5, bool direccion) {
    if (direccion) {
        int espacio = jarra5 - b;
        int transfer = std::min(a, espacio);
        return {a - transfer, b + transfer};
    } else {
        int espacio = jarra4 - a;
        int transfer = std::min(b, espacio);
        return {a + transfer, b - transfer};
    }
}

std::vector<Movimiento> generarHijos(int a, int b, int jarra4, int jarra5) {
    std::vector<Movimiento> hijos;

    hijos.push_back({llenarJarra(a, b, jarra4, true), "Llenar jarra 4L"});
    hijos.push_back({llenarJarra(a, b, jarra5, false), "Llenar jarra 5L"});
    hijos.push_back({vaciarJarra(a, b, true), "Vaciar jarra 4L"});
    hijos.push_back({vaciarJarra(a, b, false), "Vaciar jarra 5L"});
    hijos.push_back({transferir(a, b, jarra4, jarra5, true), "Verter 4L → 5L"});
    hijos.push_back({transferir(a, b, jarra4, jarra5, false), "Verter 5L → 4L"});

    return hijos;
}



void construirGrafo(Grafo &g, int jarra4, int jarra5) {
    std::queue<std::pair<int,int>> cola;
    std::set<std::string> visitados;

    cola.push({0,0});
    visitados.insert(estadoToStr(0,0));
    g.agregarNodo(estadoToStr(0,0));

    while (!cola.empty()) {
        std::pair<int,int> actual = cola.front();
        cola.pop();
        int a = actual.first;
        int b = actual.second;

        std::vector<Movimiento> hijos = generarHijos(a, b, jarra4, jarra5);

        for (Movimiento hijo : hijos) {
            int na = hijo.estado.first;
            int nb = hijo.estado.second;
            std::string hijoStr = estadoToStr(na, nb);
            std::string actualStr = estadoToStr(a, b);

            if (hijoStr != actualStr) {
                if (!visitados.count(hijoStr)) {
                    visitados.insert(hijoStr);
                    cola.push({na, nb});
                    g.agregarNodo(hijoStr);
                }       
                g.agregarArista(actualStr, hijoStr, hijo.accion); 
            }
        }
    }
}

void imprimirCamino(const std::vector<std::string> &camino) {
    std::cout << "Pasos a la solución\n";
    for (const std::string &estado : camino) {
        std::cout << estado << "\n";
    }
}



int main() {
    Grafo g;
    const int jarra4 = 4, jarra5 = 5;

    construirGrafo(g, jarra4, jarra5);

    std::vector<std::string> camino;
    std::string inicio = estadoToStr(0,0);

    if (g.caminoBestFirst(inicio, camino)) {
        imprimirCamino(camino);
    } else {
        std::cout << "No se encontró solución.\n";
    }

    std::cout << "\nEstados \n";
    g.mostrarGrafo();

    return 0;
}
