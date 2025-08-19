# Introducción a la IA - Problema de las Jarras de Agua  

Este proyecto aborda el **problema clásico de las jarras de agua**, utilizado como ejercicio de representación y resolución de problemas en Inteligencia Artificial (IA).  

El reto consiste en modelar el problema utilizando la metodología basada en el **espacio de estados**, identificando sus componentes fundamentales, los operadores que permiten transitar entre estados y los posibles caminos de solución hasta alcanzar la meta definida.  

El objetivo central es lograr que, partiendo del estado inicial en el que ambas jarras están vacías, se alcancen estados donde la jarra de 5 litros contenga **exactamente 2 litros de agua**.  

Para ello, se emplea la formulación de operadores válidos, la generación del espacio de estados y la definición de una **función heurística**, que permitirá al algoritmo **Best First Search** seleccionar de manera prioritaria aquellos estados que se encuentran más próximos a la meta.  

---

## Metodología de resolución de problemas  

### 1. Variables significativas y sus valores posibles  
- **Jarra de 4L (J4):** 0 (vacía), 1, 2, 3, 4 (llena)  
- **Jarra de 5L (J5):** 0 (vacía), 1, 2, 3, 4, 5 (llena)  

### 2. Componentes del estado  
El estado se representa mediante un par ordenado `(J4, J5)`, donde:  
- `J4` → cantidad de agua en la jarra de 4 litros (0 a 4).  
- `J5` → cantidad de agua en la jarra de 5 litros (0 a 5).  

Ejemplos:  
- `(0,0)` → ambas jarras vacías.  
- `(4,2)` → J4 llena y J5 con 2 litros.  

### 3. Estado inicial y estado final  
- **Inicial:** `(0,0)` → ambas jarras vacías.  
- **Final:** `(J4,2)` → cualquier estado válido donde `J5 = 2`.  

### 4. Acciones que cambian de estado  
- **Llenar(Jᵢ):** llenar una jarra hasta su capacidad.  
- **Vaciar(Jᵢ):** vaciar completamente una jarra.  
- **Trasvasar(Jᵢ → Jⱼ):** pasar agua de una jarra a otra hasta vaciar el origen o llenar el destino.  

### 5. Operadores con precondiciones y consecuencias  
- **Llenar J4:** `(J4’, J5’) = (4, J5)` si `J4 < 4`.  
- **Llenar J5:** `(J4’, J5’) = (J4, 5)` si `J5 < 5`.  
- **Vaciar J4:** `(J4’, J5’) = (0, J5)` si `J4 > 0`.  
- **Vaciar J5:** `(J4’, J5’) = (J4, 0)` si `J5 > 0`.  
- **Trasvasar J4→J5:** `(J4’, J5’)` según traspaso máximo posible.  
- **Trasvasar J5→J4:** `(J4’, J5’)` según traspaso máximo posible.  

### 6. Espacio de estados  
- **J4:** valores posibles → {0,1,2,3,4}  
- **J5:** valores posibles → {0,1,2,3,4,5}  
- **Total de combinaciones:** 30 estados posibles.  
- **Estados válidos:** 18  
- **Estados imposibles:** 12  

---

## Función heurística  

La función heurística utilizada no solo mide la diferencia directa entre el contenido de la jarra de 5 litros y el objetivo de 2 litros, sino que también evalúa los estados alcanzables tras verter entre jarras.  

La heurística se define como:  

\[
h(x, y) = \min( |y - 2|, |(y + \Delta4 \to 5) - 2|, |(y - \Delta5 \to 4) - 2| )
\]  

Donde:  
- `J4` → cantidad de agua en la jarra de 4 litros.  
- `J5` → cantidad de agua en la jarra de 5 litros.  
- `Δ4→5` → cantidad máxima que puede transferirse de la jarra de 4L a la de 5L.  
- `Δ5→4` → cantidad máxima que puede transferirse de la jarra de 5L a la de 4L.  

La heurística toma el **mínimo** de estos tres valores, reflejando siempre el estado más prometedor alcanzable en un solo movimiento.  

---

## Implementación  

El proyecto fue implementado en **C++**, aplicando el algoritmo **Best First Search** con la heurística definida para guiar la exploración.  

---

## Conclusión  

Este proyecto muestra cómo una representación adecuada y una heurística bien diseñada permiten al algoritmo **Best First Search** resolver el problema de manera más eficiente, evitando exploraciones innecesarias y priorizando los estados más cercanos a la meta.  
