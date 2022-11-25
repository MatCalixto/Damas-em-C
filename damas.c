#include <stdio.h>
#include <stdlib.h>
#include <locale.h>  // Linguagem
#include <string.h>  // Biblioteca para manipulação de strings
#include <windows.h> // Beep Sounds
typedef struct peca
{
    int tipo;
    // 0 = vazio; 1 = pedra branca; 2 = pedra preta; 3 = dama branca; 4 = dama preta
} peca_;
void somInicio()
{
    Beep(400, 200);
    Beep(500, 200);
    Beep(600, 200);
    Beep(500, 200);
    Beep(800, 200);
}
void somInvalido()
{
    Beep(500, 200);
    Beep(350, 200);
    Beep(500, 200);
    Beep(350, 200);
    Beep(500, 200);
}
void somFim()
{
    Beep(500, 400);
    Beep(300, 500);
    Beep(500, 100);
    Beep(600, 200);
    Beep(700, 100);
    Beep(800, 500);
}
void desenhar(peca_ tabuleiro_[8][8])
{
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            if (j == 0)
                printf("%d", i + 1);       // Número de referência na esquerda (1-8)
            switch (tabuleiro_[i][j].tipo) // Da print num caractere de damas diferente para cada número do tabuleiro
            {
            case 0:
                printf("   "); // Casa Vazia
                break;
            case 1:
                printf(" \u2B24 "); // Pedra Branca
                break;
            case 2:
                printf(" \u25EF "); // Pedra Preta
                break;
            case 3:
                printf(" \u265B "); // Rainha Branca
                break;
            case 4:
                printf(" \u2655 "); // Rainha Preta
                break;
            }
            // printf ("%d %d", i, j);
            if (j < 7)
                printf(" | "); // Barra para Separar Casas
            else if (i > 0)
                printf("\n-----|-----|-----|-----|-----|-----|-----|-----\n");
        }
        if (i == 0)
            printf("\n  a  |  b  |  c  |  d  |  e  |  f  |  g  |  h  \n"); // Barra de referência inferior (a-h)
    }
}
int colocarPeca(int i, int j, int tipoTabuleiro)
{
    // Cria o tabuleiro, peças pretas de um lado, brancas do outro
    if (tipoTabuleiro == 1)
    {
        if (((i == 0 || i == 2) && j % 2 == 0) || (i == 1 && j % 2 == 1))
            return 1; // Pedra Branca
        else if (((i == 5 || i == 7) && j % 2 == 1) || (i == 6 && j % 2 == 0))
            return 2; // Pedra Preta
        else
            return 0;
    }
    else if (tipoTabuleiro == 2)
    {
        if (((i == 0 || i == 2) && j % 2 == 0) || (i == 1 && j % 2 == 1))
            return 3; // Dama Branca
        else if (((i == 5 || i == 7) && j % 2 == 1) || (i == 6 && j % 2 == 0))
            return 4; // Dama Preta
        else
            return 0;
    }
}
int converterMovimento(char mov[4], int movInt[4])
{
    // Muda os caractéres para números manipuláveis e verifica se os caracteres estão dentro do tabuleiro
    for (int i = 0; i < 4; i++)
    {
        switch (mov[i])
        {
        case 'a':
            movInt[i] = 0;
            break;
        case 'b':
            movInt[i] = 1;
            break;
        case 'c':
            movInt[i] = 2;
            break;
        case 'd':
            movInt[i] = 3;
            break;
        case 'e':
            movInt[i] = 4;
            break;
        case 'f':
            movInt[i] = 5;
            break;
        case 'g':
            movInt[i] = 6;
            break;
        case 'h':
            movInt[i] = 7;
            break;
        case '1':
            movInt[i] = 0;
            break;
        case '2':
            movInt[i] = 1;
            break;
        case '3':
            movInt[i] = 2;
            break;
        case '4':
            movInt[i] = 3;
            break;
        case '5':
            movInt[i] = 4;
            break;
        case '6':
            movInt[i] = 5;
            break;
        case '7':
            movInt[i] = 6;
            break;
        case '8':
            movInt[i] = 7;
            break;
        default:
            return 1;
        }
    }
    return 0;
}
void comerPeca(peca_ tabuleiro[8][8], int pos1, int pos2, int pos3, int pos4, int posCom1, int posCom2, int peca, int booleans[6], int proxJog)
{
    tabuleiro[pos1][pos2].tipo = peca;
    tabuleiro[posCom1][posCom2].tipo = 0;
    tabuleiro[pos3][pos4].tipo = 0;
    Beep(350, 100); // Efeito Comer Peça
    Beep(500, 100);
    booleans[3] = proxJog; // Trocar Jogador, de branco para preto e vice-versa
}
void moverPeca(peca_ tabuleiro[8][8], int pos1, int pos2, int pos3, int pos4, int peca, int booleans[6], int proxJog)
{
    tabuleiro[pos1][pos2].tipo = peca; // Colocar na pos nova
    tabuleiro[pos3][pos4].tipo = 0;    // Apagar da pos antiga
    Beep(350, 200);                    // Efeito Mover Peça
    booleans[3] = proxJog;             // Trocar Jogador, de branco para preto e vice-versa
}
int calcularMovimento(peca_ tabuleiro_[8][8], int movInt[4], int bools[5])
{
    // Verifica se movimento é permitido pelas regras e o realiza
    int pecaInicial = tabuleiro_[movInt[1]][movInt[0]].tipo;
    int pecaFinal = tabuleiro_[movInt[3]][movInt[2]].tipo;
    // printf("%d %d %d %d", movInt[0], movInt[1], movInt[2], movInt[3]);
    if (pecaFinal == 0) // Se pos final não tem nada, é vazia
    {
        int pecaIntermediaria[6];
        if (bools[3] == 0 && (pecaInicial == 1 || pecaInicial == 3))
        {

            // -------------------------------------------------- PEDRA BRANCA -------------------------------------------------- //

            if (pecaInicial == 1)
            {
                if (movInt[3] == movInt[1] + 1 && (movInt[2] == movInt[0] + 1 || movInt[2] == movInt[0] - 1)) // Se mover apenas uma casa na diagonal
                {
                    if (movInt[3] == 7)
                        moverPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], 3, bools, 1);
                    else
                        moverPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], 1, bools, 1);
                    return 0;
                }
                else if (movInt[3] == movInt[1] + 2 && (movInt[2] == movInt[0] + 2 || movInt[2] == movInt[0] - 2)) // Se mover duas casas na diagonal
                {
                    pecaIntermediaria[0] = tabuleiro_[(movInt[1] + movInt[3]) / 2][(movInt[0] + movInt[2]) / 2].tipo;
                    if ((pecaIntermediaria[0] == 2 || pecaIntermediaria[0] == 4))
                    {
                        if (movInt[3] == 7)
                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], (movInt[1] + movInt[3]) / 2, (movInt[0] + movInt[2]) / 2, 3, bools, 1);
                        else
                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], (movInt[1] + movInt[3]) / 2, (movInt[0] + movInt[2]) / 2, 1, bools, 1);
                        return 0;
                    }
                }
            }

            // -------------------------------------------------- DAMA BRANCA -------------------------------------------------- //

            else if (pecaInicial == 3)
            {
                if (movInt[3] > movInt[1] + 1) // Se o movimento for para cima
                {
                    if (movInt[2] > movInt[0]) // Se o movimento for para direita
                        for (int i = 0; i < movInt[3] - movInt[1] - 1; i++)
                        {
                            pecaIntermediaria[i] = tabuleiro_[movInt[1] + 1 + i][movInt[0] + 1 + i].tipo;
                        }
                    else // Se o movimento for para esquerda
                        for (int i = 0; i < movInt[3] - movInt[1] - 1; i++)
                        {
                            pecaIntermediaria[i] = tabuleiro_[movInt[1] + 1 + i][movInt[0] - 1 - i].tipo;
                        }
                    for (int i = movInt[3] - movInt[1] - 1; i < 6; i++)
                    {
                        pecaIntermediaria[i] = 0; // Limpa quaisquer informações guardadas de outros movimentos em endereços não utilizados
                    }
                }
                else if (movInt[3] < movInt[1] - 1) // Se o movimento for para baixo
                {
                    if (movInt[2] > movInt[0]) // Se o movimento for para direita
                        for (int i = 0; i < movInt[1] - movInt[3] - 1; i++)
                        {
                            pecaIntermediaria[i] = tabuleiro_[movInt[1] - 1 - i][movInt[0] + 1 + i].tipo;
                        }
                    else // Se o movimento for para esquerda
                        for (int i = 0; i < movInt[1] - movInt[3] - 1; i++)
                        {
                            pecaIntermediaria[i] = tabuleiro_[movInt[1] - 1 - i][movInt[0] - 1 - i].tipo;
                        }
                    for (int i = movInt[1] - movInt[3] - 1; i < 6; i++)
                    {
                        pecaIntermediaria[i] = 0; // Limpa quaisquer informações guardadas de outros movimentos em endereços não utilizados
                    }
                }
                // for (int i = 0; i < 6; i++)
                // {
                //     if (i < 4)
                //         printf("%d ", movInt[i]);
                //     else
                //         printf("  ");
                //     printf("%d %d\n", pecaIntermediaria[i], i);
                // }
                if ((movInt[3] == movInt[1] + 1 || movInt[3] == movInt[1] - 1) && (movInt[2] == movInt[0] + 1 || movInt[2] == movInt[0] - 1)) // Se mover apenas uma casa na diagonal
                {
                    moverPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], 3, bools, 1);
                    return 0;
                }
                else if ((movInt[3] == movInt[1] + 2 || movInt[3] == movInt[1] - 2) && (movInt[2] == movInt[0] + 2 || movInt[2] == movInt[0] - 2)) // Se mover duas casas na diagonal
                {
                    // pecaIntermediaria[0] = tabuleiro_[(movInt[1] + movInt[3]) / 2][(movInt[0] + movInt[2]) / 2].tipo;
                    if ((pecaIntermediaria[0] == 2 || pecaIntermediaria[0] == 4))
                    {
                        comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], (movInt[1] + movInt[3]) / 2, (movInt[0] + movInt[2]) / 2, 3, bools, 1);
                        return 0;
                    }
                    else
                    {
                        moverPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], 3, bools, 1);
                        return 0;
                    }
                }
                else // Lógica para as outras 6 casas
                {
                    if (movInt[3] > movInt[1] + 1) // Se for para cima
                    {
                        for (int i = 0; i < movInt[3] - movInt[1] - 1; i++)
                        {
                            if (movInt[3] == movInt[1] + 3 + i && (movInt[2] == movInt[0] + 3 + i || movInt[2] == movInt[0] - 3 - i))
                            {
                                // Se tem uma pedra ou dama no caminho antes da pos final
                                if (pecaIntermediaria[movInt[3] - movInt[1] - 2] == 2 || pecaIntermediaria[movInt[3] - movInt[1] - 2] == 4)
                                {
                                    if (movInt[3] - movInt[1] - 3 >= 0)
                                    {
                                        if (pecaIntermediaria[movInt[3] - movInt[1] - 3] == 0)
                                        {
                                            if (movInt[3] - movInt[1] - 4 >= 0)
                                            {
                                                if (pecaIntermediaria[movInt[3] - movInt[1] - 4] == 0)
                                                {
                                                    if (movInt[3] - movInt[1] - 5 >= 0)
                                                    {
                                                        if (pecaIntermediaria[movInt[3] - movInt[1] - 5] == 0)
                                                        {
                                                            if (movInt[3] - movInt[1] - 6 >= 0)
                                                            {
                                                                if (pecaIntermediaria[movInt[3] - movInt[1] - 6] == 0)
                                                                {
                                                                    if (movInt[3] - movInt[1] - 7 >= 0)
                                                                    {
                                                                        if (pecaIntermediaria[movInt[3] - movInt[1] - 7] == 0)
                                                                        {
                                                                            if (movInt[2] == movInt[0] + 3 + i)
                                                                                comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] - 1, 3, bools, 1);
                                                                            else
                                                                                comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] + 1, 3, bools, 1);
                                                                            return 0;
                                                                        }
                                                                    }
                                                                    else
                                                                    {
                                                                        if (movInt[2] == movInt[0] + 3 + i)
                                                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] - 1, 3, bools, 1);
                                                                        else
                                                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] + 1, 3, bools, 1);
                                                                        return 0;
                                                                    }
                                                                }
                                                            }
                                                            else
                                                            {
                                                                if (movInt[2] == movInt[0] + 3 + i)
                                                                    comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] - 1, 3, bools, 1);
                                                                else
                                                                    comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] + 1, 3, bools, 1);
                                                                return 0;
                                                            }
                                                        }
                                                    }
                                                    else
                                                    {
                                                        if (movInt[2] == movInt[0] + 3 + i)
                                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] - 1, 3, bools, 1);
                                                        else
                                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] + 1, 3, bools, 1);
                                                        return 0;
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                if (movInt[2] == movInt[0] + 3 + i)
                                                    comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] - 1, 3, bools, 1);
                                                else
                                                    comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] + 1, 3, bools, 1);
                                                return 0;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (movInt[2] == movInt[0] + 3 + i)
                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] - 1, 3, bools, 1);
                                        else
                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] + 1, 3, bools, 1);
                                        return 0;
                                    }
                                }
                                // Se há apenas vazio entre a posição inicial e final
                                else if (pecaIntermediaria[0] == 0 && pecaIntermediaria[1] == 0 && pecaIntermediaria[2] == 0 && pecaIntermediaria[3] == 0 && pecaIntermediaria[4] == 0 && pecaIntermediaria[5] == 0)
                                {
                                    moverPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], 3, bools, 1);
                                    return 0;
                                }
                            }
                        }
                    }
                    else if (movInt[3] < movInt[1] - 1) // Se for para baixo
                    {
                        for (int i = 0; i < movInt[1] - movInt[3] - 1; i++)
                        {
                            if (movInt[3] == movInt[1] - 3 - i && (movInt[2] == movInt[0] + 3 + i || movInt[2] == movInt[0] - 3 - i))
                            {
                                // Se tem uma pedra ou dama no caminho antes da pos final
                                if (pecaIntermediaria[movInt[1] - movInt[3] - 2] == 2 || pecaIntermediaria[movInt[1] - movInt[3] - 2] == 4)
                                {
                                    if (movInt[3] - movInt[1] - 3 >= 0)
                                    {
                                        if (pecaIntermediaria[movInt[3] - movInt[1] - 3] == 0)
                                        {
                                            if (movInt[3] - movInt[1] - 4 >= 0)
                                            {
                                                if (pecaIntermediaria[movInt[3] - movInt[1] - 4] == 0)
                                                {
                                                    if (movInt[3] - movInt[1] - 5 >= 0)
                                                    {
                                                        if (pecaIntermediaria[movInt[3] - movInt[1] - 5] == 0)
                                                        {
                                                            if (movInt[3] - movInt[1] - 6 >= 0)
                                                            {
                                                                if (pecaIntermediaria[movInt[3] - movInt[1] - 6] == 0)
                                                                {
                                                                    if (movInt[3] - movInt[1] - 7 >= 0)
                                                                    {
                                                                        if (pecaIntermediaria[movInt[3] - movInt[1] - 7] == 0)
                                                                        {
                                                                            if (movInt[2] == movInt[0] + 3 + i)
                                                                                comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] - 1, 3, bools, 1);
                                                                            else
                                                                                comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] + 1, 3, bools, 1);
                                                                            return 0;
                                                                        }
                                                                    }
                                                                    else
                                                                    {
                                                                        if (movInt[2] == movInt[0] + 3 + i)
                                                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] - 1, 3, bools, 1);
                                                                        else
                                                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] + 1, 3, bools, 1);
                                                                        return 0;
                                                                    }
                                                                }
                                                            }
                                                            else
                                                            {
                                                                if (movInt[2] == movInt[0] + 3 + i)
                                                                    comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] - 1, 3, bools, 1);
                                                                else
                                                                    comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] + 1, 3, bools, 1);
                                                                return 0;
                                                            }
                                                        }
                                                    }
                                                    else
                                                    {
                                                        if (movInt[2] == movInt[0] + 3 + i)
                                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] - 1, 3, bools, 1);
                                                        else
                                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] + 1, 3, bools, 1);
                                                        return 0;
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                if (movInt[2] == movInt[0] + 3 + i)
                                                    comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] - 1, 3, bools, 1);
                                                else
                                                    comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] + 1, 3, bools, 1);
                                                return 0;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (movInt[2] == movInt[0] + 3 + i)
                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] - 1, 3, bools, 1);
                                        else
                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] + 1, 3, bools, 1);
                                        return 0;
                                    }
                                }
                                // Se há apenas vazio entre a posição inicial e final
                                else if (pecaIntermediaria[0] == 0 && pecaIntermediaria[1] == 0 && pecaIntermediaria[2] == 0 && pecaIntermediaria[3] == 0 && pecaIntermediaria[4] == 0 && pecaIntermediaria[5] == 0)
                                {
                                    moverPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], 3, bools, 1);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (bools[3] == 1 && (pecaInicial == 2 || pecaInicial == 4))
        {

            // -------------------------------------------------- PEDRA PRETA -------------------------------------------------- //

            if (pecaInicial == 2)
            {
                if (movInt[3] == movInt[1] - 1 && (movInt[2] == movInt[0] + 1 || movInt[2] == movInt[0] - 1))
                {
                    if (movInt[3] == 0)
                        moverPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], 4, bools, 0);
                    else
                        moverPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], 2, bools, 0);
                    return 0;
                }
                else if (movInt[3] == movInt[1] - 2 && (movInt[2] == movInt[0] + 2 || movInt[2] == movInt[0] - 2))
                {
                    pecaIntermediaria[0] = tabuleiro_[(movInt[1] + movInt[3]) / 2][(movInt[0] + movInt[2]) / 2].tipo;
                    if ((pecaIntermediaria[0] == 1 || pecaIntermediaria[0] == 3))
                    {
                        if (movInt[3] == 7)
                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], (movInt[1] + movInt[3]) / 2, (movInt[0] + movInt[2]) / 2, 4, bools, 0);
                        else
                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], (movInt[1] + movInt[3]) / 2, (movInt[0] + movInt[2]) / 2, 2, bools, 0);
                        return 0;
                    }
                }
            }

            // -------------------------------------------------- DAMA PRETA -------------------------------------------------- //

            else if (pecaInicial == 4)
            {
                if (movInt[3] > movInt[1] + 1) // Se o movimento for para cima
                {
                    if (movInt[2] > movInt[0]) // Se o movimento for para direita
                        for (int i = 0; i < movInt[3] - movInt[1] - 1; i++)
                        {
                            pecaIntermediaria[i] = tabuleiro_[movInt[1] + 1 + i][movInt[0] + 1 + i].tipo;
                        }
                    else // Se o movimento for para esquerda
                        for (int i = 0; i < movInt[3] - movInt[1] - 1; i++)
                        {
                            pecaIntermediaria[i] = tabuleiro_[movInt[1] + 1 + i][movInt[0] - 1 - i].tipo;
                        }
                    for (int i = movInt[3] - movInt[1] - 1; i < 6; i++)
                    {
                        pecaIntermediaria[i] = 0; // Limpa quaisquer informações guardadas de outros movimentos em endereços não utilizados
                    }
                }
                else if (movInt[3] < movInt[1] - 1)
                {
                    if (movInt[2] > movInt[0])
                        for (int i = 0; i < movInt[1] - movInt[3] - 1; i++)
                        {
                            pecaIntermediaria[i] = tabuleiro_[movInt[1] - 1 - i][movInt[0] + 1 + i].tipo;
                        }
                    else // Se o movimento for para esquerda
                        for (int i = 0; i < movInt[1] - movInt[3] - 1; i++)
                        {
                            pecaIntermediaria[i] = tabuleiro_[movInt[1] - 1 - i][movInt[0] - 1 - i].tipo;
                        }
                    for (int i = movInt[1] - movInt[3] - 1; i < 6; i++)
                    {
                        pecaIntermediaria[i] = 0; // Limpa quaisquer informações guardadas de outros movimentos em endereços não utilizados
                    }
                }
                // for (int i = 0; i < 6; i++)
                // {
                //     if (i < 4)
                //         printf("%d ", movInt[i]);
                //     else
                //         printf("  ");
                //     printf("%d %d\n", pecaIntermediaria[i], i);
                // }
                if ((movInt[3] == movInt[1] + 1 || movInt[3] == movInt[1] - 1) && (movInt[2] == movInt[0] + 1 || movInt[2] == movInt[0] - 1)) // Se mover apenas uma casa na diagonal
                {
                    moverPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], 4, bools, 0);
                    return 0;
                }
                else if ((movInt[3] == movInt[1] + 2 || movInt[3] == movInt[1] - 2) && (movInt[2] == movInt[0] + 2 || movInt[2] == movInt[0] - 2)) // Se mover duas casas na diagonal
                {
                    // pecaIntermediaria[0] = tabuleiro_[(movInt[1] + movInt[3]) / 2][(movInt[0] + movInt[2]) / 2].tipo;
                    if ((pecaIntermediaria[0] == 1 || pecaIntermediaria[0] == 3))
                    {
                        comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], (movInt[1] + movInt[3]) / 2, (movInt[0] + movInt[2]) / 2, 4, bools, 0);
                        return 0;
                    }
                    else
                    {
                        moverPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], 4, bools, 0);
                        return 0;
                    }
                }
                else // Lógica para as outras 6 casas
                {
                    if (movInt[3] > movInt[1] + 1) // Se for para cima
                    {
                        for (int i = 0; i < movInt[3] - movInt[1] - 1; i++)
                        {
                            if (movInt[3] == movInt[1] + 3 + i && (movInt[2] == movInt[0] + 3 + i || movInt[2] == movInt[0] - 3 - i))
                            {
                                // Se tem uma pedra ou dama no caminho antes da pos final
                                if (pecaIntermediaria[movInt[3] - movInt[1] - 2] == 1 || pecaIntermediaria[movInt[3] - movInt[1] - 2] == 3)
                                {
                                    if (movInt[3] - movInt[1] - 3 >= 0)
                                    {
                                        if (pecaIntermediaria[movInt[3] - movInt[1] - 3] == 0)
                                        {
                                            if (movInt[3] - movInt[1] - 4 >= 0)
                                            {
                                                if (pecaIntermediaria[movInt[3] - movInt[1] - 4] == 0)
                                                {
                                                    if (movInt[3] - movInt[1] - 5 >= 0)
                                                    {
                                                        if (pecaIntermediaria[movInt[3] - movInt[1] - 5] == 0)
                                                        {
                                                            if (movInt[3] - movInt[1] - 6 >= 0)
                                                            {
                                                                if (pecaIntermediaria[movInt[3] - movInt[1] - 6] == 0)
                                                                {
                                                                    if (movInt[3] - movInt[1] - 7 >= 0)
                                                                    {
                                                                        if (pecaIntermediaria[movInt[3] - movInt[1] - 7] == 0)
                                                                        {
                                                                            if (movInt[2] == movInt[0] + 3 + i)
                                                                                comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] - 1, 4, bools, 0);
                                                                            else
                                                                                comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] + 1, 4, bools, 0);
                                                                            return 0;
                                                                        }
                                                                    }
                                                                    else
                                                                    {
                                                                        if (movInt[2] == movInt[0] + 3 + i)
                                                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] - 1, 4, bools, 0);
                                                                        else
                                                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] + 1, 4, bools, 0);
                                                                        return 0;
                                                                    }
                                                                }
                                                            }
                                                            else
                                                            {
                                                                if (movInt[2] == movInt[0] + 3 + i)
                                                                    comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] - 1, 4, bools, 0);
                                                                else
                                                                    comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] + 1, 4, bools, 0);
                                                                return 0;
                                                            }
                                                        }
                                                    }
                                                    else
                                                    {
                                                        if (movInt[2] == movInt[0] + 3 + i)
                                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] - 1, 4, bools, 0);
                                                        else
                                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] + 1, 4, bools, 0);
                                                        return 0;
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                if (movInt[2] == movInt[0] + 3 + i)
                                                    comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] - 1, 4, bools, 0);
                                                else
                                                    comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] + 1, 4, bools, 0);
                                                return 0;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (movInt[2] == movInt[0] + 3 + i)
                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] - 1, 4, bools, 0);
                                        else
                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] - 1, movInt[2] + 1, 4, bools, 0);
                                        return 0;
                                    }
                                }
                                // Se há apenas vazio entre a posição inicial e final
                                else if (pecaIntermediaria[0] == 0 && pecaIntermediaria[1] == 0 && pecaIntermediaria[2] == 0 && pecaIntermediaria[3] == 0 && pecaIntermediaria[4] == 0 && pecaIntermediaria[5] == 0)
                                {
                                    moverPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], 4, bools, 0);
                                    return 0;
                                }
                            }
                        }
                    }
                    else if (movInt[3] < movInt[1] - 1) // Se for para baixo
                    {
                        for (int i = 0; i < movInt[1] - movInt[3] - 1; i++)
                        {
                            if (movInt[3] == movInt[1] - 3 - i && (movInt[2] == movInt[0] + 3 + i || movInt[2] == movInt[0] - 3 - i))
                            {
                                // Se tem uma pedra ou dama no caminho antes da pos final
                                if (pecaIntermediaria[movInt[1] - movInt[3] - 2] == 1 || pecaIntermediaria[movInt[1] - movInt[3] - 2] == 3)
                                {
                                    if (movInt[3] - movInt[1] - 3 >= 0)
                                    {
                                        if (pecaIntermediaria[movInt[3] - movInt[1] - 3] == 0)
                                        {
                                            if (movInt[3] - movInt[1] - 4 >= 0)
                                            {
                                                if (pecaIntermediaria[movInt[3] - movInt[1] - 4] == 0)
                                                {
                                                    if (movInt[3] - movInt[1] - 5 >= 0)
                                                    {
                                                        if (pecaIntermediaria[movInt[3] - movInt[1] - 5] == 0)
                                                        {
                                                            if (movInt[3] - movInt[1] - 6 >= 0)
                                                            {
                                                                if (pecaIntermediaria[movInt[3] - movInt[1] - 6] == 0)
                                                                {
                                                                    if (movInt[3] - movInt[1] - 7 >= 0)
                                                                    {
                                                                        if (pecaIntermediaria[movInt[3] - movInt[1] - 7] == 0)
                                                                        {
                                                                            if (movInt[2] == movInt[0] + 3 + i)
                                                                                comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] - 1, 4, bools, 0);
                                                                            else
                                                                                comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] + 1, 4, bools, 0);
                                                                            return 0;
                                                                        }
                                                                    }
                                                                    else
                                                                    {
                                                                        if (movInt[2] == movInt[0] + 3 + i)
                                                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] - 1, 4, bools, 0);
                                                                        else
                                                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] + 1, 4, bools, 0);
                                                                        return 0;
                                                                    }
                                                                }
                                                            }
                                                            else
                                                            {
                                                                if (movInt[2] == movInt[0] + 3 + i)
                                                                    comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] - 1, 4, bools, 0);
                                                                else
                                                                    comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] + 1, 4, bools, 0);
                                                                return 0;
                                                            }
                                                        }
                                                    }
                                                    else
                                                    {
                                                        if (movInt[2] == movInt[0] + 3 + i)
                                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] - 1, 4, bools, 0);
                                                        else
                                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] + 1, 4, bools, 0);
                                                        return 0;
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                if (movInt[2] == movInt[0] + 3 + i)
                                                    comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] - 1, 4, bools, 0);
                                                else
                                                    comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] + 1, 4, bools, 0);
                                                return 0;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (movInt[2] == movInt[0] + 3 + i)
                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] - 1, 4, bools, 0);
                                        else
                                            comerPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], movInt[3] + 1, movInt[2] + 1, 4, bools, 0);
                                        return 0;
                                    }
                                }
                                // Se há apenas vazio entre a posição inicial e final
                                else if (pecaIntermediaria[0] == 0 && pecaIntermediaria[1] == 0 && pecaIntermediaria[2] == 0 && pecaIntermediaria[3] == 0 && pecaIntermediaria[4] == 0 && pecaIntermediaria[5] == 0)
                                {
                                    moverPeca(tabuleiro_, movInt[3], movInt[2], movInt[1], movInt[0], 4, bools, 0);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 1;
}
int main()
{
    setlocale(LC_ALL, "Portuguese");
    peca_ tabuleiro[8][8];
    char movimento[5];
    int movimentoInt[4];
    int booleans[5];
    // 0 = jogar novamente; 1 = abrir regras; 2 = movimento invalido; 3 = jogador; 4 = loop terminar
    // Jogador: 0 = Branco; 1 = Preto
    do
    {
        do
        {
            printf("Pressione 0 para consultar regras ou 1 para iniciar jogo: ");
            scanf("%d", &booleans[1]);
            if (booleans[1] == 0)
            {
                printf("------ REGRAS ------\n");
                printf(" - O jogo funciona com as regras usuais de Damas: as peças movem-se na diagonal, ");
                printf("podendo capturar peças inimigas se e somente se pularem para a casa atrás da peça inimiga");
                printf("e essa for vazia. \n");
                printf(" - Ademais, pedras que alcancem o outro lado do tabuleiro tornam-se Damas, as quais possuem maior alcance, ");
                printf("visto que as pedras comuns só podem pular uma casa do tabuleiro a cada movimento, enquanto as Damas não possuem ");
                printf("tal restrição. \n");
                printf(" - Quanto ao funcionamento desse programa, os movimentos são dados dentro do tabuleiro utilizando-se de números para a vertical ");
                printf("e letras na horizontal, assim como num plano cartesiano. \n");
                printf("Para que um jogador realize um movimento, o mesmo deve verificar qual a posição de sua peça escolhida e qual a posição final, ");
                printf("dizendo primeiramente a letra da horizontal, seguida do número da vertical. \n");
                printf(" - Alguns exemplos: a3b4, d6e5 e b4d6. \n");
                printf(" - Caso o jogador digite errado, faça um movimento que seja contra as regras ou que seja impossível, o programa irá pedir que o mesmo ");
                printf("tente novamente.\n");
                printf(" - Bom jogo!\n");
            }
        } while (!booleans[1]);
        booleans[2] = 0;
        booleans[3] = 0; // Jogador = branco
        booleans[4] = 0;
        // Posicionar pedras brancas e pretas
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                tabuleiro[i][j].tipo = colocarPeca(i, j, booleans[1]); // Preenche o tabuleiro
            }
        }
        somInicio();
        do
        {
            do
            {
                do
                {
                    desenhar(tabuleiro); // Dá print no tabuleiro
                    if (booleans[2])
                    {
                        printf("Movimento Inválido. Tente Novamente.\n");
                        somInvalido();
                    }
                    if (booleans[3] == 0)
                        printf("É a vez das peças brancas: ");
                    else
                        printf("É a vez das peças pretas: ");
                    scanf("%s", movimento);
                    booleans[2] = converterMovimento(movimento, movimentoInt); // Verifica se movimento está dentro do tabuleiro e converte letras para números para manipulação
                } while (booleans[2]);
                booleans[2] = calcularMovimento(tabuleiro, movimentoInt, booleans); // Verifica se movimento é possível e o realiza
            } while (booleans[2]);
            booleans[4]++;
        } while (booleans[4] < 50); // Verifica se jogo foi encerrado
        somFim();
        printf("Fim de jogo. Digite 1 para jogar novamente ou 0 para encerrar: ");
        scanf("%d", &booleans[0]);
    } while (booleans[0]);
    printf("Programa encerrado.");
}
// Beep(350, 200); // Efeito Mover Peça

// Beep(350, 100); // Efeito Comer Peça
// Beep(500, 100);

// Beep(500, 400); // Win
// Beep(300, 500);
// Beep(500, 100);
// Beep(600, 200);
// Beep(700, 100);
// Beep(800, 500);