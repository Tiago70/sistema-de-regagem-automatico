/*
Objeto modelo para os sensores, este código define
um comportamento padrão para todos os sensores.

Todas as classes de sensores herdam desse modelo.
*/

#ifndef __SENSOR_MODELO_
#define __SENSOR_MODELO_

#include <stdint.h>

class Sensor {
protected:
  uint8_t pino;

public:
  // valores medidos pelo sensor
  float valorAtual;
  float valorMax;
  float valorMin;

public:
  Sensor(uint8_t pino);

  // função para iniciar as portas
  virtual void begin() = 0;

  // funções de medição padrão
  virtual float medir() = 0;
  virtual float medir_agora() = 0;
};

#endif