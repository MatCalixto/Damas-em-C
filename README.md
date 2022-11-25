## Trabalho de C - Damas
### Relatório:

Lista de integrantes:

1 - João Guilherme Fortes Maciel
CPF: 144.644.944-04

2 - Matheus Henrique Calixto 
CPF: 101.029.044-48

3 - João marcelo Queiroz lopes
RGM: 3016860-1

4 - Arthur Travassos de Queiroz
RGM: 30195331

instrução:

O jogo de Damas se baseia em uma disputa de dois participantes que usam um tabuleiro xadrez para jogar. No jogo cada jogador tem 12 peças divididas entre brancas e pretas, o jogador com as peças brancas inicia o jogo posicionadas nas casas claras, as peças ocupam as casas das respectivas cores, sendo as três primeira linhas mais próximas de cada jogador abrindo espaço no meio do tabuleiro para movimentação. Ao inicio do movimento pelas peças brancas, os jogadores só podem andar uma casa por peça na diagonal passando a vez a cada movimento, durante o jogo podem capturar uma peça do rival pulando a casa onde se encontra a peça na diagonal, caso um dos jogadores chegue ao ponto de partida do outro a peça se torna uma "Dama", uma peça que não tem limite de movimentos podendo andar quantas casas quiser na diagonal. Objetivo - Capturar todas as peças do oponente ou deixá-lo impossibilitado de mover, assim ganhando o jogo.



Resultados: 

O código inicia por funções implementadas para sons do jogo, ao começar tocando uma musica simples e ao se mover uma peça. O jogo inicia mostrando as peças brancas e pretas no tabuleiro oito por oito com a vez para as peças brancas, o tabuleiro se organiza em ordem alfabética na horizontal e numérica na vertical para identificar cada casa, para movimentar uma peça o jogador escreve a casa da peça que deseja mover como b3 e em sequencia a casa que quer ir como c4, lembrando que as peças só se movem na diagonal por isso se o jogador fizer um movimento fora das regras, um comando o avisara e será repetido o movimento. As peças são criadas por meio de uma struct para guardar o espaço onde estão seja branca, preta ou um espaço vazio. O maior conflito de se fazer o algoritmo foram as damas, quando uma peça de um jogador chega a primeira casa do oponente se trona uma dama podendo ir para qualquer casa, foi usado uma lista de if else para compor toda movimentação que a peça pode fazer dentro do tabuleiro.
