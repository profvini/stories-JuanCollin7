Stories:

O objetivo deste trabalho é simular os stories do aplicativo instagram.
Funções criadas: Aplicação de filtro, stickers e texto. Além de salvar a imagem.


Filtros:

Para a aplicação de filtro foi criado um array de MAT 3x3 e para modificar a imagem, foi utilizada a função 'transform', onde passamos a imagem de entrada, de saída e o filtro.
Para alterar os filtros aplicados, foi adicionado um slider como foi visto ao longo dos exercícios.


Stickers:

Para a aplicação de sticker também foi criado um array, só que desta vez de strings referentes ao nome da imagem do sticker. Então dado o índice atual do sticker, a imagem é lida com base em seu nome, e após isso é utilizado a função resize para padroniza-la ao tamanho de sticker e após isto foi usada a função copyTo para inserir o sticker na imagem original.
Foram adicionados sliders para alterar a imagem do sticker e sua posição.


Texto:

Para a aplicação de texto foi utilizado input de teclado, então quando o usuário clicar a letra 't', uma pergunta é mostrada no terminal do projeto e o usuário pode inserir o texto desejado, após clicar enter o texto aparece no canto inferior esquerdo.
Foi utilizada a função putText para adicionar o texto à imagem.
Foram adicionados sliders para alterar a posição do texto.


Salvar imagem:

Para salvar a imagem foi utilizada a função 'imwrite'. Quando a letra 's' é clicada pelo usuário, uma mensagem é exibida perguntando o nome de saída da imagem, então ao digitar o nome e clicar enter, a imagem é salva e o programa é encerrado.


Detalhes do desenvolvimento:

A primeira dúvida era de como fazer a interação do usuário, então tive a ideia de fazer tudo pelo teclado, criando uma lógica com switch case para os inputs, porém após isto, eu percebi que a maioria da funções poderiam ser utilizadas apenas com os sliders que estavam presentes nos exercícios, então adicionei sliders e fui removendo as funções do teclado. Por fim, foi necessário utilizar o teclado apenas para texto e para salvar.
Não consegui encontrar também como abrir uma imagem ou vídeo do computador, então utilizei o 'imread' para ler arquivos do projeto mesmo.

Eu iniciei pelo sistema de filtro por julgar mais fácil, visto que um dos exercícios aplicavam filtros, porém eu não sei o porque mas os filtros não estavam sendo aplicados e/ou ficaram estranhos na imagem. Então depois de pesquisar e tentar algumas coisas, encontrei o método 'transform' que resolveu o meu problema.

Após isto fiz o sistema de adicionar texto, e acho que foi a funcionalidade mais tranquila, pois foi fácil de encontrar e utilizar a função 'putText'. No início a imagem era sempre adicionada na mesma posição, depois adicionei sliders para o usuário conseguir mover a posição do texto na imagem.

E por último, adicionei o sistema de stickers, este foi bem chatinho, pois encontrei apenas umas duas respostas na internet e elas não funcionavam, então fui testando e mexendo até que por fim, funcionou. Acabei utilizando a função 'copyTo'. Único ponto negativo é que não consegui adicionar a imagem com transparência, então ela ficou com fundo preto.


Como utilizar:

Para inserir os filtros e stickers, basta utilizar os sliders referentes na janela.
Para inserir um texto, clique na letra 't', digite seu texto no terminal e pressione enter. Após isso, você pode movê-lo utilizando os sliders referentes.
Para salvar a imagem, clique na letra 's', digite o nome da imagem de saída e pressione enter. Após isto, a imagem será salva na pasta "Resources" do projeto e o programa será encerrado.
