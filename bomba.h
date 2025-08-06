#ifndef __BOMBA_
#define __BOMBA_

class Bomba{
private:
  uint8_t pino;

public:
  Bomba(uint8_t pino);
  static bool estado;
  void begin();
  void liga_desliga();
  static void trocar_estado();
};

#endif