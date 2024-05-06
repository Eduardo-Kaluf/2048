#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void invertMatrix (int tab[4][4], char move) {
    int result[4][4];
    int m1[4][4] = {{0, 0, 0, 1}, {0, 0, 1, 0}, {0, 1, 0, 0}, {1, 0, 0, 0}};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = 0;
            if (move == 'w' || move == 's') {
                for (int k = 0; k < 4; k++) {
                    result[i][j] += m1[i][k] * tab[k][j];
                }
            }
            else if (move == 'a' || move == 'd') {
                for (int k = 0; k < 4; k++) {
                    result[i][j] += tab[i][k] * m1[k][j];
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tab[i][j] = result[i][j];

        }
    }
}


void showGame (int tab[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n\n");
    }
}


int placesTwo(int tab[4][4], int linha, int coluna, int count, int count2) {
    if (tab[linha][coluna] == 0) {
        return tab[linha][coluna] = 2;
    }

    //Encontra um espaço vazio para colocar o dígito
    else {
        if (count != 4) {
            if (linha == 3) {
                return placesTwo(tab, 0, coluna, count + 1, count2);
            }
            else {
                return placesTwo(tab, linha + 1, coluna, count + 1, count2);
            }
        }

        else {
            if (count2 != 4) {
                count = 0;
                if (coluna == 3) {
                    return placesTwo(tab, linha, 0, count, count2 + 1);
                }
                else {
                    return placesTwo(tab, linha, coluna + 1, count, count2 + 1);
                }
            }

            else {
                printf("GAME OVER\n");
                exit(0);
            }
        }
    }
    return 0;
}


void addTwo (int tab[4][4]) {
    int random_line, random_column;
    int count = 0;
    int count2 = 0;

    random_line   = rand() / (RAND_MAX / (4) + 1);
    random_column = rand() / (RAND_MAX / (4) + 1);
    
    placesTwo(tab, random_line, random_column, count, count2);
}


int compare (int tab[4][4], int row1, int row2, int column1, int column2) {
    return tab[row1][column1] == tab[row2][column2];
}


void sumsMultiples (int tab[4][4], char move) {
    int comp1, comp2, comp3;
    for (int j = 0; j < 4; j++) {
        if (move == 'w' || move == 's') {
            comp1 = compare(tab, 0, 1, j, j);
            comp2 = compare(tab, 2, 3, j, j);
            comp3 = compare(tab, 1, 2, j, j);
            if (comp1 && comp2) {
                tab[0][j] = tab[0][j] * 2;
                tab[1][j] = tab[2][j] * 2;
                tab[2][j] = 0;
                tab[3][j] = 0;
            }
            else if (comp3) {
                tab[1][j] = tab[1][j] * 2;
                tab[2][j] = tab[3][j];
                tab[3][j] = 0;
            }
            else if (comp1) {
                tab[0][j] = tab[0][j] * 2;
                tab[1][j] = tab[2][j];
                tab[2][j] = tab[3][j];
                tab[3][j] = 0;
            }
            else if (comp2) {
                tab[2][j] = tab[2][j] * 2;
                tab[3][j] = 0;
            }
        }
        else if (move == 'a' || move == 'd') {
            comp1 = compare(tab, j, j, 0, 1);
            comp2 = compare(tab, j, j, 2, 3);
            comp3 = compare(tab, j, j, 1, 2);
            if (comp1 && comp2) {
                tab[j][0] = tab[j][0] * 2;
                tab[j][1] = tab[j][2] * 2;
                tab[j][2] = 0;
                tab[j][3] = 0;
            }
            else if (comp3) {
                tab[j][1] = tab[j][1] * 2;
                tab[j][2] = tab[j][3];
                tab[j][3] = 0;
            }
            else if (comp1) {
                tab[j][0] = tab[j][0] * 2;
                tab[j][1] = tab[j][2];
                tab[j][2] = tab[j][3];
                tab[j][3] = 0;
            }
            else if (comp2) {
                tab[j][2] = tab[2][j] * 2;
                tab[j][3] = 0;
            }
        }
    }
}

int gravity (int tab[4][4], char move) {
    int count;
    int zero_appears;
    if (move == 'w' || move == 's') {
        for (int j = 0; j < 4; j++) {
            count = 0;
            while (count != 3) {
                zero_appears = 0;
                if (tab[count][j] == 0) {
                    //Verifica se existe algum número diferente de zero na fileira
                    for (int i = count + 1; i <= 3; i++) {
                        if (tab[i][j] != 0) {
                            zero_appears = 1;
                            break;
                        }
                    }
                    //Caso exista um número diferente de zero, puxa todos para cima
                    if (zero_appears) {
                        for (int i = count; i < 3; i++) {
                            tab[i][j] = tab[i + 1][j];
                        }
                        tab[3][j] = 0;
                    }
                    else {
                        break;
                    }
                }
                else {
                    count++;
                }
            }
        }
    }
    else if (move == 'a' || move == 'd') {
        for (int j = 0; j < 4; j++) {
            count = 0;
            while (count != 3) {
                zero_appears = 0;
                if (tab[j][count] == 0) {
                    //Verifica se existe algum número diferente de zero na coluna
                    for (int i = count + 1; i <= 3; i++) {
                        if (tab[j][i] != 0) {
                            zero_appears = 1;
                            break;
                        }
                    //Caso exista um número diferente de zero, puxa todos para esquerda
                    }
                    if (zero_appears) {
                        for (int i = count; i < 3; i++) {
                            tab[j][i] = tab[j][i + 1];
                        }
                        tab[j][3] = 0;
                    }
                    else {
                        break;
                    }
                }
                else {
                    count++;
                }
            }
        }
    }
    return 0;
}


void combine (int tab[4][4], char move) {
    if (move == 'w') {
        gravity(tab, move);
        sumsMultiples(tab, move);
    }
    else if (move == 's') {
        invertMatrix(tab, move);
        gravity(tab, move);
        sumsMultiples(tab, move);
        invertMatrix(tab, move);
    }
    else if (move == 'a') {
        gravity(tab, move);
        sumsMultiples(tab, move);

    }
    else if (move == 'd') {
        invertMatrix(tab, move);
        gravity(tab, move);
        sumsMultiples(tab, move);
        invertMatrix(tab, move);
    }
} 


int main (void) {
    char move;
    int playing = 1;
    int tab[4][4] = {{0, 0, 0, 2}, {0, 2, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    
    printf("VAMOS JOGAR 2048!\n\n");

    while (playing) {
        showGame(tab);
        printf("SEU MOVIMENTO: ");
        scanf(" %c", &move);
        printf("\n");
        combine(tab, move);
        addTwo(tab);
    }
    return 0;
}
