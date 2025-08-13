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

  // variáveis de controle do lcd e telas
  uint8_t telaAtual;
  void (Display::*telas[NUMERO_DE_TELAS])();
  LiquidCrystal_I2C *lcd;

  // ponteiros para os sensores e bomba
  Temperatura* temp_sensor;
  Condutivimetro* condut_sensor;
  Luminosidade* lumin_sensor;
  Bomba *bomba_regagem;

  // carcateres especiais de seta
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
  Display(uint8_t largura, uint8_t altura);
  void begin(Temperatura *temperatura, Condutivimetro *condutividade, 
    Luminosidade *luminosidade, Bomba *bomba_regagem);
  bool trocar_tela;

  // método estático para atualizar o trocador de tela
  static void autorizar();
  static bool atualizar_tela_var;

  // função chamada quando a variável de troca for verdadeira
  // volta para a primeira tela quando estiver na última
  void trocarTela(bool *trocar);

  // função chamada para atualizar os valores da tela (Hz)
  // os Hz da tela depende do delay colocado na função de
  // atualização da tela no arquivo .ino, o padrão é 2 Hz
  void atualizar_tela();

  // modelo das telas
  void tela1();
  void tela2();

  // funções para formatação
  String formatar_valor(String texto);
  void printReverso(String texto, int coluna, int linha);
};

#endif