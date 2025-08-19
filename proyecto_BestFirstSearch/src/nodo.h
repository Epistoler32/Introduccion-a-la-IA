#ifndef NODO_H
#define NODO_H

#include <string>
#include <vector>

class Nodo {
private:
    std::string estado;
    std::vector<std::pair<Nodo*, std::string>> adyacentes;

public:
    Nodo(const std::string& estado);
    std::string getNombre() const;
    void agregarAdyacente(Nodo* nodo, const std::string& accion);
    const std::vector<std::pair<Nodo*, std::string>>& getAdyacentes() const;
};

#endif
