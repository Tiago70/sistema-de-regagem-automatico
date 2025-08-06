#ifndef __DISPLAY_
#define __DISPLAY_

#include <stdint.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "bomba.h"
#include "temperatura.h"
#include "condutivimetro.h"
#include "luminosidade.h"


#define NUMERO_DE_TELAS 2

class Display {
private:
  uint16_t largura;
  uint16_t altura;

  uint8_t telaAtual;
  void (Display::*telas[NUMERO_DE_TELAS])();
  LiquidCrystal_I2C *lcd;

  Temperatura* temp_sensor;
  Condutivimetro* condut_sensor;
  Luminosidade* lumin_sensor;
  Bomba *bomba_regagem;

  byte seta_para_cima[8]{
    0b00100,
    0b01010,
    0b10101,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00000
  };

  byte seta_para_baixo[8] = {
    0b00000,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b10101,
    0b01010,
    0b00100
  };

public:
  bool trocar_tela;
  Display(uint8_t largura, uint8_t altura);
  void begin(Temperatura *temperatura, Condutivimetro *condutividade, Luminosidade *luminosidade, Bomba *bomba_regagem);

  static void autorizar();
  static bool atualizar_tela_var;
  int para_esquerda(String texto);
  void tela1();
  void tela2();

  void printReverso(String texto, int coluna, int linha);
  void trocarTela(bool *trocar);
  void atualizar_tela();
};

#endif