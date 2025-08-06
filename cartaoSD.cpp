#include "cartaoSD.h"

#include <SD.h>

bool cartaoSD::hora_de_anotar = 0;

cartaoSD::cartaoSD(uint8_t pino){
  this->pino = pino;
}

void cartaoSD::begin(){
  
  SD.begin(this->pino);
}

bool cartaoSD::novo_arquivo(String nome){
  if (SD.exists(nome)){
    SD.remove(nome);
  }

  File arquivo = SD.open(nome, FILE_WRITE);
  if (arquivo){
    arquivo.close();
    return true;
  }
  return false;
}

bool cartaoSD::escrever(String arquivo, String texto){
  File arq = SD.open(arquivo);

  if (arq){
    arq.print(texto);
    arq.close();
    return true;
  }
  return false;
}

void cartaoSD::autorizar_anotacao(){
  cartaoSD::hora_de_anotar = 1;
}

void cartaoSD::anotar_dados(String arquivo, float temperatura, float luminosidade, float condutividade){
  if (!hora_de_anotar) return;

  File arq = SD.open(arquivo);
  String conteudo =  String(String(temperatura) + "," + String(luminosidade) + "," + String(condutividade));
  arq.println(conteudo);
  arq.close();

  hora_de_anotar = 0;
}