#include "Arduino.h"
#include "bomba.h"

bool Bomba::estado = 0;

Bomba::Bomba(uint8_t pino){
  this->pino = pino;
}

void Bomba::begin(){
  pinMode(this->pino, OUTPUT);
}

void Bomba::trocar_estado(){
  Bomba::estado = !Bomba::estado;
}

void Bomba::liga_desliga(){
  if (Bomba::estado){
    digitalWrite(this->pino, 1);
  }
  else {
    digitalWrite(this->pino, 0);
  }
}