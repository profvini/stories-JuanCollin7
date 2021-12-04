Kmeans:

Executei mais de 10 vezes o algoritmo pois não sei se o randômico não estava gerando pontos tão distintos para gerar uma saída diferente, mas no fim obtive um resultado final bem distinto do padrão, que pode ser visto em "Images/KmeansDiff.png".

A diferença das imagens se dá devido ao uso do KMEANS_RANDOM_CENTERS, gerando centros iniciais diferentes a cada execução, e ao número de rodadas ser apenas um. Pois o algoritmo envolve calculos baseados nos centros iniciais e tendo apenas uma rodada, o algoritmo não é longiquo o suficiente para recalcular e classificar os centros novamente. Ou seja, baseado sempre em diferentes centros iniciais e calculando e classificando apenas uma vez, é bem provavel que teremos saídas diferentes.
