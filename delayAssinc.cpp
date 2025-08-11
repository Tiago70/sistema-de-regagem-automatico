#include "Arduino.h"
#include "delayAssinc.h"
#include "relogio.h"

DelayAssinc::DelayAssinc() {
  tamanho_atual_simples = 0;
  tamanho_atual_composto = 0;
}

void DelayAssinc::verificar() {
  uint32_t tempo_atual = millis();

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

  /* mudar isso quando houver mais de um delay composto*/
  uint32_t tempo_atual = millis();

  if (this->lista_composta[0].delayAtual){
    return (this->lista_composta[0].delay2 + this->lista_composta[0].ultimo_delay) - tempo_atual;
  }
  else {
    return (this->lista_composta[0].delay1 + this->lista_composta[0].ultimo_delay) - tempo_atual;
  }
}

/*
Não é necessário lembrar quando o sensor mediu pela última vez,
já que sempre que o arduino liga ele já faz uma medição automáticamente
*/
void DelayAssinc::novoDelayMillis(String nome, void (*funcao)(), uint32_t delay) {
  // último delay iniciando com 0
  lista_simples[tamanho_atual_simples] = { nome, funcao, delay, 0 };
  tamanho_atual_simples++;
}

void DelayAssinc::novoDelayMillis(String nome, void (*funcao)(), uint32_t delay1, uint32_t delay2) {
  // último delay iniciando com 0
  lista_composta[tamanho_atual_composto] = { nome, funcao, delay1, delay2, 0, 0 };
  tamanho_atual_composto++;
}

DelayAssinc DelayAssincrono;