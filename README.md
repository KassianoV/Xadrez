# Xadrez
## Trabalho “Eu vencerei Beth Harmon”
<p>A primeira parte do trabalho consiste em modelar (representar através de código de programação) um jogo de xadrez e indicar as possibilidades de movimentação de cada peça. O 
Tabuleiro será representado por uma matriz 8x8 de números inteiros. Cada peça será representada pelo código abaixo: <p/>
|>>>Peças>>>|   Branco   |   Preto   | <br/>
|>>>Peão>>>|     1      |    -1     | <br/>
|>>>Cavalo>>>|     2      |    -2     | <br/>
|>>>Bispo>>>|     3      |    -3     | <br/>
|>>>Torre>>>|     4      |    -4     | <br/>
|>>>Rainha>>>|     5      |    -5     | _(também chamada de Dama)_ <br/> 
|>>>Rei>>>|     6      |    -6     | <br/>

<p>O posicionamento inicial das peças é dado pela figura abaixo. Por causa dos índices da matriz na
linguagem C, vamos considerar que a linha 0 é onde fica o Rei branco (linha 1 na figura abaixo) e a
linha 7 é onde fica o Rei preto (linha 8 na figura abaixo). As torres vão ficar na coluna 0 (coluna ‘a’
na figura abaixo) e na coluna 7 (coluna ‘h’ na figura abaixo). <p/>

<img src="http://comojogarxadrez.com.br/uploads/1/1/3/9/113979129/como-jogar-xadrez-posi-o-inicial_orig.png" alt="Tabuleiro Inicial Xadrez" />

Cada jogada será representada pelo struct jogada abaixo, que indicará a posição de onde a peça saiu e a posição na qual ela foi movida. <br/>

<blockquote> struct jogada{<br/>
int linhaDe, colunaDe, linhaPara, colunaPara;
};</blockquote>
