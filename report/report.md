
# Relatório 1º projecto ASA 2020/2021

Aluno: Bruno Mendes
----

## Descrição do Problema e da Solução
O Professor João Caracol desenvolveu um algoritmo para conseguir determinar qual o número mínimo de dominós que tem de deitar abaixo com a mão e o número de peças pertencente à maior sequência de dominós a cair, de cada vez que ele deita abaixo com a mão um dominó, numa sequência de dominós feita por ele.

A sequência de dominós é representada por um DAG e o objetivo do projeto é encontrar o número de sources para saber quantas peças deitar abaixo com a mão e o caminho mais longo para saber qual a maior sequência.

A solução que eu proponho envolve a criação de um DAG, encontrar os seus sources, ordená-lo topologicamente e relaxar os seus vértices para encontrar o caminho mais longo desde uma das sources até uma das sinks.

Fontes de código externas:
- https://en.wikipedia.org/wiki/Topological_sorting#Kahn's_algorithm
- https://en.wikipedia.org/wiki/Topological_sorting#Application_to_shortest_path_finding

## Análise Teórica
Sendo a input formada pelo conjunto das ligações que os dominós têm entre eles, decidi usar uma lista de adjacências para representar o DAG pois têm uma complexidade em termos de espaço menor que uma matriz de adjacências.

Como estruturas de dados para representar o DAG decidi usar um array de tamanho fixo  de vertex. Cada vertex é constituído por dois inteiros (número de incoming edges e distância à source mais longínqua) e um vector cujos elementos são apontadores para outros vertex, pois depois de alguns testes provou ser a estrutura que apresentava um melhor equilíbrio entre tempo de execução e memória alocada. Assim, a complexidade espacial é O(V+E).

Para a leitura dos dados de entrada utilizei ciclo que lê o input e insere cada edge com operações de tempo constante (push_back do ponteiro para o vértice destino da edge no vector do vértice de origem e incremento do número de incoming edges para o vértice a ser inserido), logo depende linearmente de E.

Para obter a ordem topológica implementei o algoritmo de Kahn que consiste em encontrar todas as sources percorrendo todos os vértices - Θ(V) - inserindo-os numa queue. De seguida, percorro todos os vértices adjacentes aos vértices na queue e sempre que descobro um vértice subtraio um ao número de incoming edges. Se o número de incoming edges de um vértice chegar a zero insiro esse vértice na queue. A ordem topológica é construída inserindo cada vértice na queue que representa a ordem topológica pela ordem que são visitados. Como percorro obrigatoriamente todos os vértices e todos os edges a complexidade para este passo é Θ(V+E).

Para obter o caminho mais longo de uma source até uma sink percorro a ordem topológica e quando observo um vértice relaxo-o, assumindo que o custo do caminho de um vértice até um dos seus descendentes é 1. Assim, no final de cada iteração posso guardar o maior caminho já percorrido e quando acabar de percorrer a ordem topológica obtenho o maior caminho existente no DAG. Como percorro todos os vértices e todos os edges a complexidade para este passo é O(V+E).

Para apresentar os resultados utilizo uma chamada ao printf que no contexto do problema assume-se que demora tempo constante - O(1).

## Complexidade global da solução: O(E + V + (V + E) + (V + E) + 1) = O(V+E)
- Leitura dos dados de entrada - Θ(E)
- Processamento do grafo para encontrar as sources do DAG - Θ(V)
- Aplicação do algoritmo de Kahn para encontrar uma ordem topológica válida - Θ(V+E)
- Processamento da ordem topológica para encontrar o maior caminho - O(V+E)
- Apresentação dos dados - O(1)

## Avaliação Experimental dos Resultados
Para avaliar experimentalmente a minha solução, gerei gráficos com um número de vértices e edges incremental e calculei o tempo de execução do programa para cada input.

Em baixo apresento o gráfico que relaciona o número de vértices e edges (V+E) no eixo XX com o tempo em segundos que a que o output demora a ser gerado no eixo YY.

![alt text](graph.png "Grafico")

Analisando a complexidade teoricamente, concluí que a minha solução deve apresentar uma relação linear entre o número de vértices e edges, o que é corroborado pelo gráfico obtido experimentalmente.

