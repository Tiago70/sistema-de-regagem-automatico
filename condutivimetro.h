#ifndef __CONDUTIVIMETRO_
#define __CONDUTIVIMETRO_

#include "modelo.h"
#include "temperatura.h"

class Condutivimetro : public Sensor{
private:
  // atributos para o calculo da condutividade
  uint8_t Vin;
  float K;
  float temp_coeficiente;
  uint16_t resistorPadrao;
  Temperatura* sensor_temperatura;

public:
  Condutivimetro(uint8_t pino, Temperatura* temperatura);
  static bool hora_de_medir;

  void begin() override;
  float medir_agora();
  static void ativar_medicao();
  float medir() override;
};

#endif