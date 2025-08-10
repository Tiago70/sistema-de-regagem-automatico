/*
Relógio usado para registro dos horários das medições.

Também pode ser usado para agendar regagens e lembrar regagens.
*/

#include <stdint.h>
#ifndef __RELOGIO_
#define __RELOGIO_

#include <Arduino.h>
#include <Ds1302.h>

class relogioObj{
private:
  Ds1302* rtc = nullptr;

public:
  void begin(int CE, int IO, int CLK);
  String getTempoString();
  uint32_t timestamp();
};

extern relogioObj relogio;

#endif