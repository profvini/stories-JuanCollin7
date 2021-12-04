Equalize:
 
Neste eu deixei a imagem em tons de cinza utilizando o "cvtColor" e após isto, utilizei a "equalizeHist" para equalizar a imagem e como output mostrei a imagem normal e a equalizada.

Imagens comparativas podem ser observadas no caminho "Equalize/Images".


Motion Detector:

Utilizei a função "clone" no inicio do while para guardar o histograma R anterior, após calcular os histogramas, usei a função "compareHist" para comparar o histograma R atual com o anterior e receber o valor da diferença. Por fim, comparei a diferença com o limiar de 0.2, toda vez que esta limiar é ultrapassada, o programa faz um print com o valor da diferença.

Fiz um vídeo colocando luz em mim e depois colocando a mão na frente da câmera. Enquanto no fundo aparece o terminal com os prints da diff quando ultrapassa a limiar. Vídeo está no caminho "Motion Detector/Motion Detector.mov".
