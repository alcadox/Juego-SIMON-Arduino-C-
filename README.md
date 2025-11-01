# Juego SIMÓN con Arduino

Este proyecto implementa el clásico juego **SIMÓN** usando Arduino, LEDs, pulsadores y un buzzer.  
El objetivo del juego es repetir correctamente la secuencia de colores y sonidos generada por el sistema.

---

## 🎮 Componentes

- 1 Arduino (Uno, Nano, etc.)
- 4 LEDs de colores
- 4 pulsadores
- 1 buzzer
- Resistencias para LEDs y pulsadores
- Cables de conexión y protoboard

---

## ⚡ Conexiones

| Componente | Pin en Arduino |
|-----------|----------------|
| LED 1     | 2              |
| LED 2     | 3              |
| LED 3     | 4              |
| LED 4     | 5              |
| Pulsador 1| 6              |
| Pulsador 2| 7              |
| Pulsador 3| 8              |
| Pulsador 4| 9              |
| Buzzer    | 10             |

> Se puede cambiar fácilmente los pines modificando los arreglos `luces[]`, `pulsadores[]` y la variable `sonidos` en el código.

---

## ⏱ Configuración de tiempos

Todos los tiempos se definen como constantes para poder modificarlos fácilmente:

```cpp
const int NUM_LEDS = 4;
const int NUM_RONDAS = 20;
const int TIEMPO_MOSTRAR = 500;     // ms que se enciende cada led
const int TIEMPO_ENTRE_LEDS = 250;  // ms entre leds
const int TIEMPO_ESPERA = 5000;     // ms máximo para pulsar
const int TIEMPO_PAUSA_RONDA = 1000;
````

# Funcionamiento

## Inicio del juego:

- Los LEDs se encienden en una secuencia inicial con sonido para indicar que el juego empieza.

## Generación de la secuencia:

- Se genera aleatoriamente un color por ronda hasta un máximo de 20 rondas.

## Mostrar la secuencia:

Cada LED se enciende con su sonido correspondiente por TIEMPO_MOSTRAR.

- Pausa entre LEDs: TIEMPO_ENTRE_LEDS.

## Interacción del jugador:

- El jugador debe pulsar los botones en el mismo orden que la secuencia mostrada.

- Cada pulsación activa el LED y su sonido mientras se mantiene pulsado.

- Tiempo máximo para pulsar cada color: TIEMPO_ESPERA.

## Verificación:

- Si el jugador acierta, se genera un efecto de acierto con todos los LEDs y un sonido.

- Si el jugador falla o se pasa el tiempo, se reproduce un sonido de pérdida y los LEDs parpadean tantas veces como rondas correctas haya completado.

## Victoria:

- Si se completan las 20 rondas, se reproduce un efecto de victoria con sonido y LEDs.

## 🔹 Funciones principales

| Función | Descripción |
|---------|-------------|
| `inicioJuego()` | Muestra una secuencia de LEDs y sonidos al iniciar el juego. |
| `mostrarSecuencia(int ronda)` | Muestra la secuencia generada hasta la ronda actual. |
| `leerSecuenciaJugador(int ronda)` | Lee la secuencia introducida por el jugador y verifica si es correcta. |
| `reproducirSonido(int indice)` | Reproduce el sonido correspondiente a cada color. |
| `acierto()` | Indica un acierto del jugador con sonido y LEDs. |
| `perder()` | Genera el sonido y parpadeo al fallar el jugador. |
| `ganar()` | Genera el efecto de victoria si se completan todas las rondas. |
| `parpadearAciertos(int veces)` | Parpadea los LEDs tantas veces como rondas acertadas antes de perder. |
