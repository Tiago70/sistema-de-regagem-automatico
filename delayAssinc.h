#ifndef __DELAY_ASSINC_
#define __DELAY_ASSINC_

#include <stdint.h>
#include <Arduino.h>

// tamanho dos vetores de funções (estático para ser mais simples)
#define LISTA_SIMPLES 5
#define LISTA_COMPOSTA 1

// um delay com intervalos constantes
typedef struct {
  String nome;
  void (*funcao)();
  uint32_t delay;
  uint32_t ultimo_delay;
} delay_simples;

// um delay com intervalos alternados (alterna entre o delay1 e delay2)
// útil para deixar a bomba ligada por um certo tempo e desligada em outro
typedef struct {
  String nome;
  void (*funcao)();
  uint32_t delay1;
  uint32_t delay2;
  bool delayAtual;          // 0 para o delay1, 1 para o delay2
  uint32_t ultimo_delay;
} delay_composto;

// objeto para controle dos intervalos
class DelayAssinc{
private:
  uint32_t tempo_atual_ts;

  delay_simples lista_simples[LISTA_SIMPLES];
  uint8_t tamanho_atual_simples;

  delay_composto lista_composta[LISTA_COMPOSTA];
  uint8_t tamanho_atual_composto;
  
public:
  DelayAssinc();
  void verificar();
  uint32_t tempo_restante_comp(String nome);

  void novoDelaySeg(String nome, void (*funcao)(), uint32_t delay);
  void novoDelaySeg(String nome, void (*funcao)(), uint32_t delay1, uint32_t delay2);
};

extern DelayAssinc DelayAssincrono;
#endif