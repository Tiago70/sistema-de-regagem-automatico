#include "delayAssinc.h"
#include "condutivimetro.h"
#include "temperatura.h"
#include "luminosidade.h"
#include "bomba.h"
#include "cartaoSD.h"
#include "display.h"

// adicionar a biblioteca quando utilar o rtc
// #include "relogio.h"

Temperatura temp_sensor(2);
Condutivimetro condut_sensor(13, &temp_sensor);
Luminosidade lumin_sensor(12);
Bomba bomba_regagem(5);
Display tela(20, 4);
cartaoSD micro_SD(53);

void trocar_tela(){
  tela.trocar_tela = 1;
}

void setup() {
  // remover o comentário do begin quando utilizar o rtc
  // relogio.begin(0, 1, 2);

  // iniciando os sensores e o lcd
  temp_sensor.begin();
  lumin_sensor.begin();
  condut_sensor.begin();
  tela.begin(&temp_sensor, &condut_sensor, &lumin_sensor, &bomba_regagem);

  // definindo os intervalos (valor em milisegundos)
  DelayAssincrono.novoDelaySeg("temperatura", temp_sensor.ativar_medicao, 5);
  DelayAssincrono.novoDelaySeg("condutividade", condut_sensor.ativar_medicao, 5);
  DelayAssincrono.novoDelaySeg("luminosidade", lumin_sensor.ativar_medicao, 5);
  DelayAssincrono.novoDelaySeg("boma", bomba_regagem.trocar_estado, 5, 10);
  DelayAssincrono.novoDelaySeg("Cartao SD", micro_SD.autorizar_anotacao, 5);
  DelayAssincrono.novoDelaySeg("tela", tela.autorizar, 1);

  // interrupção para o botão de trocar de tela
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), trocar_tela, FALLING);

  micro_SD.novo_arquivo("dados");
  micro_SD.escrever("dados", "Temperatura,Luminosidade,Condutividade\n");
}

void loop() {
  // chamada das verificações e medições
  DelayAssincrono.verificar();
  temp_sensor.medir();
  condut_sensor.medir();
  lumin_sensor.medir();
  bomba_regagem.liga_desliga();
  tela.atualizar_tela();
  // micro_SD.anotar_dados("dados", temp_sensor.medir_agora(), lumin_sensor.medir_agora(), condut_sensor.medir_agora());
}
