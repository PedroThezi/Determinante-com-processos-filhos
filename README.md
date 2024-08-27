# Determinante com processos filhos
***
Repositório dedicado ao projeto de _SOII_ para calcular __determinante__ através de processos filhos pela *__Regra de Sarrus__*. Onde um filho calcula a diagonal principal e o outro filho calcula a diagonal secundária atraves de uma _variavel global_. A matriz tem tamnho [3][3] e está armazenada na pasta `Matriz` em um arquivo txt chamado `matriz.txt`. 

## Determinante com filho thread.
***
Utiliza *__mutex__* para controlar o uso da _variável global_ pelo processos threads.

## Determinante com filho tradicional com pipe.
***
Utliza *__pipe__* como meio de comunicação entre os filhos tradicionais e o pai.
