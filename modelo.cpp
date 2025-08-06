#include "modelo.h"

Sensor::Sensor(uint8_t pino){
  this->pino = pino;
  
  this->valorAtual = 0;
  this->valorMax = 0;
  this->valorMin = 0;
}