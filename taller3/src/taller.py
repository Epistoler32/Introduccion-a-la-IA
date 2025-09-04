import sys
import re

class RedSemantica:
    def __init__(self):
        self.clases = {}
        self.instancias = {}
        self.atributos = {}

    def agregar_es_un(self, clase, superclase):
        self.clases[clase] = superclase

    def agregar_instancia(self, instancia, clase):
        self.instancias[instancia] = clase

    def agregar_atributo(self, entidad, atributo, valor):
        if entidad not in self.atributos:
            self.atributos[entidad] = {}
        self.atributos[entidad][atributo] = valor

    def obtener_atributo(self, entidad, atributo):
        if entidad in self.instancias:
            clase = self.instancias[entidad]
            if atributo in self.atributos.get(entidad, {}):
                return self.atributos[entidad][atributo]
            return self._buscar_en_clase(clase, atributo)
        if entidad in self.clases or entidad in self.atributos:
            return self._buscar_en_clase(entidad, atributo)
        return None

    def _buscar_en_clase(self, clase, atributo):
        if atributo in self.atributos.get(clase, {}):
            return self.atributos[clase][atributo]
        if clase in self.clases:
            return self._buscar_en_clase(self.clases[clase], atributo)
        return None

    def entidades_con_atributo(self, atributo, valor):
        resultado = []
        for entidad in set(list(self.clases.keys()) + list(self.instancias.keys()) + list(self.atributos.keys())):
            val = self.obtener_atributo(entidad, atributo)
            if val == valor:
                resultado.append(entidad)
        return resultado


def cargar_red(nombre_archivo):
    red = RedSemantica()
    with open(nombre_archivo, "r", encoding="utf-8") as f:
        for linea in f:
            linea = linea.strip()
            if linea.startswith("es_un"):
                m = re.match(r"es_un\(([^,]+),([^)]+)\)", linea)
                red.agregar_es_un(m.group(1), m.group(2))
            elif linea.startswith("instancia"):
                m = re.match(r"instancia\(([^,]+),([^)]+)\)", linea)
                red.agregar_instancia(m.group(1), m.group(2))
            elif linea.startswith("atributo"):
                m = re.match(r"atributo\(([^,]+),([^,]+),([^)]+)\)", linea)
                red.agregar_atributo(m.group(1), m.group(2), m.group(3))
    return red


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Uso: python3 main.py archivo_red.txt")
        sys.exit(1)

    archivo = sys.argv[1]
    red = cargar_red(archivo)

    print("Puedes hacer preguntas en los siguientes formatos:\n")
    print("1) atributo <nombre_atributo> de <clase/instancia>?")
    print("   Ejemplo: atributo vel/max de Ferrari?")
    print("            atributo color de FordFiesta?\n")
    print("2) clases con atributo <nombre_atributo> y valor <valor>?")
    print("   Ejemplo: clases o instancias con atributo color y valor rojo?")
    print("            clases o instancias con atributo #ruedas y valor 2?\n")
    print("3) instancias con atributo <nombre_atributo> y valor <valor>?")
    print("            clases o instancias con atributo #ruedas y valor 2?\n")
    print("Escribe 'salir' para terminar.\n")

    while True:
        pregunta = input("> ").strip()
        if pregunta.lower() == "salir":
            break

        m1 = re.match(r"atributo (.+) de (.+)\?", pregunta, re.IGNORECASE)
        if m1:
            atributo, entidad = m1.group(1), m1.group(2)
            valor = red.obtener_atributo(entidad, atributo)
            if valor:
                print(f"{entidad} tiene {atributo} = {valor}")
            else:
                print(f"{entidad} no tiene el atributo {atributo}")
            continue

        m2 = re.match(r"clases con atributo (.+) y valor (.+)\?", pregunta, re.IGNORECASE)
        if m2:
            atributo, valor = m2.group(1), m2.group(2)
            entidades = red.entidades_con_atributo(atributo, valor)
            if entidades:
                print("Entidades encontradas:", ", ".join(entidades))
            else:
                print(f"Ninguna entidad tiene {atributo} = {valor}")
            continue

        m3 = re.match(r"instancias con atributo (.+) y valor (.+)\?", pregunta, re.IGNORECASE)
        if m2:
            atributo, valor = m2.group(1), m2.group(2)
            entidades = red.entidades_con_atributo(atributo, valor)
            if entidades:
                print("Entidades encontradas:", ", ".join(entidades))
            else:
                print(f"Ninguna entidad tiene {atributo} = {valor}")
            continue

        print("Formato de pregunta no reconocido. Usa los ejemplos de la guía.")