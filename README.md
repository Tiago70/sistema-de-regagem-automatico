# Sistema de regagem automático com Arduino

Este é um projeto feito para a cultivação de hortaliças de forma hidropônica (sem a utilização de terra). Para isso o sistema conta com sensores de condutividade, temperatura e luminosidade para monitorar o nível de nutrientes e qualidade da água.

Este modelo também pode ser usado para a cultivação tradicional utilizando terra, podendo adicionar ou remover sensores para se adequar ao que você precisar.

## Funcionalidades
O sistema rega e mede as informações da água com base em intervalos fixos, você define no código o intervalo de cada componente, podendo escolher quantas regagens e quantas medições serão feitas por dia.

Para melhorar o monitoramento, foi incluso um cartão SD e uma tela LCD, o cartão guarda os valores dos sensores e o LCD mostra tudo, tanto os valores quanto os intervalos entre as regagens, e novamente, você escolhe quantas vezes por dia o cartão SD guardará as informações e quantas vezes por segundo o LCD irá atualizar (Hz), tudo pelo código. Com base nos dados do cartão SD, você pode fazer pequenas análises e descobrir se precisa ou se pode melhorar o ambiente para as suas hortaliças.

Por último, também foi incluso um relógio RTC para que futuramente seja possível agendar regagens ou medições com base no horário real e não apenas em intervalos constantes.

## Sobre o programa
Para gerenciar tudo isso de forma que não travasse o Arduino, foi utilizado o conceito de máquinas de estado, onde todos os componentes (sensores, LCD, SD, bomba d’água) são objetos com um atributo que representa o estado de “rodar” e “não rodar”.

Agora para criar intervalos que ativam e desativam o estado dos componentes, foi feito um tipo de lista, contento os atributos que representam o tempo de espera e as funções que serão chamadas quando o intervalo estiver passado, essa lista foi feita no arquivo delayAssinc.h e delayAssinc.cpp, caso você queira alterar como os intervalos funcionam, dê uma olhada nesses dois arquivos.
O LCD trabalha com telas, e essas telas são funções que o LCD vai chamar quando for a “hora de atualizar”, um botão também foi adicionado para que consiga trocar entre as telas (as telas são armazenadas em um vetor de funções, ao clicar no botão o índice do vetor avança).

Significado dos arquivos:
* [delayAssinc](https://github.com/Tiago70/sistema-de-regagem-automatico/blob/master/delayAssinc.h) está todo o funcionamento do delay
* [modelo](https://github.com/Tiago70/sistema-de-regagem-automatico/blob/master/modelo.h) representa uma classe modelo para todos os sensores, ele fala o que deve ter em cada classe dos sensores.
* [condutivimetro](https://github.com/Tiago70/sistema-de-regagem-automatico/blob/master/condutivimetro.h), [temperatura](https://github.com/Tiago70/sistema-de-regagem-automatico/blob/master/temperatura.h) e [luminosidade](https://github.com/Tiago70/sistema-de-regagem-automatico/blob/master/luminosidade.h) são os sensores
* [bomba](https://github.com/Tiago70/sistema-de-regagem-automatico/blob/master/bomba.h) representa a bomba que irá regar o sistema
* [display](https://github.com/Tiago70/sistema-de-regagem-automatico/blob/master/display.h) é o código do LCD e das telas
* [cartaoSD](https://github.com/Tiago70/sistema-de-regagem-automatico/blob/master/cartaoSD.h) está o código para armazenar as medições
* [relogio](https://github.com/Tiago70/sistema-de-regagem-automatico/blob/master/relogio.h) representam o relógio de tempo real RTC

Caso queira ver mais, o código está com vários comentários que irá auxiliá-lo em algumas funcionalidades.

## Simulação
Aqui está uma simulação do código rodando no site [Wokwi](https://wokwi.com/) (este site simula o Arduino e seus componentes).

Nesta simulação, foi removido o RTC e o cartão SD pois os modelos desses componentes que foram utilizados no código não tinham no wokwi.
[Clique neste link](https://wokwi.com/projects/439041742970872833) para rodar o projeto.

Você pode alterar o valor do sensor de temperatura e de luminosidade e depois vê-los no LCD.

Obs: por algum motivo os resistores não estão funcionando no site, por isso mesmo alterando o valor dos resistores, o valor da condutividade não irá sair do 0.

Imagem do projeto no Wokwi:
<p aling="center">
  <img width="1546" height="750" alt="image" src="https://github.com/user-attachments/assets/69a847fd-82bd-48eb-a955-d696fd45d085" />
</p>

