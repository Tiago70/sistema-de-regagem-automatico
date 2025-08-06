#ifndef __TEMPERATURA_
#define __TEMPERATURA_

#include "modelo.h"
#include <DallasTemperature.h>
#include <OneWire.h>
#include <stdint.h>

class Temperatura : public Sensor {
private:
  DallasTemperature medidor;
  OneWire oneWire;

public:
  Temperatura(uint8_t pino);
  static bool hora_de_medir;

  void begin() override;
  float medir_agora();
  static void ativar_medicao();
  float medir() override;
};
#endif