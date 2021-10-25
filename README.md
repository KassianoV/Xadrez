# Xadrez
## Trabalho “Eu vencerei Beth Harmon”
### Parte 1
<p>A primeira parte do trabalho consiste em modelar (representar através de código de programação) um jogo de xadrez e indicar as possibilidades de movimentação de cada peça. O 
Tabuleiro será representado por uma matriz 8x8 de números inteiros. Cada peça será representada pelo código abaixo: <p/>
| &nbsp; &nbsp;Peças &nbsp; &nbsp; &nbsp; &nbsp; Branco &nbsp; &nbsp; &nbsp; &nbsp; Preto &nbsp; &nbsp;  <br/>
| &nbsp; &nbsp;Peão &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 1 &nbsp; &nbsp; &nbsp; | &nbsp; &nbsp; &nbsp; -1 &nbsp; &nbsp; &nbsp;  <br/>
| &nbsp; &nbsp;Cavalo &nbsp;| &nbsp; &nbsp; &nbsp; 2 &nbsp; &nbsp; &nbsp; | &nbsp; &nbsp; &nbsp; -2 &nbsp; &nbsp; &nbsp;  <br/>
| &nbsp; &nbsp;Bispo &nbsp; &nbsp;| &nbsp; &nbsp; &nbsp; 3 &nbsp; &nbsp; &nbsp; | &nbsp; &nbsp; &nbsp; -3 &nbsp; &nbsp; &nbsp;  <br/>
| &nbsp; &nbsp;Torre &nbsp; &nbsp; &nbsp;| &nbsp; &nbsp; &nbsp; 4 &nbsp; &nbsp; &nbsp; | &nbsp; &nbsp; &nbsp; -4 &nbsp; &nbsp; &nbsp;  <br/>
| &nbsp; &nbsp;Rainha &nbsp;| &nbsp; &nbsp; &nbsp; 5 &nbsp; &nbsp; &nbsp; | &nbsp; &nbsp; &nbsp; -5 &nbsp; &nbsp; &nbsp;  (também chamada de Dama) <br/> 
| &nbsp; &nbsp;Rei &nbsp; &nbsp; &nbsp; &nbsp;| &nbsp; &nbsp; &nbsp; 6 &nbsp; &nbsp; &nbsp; | &nbsp; &nbsp; &nbsp; -6 &nbsp; &nbsp; &nbsp;  <br/>

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

### Parte 2

<p>Num jogo de xadrez o termo “posição” é utilizado para indicar uma organização qualquer das
peças que ainda não foram capturadas. O jogo sempre começa com a posição inicial e, a cada
movimento válido, o jogo passa para uma nova posição até que haja o cheque-mate, desistência ou
empate (ou um jogador perca por tempo).</p>
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
de peças brancas ou pretas.</p>

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
empate (ou um jogador perca por tempo).</p>
<p>Na terceira parte do trabalho, os grupos devem implementar algumas funções que serão utilizadas
na implementação da IA. A primeira função, chamada CopiaPosicao, deve criar uma cópia completa
e independente de uma struct Posicao, passada como parâmetro. A cópia deve ser retornada pela
função e deve ter as peças nas mesmas casas da posição passada como parâmetro, sem realizar
nenhum tipo de alteração nessas peças. Obviamente, a memória alocada para as listas de peças
brancas e pretas será diferente da memória alocada para a posição original. A ordem das peças na
lista copiada pode ser diferente da lista original, mas é aconselhável que seja a mesma ordem.</p>
<p>A segunda função a ser implementada, chamada LiberaMemoria, deve receber uma posição como
parâmetro e destruir as listas de peças brancas e pretas. Os ponteiros do campo tab não precisam
ser modificados para NULL (mas não podem mais ser usados, atenção!!!).</p>
<p>A terceira função, chamada AvaliaPosicao, deve receber como parâmetro uma posição e deve
retornar um valor double, contendo a avaliação da posição indicada. Essa avaliação deve indicar,
por meio de um valor double, o quão bem é essa posição sob o ponto de vista das peças pretas. Ou
seja, quanto maior esse valor retornado melhor está o jogador de pretas em relação ao jogador de
brancas e vice-versa. Uma sugestão para essa avaliação é calcular um valor para todas as peças
pretas (somadas) e subtrair do total das peças brancas, mas qualquer outro tipo de avaliação é
permitida, desde que quanto maior o valor final, melhor seja a posição para as peças pretas (que
serão comandas pela IA na versão final).</p>

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
<strong>struct Posicao posAtual (struct contendo a posição atual do jogo)
int nível (inteiro que indica o nível a ser analisado na árvore MiniMax)
double alfa (número real que indica o valor da poda alfa)
double beta (número real que indica o valor da poda beta)</strong>
Essa função retornará um struct Jogada, contendo a melhor jogada encontrada pela IA para a
posição em questão.<p/>

  ##### A função deve executar os seguintes passos:
<p>1) Ter uma variável local “melhorValor”, do tipo double, valendo infinito negativo, se “nível” for
par ou infinito positivo, se “nível” for ímpar. Uma variável inteira “podado”, valendo zero. Uma
variável local “melhorJogada”, do tipo struct Jogada, sem valor inicial. Uma variável local
“jogadaIA”, do tipo struct Jogada, sem valor inicial. Uma variável double, chamada
“valorJogada”, sem valor inicial.</p>
<p>2) Calcular todas as jogadas possíveis de cada um dos jogadores, guardando as respectivas listas
de jogadas.</p>
<p>3) Se o valor de <strong>“nível”</strong> for par, a lista de jogadas das peças pretas deve ser percorrida
inteiramente, de acordo com os passos seguintes. Se o valor de <strong>“nível”</strong> for ímpar, será utilizada
a lista de jogadas das peças brancas.</p>
<p>4) A cada jogada da lista, o parâmetro “posAtual” será copiado para a variável local “posCopia”,
utilizando a função CopiaPosicao (terceira parte). A jogada em questão será executada na
variável <strong>“posCopia”</strong>.</p>
<p>5) O algoritmo deve então verificar se <strong>“nível”</strong> é menor do que uma constante chamada de
<strong>“MAX_NIVEL”</strong> (recomendo utilizar um valor menor do que 10 para essa constante).<br/>
a. Se o valor de “nível” for menor do que uma constante “MAX_NIVEL” e <strong>“nível”</strong> for par, a
função recursiva ExecutaIA será chamada, passando como parâmetros: “posCopia”,
“nível”+1, “melhorValor” e “beta”. A jogada retornada pela função será armazenada
em “jogadaIA”.<br/>
b. Se o valor de “nível” for menor do que uma constante “MAX_NIVEL” e “nível” for
ímpar, a função recursiva ExecutaIA será chamada, passando como parâmetros:<br/>
“posCopia”, “nível”+1, “alfa” e “melhorValor”. A jogada retornada pela função será
armazenada em “jogadaIA”.<br/>
c. Se o item 5a ou 5b forem executados, a jogada “jogadaIA” que foi retornada pela
função ExecutaIA deve ser executada sobre a variável “posCopia”. Se nem o item 5a
nem o item 5b forem executados, não é necessário executar nenhuma jogada neste
ponto do algoritmo.</p>

<p>6) Nesse momento, a função AvaliaPosicao (terceira parte) será chamada, passando como
parâmetro “posCopia”. O valor retornado será guardado em “valorJogada”. Se “valorJogada”
for menor do que “alfa” ou maior do que “beta”, a variável “podado” receberá o valor 1.</p>
<p>7) Após o item 6, “valorJogada” será utilizado para indicar se esta foi a melhor jogada encontrada
até o momento ou não, da seguinte forma. Se “nível” for par e “valorJogada” for maior ou igual
a “melhorValor”, “melhorValor” recebe esse valor e “melhorJogada” recebe a jogada que foi
executada no item 4. Se “nível” for ímpar e “valorJogada” for menor ou igual a “melhorValor”,
“melhorValor” recebe esse valor e “melhorJogada” recebe a jogada do item 4.</p>
<p>8) Antes de passar para a próxima possível jogada da lista de jogadas, o algoritmo deve chamar a
função “LimpaMemoria” (terceira parte) para liberar a memória utilizada pela variável “posCopia”.</p>
<p>9) Ao final, a função deve liberar a memória utilizada pelas 2 listas de jogadas possíveis (peças
brancas e pretas) e retornar a variável “melhorJogada”. Um código incompleto desse algoritmo
será fornecido aos grupos.</p>

<p>OBS: A função ExecutaIA será chamada apenas na vez do jogador de pretas. Na vez do jogador de
brancas, o usuário decidirá qual jogada fazer da mesma forma que na terceira etapa do trabalho. A
jogada indicada pela IA deve ser executada e, então, passar a vez para o jogador de peças brancas.</p>
<p>Nessa última parte, o jogo também armazenará as jogadas que forem feitas pelos jogadores. Será
utilizada uma função chamada “SalvaJogada”, que recebe como parâmetro o nome do arquivo e
um ponteiro para a jogada que acabou de ser feita. Se o ponteiro estiver valendo NULL, a função
deve abrir o arquivo em modo escrita e fechá-lo imediatamente, sem escrever nada nele. Se o
ponteiro for diferente de NULL, a função deve abrir o arquivo em modo de acréscimo (append),
escrever os 4 números inteiros que representam a jogada (deLinha, deColuna, paraLinha,
paraColuna) e fechar o arquivo.</p>
<p>No início do programa, deve ser criado um arquivo binário vazio, chamado “jogadas.bin” com um
ponteiro valendo NULL, apenas para que o arquivo seja criado. A cada jogada realizada pelo
jogador ou pela IA, a função “SalvaJogada” deve ser chamada passando um ponteiro para jogada
que acabou de ser feita, para que ela seja salva no arquivo.</p>

  <blockquote>
  struct Peca{
  &nbsp;int codigo;
  &nbsp;int linha,coluna;
  &nbsp;int ataques;
  &nbsp;struct Peca *prox,*ant;
  };
  </blockquote>
  
  <blockquote>
  struct Posicao{
  &nbsp;int qtdBrancas;
  &nbsp;struct Peca *brancas;
  &nbsp;int qtdPretas;
  &nbsp;struct Peca *pretas;
  &nbsp;int jogVez;
  &nbsp;struct Peca *tab[8][8];
}
 </blockquote>
