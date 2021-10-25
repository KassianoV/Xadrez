# Xadrez
## Trabalho “Eu vencerei Beth Harmon”
### Parte 1
<p>A primeira parte do trabalho consiste em modelar (representar através de código de programação) um jogo de xadrez e indicar as possibilidades de movimentação de cada peça. O 
Tabuleiro será representado por uma matriz 8x8 de números inteiros. Cada peça será representada pelo código abaixo: <p/>
| &nbsp; &nbsp;Peças &nbsp; &nbsp;| &nbsp; &nbsp; Branco &nbsp; &nbsp; |  &nbsp; &nbsp; Preto &nbsp; &nbsp; | <br/>
| &nbsp; &nbsp;Peão &nbsp; &nbsp; &nbsp;| &nbsp; &nbsp; &nbsp; 1 &nbsp; &nbsp; &nbsp; | &nbsp; &nbsp; &nbsp; -1 &nbsp; &nbsp; &nbsp; | <br/>
| &nbsp; &nbsp;Cavalo &nbsp;| &nbsp; &nbsp; &nbsp; 2 &nbsp; &nbsp; &nbsp; | &nbsp; &nbsp; &nbsp; -2 &nbsp; &nbsp; &nbsp; | <br/>
| &nbsp; &nbsp;Bispo &nbsp; &nbsp;| &nbsp; &nbsp; &nbsp; 3 &nbsp; &nbsp; &nbsp; | &nbsp; &nbsp; &nbsp; -3 &nbsp; &nbsp; &nbsp; | <br/>
| &nbsp; &nbsp;Torre &nbsp; &nbsp; &nbsp;| &nbsp; &nbsp; &nbsp; 4 &nbsp; &nbsp; &nbsp; | &nbsp; &nbsp; &nbsp; -4 &nbsp; &nbsp; &nbsp; | <br/>
| &nbsp; &nbsp;Rainha &nbsp;| &nbsp; &nbsp; &nbsp; 5 &nbsp; &nbsp; &nbsp; | &nbsp; &nbsp; &nbsp; -5 &nbsp; &nbsp; &nbsp; | _ (também chamada de Dama) _ <br/> 
| &nbsp; &nbsp;Rei &nbsp; &nbsp; &nbsp; &nbsp;| &nbsp; &nbsp; &nbsp; 6 &nbsp; &nbsp; &nbsp; | &nbsp; &nbsp; &nbsp; -6 &nbsp; &nbsp; &nbsp; | <br/>

<p>O posicionamento inicial das peças é dado pela figura abaixo. Por causa dos índices da matriz na
linguagem C, vamos considerar que a linha 0 é onde fica o Rei branco (linha 1 na figura abaixo) e a
linha 7 é onde fica o Rei preto (linha 8 na figura abaixo). As torres vão ficar na coluna 0 (coluna ‘a’
na figura abaixo) e na coluna 7 (coluna ‘h’ na figura abaixo). <p/>

<img src="http://comojogarxadrez.com.br/uploads/1/1/3/9/113979129/como-jogar-xadrez-posi-o-inicial_orig.png" alt="Tabuleiro Inicial Xadrez" />

Cada jogada será representada pelo struct jogada abaixo, que indicará a posição de onde a peça saiu e a posição na qual ela foi movida. <br/>

<blockquote>
  struct jogada{<br/>
&nbsp;int linhaDe, colunaDe, linhaPara, colunaPara;<br/>
};</blockquote>

###Parte 2

<p>Num jogo de xadrez o termo “posição” é utilizado para indicar uma organização qualquer das
peças que ainda não foram capturadas. O jogo sempre começa com a posição inicial e, a cada
movimento válido, o jogo passa para uma nova posição até que haja o cheque-mate, desistência ou
empate (ou um jogador perca por tempo).<p/>
<p>Na segunda parte do trabalho, cada peça será representada por um struct Peca descrito abaixo,
contendo o código da peça (positivo ou negativo), a linha e a coluna onde a peça está e a
quantidade de ataques que a peça está sofrendo, além dos ponteiros. O programa deve possuir
também um struct Posicao indicado abaixo, contento a quantidade de peças brancas não
capturadas, uma lista (circular duplamente encadeada com sentinela) das peças brancas, a
quantidade de peças pretas não capturadas, uma lista (circular duplamente encadeada com
sentinela) de peças pretas e um número inteiro que indica o jogador da vez (1, para o jogador de
brancas; -1, para o jogador de pretas). Além disso, a posição deve conter também uma matriz[8][8]
de ponteiros para as peças não-capturadas. Essa matriz de ponteiros funciona da seguinte maneira:
se numa casa qualquer (i,j) da matriz não tem nenhuma peça, nessa casa fica um ponteiro para
NULL. Se nessa casa tiver uma peça, o ponteiro deve apontar para a peça correspondente na lista
de peças brancas ou pretas.<p/>

<blockquote>
  struct Peca{<br/>
  &nbsp;int codigo;<br/>
  &nbsp;int linha,coluna;<br/>
  &nbsp;int ataques;<br/>
  &nbsp;struct Peca *prox,*ant;<br/>
};
</blockquote>

<blockquote>
  struct Posicao{ <br/>
  &nbsp;int qtdBrancas;<br/>
  &nbsp;struct Peca *brancas;<br/>
  &nbsp;int qtdPretas;<br/>
  &nbsp;struct Peca *pretas;<br/>
  &nbsp;int jogVez;<br/>
  &nbsp;struct Peca *tab[8][8];<br/>
}
 </blockquote>

### Parte 3

<p>Num jogo de xadrez o termo “posição” é utilizado para indicar uma organização qualquer das
peças que ainda não foram capturadas. O jogo sempre começa com a posição inicial e, a cada
movimento válido, o jogo passa para uma nova posição até que haja o cheque-mate, desistência ou
empate (ou um jogador perca por tempo).<p/>
<p>Na terceira parte do trabalho, os grupos devem implementar algumas funções que serão utilizadas
na implementação da IA. A primeira função, chamada CopiaPosicao, deve criar uma cópia completa
e independente de uma struct Posicao, passada como parâmetro. A cópia deve ser retornada pela
função e deve ter as peças nas mesmas casas da posição passada como parâmetro, sem realizar
nenhum tipo de alteração nessas peças. Obviamente, a memória alocada para as listas de peças
brancas e pretas será diferente da memória alocada para a posição original. A ordem das peças na
lista copiada pode ser diferente da lista original, mas é aconselhável que seja a mesma ordem.<p/>
<p>A segunda função a ser implementada, chamada LiberaMemoria, deve receber uma posição como
parâmetro e destruir as listas de peças brancas e pretas. Os ponteiros do campo tab não precisam
ser modificados para NULL (mas não podem mais ser usados, atenção!!!).<p/>
<p>A terceira função, chamada AvaliaPosicao, deve receber como parâmetro uma posição e deve
retornar um valor double, contendo a avaliação da posição indicada. Essa avaliação deve indicar,
por meio de um valor double, o quão bem é essa posição sob o ponto de vista das peças pretas. Ou
seja, quanto maior esse valor retornado melhor está o jogador de pretas em relação ao jogador de
brancas e vice-versa. Uma sugestão para essa avaliação é calcular um valor para todas as peças
pretas (somadas) e subtrair do total das peças brancas, mas qualquer outro tipo de avaliação é
permitida, desde que quanto maior o valor final, melhor seja a posição para as peças pretas (que
serão comandas pela IA na versão final).<p/>

  <blockquote>
  struct Peca{
  &nbsp;int codigo;<br/>
  &nbsp;int linha,coluna;<br/>
  &nbsp;int ataques;<br/>
  &nbsp;struct Peca *prox,*ant;<br/>
};
  </blockquote>
  
  ### Parte 4
  
<p>Na última parte do trabalho, os grupos devem implementar o algoritmo de IA que será responsável
por movimentar as peças pretas. A primeira função a ser implementada chama-se ExecutaIA
(recursiva), que receberá 4 parâmetros:
struct Posicao posAtual (struct contendo a posição atual do jogo)
int nível (inteiro que indica o nível a ser analisado na árvore MiniMax)
double alfa (número real que indica o valor da poda alfa)
double beta (número real que indica o valor da poda beta)
Essa função retornará um struct Jogada, contendo a melhor jogada encontrada pela IA para a
posição em questão.<p/>
