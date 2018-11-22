/*
	Proyecto final de Seminario Taller III Multimedia 2018.
	Universidad Nacional del Nordeste. 
	Facultad de Artes, Diseño y Ciencias de la Cultura.
	Licenciatura en Artes Combinadas.

	Las tiras de leds se prenden al detectar un objeto cercano al sensor.

	Copyleft 2018.
	- Schaller, Carolina
	- Delset, Valeria
	- Colcombet, Lelis
  -------------------------------------------------------------------------
	Licence GPL v3

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


//Constantes para el pre-procesador
#define VELOCIDAD_DE_COMUNICACION 9600
//Constantes y variables para el sensor
#define ECHO 6
#define TRIG 7
int distancia;
//Constantes para el programa
//Definimos velocidad de prendido en intensidad/milisegundo
const int velocidadDePrendido = 3;
const int velocidadDeApagado = 3;
//Definimos tiempo de espera entre detecciones de distancia en milisegundos
const int tiempoDeEsperaEntreDetecciones = 100;
//Definimos intensidades de led
const int intensidadMinima = 0;
const int intensidadMaxima = 255;
//Definimos rango entre el cual el efecto escalera comienza
const int distanciaMinima = 1;
const int distanciaMaxima = 300;

//Declaro una lista de numeros aleatorios con los pines donde van los leds
int listaDePines[] = { 8,9,10,11 };
const int cantidadDePines = (sizeof(listaDePines)/sizeof(*listaDePines));

void setup() {
  Serial.begin(VELOCIDAD_DE_COMUNICACION);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
}

void mezclarListaDePines() {
  for (int i = 1; i <= cantidadDePines; i++) {
    int r = random(0, cantidadDePines-i);
    intercambiarPosicion(r, cantidadDePines-i);
  }
}

void intercambiarPosicion(int a, int b) {
  int resguardo = listaDePines[a];
  listaDePines[a] = listaDePines[b];
  listaDePines[b] = resguardo;
}

void loop() {
  delay(tiempoDeEsperaEntreDetecciones);
  
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);   // genera el pulso de triger por 10ms
  delayMicroseconds(10);

  distancia = pulseIn(ECHO, HIGH);
  distancia = (distancia / 2) / 29;   // calcula la distancia en centimetros

 if (distancia >= distanciaMinima && distancia <= distanciaMaxima) {
    //Mezclamos lista de pines y prendemos leds aleatoriamente
    mezclarListaDePines();
    for (int pin = 0; pin < cantidadDePines; pin++) {
      for (int i = intensidadMinima; i <= intensidadMaxima; i++) {
        analogWrite(listaDePines[pin], i);
        delay(velocidadDePrendido); 
      }
    }
    //Mezclamos lista de pines y apagamos leds aleatoriamente
    mezclarListaDePines();
    for (int pin = 0; pin < cantidadDePines; pin++) {
      for (int i = intensidadMaxima; i >= intensidadMinima; i--) {
        analogWrite(listaDePines[pin], i);
        delay(velocidadDeApagado); 
      }
    }
  }
}

