## 1.1. Requisitos Funcionales

1. **Tablero**

   - Tablero de 8×8 casillas, jugando únicamente sobre las casillas negras.&#x20;

2. **Fichas**

   - Cada jugador dispone de 12 fichas situadas en las casillas negras más próximas a él.&#x20;

3. **Movimientos**

   - **Movimiento simple**: una posición en diagonal (adelante) a casilla vacía.
   - **Captura**: si hay ficha contraria en diagonal contigua y casilla vacía tras ella, saltar por encima y retirar la ficha.
   - **Captura múltiple**: tras cada salto válido, repetir mientras haya nuevas capturas posibles.&#x20;

4. **Promoción a dama**

   - Al llegar a la fila opuesta, la ficha se convierte en dama.
   - La dama puede moverse en diagonal una posición tanto hacia adelante como hacia atrás.&#x20;

5. **Prioridad de captura**

   - Las damas (y en general cualquier captura) tienen siempre prioridad sobre movimientos simples.&#x20;

6. **Finalización de la partida**

   - Un jugador pierde si se queda sin fichas o no puede realizar ningún movimiento en su turno.
   - La partida puede terminar en tablas si quedan pocas fichas de ambos y no hay forma de resolución.&#x20;

7. **Modos de juego**

   - Humano vs. Humano
   - Computadora vs. Humano
   - Computadora vs. Computadora
   - La IA siempre debe buscar el objetivo de vencer al adversario.&#x20;

8. **Interfaz de usuario**

   - Consola de comandos: tras cada jugada se muestra el estado actualizado del tablero.&#x20;

9. **Persistencia**

   - Guardar en un archivo de texto el resultado final de cada partida (fecha, jugadores, ganador y secuencia de movimientos).&#x20;

---

## 1.2. Requisitos No-Funcionales

- **Lenguaje y estándar**: C++17.
- **Arqui­tectura**: Modelo de 3 capas

  - **Presentación**: clases de UI en consola.
  - **Negocios**: lógica del juego (reglas, IA).
  - **Datos**: lectura/escritura de archivos.

- **Calidad de código**: comentarios estilo Doxygen, estilo uniforme y legible.
- **Documentación**: informe final con análisis, diagrama de clases, tabla de funciones y evaluación de complejidad del algoritmo de IA.&#x20;
