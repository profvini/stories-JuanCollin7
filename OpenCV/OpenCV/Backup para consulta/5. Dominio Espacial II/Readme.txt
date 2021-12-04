Tiltshift:

Para este exercício primeiramente eu apliquei um filtro para deixar a imagem bem "diferente" para podermos visualizar o efeito aplicado de forma mais clara.

Na main criei as três trackbars referentes aos efeitos solicitados pelo exercício;
Na função on_track_centro fiz o cálculo do centro do efeito com base no valor atual do slider e o tamanho da imagem.
Na função on_track_decaimento apenas guardo o valor do slider de decaimento em uma variável para ser utilizada pela última função.
Por último, na função on_track_regiao calculo as duas linhas da região, aplico a fórmula do tutorial para encontrar o alfa com base no decaimento, atualizo a imagem que está sendo exibida e também à salvo.

Imagens de exemplo podem ser encontradas no caminho "Tiltshift/Images".

Na "Image1" o slider de centro está aproximadamente no centro e podemos observar uma linha no centro da imagem.
Na "Image2" foi alterado o slider de região e podemos observar na imagem uma região nítida.
Na "Image3" o slider de decaimento foi alterado e podemos ver que não temos mais linhas bem definidas para o efeito, mas sim um efeito gradual.
E por último, na "Image4" o slider de região foi alterado novamente apenas para aumentar à região, deixando a maior área da imagem "visível".


TiltshiftVideo:

Este foi bem parecido com o exercício anterior, então usei a mesma l'gocia de aplicar um filtro para deixar a imagem bem "diferente" para podermos visualizar o efeito aplicado de forma mais clara.

Ao invés dos sliders criei variáveis predefinidas para a região, centro e decaimento.

A lógica de aplicação foi a mesma do exercício anterior, porém por ser um vídeo, tive que fazer uma pesquisa para abrir e salvar um arquvio mp4 e também foi necessário utilizar um "for" para aplicar o filtro em todo o vídeo.

Para visualizar o resultado final, basta abrir o arquivo localizado em "OutputVideo/SunsetTimelapseSaida.mp4".

Ou também, ao final de cada execução o programa salva o arquivo em "OpenCV/Resources/SunsetTimelapseSaida.mp4", porém este não fica indexado no xcode, apenas na pasta do projeto.
