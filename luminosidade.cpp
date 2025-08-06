#include "luminosidade.h"
#include <Arduino.h>

static bool Luminosidade::hora_de_medir = 0;

Luminosidade::Luminosidade(uint8_t pino)
  : Sensor(pino) {
}

void Luminosidade::begin() {
  pinMode(this->pino, INPUT);

  float luminosidade = medir_agora();
  this->valorAtual = luminosidade;
  this->valorMax = luminosidade;
  this->valorMin = luminosidade;
}

void Luminosidade::ativar_medicao() {
  Luminosidade::hora_de_medir = 1;
}

float Luminosidade::medir_agora() {
  float luminosidade = (float)analogRead(this->pino);
  this->valorAtual = luminosidade;

  if (this->valorAtual > this->valorMax) this->valorMax = this->valorAtual;
  else if (this->valorAtual < this->valorMin) this->valorMin = this->valorAtual;

  return luminosidade;
}

float Luminosidade::medir() {
  if (Luminosidade::hora_de_medir) {

    Luminosidade::hora_de_medir = 0;
    return this->medir_agora();
  }

  return this->valorAtual;
}