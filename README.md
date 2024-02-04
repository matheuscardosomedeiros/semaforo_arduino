# Automação de Semáforo com Arduino e C#
 
Projeto de automação de um semáforo utilizando Arduino e comunicação serial com a linguagem C#. Este projeto foi realizado durante o primeiro semestre do curso de Engenharia de Controle e Automação.

## Lista de componentes utilizados:

* 6x LEDs (2 amarelos, 2 vermelhos e 2 verdes)
* 6x Resistores 220 ohms
* 2x Resistores 10k ohms
* 2x Push-Buttons
* 1x Buzzer
* 1x Sensor Infravermelho
* 1x Protoboard
* 1x Arduino Mega 2560

## Esquemático do projeto:

<img src="/img/Esquemático do circuito.png">

## Funcionamento do projeto:

Foram desenvolvidos 2 códigos para a execução da automação do semáforo. Um código foi escrito com o objetivo do semáforo ser inteiramente controlado pelo arduino, e o outro código controla o semáforo via comunicação serial com um programa escrito em C#.

__Interface do programa em C#:__

<img src="/img/Interface.png">

A partir desta interface, é possível acompanhar os estados dos semáforos, assim como o tempo de execução. Também é possível trocar a função semáforo pela função pisca-alerta, onde apenas o LEDs amarelos piscam de segundo em segundo.

No código escrito unicamente para Arduino, a troca de estado dos semáforos é realizada através de 2 push-buttons em pull-down, e também pode ser feita através de um controle com o sensor infravermelho.

