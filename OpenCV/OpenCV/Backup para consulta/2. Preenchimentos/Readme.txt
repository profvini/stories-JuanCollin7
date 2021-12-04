Exercicios 1:

Primeiro exercício:
 
Minha sugestão foi usar um count no floodfill ao invés de usar o número de objetos. Adicionei um % 255 neste count, assim sempre que chegar no 254, o próximo voltará ao 0, porém utilizei a função "max" para sempre utilizar no mínimo o valor 1. Ou seja, os valores utilizados sempre estarão entre 1 e 254.

A solução pode ser visualizada no commit "Adicionada a resolução do primeiro exercício".


Segundo exercício:

1. Removo as bolhas das 4 bordas da imagem;
2. Troco a cor do fundo para cinza para diferenciar da cor dos buracos das bolhas;
3. Percorro cada pixel da imagem em busca de uma bolha:
    - Se encontro um pixel branco: Pinto de verde e incremento o número de bolhas normais;
    - Se encontro um pixel preto com o pixel anterior à ele verde, significa que encontrei um buraco, então pinto este buraco preto da cor do background
    e o pixel anterior(toda a borda) de vermelho para simbolizar uma bolha com buraco, decremento o número de bolhas normais e incremento o número de bolhas com buracos;
    - Se encontro um pixel preto com o pixel anterior de qualquer cor, significa que este é um buraco de uma bolha com buraco já computada, ou seja,
    o caso de uma bolha com mais de um buraco. Sendo assim, apenas pinto o buraco com a cor do background e nada mais.
    

Com estes 3 passos e estas condições, consigo contabilizar o número de bolhas com e sem buracos na imagem, incluindo o caso de bolhas com mais de um buraco.

O resultado pode ser visto na pasta "Resultados".
