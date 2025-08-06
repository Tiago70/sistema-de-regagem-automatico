#ifndef __CARTAO_SD_
#define __CARTAO_SD_

#include <stdint.h>
#include <Arduino.h>

class cartaoSD{
private:
  uint8_t pino;

public:
  cartaoSD(uint8_t pino);
  static bool hora_de_anotar;

  void begin();
  bool novo_arquivo(String nome);
  bool escrever(String arquivo, String texto);

  static void autorizar_anotacao();
  void anotar_dados(String arquivo, float temperatura, float luminosidade, float condutividade);
};

#endif