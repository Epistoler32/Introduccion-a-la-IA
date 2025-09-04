Taller 3 - Representación de Conocimiento

Este taller corresponde al curso Introducción a la Inteligencia Artificial y tiene como objetivo implementar una red semántica que permita representar conocimiento en un contexto dado.

Objetivos

Familiarizarse con la definición y reglas de una red semántica.

Implementar la representación en un lenguaje de programación (Python, Java o C++).

Incluir un mecanismo de herencia de atributos que permita responder preguntas sobre la información almacenada.

Funcionalidades requeridas

Leer la red semántica desde un archivo con relaciones es_un, instancia y atributo.

Consultar:

El valor de un atributo para una clase o instancia.

Todas las clases o instancias que poseen un atributo con un valor específico.

Validar con dos redes semánticas:

Ejemplo de vehículos visto en clase.

Una nueva red con al menos 5 clases, 3 instancias y 6 atributos.

Instrucciones de ejecución

Crear un archivo de texto con la red semántica, por ejemplo red.txt:

es_un(Automóvil,Vehículo)
es_un(Bicicleta,Vehículo)
es_un(Deportivo,Automóvil)
instancia(FordFiesta,Automóvil)
instancia(Ferrari,Deportivo)
atributo(Vehículo,#ruedas,4)
atributo(Automóvil,vel/max,200km/h)
atributo(FordFiesta,color,blanco)
atributo(Ferrari,color,rojo)


Guardar el código en un archivo Python, por ejemplo taller.py.

Ejecutar el programa desde la terminal indicando el archivo de la red como parámetro:

python3 taller.py red.txt


Una vez cargada la red, escribir preguntas en la consola siguiendo estos formatos:

Consultar un atributo de una clase o instancia:

atributo <nombre_atributo> de <clase/instancia>?


Ejemplo:

atributo vel/max de Ferrari?
atributo color de FordFiesta?


Buscar clases o instancias con un atributo específico:

clases o instancias con atributo <nombre_atributo> y valor <valor>?


Ejemplo:

clases o instancias con atributo color y valor rojo?
clases o instancias con atributo #ruedas y valor 2?


Para salir, escribir:

salir
