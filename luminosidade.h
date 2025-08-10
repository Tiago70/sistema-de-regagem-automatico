#ifndef __LUMINOSIDADE_
#define __LUMINOSIDADE_

#include "modelo.h"
#include <stdint.h>

class Luminosidade : public Sensor{
public:
  Luminosidade(uint8_t pino);

  // variável indicando o estado
  static bool hora_de_medir;

  void begin() override;
  float medir_agora();
  static void ativar_medicao();
  float medir() override;
};

#endif