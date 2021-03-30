# ASA project

## Projeto 1

O Professor João Caracol tem um fascínio por dominós e passa tardes a fazer longas sequências de dominós. Depois chama os vizinhos para todos observarem os dominós a cairem em sequência quando o professor deita alguns dos dominós abaixo.
Como passatempo decidiu desenvolver um algoritmo para conseguir determinar qual o número mínimo de dominós que tem de deitar abaixo com a mão, de forma a garantir que todos os dominós caiem. 
Adicionalmente, ficou curioso em saber qual o número de peças pertencente à maior sequência de dominós a cair, de cada vez que ele deita abaixo com a mão um dominó.

### Input

O ficheiro de entrada contém a informação sobre as sequências de dominós, e é definido daseguinte forma:
- Uma linha contendo dois inteiros: o número n de peças de dominó (n ≥ 2), e o número de dependências m a indicar (m ≥ 0);
- Uma lista em que cada linha i contém dois inteiros x e y indicando que se o dominó x cair, então o dominó y também cai.

Quaisquer inteiros numa linha estão separados por no máximo um espaço em branco, não contendo qualquer outro caractér, a não ser o fim de linha.

Assuma que os grafos de input são um DAG (grafo dirigido acíclico).

### Solution

Since we are given a DAG, I can sort it topologically. 
All the dominoes Joao Caracol had to drop by hand are the sources of the DAG.
Using kahn algorithm we get a topological sort of the DAG and then we can use a modified SSSP to find the longest line streak of falling dominoes.
