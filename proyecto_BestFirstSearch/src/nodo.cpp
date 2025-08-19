#include "nodo.h"

Nodo::Nodo(const std::string& estado) : estado(estado) {}

std::string Nodo::getNombre() const {
    return estado;
}

void Nodo::agregarAdyacente(Nodo* nodo, const std::string& accion) {
    adyacentes.push_back({nodo, accion});
}

const std::vector<std::pair<Nodo*, std::string>>& Nodo::getAdyacentes() const {
    return adyacentes;
}

