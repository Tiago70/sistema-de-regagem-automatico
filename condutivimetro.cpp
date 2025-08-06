#include "condutivimetro.h"
#include <Arduino.h>

bool Condutivimetro::hora_de_medir = 0;

Condutivimetro::Condutivimetro(uint8_t pino, Temperatura* temperatura)
  : Sensor(pino) {
  this->sensor_temperatura = temperatura;
}

void Condutivimetro::begin() {
  pinMode(this->pino, INPUT);

  float condutividade = medir_agora();
  this->valorAtual = condutividade;
  this->valorMax = condutividade;
  this->valorMin = condutividade;
}

void Condutivimetro::ativar_medicao() {
  Condutivimetro::hora_de_medir = 1;
}

float Condutivimetro::medir_agora() {
  float vout = analogRead(this->pino);
  vout = (float)vout / 1023 * this->Vin;

  float resistencia = this->resistorPadrao * (vout / (this->Vin - vout));

  float condutividade = this->resistorPadrao / (resistencia * K);
  Temperatura::hora_de_medir = 1;
  condutividade = condutividade * (1 / (1 + this->temp_coeficiente * (this->sensor_temperatura->medir() - 25)));

  this->valorAtual = condutividade;
  if (this->valorAtual > this->valorMax) this->valorMax = this->valorAtual;
  else if (this->valorAtual < this->valorMin) this->valorMin = this->valorAtual;

  return condutividade;
}

float Condutivimetro::medir() {
  if (Condutivimetro::hora_de_medir) {
    Condutivimetro::hora_de_medir = 0;
    return this->medir_agora();
  }

  return this->valorAtual;
}