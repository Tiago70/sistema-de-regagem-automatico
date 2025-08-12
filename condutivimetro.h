#ifndef __CONDUTIVIMETRO_
#define __CONDUTIVIMETRO_

#include "modelo.h"
#include "temperatura.h"

class Condutivimetro : public Sensor{
private:
  // atributos para o calculo da condutividade
  uint8_t Vin = 5;                    // valor da entrada em volts (5v do arduino)
  float K = 0.996;                    // valor médio do coeficiente K
  float temp_coeficiente = 0.015;     // também é um valor médio
  uint16_t resistorPadrao = 1000;     // valor em Ohms
  
  Temperatura* sensor_temperatura;

public:
  Condutivimetro(uint8_t pino, Temperatura* temperatura);
  
  // variável indicando o estado
  static bool hora_de_medir;

  void begin() override;
  float medir_agora();
  static void ativar_medicao();
  float medir() override;
};

#endif