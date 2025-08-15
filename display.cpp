#include "display.h"
#include "delayAssinc.h"
#include "relogio.h"

bool Display::atualizar_tela_var = 0;

void Display::autorizar() {
  Display::atualizar_tela_var = 1;
}

Display::Display(uint8_t largura, uint8_t altura) {
  this->largura = largura;
  this->altura = altura;

  this->telas[0] = &Display::tela1;
  this->telas[1] = &Display::tela2;

  this->telaAtual = 0;
}

void Display::begin(Temperatura *temperatura, Condutivimetro *condutividade, Luminosidade *luminosidade, Bomba *bomba_regagem) {
  this->temp_sensor = temperatura;
  this->lumin_sensor = luminosidade;
  this->condut_sensor = condutividade;

  this->bomba_regagem = bomba_regagem;

  this->lcd = new LiquidCrystal_I2C(0x27, this->largura, this->altura);
  this->lcd->init();
  this->lcd->backlight();
  this->lcd->clear();
  this->lcd->noCursor();

  this->lcd->createChar(0, this->seta_para_cima);
  this->lcd->createChar(1, this->seta_para_baixo);
}

void Display::atualizar_tela() {
  if (!Display::atualizar_tela_var) return;

  Display::atualizar_tela_var = 0;
  if (this->trocar_tela){
    if (this->telaAtual == NUMERO_DE_TELAS-1) this->telaAtual = 0;
    else this->telaAtual++;
    this->trocar_tela = 0;
    this->lcd->clear();
  }
  (this->*telas[this->telaAtual])();
}

String Display::formatar_valor(String texto) {
  char buffer[8];
  sprintf(buffer, "%7s", texto.c_str());
  return buffer;
}

void Display::tela1() {
  String temperatura, condutividade, luminosidade;
  temperatura = String(this->temp_sensor->valorAtual);
  condutividade = String(this->condut_sensor->valorAtual);
  luminosidade = String(this->lumin_sensor->valorAtual);

  this->lcd->home();
  this->lcd->print("Temp");
  this->lcd->setCursor(13, 0);
  this->lcd->print(this->formatar_valor(temperatura));

  this->lcd->setCursor(0, 1);
  this->lcd->print("Condut");
  this->lcd->setCursor(13, 1);
  this->lcd->print(this->formatar_valor(condutividade));

  this->lcd->setCursor(0, 2);
  this->lcd->print("Luz");
  this->lcd->setCursor(13, 2);
  this->lcd->print(this->formatar_valor(luminosidade));

  this->lcd->setCursor(0, 3);
  String tempo_bomba;
  if (!this->bomba_regagem->estado) {
    tempo_bomba = relogio.formatarSeg(DelayAssincrono.tempo_restante_comp("bomba") / 1000);
    this->lcd->print("Em espera");
    this->lcd->setCursor(12, 3);
    this->lcd->print(tempo_bomba);
  } else {
    tempo_bomba = relogio.formatarSeg(DelayAssincrono.tempo_restante_comp("bomba") / 1000);
    this->lcd->print("Regando  ");
    this->lcd->setCursor(12, 3);
    this->lcd->print(tempo_bomba);
  }
}

// depois eu faço

void Display::tela2() {
  String temperaturaMax, condutividadeMax, luminosidadeMax;
  String temperaturaMin, condutividadeMin, luminosidadeMin;

  temperaturaMax = String(this->temp_sensor->valorMax);
  temperaturaMin = String(this->temp_sensor->valorMin);
  
  condutividadeMax = String(this->condut_sensor->valorMax);
  condutividadeMin = String(this->condut_sensor->valorMin);

  luminosidadeMax = String(this->lumin_sensor->valorMax);
  luminosidadeMin = String(this->lumin_sensor->valorMin);

  // temperatura
  this->lcd->home();
  this->lcd->print("T: ");
  this->lcd->write(byte(0));

  this->lcd->setCursor(12, 0);
  this->lcd->write(byte(1));

  this->lcd->setCursor(4, 0);
  this->lcd->print(this->formatar_valor(temperaturaMax));

  this->lcd->setCursor(13, 0);
  this->lcd->print(this->formatar_valor(temperaturaMin ));

  // condutividade
  this->lcd->setCursor(0, 1);
  this->lcd->print("C: ");
  this->lcd->write(byte(0));

  this->lcd->setCursor(12, 1);
  this->lcd->write(byte(1));

  this->lcd->setCursor(4, 1);
  this->lcd->print(this->formatar_valor(condutividadeMax));

  this->lcd->setCursor(13, 1);
  this->lcd->print(this->formatar_valor(condutividadeMin));

  // luminosidade
  this->lcd->setCursor(0, 2);
  this->lcd->print("L: ");
  this->lcd->write(byte(0));

  this->lcd->setCursor(12, 2);
  this->lcd->write(byte(1));

  this->lcd->setCursor(4, 2);
  this->lcd->print(this->formatar_valor(luminosidadeMax));

  this->lcd->setCursor(13, 2);
  this->lcd->print(this->formatar_valor(luminosidadeMin));

  // tempo atual
  this->lcd->setCursor(0, 3);
  this->lcd->print("Hora:   Indisponivel");

  /*adiicionar o horário do rtc quando o relógioestiver disponível*/
  // this->lcd->setCursor(0, 11);
  // this->lcd->print(relogio.getTempoString());
}