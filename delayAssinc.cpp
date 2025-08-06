#include "Arduino.h"
#include "delayAssinc.h"
#include "relogio.h"

DelayAssinc::DelayAssinc() {
  tamanho_atual_simples = 0;
  tamanho_atual_composto = 0;

  tempo_atual_ts = relogio.timestamp();
}

void DelayAssinc::verificar() {
  uint32_t tempo_atual = this->tempo_atual_ts + (millis() / 1000);

  // verificação da lista simples
  for (int i = 0; i < tamanho_atual_simples; i++) {
    if (tempo_atual - lista_simples[i].ultimo_delay >= lista_simples[i].delay) {
      lista_simples[i].ultimo_delay = tempo_atual;
      lista_simples[i].funcao();
    }
  }

  // verificação da lista composta
  for (int i = 0; i < tamanho_atual_composto; i++) {

    // verifica se o delay ativo é o primeiro ou o segundo (0 para o primerio, 1 para o segundo)
    if (!lista_composta[i].delayAtual) {
      if (tempo_atual - lista_composta[i].ultimo_delay >= lista_composta[i].delay1) {
        lista_composta[i].delayAtual = 1;
        lista_composta[i].ultimo_delay = tempo_atual;
        lista_composta[i].funcao();
      }
    }

    else {
      if (tempo_atual - lista_composta[i].ultimo_delay >= lista_composta[i].delay2) {
        lista_composta[i].delayAtual = 0;
        lista_composta[i].ultimo_delay = tempo_atual;
        lista_composta[i].funcao();
      }
    }
  }
}

uint32_t DelayAssinc::tempo_restante_comp(String nome){
  // usando o indice direto por só existir a bomba de delay composto
  // mudar isso quando houver mais de um
  uint32_t tempo_atual = this->tempo_atual_ts + (millis() / 1000);

  if (this->lista_composta[0].delayAtual){
    return (this->lista_composta[0].delay2 + this->lista_composta[0].ultimo_delay) - tempo_atual;
  }
  else {
    return (this->lista_composta[0].delay1 + this->lista_composta[0].ultimo_delay) - tempo_atual;
  }
}

/*
LEMBRAR DE ARMAZENAR O ULTIMO DELAY NO CARTÃO SD
PELO AMOR DE DEUS
*/
void DelayAssinc::novoDelaySeg(String nome, void (*funcao)(), uint32_t delay) {
  // trocar esse 0 pelo tempo do rtc
  lista_simples[tamanho_atual_simples] = { nome, funcao, delay, 0 };
  tamanho_atual_simples++;
}

void DelayAssinc::novoDelaySeg(String nome, void (*funcao)(), uint32_t delay1, uint32_t delay2) {
  // trocar esse 0 pelo tempo do rtc
  lista_composta[tamanho_atual_composto] = { nome, funcao, delay1, delay2, 0, 0 };
  tamanho_atual_composto++;
}

DelayAssinc DelayAssincrono;