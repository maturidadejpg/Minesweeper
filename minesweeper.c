/*
Facil = 9x9 (10 bombas)
Médio = 16x16(40 bombas)
Dificil = 16x30(99 bombas)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIN 16
#define COL 30

void menu();
int criaMatriz(int);
void mostraCampo(int [LIN][COL], int, int);
void mostraTela(char [LIN][COL], int, int);
void preencheCampo(int, int, int [LIN][COL]);
void preencheTela(int , int, int, char [LIN][COL]);
void abreCasas(int [LIN][COL], char [LIN][COL], int, int, int, int);
void criaBombas(int [LIN][COL], int, int, int);
void criaDicas(int [LIN][COL], int, int);
void abreZeros(int [LIN][COL], char [LIN][COL], int, int, int, int);
void posicionaBandeira(char [LIN][COL], int, int);
void gameOver(int [LIN][COL], char [LIN][COL], int, int);
int vitoria(int [LIN][COL], char [LIN][COL], int, int, int);

int main(){
    int level;  //dificuldade selecionada
    int campo[LIN][COL] = {0};    //campo interpretado pelo computador
    char tela[LIN][COL] = {0};    //tela usada pelo usuario
    int x;  //coordenada x selecionada
    int y;  //coordenada y selecionada
    int row;    //numero de linhas do jogo
    int coll;   //numero de colunas do jogo
    int bombas; //numero de bombas do jogo
    int k;  //booleano que mantém o jogo rodando
    int v;  //verifica a vitória
    char escolha;   //escolha entre abrir casa ou colocar bandeira
    k = 0;

    menu();

    scanf("%d", &level);
        if (level >= 1 && level <= 4){
        switch (level){     //switch baseado na dificuldade selecionada
        case 1:
            row = 9;
            coll = 9;
            bombas = 10;
            break;
        case 2:
            row = 16;
            coll = 16;
            bombas = 40;
            break;
        case 3:
            row = 16;
            coll = 30;
            bombas = 99;
            break;
        case 4:
            printf("Escolha a quantidade de linhas (máx. 16): ");
            scanf("%d", &row);
            printf("Escolha a quantidade de linhas (máx. 30): ");
            scanf("%d", &coll);
            printf("Escolha a quantidade de bombas: ");
            scanf("%d", &bombas);
            break;
        }
        preencheCampo(row, coll, campo);
        preencheTela(level,row, coll, tela);
        criaBombas(campo, row, coll, bombas);
        criaDicas(campo, row, coll);

        while (k == 0){
            x = 0;
            y = 0;

            printf("\n");
            printf("Tela: \n");
            mostraTela(tela, row, coll);
            printf("\n");

            printf("Selecione a coordenada x: ");
            scanf("%d", &x);
            printf("Selecione a coordenada y: ");
            scanf("%d", &y);
            printf("Abrir a casa(a) ou colocar uma flag(f)? ");
            scanf(" %c", &escolha);

            if (escolha == 'a'){
                if (campo[x-1][y-1] == -1){
                    printf("Bomba explodiu!\n");
                    gameOver(campo, tela, row, coll);
                    mostraTela(tela, row, coll);
                    printf("GAME OVER!");
                    exit(1);
                }
                else{
                    abreCasas(campo, tela, x, y, row, coll);
                }
            }
            else if (escolha == 'f'){
                posicionaBandeira(tela, x, y);
            }
            if (x > row || y > coll){
                exit(1);
            }
            v = vitoria(campo, tela, row, coll, bombas);
            if (v == 1){
                mostraTela(tela, row, coll);
                printf("Voce venceu!");
                exit(1);
            }

            
        }
    }
    return 0;
}

void menu(){    //Printar menu
    printf("\n | MINESWEEPER |\nFeito por: Rafael Honorio Venetikides\n");
    printf("\nSelecione a dificuldade: ");
    printf("\n    1 - Fácil.\n    2 - Médio.\n    3 - Difícil.\n    4 - Modo livre.\n    0 - Sair.\n");
}

void preencheTela(int level,int row, int coll, char tela[LIN][COL]){  //Preenche a tela mostrada ao jogador
    int i;  //linhas
    int j;  //colunas
    
    for (i = 0; i <= (LIN -1); i++){
        for (j = 0; j<= (COL -1); j++){
            if (i < row && j < coll){
                tela[i][j] = ("%s", 45);
            }
        }
    }
        
}

void preencheCampo(int row, int coll, int campo[LIN][COL]){   //Preenche o campo interpretado pelo computador
    int i;  //linhas
    int j;  //colunas
    int l, c;

        for (i = 0; i <= (LIN -1); i++){
            for (j = 0; j<= (COL -1); j++){
                if (i < row && j < coll){
                    campo[i][j] = 0;
                }
                else{
                    campo[i][j] = 9;
                }
            }
        }
}

void mostraCampo(int campo[LIN][COL], int row, int coll){  //Printa o campo interpretado pelo computador
    int i;  //linhas
    int j;  //colunas
    for (i = 0; i < row; i++){
        for (j = 0; j< coll; j++){
            printf("[%2d]", campo[i][j]);
        }
        printf("\n");
    }
}

void mostraTela(char tela[LIN][COL], int row, int coll){   //Printa a tela mostrada ao jogador
    int i;  //linhas
    int j;  //colunas
    int num;
    printf("     ");
    for (num = 0; num < coll; num ++){
        printf("%2d ", (num+1));
    }
    printf("\n");
    for (i = 0; i < row; i++){
        for (j = 0; j< coll; j++){
                if (j == 0){
                    printf("%2d | [%1c]", (i+1), tela[i][j]);
                }
                else{
                printf("[%1c]", tela[i][j]);
                }
        }
    printf("\n");
    }
}

void abreCasas(int campo[LIN][COL], char tela[LIN][COL], int x, int y, int row, int coll){   //abre a respectiva coordenada selecionada
    if (campo[x-1][y-1] != -1){
        if (campo[x-1][y-1] != 0){
            tela[x-1][y-1] = ("%s", (campo[x-1][y-1] + '0'));
        }
        if (campo[x-1][y-1] == 0){
            tela[x-1][y-1] = ' ';
            abreZeros(campo, tela, x, y, row, coll);
        }
    }
}

void abreZeros(int campo[LIN][COL], char tela[LIN][COL], int x, int y, int row, int coll){      //navega as casas em volta caso um espaço vazio seja aberto
    int i, j;
    for (i = (x-2); i <= x; i++){
        for (j = (y-2); j <= y; j++){
            if (i >= 0 && j >= 0){
                if (i < row && j < coll){
                    if (tela[i][j] != ' '){
                        abreCasas(campo, tela, (i+1), (j+1), row, coll);
                    }
                }
            }
        }
    }
}

void criaBombas(int campo[LIN][COL], int row, int coll, int bombas){  //posiciona as bombas no campo
    int bombax; //coordenada x da bomba
    int bombay; //coordenada y da bomba
    int i;  //numero de bombas
    srand(time(NULL));
    for (i = 0; i< bombas; i++){
        bombax = rand() % row;
        bombay = rand() % coll;
        if (campo[bombax][bombay] == -1){
            i--;
        }
        else{
            campo[bombax][bombay] = -1;
        }
    }
}

void criaDicas(int campo[LIN][COL], int row, int coll){     //posiciona as dicas no campo
    int i;
    int j;
    int l;
    int c;
    int dica;

    for (i = 0; i < row; i++){
        for (j = 0; j < coll; j++){
            dica = 0;
            for (l = (i-1); l <= i+1; l++){
                for (c = (j-1); c <= (j+1); c++){
                    if (l >= 0 && c >= 0){
                        if (l < row && c < coll){
                            if (campo[l][c] == -1){
                                dica++;
                            }
                        }
                    }
                }
            }
            if (campo[i][j] != -1){
                    campo[i][j] = dica;
                }
        }
    }
}

void posicionaBandeira(char tela[LIN][COL], int x, int y){      //coloca ou retira uma bandeira de um local selecionado
    if (tela[x-1][y-1] == '-'){
        tela[x-1][y-1] = 'f';
    }
    else if(tela[x-1][y-1] == 'f'){
        tela[x-1][y-1] = '-';
    }
}

void gameOver(int campo[LIN][COL], char tela[LIN][COL], int row, int coll){     //define a condição de derrota do jogo
    int i,j;

    for (i = 0; i < row; i++){
        for (j = 0; j < coll; j++){
            if (campo[i][j] == -1){
                tela[i][j] = '*';
            }
        }
    }
}

int vitoria(int campo[LIN][COL], char tela[LIN][COL], int row, int coll, int bombas){       //define a condição de vitória do jogo
    int bandeirascorretas, bandeiras, i, j;
    bandeirascorretas = 0;
    bandeiras = 0;
    for (i = 0; i< row; i++){
        for (j = 0; j< coll; j++){
            if (tela[i][j] == 'f'){
                bandeiras += 1;
            }
            if (campo[i][j] == -1){
                if (tela[i][j] == 'f'){
                    bandeirascorretas += 1;
                }
            }
        }
    }
    if (bandeiras == bombas && bandeiras == bandeirascorretas){
        return 1;
    }
    else{
        return 0;
    }
}