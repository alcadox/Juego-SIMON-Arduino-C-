// ==================== CONFIGURACIÓN ====================
const int NUM_LEDS = 4;
const int NUM_RONDAS = 20;

const int TIEMPO_MOSTRAR = 500;     // ms que se enciende cada led en la secuencia
const int TIEMPO_ENTRE_LEDS = 250;  // ms entre cada led
const int TIEMPO_ESPERA = 5000;     // ms máximo para pulsar
const int TIEMPO_PAUSA_RONDA = 1000;

// ==================== PINES ====================
int luces[NUM_LEDS] = {2, 3, 4, 5};
int pulsadores[NUM_LEDS] = {6, 7, 8, 9};
int sonidos = 10;

// ==================== VARIABLES ====================
int secuenciaAleatoria[NUM_RONDAS];
int secuenciaIntroducida[NUM_RONDAS];
int contadorAciertos = 0;
int contadorRonda = 0;

// ==================== SETUP ====================
void setup() {
  randomSeed(analogRead(A0));
  pinMode(sonidos, OUTPUT);

  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(luces[i], OUTPUT);
    pinMode(pulsadores[i], INPUT);
  }
}

// ==================== PRINCIPAL ====================
void loop() {
  contadorAciertos = 0;
  contadorRonda = 0;

  inicioJuego();

  while (contadorRonda < NUM_RONDAS) {
    delay(1000);
    contadorRonda++;
    int numeroRandom = random(0, NUM_LEDS);
    secuenciaAleatoria[contadorRonda - 1] = numeroRandom;

    // Mostrar secuencia
    mostrarSecuencia(contadorRonda);

    // Leer secuencia del jugador
    if (!leerSecuenciaJugador(contadorRonda)) {
      delay(300);
      perder();
      delay(500);
      parpadearAciertos(contadorAciertos);
      delay(1000);
      return; // termina el juego
    }

    // Si acierta
    delay(500);
    contadorAciertos++;
    acierto();
  }

  // Si llega a 20 rondas
  ganar();
}

// ==================== FUNCIONES ====================

void inicioJuego() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(luces[i], HIGH);
    reproducirSonido(i);
    delay(300);
    digitalWrite(luces[i], LOW);
  }
  delay(300);
  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    digitalWrite(luces[i], HIGH);
    reproducirSonido(i);
    delay(300);
    digitalWrite(luces[i], LOW);
  }
  delay(200);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < NUM_LEDS; j++) digitalWrite(luces[j], HIGH);
    tone(sonidos, 999, 200);
    delay(200);
    for (int j = 0; j < NUM_LEDS; j++) digitalWrite(luces[j], LOW);
    delay(200);
  }
}

void reproducirSonido(int indice) {
  switch (indice) {
    case 0: tone(sonidos, 200, TIEMPO_MOSTRAR); break;
    case 1: tone(sonidos, 400, TIEMPO_MOSTRAR); break;
    case 2: tone(sonidos, 600, TIEMPO_MOSTRAR); break;
    case 3: tone(sonidos, 800, TIEMPO_MOSTRAR); break;
  }
}

void mostrarSecuencia(int ronda) {
  for (int i = 0; i < ronda; i++) {
    int indice = secuenciaAleatoria[i];
    digitalWrite(luces[indice], HIGH);
    reproducirSonido(indice);
    delay(TIEMPO_MOSTRAR);
    digitalWrite(luces[indice], LOW);
    delay(TIEMPO_ENTRE_LEDS);
  }
}

bool leerSecuenciaJugador(int ronda) {
  int contadorLuzIntroducida = 0;
  unsigned long tiempoInicio = millis();

  while (contadorLuzIntroducida < ronda) {
    bool pulsado = false;
    for (int i = 0; i < NUM_LEDS; i++) {
      if (digitalRead(pulsadores[i]) == HIGH) {
        pulsado = true;
        digitalWrite(luces[i], HIGH);
        reproducirSonido(i);
        while (digitalRead(pulsadores[i]) == HIGH);
        digitalWrite(luces[i], LOW);

        secuenciaIntroducida[contadorLuzIntroducida] = i;
        contadorLuzIntroducida++;
        delay(100);

        // Reiniciar contador de tiempo tras una pulsación válida
        tiempoInicio = millis();
      }
    }

    // Si pasan más de 5 segundos sin pulsar => pierde
    if (millis() - tiempoInicio > TIEMPO_ESPERA) {
      return false;
    }
  }

  // Comparar secuencias
  for (int i = 0; i < ronda; i++) {
    if (secuenciaIntroducida[i] != secuenciaAleatoria[i]) {
      return false;
    }
  }
  return true;
}

void acierto() {
  for (int i = 0; i < NUM_LEDS; i++) digitalWrite(luces[i], HIGH);
  tone(sonidos, 1000, 400);
  delay(400);
  for (int i = 0; i < NUM_LEDS; i++) digitalWrite(luces[i], LOW);
  delay(TIEMPO_PAUSA_RONDA);
}

void perder() {
  tone(sonidos, 150, 800);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < NUM_LEDS; j++) digitalWrite(luces[j], HIGH);
    delay(200);
    for (int j = 0; j < NUM_LEDS; j++) digitalWrite(luces[j], LOW);
    delay(200);
  }
}

void ganar() {
  for (int i = 0; i < 3; i++) {
    tone(sonidos, 500 + (i * 300), 300);
    for (int j = 0; j < NUM_LEDS; j++) digitalWrite(luces[j], HIGH);
    delay(300);
    for (int j = 0; j < NUM_LEDS; j++) digitalWrite(luces[j], LOW);
    delay(300);
  }
  tone(sonidos, 1200, 600);
  delay(600);
}

void parpadearAciertos(int veces) {
  for (int i = 0; i < veces; i++) {
    for (int j = 0; j < NUM_LEDS; j++) digitalWrite(luces[j], HIGH);
    delay(200);
    for (int j = 0; j < NUM_LEDS; j++) digitalWrite(luces[j], LOW);
    delay(200);
  }
}
