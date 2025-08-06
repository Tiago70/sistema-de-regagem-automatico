#include "temperatura.h"
#include <Arduino.h>

static bool Temperatura::hora_de_medir = 0;

Temperatura::Temperatura(uint8_t pino)
  : Sensor(pino) {
}

void Temperatura::begin() {
  pinMode(this->pino, INPUT);
  this->oneWire = OneWire(this->pino);
  this->medidor = DallasTemperature(&(this->oneWire));
  this->medidor.begin();

  float temperatura = this->medir_agora();
  this->valorAtual = temperatura;
  this->valorMax = temperatura;
  this->valorMin = temperatura;
}

void Temperatura::ativar_medicao() {
  Temperatura::hora_de_medir = 1;
}

float Temperatura::medir_agora(){
  this->medidor.requestTemperatures();
  float temperatura = this->medidor.getTempCByIndex(0);
  this->valorAtual = temperatura;


  if (this->valorAtual > this->valorMax) this->valorMax = this->valorAtual;
  else if (this->valorAtual < this->valorMin) this->valorMin = this->valorAtual;

  return temperatura;
}

float Temperatura::medir() {
  if (Temperatura::hora_de_medir) {
    
    Temperatura::hora_de_medir = 0;
    return this->medir_agora();
  }

  return this->valorAtual;
}