#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<math.h>

#define PACMAN 'O'
#define BLINKY 'B'
#define PINKY 'P'
#define INKY 'I'
#define CLYDE 'C'
#define WALL '#'
#define FOOD '.'
#define ESP_FOOD ':'
#define WALL_PAIR 1
#define ESP_FOOD_PAIR 2
#define PACMAN_PAIR 3
#define BLINKY_PAIR 4
#define PINKY_PAIR 5
#define INKY_PAIR 6
#define CLYDE_PAIR 7
#define SCARED_PAIR 8
#define LIN 40
#define COL 120

typedef struct pacman
{
    int x0;
    int x1;
    int x2;
    int x3;
    int x4;
    int x5;
    int x6;
    int x7;
    int x8;
    int y0;
    int y1;
    int y2;
    int y3;
    int y4;
    int y5;
    int y6;
    int y7;
    int y8;
    char character;
    int power_up;
    int score;
    int life;
}pacman;

typedef struct ghost
{
    int x0;
    int x1;
    int x2;
    int x3;
    int x4;
    int x5;
    int x6;
    int x7;
    int x8;
    int y0;
    int y1;
    int y2;
    int y3;
    int y4;
    int y5;
    int y6;
    int y7;
    int y8;
    char character;
    int chase;
    int kills;
    char last_move;
}ghost;

char **ini_map()
{
    char **map;
    int cont = 0;
    map = (char **)malloc(LIN*sizeof(char *)); 
    for (int i=1; i<LIN; i++)
    {   
        map[i] = (char *)malloc(COL*sizeof(char));
        for(int j=1; j<COL; j++)
        //    CONTRUÇÃO DO MAPA/
        {   
            if(i == 1 || i == (LIN-1) || j == 1 || j == (COL-1))
            {
                map[i][j] = WALL;
            }
            else if(cont == 270)
            {
                map[i][j] = ESP_FOOD;
                cont = 0;
            }
            else
            {
                map[i][j] = FOOD;
                cont++;
            }                
        }
    }
    return map;
}

void build_walls(char **map)
{
    // BLOCO CANTO SUPERIOR ESQUERDO
    for(int i=LIN-35; i<LIN-30; i++)
        for(int j=COL-115; j<COL-107; j++)
            map[i][j] = WALL;
       // BLOCO CANTO INFERIOR ESQUERDO
    for(int i=LIN-5; i>LIN-11; i--)
        for(int j=COL-115; j<COL-107; j++)
            map[i][j] = WALL;
    // BLOCO SUPERIOR ESQUERDO
    for (int i=LIN-35; i<LIN-30; i++)
        for(int j=COL-104; j<COL-100; j++)
            map[i][j] = WALL;
    // BLOCO INFERIOR ESQUERDO
    for(int i=LIN-5; i>LIN-11; i--)
        for(int j=COL-104; j<COL-100; j++)
            map[i][j] = WALL;
    // BLOCO SUPERIOR ESQUERDO CENTRAL
    for(int i=LIN-39; i<LIN-30; i++)
        for(int j=COL-97; j<COL-93; j++)
            map[i][j] = WALL;
    // BLOCO INFERIOR ESQUERDO CENTRAL
    for(int i=LIN-2; i>LIN-11; i--)
        for(int j=COL-97; j<COL-93; j++)
            map[i][j] = WALL;
    // BLOCO ESQUERDO CENTRAL SUPERIOR
    for(int i=LIN-39; i<LIN-27; i++)
        for(int j=COL-107; j<COL-106; j++)
            map[j][i] = WALL;
    for(int i=1; i<7; i++)
        for(int j=14; j<15; j++)
            map[j][i] = WALL;
    // BLOCO ESQUERDO CENTRAL INFERIOR
    for(int i=LIN-15; i>LIN-16; i--)
        for(int j=COL-119; j<COL-113; j++)
            map[i][j] = WALL;
    for(int i=LIN-14; i>LIN-15; i--)
        for(int j=COL-119; j<COL-107; j++)
            map[i][j] = WALL;
    // WALL EM "T" CANTO ESQUERDO
    for(int i=LIN-23; i<LIN-17; i++)
        for(int j=COL-110; j<COL-107; j++)
            map[i][j] = WALL;
    for(int i=LIN-22; i<LIN-18; i++)
        for(int j=COL-115; j<COL-109; j++)
            map[i][j] = WALL;
    // WALL EM "T" CENTRAL ESQUERDO
    for(int i=LIN-27; i<LIN-13; i++)
        for(int j=COL-104; j<COL-100; j++)
            map[i][j] = WALL;
    for(int i=LIN-24; i<LIN-16; i++)
        for(int j=COL-100; j<COL-96; j++)
            map[i][j] = WALL;
    // BLOCO CANTO SUPERIOR DIREITO
    for(int i=LIN-35; i<LIN-30; i++)
        for(int j=COL-5; j>COL-13; j--)
            map[i][j] = WALL;
    // BLOCO CANTO INFERIOR DIREITO
    for(int i=LIN-5; i>LIN-11; i--)
        for(int j=COL-5; j>COL-13; j--)
            map[i][j] = WALL;
    // BLOCO SUPERIOR DIREITO
    for (int i=LIN-35; i<LIN-30; i++)
        for(int j=COL-16; j>COL-20; j--)
            map[i][j] = WALL;
    // BLOCO INFERIOR DIREITO
    for(int i=LIN-5; i>LIN-11; i--)
        for(int j=COL-16; j>COL-20; j--)
            map[i][j] = WALL;
    // BLOCO SUPERIOR DIREITO
    for(int i=LIN-39; i<LIN-30; i++)
        for(int j=COL-23; j>COL-27; j--)
            map[i][j] = WALL;
    // BLOCO INFERIOR DIREITO
    for(int i=LIN-1; i>LIN-11; i--)
        for(int j=COL-23; j>COL-27; j--)
            map[i][j] = WALL;
    // BLOCO DIREITO CENTRAL SUPERIOR
    for(int i=LIN-27; i<LIN-26; i++)
        for(int j=COL-1; j>COL-13; j--)
            map[i][j] = WALL;
    for(int i=LIN-26; i<LIN-25; i++)
        for(int j=COL-1; j>COL-7; j--)
            map[i][j] = WALL;
    // BLOCO DIREITO CENTRAL INFERIOR
    for(int i=LIN-14; i>LIN-15; i--)
        for(int j=COL-1; j>COL-13; j--)
            map[i][j] = WALL;
    for(int i=LIN-15; i>LIN-16; i--)
        for(int j=COL-1; j>COL-7; j--)
            map[i][j] = WALL;
    // WALL EM "T" CANTO DIREITO
    for(int i=LIN-22; i<LIN-18; i++)
        for(int j=COL-9; j<COL-4; j++)
            map[i][j] = WALL;
    for(int i=LIN-23; i<LIN-17; i++)
        for(int j=COL-12; j<COL-9; j++)
            map[i][j] = WALL;
    // WALL EM "T" CENTRAL DIREITO
    for(int i=LIN-27; i<LIN-13; i++)
        for(int j=COL-19; j<COL-15; j++)
            map[i][j] = WALL;
    for(int i=LIN-24; i<LIN-16; i++)
        for(int j=COL-20; j>COL-24; j--)
            map[i][j] = WALL;
    // BLOCO ESQUERDO ACIMA DA CASA DOS FANTASMAS
    for(int i=LIN-35; i<LIN-30; i++)
        for(int j=COL-90; j<COL-88; j++)
            map[i][j] = WALL;
    // BLOCO ESQUERDO ABAIXO DA CASA DOS FANTASMAS
    for(int i=LIN-5; i>LIN-11; i--)
        for(int j=COL-90; j<COL-88; j++)
            map[i][j] = WALL;
    // BLOCO DIREITO ACIMA DA CASA DOS FANTASMAS
    for(int i=LIN-35; i<LIN-30; i++)
        for(int j=COL-31; j<COL-29; j++)
            map[i][j] = WALL;
    // BLOCO DIREITO ABAIXO DA CASA DOS FANTASMAS
    for(int i=LIN-5; i>LIN-11; i--)
        for(int j=COL-31; j<COL-29; j++)
            map[i][j] = WALL;
    // BLOCO ESQUERDO MEIO CENTRAL ACIMA DA CASA DOS FANTASMAS
    for(int i=LIN-35; i<LIN-26; i++)
        for(int j=COL-85; j<COL-81; j++)
            map[i][j] = WALL;
    // BLOCO ESQUERDO MEIO CENTRAL ABAIXO DA CASA DOS FANTASMAS
    for(int i=LIN-5; i>LIN-14; i--)
        for(int j=COL-85; j<COL-81; j++)
            map[i][j] = WALL;
    // BLOCO DIREITO MEIO CENTRAL ACIMA DA CASA DOS FANTASMAS
    for(int i=LIN-35; i<LIN-26; i++)
        for(int j=COL-38; j<COL-34; j++)
            map[i][j] = WALL;
    // BLOCO DIREITO MEIO CENTRAL ABAIXO DA CASA DOS FANTASMAS
    for(int i=LIN-5; i>LIN-14; i--)
        for(int j=COL-38; j<COL-34; j++)
            map[i][j] = WALL;
    // FAIXAS ACIMA  E DO LADO DA CASA DOS FANTASMAS
    for(int j=COL-78; j<COL-66; j++)
    {
        map[5][j] = WALL;
        map[9][j] = WALL;
        map[35][j] = WALL;
        map[31][j] = WALL;
    }
    for(int j=COL-63; j<COL-56; j++)
    {
        map[5][j] = WALL;
        map[9][j] = WALL;
        map[35][j] = WALL;
        map[31][j] = WALL;
    }
    for(int j=COL-53; j<COL-41; j++)
    {
        map[5][j] = WALL;
        map[9][j] = WALL;
        map[35][j] = WALL;
        map[31][j] = WALL;
    }
    for(int i=LIN-19; i<LIN-12; i++)
    {
        map[i][COL-74] = WALL;
        map[i][COL-46] = WALL;
    }
    for(int i=LIN-27; i<LIN-24; i++)
    {
        map[i][COL-74] = WALL;
        map[i][COL-46] = WALL;
    }
    for(int i=LIN-17; i<LIN-12; i++)
    {
        for(int j=COL-68; j>COL-71; j--)
            map[i][j] = WALL;
        for(int j=COL-50; j>COL-53; j--)
            map[i][j] = WALL;
    }
    for(int i=LIN-27; i<LIN-24; i++)
    {
        for(int j=COL-68; j>COL-71; j--)
            map[i][j] = WALL;
        for(int j=COL-50; j>COL-53; j--)
            map[i][j] = WALL;
    }
    for(int i=LIN-21; i<LIN-19; i++)
    {
        map[i][COL-42] = WALL;
        for(int j=COL-38; j<COL-33; j++)
            map[i][j] = WALL;
        for(int j=COL-30; j<COL-26; j++)
            map[i][j] = WALL;
        map[i][COL-78] = WALL;
        for(int j=COL-90; j>COL-94; j--)
            map[i][j] = WALL;
        for(int j=COL-82; j>COL-87; j--)
            map[i][j] = WALL;
    }

    // WALL EM VOLTA DAS CASAS DOS FANTASMAS
    for(int i=LIN-16; i<LIN-13; i++)
        for(int j=COL-78; j>COL-94; j--)
            map[i][j] = WALL;
    for(int i=LIN-27; i<LIN-24; i++)
        for(int j=COL-78; j>COL-94; j--)
            map[i][j] = WALL;
    // WALL EM VOLTA DAS CASAS DOS FANTASMAS
    for(int i=LIN-16; i<LIN-13; i++)   
        for(int j=COL-42; j<COL-26; j++)
            map[i][j] = WALL;
    for(int i=LIN-27; i<LIN-24; i++)
        for(int j=COL-42; j<COL-26; j++)
            map[i][j] = WALL;
    for (int i=LIN-27; i<LIN-12; i++)
    {
        map[i][COL-60] = WALL;
    }
    for(int j=COL-70; j<COL-49; j++)
    {
        map[LIN-21][j] = WALL;
    }

    // CASA DOS FANTASMAS
    // CASA FANTASMA 1
    map[16][56] = ' ';
    map[16][57] = ' ';
    map[16][58] = ' ';
    map[16][59] = ' ';
    
    map[17][56] = ' ';
    map[17][57] = ' ';
    map[17][58] = ' ';
    map[17][59] = ' ';
    
    map[18][56] = ' ';
    map[18][57] = ' ';
    map[18][58] = ' ';
    map[18][59] = ' ';
    // CASA FANTASMA 2
    map[16][61] = ' ';
    map[16][62] = ' ';
    map[16][63] = ' ';
    map[16][64] = ' ';
    
    map[17][61] = ' ';
    map[17][62] = ' ';
    map[17][63] = ' ';
    map[17][64] = ' ';
    
    map[18][61] = ' ';
    map[18][62] = ' ';
    map[18][63] = ' ';
    map[18][64] = ' ';
    // CASA FANTASMA 3
    map[20][56] = ' ';
    map[20][57] = ' ';
    map[20][58] = ' ';
    map[20][59] = ' ';
    
    map[21][56] = ' ';
    map[21][57] = ' ';
    map[21][58] = ' ';
    map[21][59] = ' ';
    
    map[22][56] = ' ';
    map[22][57] = ' ';
    map[22][58] = ' ';
    map[22][59] = ' ';
    // CASA 4 FANTASMA
    map[20][61] = ' ';
    map[20][62] = ' ';
    map[20][63] = ' ';
    map[20][64] = ' ';

    map[21][61] = ' ';
    map[21][62] = ' ';
    map[21][63] = ' ';
    map[21][64] = ' ';

    map[22][61] = ' ';
    map[22][62] = ' ';
    map[22][63] = ' ';
    map[22][64] = ' ';
}

void display_map(char **map, pacman pacman, ghost blinky, ghost pinky, ghost inky, ghost clyde)
{
    int i,j;
    clear();
    refresh();
    for (i=1; i<LIN; i++)
    {
        for(j=1; j<COL; j++)
        {
            if(map[i][j] == WALL)
            {
                attron(COLOR_PAIR(WALL_PAIR));
                printw("%c",map[i][j]);
                attroff(COLOR_PAIR(WALL_PAIR));
            }
            else if(map[i][j] == ESP_FOOD)
            {
                attron(COLOR_PAIR(ESP_FOOD_PAIR));
                printw("%c",map[i][j]);
                attroff(COLOR_PAIR(ESP_FOOD_PAIR));
            }
            else if(map[i][j] == PACMAN)
            {
                attron(COLOR_PAIR(PACMAN_PAIR));
                printw("%c",map[i][j]);
                attroff(COLOR_PAIR(PACMAN_PAIR));
            }
            else if(map[i][j] == BLINKY && pacman.power_up == 1)
            {
                attron(COLOR_PAIR(SCARED_PAIR));
                printw("%c",map[i][j]);
                attroff(COLOR_PAIR(SCARED_PAIR));
            }
            else if(map[i][j] == BLINKY)
            {
                attron(COLOR_PAIR(BLINKY_PAIR));
                printw("%c",map[i][j]);
                attroff(COLOR_PAIR(BLINKY_PAIR));
            }
            else if(map[i][j] == PINKY && pacman.power_up == 1)
            {
                attron(COLOR_PAIR(SCARED_PAIR));
                printw("%c",map[i][j]);
                attroff(COLOR_PAIR(SCARED_PAIR));
            }
            else if(map[i][j] == PINKY)
            {
                attron(COLOR_PAIR(PINKY_PAIR));
                printw("%c",map[i][j]);
                attroff(COLOR_PAIR(PINKY_PAIR));
            }
            else if(map[i][j] == INKY && pacman.power_up == 1)
            {
                attron(COLOR_PAIR(SCARED_PAIR));
                printw("%c",map[i][j]);
                attroff(COLOR_PAIR(SCARED_PAIR));                
            }
            else if(map[i][j] == INKY)
            {
                attron(COLOR_PAIR(INKY_PAIR));
                printw("%c",map[i][j]);
                attroff(COLOR_PAIR(INKY_PAIR));                
            }
            else if(map[i][j] == CLYDE && pacman.power_up == 1)
            {
                attron(COLOR_PAIR(SCARED_PAIR));
                printw("%c",map[i][j]);
                attroff(COLOR_PAIR(SCARED_PAIR));
            }
            else if(map[i][j] == CLYDE)
            {
                attron(COLOR_PAIR(CLYDE_PAIR));
                printw("%c",map[i][j]);
                attroff(COLOR_PAIR(CLYDE_PAIR));
            }
            else
            {
                printw("%c",map[i][j]);
            }
        }
        printw("\n");
    }
    move(3,122);
    printw("Pacman Score: %i", pacman.score);
    move(4,122);
    printw("Pacman's Life: %i", pacman.life);
    move(5,122);
    printw("Pacman PowerUp: %i", pacman.power_up);
    move(3, 140);
    printw("Blinky Total Kills: %i", blinky.kills);
    move(4, 140);
    printw("Pinky Total Kills: %i", pinky.kills);
    move(5, 140);
    printw("Inky Total Kills: %i", inky.kills);
    move(6, 140);
    printw("Clyde Total Kills: %i", clyde.kills);
    refresh();
}

int calc_dist(int X, int Y, int x, int y)
{
    return sqrt(pow(X-x,2) + pow(Y-y,2));
}

ghost ini_ghost(int kills, char last_move, char ghost_ID, char **map,int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,int x5,int y5,int x6,int y6,int x7,int y7,int x8,int y8)
{
    ghost tmp;
    tmp.kills = kills;
    tmp.last_move = last_move;
    tmp.x0 = x0;
    tmp.x1 = x1;
    tmp.x2 = x2;
    tmp.x3 = x3;
    tmp.x4 = x4;
    tmp.x5 = x5;
    tmp.x6 = x6;
    tmp.x7 = x7;
    tmp.x8 = x8;
    tmp.y0 = y0;
    tmp.y1 = y1;
    tmp.y2 = y2;
    tmp.y3 = y3;
    tmp.y4 = y4;
    tmp.y5 = y5;
    tmp.y6 = y6;
    tmp.y7 = y7;
    tmp.y8 = y8;
    tmp.character = ghost_ID;
    tmp.chase = 1;
    map[x0][y0] = tmp.character;
    map[x1][y1] = tmp.character;
    map[x2][y2] = tmp.character;
    map[x3][y3] = tmp.character;
    map[x4][y4] = tmp.character;
    map[x5][y5] = tmp.character;
    map[x6][y6] = tmp.character;
    map[x7][y7] = tmp.character;
    map[x8][y8] = tmp.character;
    return tmp;
}

ghost blinky_movement(char **map, ghost blinky, pacman pacman)
{
    // VERIFICA O QUE TEM NO LADO ESQUERDO DO FANTASMA 
    char before_blinky_left_y0,before_blinky_left_y3,before_blinky_left_y6;
    before_blinky_left_y0 = map[blinky.x0][blinky.y0-1];    
    before_blinky_left_y3 = map[blinky.x3][blinky.y3-1];    
    before_blinky_left_y6 = map[blinky.x6][blinky.y6-1];

    // VERIFICA O QUE TEM NO LADO DIREITO DO FANTASMA
    char before_blinky_right_y2,before_blinky_right_y5,before_blinky_right_y8;
    before_blinky_right_y2 = map[blinky.x2][blinky.y2+1];
    before_blinky_right_y5 = map[blinky.x5][blinky.y5+1];
    before_blinky_right_y8 = map[blinky.x8][blinky.y8+1];

    // VERIFICA O QUE TEM ACIMA DO FANTASMA
    char before_blinky_up_x0,before_blinky_up_x1,before_blinky_up_x2;
    before_blinky_up_x0 = map[blinky.x0-1][blinky.y0];
    before_blinky_up_x1 = map[blinky.x1-1][blinky.y1];
    before_blinky_up_x2 = map[blinky.x2-1][blinky.y2];

    // VERIFICA O QUE TEM ABAIXO DO FANTASMA
    char before_blinky_down_x6,before_blinky_down_x7,before_blinky_down_x8;
    before_blinky_down_x6 = map[blinky.x6+1][blinky.y6];
    before_blinky_down_x7 = map[blinky.x7+1][blinky.y7];
    before_blinky_down_x8 = map[blinky.x8+1][blinky.y8];

    // BLOCO QUE ESCOLHE MENOR DISTÂNCIA COM BASE NA MENOR POSIÇÃO
    int small_dist, blinky_posx_menor1, blinky_posx_menor2, blinky_posx_menor3, blinky_posy_menor1, blinky_posy_menor2, blinky_posy_menor3;
    small_dist = calc_dist(blinky.x4,blinky.y4,pacman.x4,pacman.y4);
    blinky_posx_menor1 = blinky.x4;
    blinky_posy_menor1 = blinky.y4;
    // VERIFICA SE IR PARA ESQUERDA(Yn-1) É A MENOR DISTÂNCIA COMPARADA COM O CENTRO DO FANTASMA
    if((calc_dist(blinky.x4,blinky.y4-1,pacman.x4,pacman.y4) < small_dist))
    {
        if((before_blinky_left_y0 != WALL) && (before_blinky_left_y3 != WALL) && (before_blinky_left_y6 != WALL))
        {
            blinky_posy_menor1 = blinky.y0-1;
            blinky_posy_menor2 = blinky.y3-1;
            blinky_posy_menor3 = blinky.y6-1;

            blinky_posx_menor1 = blinky.x0;
            blinky_posx_menor2 = blinky.x3;
            blinky_posx_menor3 = blinky.x6;
        }
    }
    // VERIFICA SE IR PARA DIREITA(Yn+1) É A MENOR DISTÂNCIA COMPARADA COM O CENTRO DO FANTASMA
    else if((calc_dist(blinky.x4,blinky.y4+1,pacman.x4,pacman.y4) < small_dist))
    {
        if((before_blinky_right_y2 != WALL) && (before_blinky_right_y5 != WALL) && (before_blinky_right_y8 != WALL))
        {
            blinky_posy_menor1 = blinky.y2+1;
            blinky_posy_menor2 = blinky.y5+1;
            blinky_posy_menor3 = blinky.y8+1;

            blinky_posx_menor1 = blinky.x2;
            blinky_posx_menor2 = blinky.x5;
            blinky_posx_menor3 = blinky.x8;
        }
    }
    // VERIFICA SE IR PARA CIMA(Xn-1) É A MENOR DISTÂNCIA COMPARADA COM O CENTRO DO FANTASMA
    if((calc_dist(blinky.x4-1,blinky.y4,pacman.x4,pacman.y4) < small_dist))
    {
        if((before_blinky_up_x0 != WALL) && (before_blinky_up_x1 != WALL) && (before_blinky_up_x2 != WALL))
        {
            blinky_posx_menor1 = blinky.x0-1;
            blinky_posx_menor2 = blinky.x1-1;
            blinky_posx_menor3 = blinky.x2-1;

            blinky_posy_menor1 = blinky.y0;
            blinky_posy_menor2 = blinky.y1;
            blinky_posy_menor3 = blinky.y2;
        }
    }
    // VERIFICA SE IR PARA BAIXO(Xn+1) É A MENOR DISTÂNCIA COMPARADA COM O CENTRO DO FANTASMA
    else if((calc_dist(blinky.x4+1,blinky.y4,pacman.x4,pacman.y4) < small_dist))
    {
        if((before_blinky_down_x6 != WALL) && (before_blinky_down_x7 != WALL) && (before_blinky_down_x8 != WALL))
        {
            blinky_posx_menor1 = blinky.x6+1;
            blinky_posx_menor2 = blinky.x7+1;
            blinky_posx_menor3 = blinky.x8+1;

            blinky_posy_menor1 = blinky.y6;
            blinky_posy_menor2 = blinky.y7;
            blinky_posy_menor3 = blinky.y8;
        }
    }
    // BLOCO QUE ESCOLHE MENOR DISTÂNCIA COM BASE NA COLUNA OU LINHA MAIS PRÓXIMA
    if((blinky.x4 == blinky_posx_menor1) && (blinky.y4 == blinky_posy_menor1))
    {
        // CIMA, Xn-1
        if((before_blinky_up_x0 != WALL) && (before_blinky_up_x1 != WALL) && (before_blinky_up_x2 != WALL))
        {
            if(pow((blinky.x4-1)-pacman.x4,2) < pow(blinky.x4-pacman.x4,2))
            {
                blinky_posx_menor1 = blinky.x0-1;
                blinky_posx_menor2 = blinky.x1-1;
                blinky_posx_menor3 = blinky.x2-1;

                blinky_posy_menor1 = blinky.y0;
                blinky_posy_menor2 = blinky.y1;
                blinky_posy_menor3 = blinky.y2;
            }
        }
        // BAIXO, Xn+1
        else if((before_blinky_down_x6 != WALL) && (before_blinky_down_x7 != WALL) && (before_blinky_down_x8 != WALL))
        {
            if(pow((blinky.x4+1)-pacman.x4,2) < pow(blinky.x4-pacman.x4,2))
            {
                blinky_posx_menor1 = blinky.x6+1;
                blinky_posx_menor2 = blinky.x7+1;
                blinky_posx_menor3 = blinky.x8+1;

                blinky_posy_menor1 = blinky.y6;
                blinky_posy_menor2 = blinky.y7;
                blinky_posy_menor3 = blinky.y8;
            }
        }
        // ESQUERDA, Yn-1
        if((before_blinky_left_y0 != WALL) && (before_blinky_left_y3 !=WALL) && (before_blinky_left_y6 != WALL))
        {
            if(pow((blinky.y4-1)-pacman.y4,2) < pow(blinky.y4-pacman.y4,2))
            {
                blinky_posy_menor1 = blinky.y0-1;
                blinky_posy_menor2 = blinky.y3-1;
                blinky_posy_menor3 = blinky.y6-1;

                blinky_posx_menor1 = blinky.x0;
                blinky_posx_menor2 = blinky.x3;
                blinky_posx_menor3 = blinky.x6;
            }
        }
        // DIREITA, Yn+1
        else if((before_blinky_right_y2 != WALL) && (before_blinky_right_y5 != WALL) && (before_blinky_right_y8 != WALL))
        {
            if(pow((blinky.y4+1)-pacman.y4,2) < pow(blinky.y4-pacman.y4,2))
            {
                blinky_posy_menor1 = blinky.y2+1;
                blinky_posy_menor2 = blinky.y5+1;
                blinky_posy_menor3 = blinky.y8+1;

                blinky_posx_menor1 = blinky.x2;
                blinky_posx_menor2 = blinky.x5;
                blinky_posx_menor3 = blinky.x8;
            }
        }
    }
    // MOVIMENTA FANTASMA
    // MOVIMENTA PARA ESQUERDA <
    if((blinky_posy_menor1 == blinky.y0-1) && (blinky_posy_menor2 == blinky.y3-1) && (blinky_posy_menor3 == blinky.y6-1))
        if((before_blinky_left_y0 != WALL) && (before_blinky_left_y3 != WALL) && (before_blinky_left_y6 != WALL))
            if((before_blinky_left_y0 != PINKY) && (before_blinky_left_y3 != PINKY) && (before_blinky_left_y6 != PINKY))
                if((before_blinky_left_y0 != INKY) && (before_blinky_left_y3 != INKY) && (before_blinky_left_y6 != INKY))
                    if((before_blinky_left_y0 != CLYDE) && (before_blinky_left_y3 != CLYDE) && (before_blinky_left_y6 != CLYDE))
                    {
                        map[blinky.x0][blinky.y0] = before_blinky_left_y0;
                        map[blinky.x0][blinky.y0-1] = blinky.character;
                        blinky.y0 = blinky.y0-1;

                        map[blinky.x3][blinky.y3] = before_blinky_left_y3;
                        map[blinky.x3][blinky.y3-1] = blinky.character;
                        blinky.y3 = blinky.y3-1;

                        map[blinky.x6][blinky.y6] = before_blinky_left_y6;
                        map[blinky.x6][blinky.y6-1] = blinky.character;
                        blinky.y6 = blinky.y6-1;        
                        
                        map[blinky.x1][blinky.y1] = before_blinky_left_y0;
                        map[blinky.x1][blinky.y1-1] = blinky.character;
                        blinky.y1 = blinky.y1-1;        
                        
                        map[blinky.x4][blinky.y4] = before_blinky_left_y3;
                        map[blinky.x4][blinky.y4-1] = blinky.character;
                        blinky.y4 = blinky.y4-1;
                        
                        map[blinky.x7][blinky.y7] = before_blinky_left_y6;
                        map[blinky.x7][blinky.y7-1] = blinky.character;
                        blinky.y7 = blinky.y7-1;
                        
                        map[blinky.x2][blinky.y2] = before_blinky_left_y0;
                        map[blinky.x2][blinky.y2-1] = blinky.character;
                        blinky.y2 = blinky.y2-1;
                        
                        map[blinky.x5][blinky.y5] = before_blinky_left_y3;
                        map[blinky.x5][blinky.y5-1] = blinky.character;
                        blinky.y5 = blinky.y5-1;
                        
                        map[blinky.x8][blinky.y8] = before_blinky_left_y6;
                        map[blinky.x8][blinky.y8-1] = blinky.character;
                        blinky.y8 = blinky.y8-1;
                    }
    // MOVIMENTA PARA DIREITA >
    if((blinky_posy_menor1 == blinky.y2+1) && (blinky_posy_menor2 == blinky.y5+1) && (blinky_posy_menor3 == blinky.y8+1))
        if((before_blinky_right_y2 != WALL) && (before_blinky_right_y5 != WALL) && (before_blinky_right_y8 != WALL))
            if((before_blinky_right_y2 != PINKY) && (before_blinky_right_y5 != PINKY) && (before_blinky_right_y8 != PINKY))
                if((before_blinky_right_y2 != INKY) && (before_blinky_right_y5 != INKY) && (before_blinky_right_y8 != INKY))
                    if((before_blinky_right_y2 != CLYDE) && (before_blinky_right_y5 != CLYDE) && (before_blinky_right_y8 != CLYDE))
                    {
                        map[blinky.x2][blinky.y2] = before_blinky_right_y2;
                        map[blinky.x2][blinky.y2+1] = blinky.character;
                        blinky.y2 = blinky.y2+1;

                        map[blinky.x5][blinky.y5] = before_blinky_right_y5;
                        map[blinky.x5][blinky.y5+1] = blinky.character;
                        blinky.y5 = blinky.y5+1;

                        map[blinky.x8][blinky.y8] = before_blinky_right_y8;
                        map[blinky.x8][blinky.y8+1] = blinky.character;
                        blinky.y8 = blinky.y8+1;

                        map[blinky.x1][blinky.y1] = before_blinky_right_y2;
                        map[blinky.x1][blinky.y1+1] = blinky.character;
                        blinky.y1 = blinky.y1+1;

                        map[blinky.x4][blinky.y4] = before_blinky_right_y5;;
                        map[blinky.x4][blinky.y4+1] = blinky.character;
                        blinky.y4 = blinky.y4+1;

                        map[blinky.x7][blinky.y7] = before_blinky_right_y8;
                        map[blinky.x7][blinky.y7+1] = blinky.character;
                        blinky.y7 = blinky.y7+1;

                        map[blinky.x0][blinky.y0] = before_blinky_right_y2;
                        map[blinky.x0][blinky.y0+1] = blinky.character;
                        blinky.y0 = blinky.y0+1;

                        map[blinky.x3][blinky.y3] = before_blinky_right_y5;
                        map[blinky.x3][blinky.y3+1] = blinky.character;
                        blinky.y3 = blinky.y3+1;  

                        map[blinky.x6][blinky.y6] = before_blinky_right_y8;
                        map[blinky.x6][blinky.y6+1] = blinky.character;
                        blinky.y6 = blinky.y6+1;
                    }        
    // MOVIMENTA PARA CIMA ^
    if((blinky_posx_menor1 == blinky.x0-1) && (blinky_posx_menor2 == blinky.x1-1) && (blinky_posx_menor3 == blinky.x2-1))
        if((before_blinky_up_x0 != WALL) && (before_blinky_up_x1 != WALL) && (before_blinky_up_x2 != WALL))
            if((before_blinky_up_x0 != PINKY) && (before_blinky_up_x1 != PINKY) && (before_blinky_up_x2 != PINKY))
                if((before_blinky_up_x0 != INKY) && (before_blinky_up_x1 != INKY) && (before_blinky_up_x2 != INKY))
                    if((before_blinky_up_x0 != CLYDE) && (before_blinky_up_x1 != CLYDE) && (before_blinky_up_x2 != CLYDE))
                    {
                        map[blinky.x0][blinky.y0] = before_blinky_up_x0;
                        map[blinky.x0-1][blinky.y0] = blinky.character;
                        blinky.x0 = blinky.x0-1;

                        map[blinky.x1][blinky.y1] = before_blinky_up_x1;
                        map[blinky.x1-1][blinky.y1] = blinky.character;
                        blinky.x1 = blinky.x1-1;

                        map[blinky.x2][blinky.y2] = before_blinky_up_x2;
                        map[blinky.x2-1][blinky.y2] = blinky.character;
                        blinky.x2 = blinky.x2-1;

                        map[blinky.x3][blinky.y3] = before_blinky_up_x0;
                        map[blinky.x3-1][blinky.y3] = blinky.character;
                        blinky.x3 = blinky.x3-1;

                        map[blinky.x4][blinky.y4] = before_blinky_up_x1;
                        map[blinky.x4-1][blinky.y4] = blinky.character;
                        blinky.x4 = blinky.x4-1;

                        map[blinky.x5][blinky.y5] = before_blinky_up_x2;
                        map[blinky.x5-1][blinky.y5] = blinky.character;
                        blinky.x5 = blinky.x5-1;

                        map[blinky.x6][blinky.y6] = before_blinky_up_x0;
                        map[blinky.x6-1][blinky.y6] = blinky.character;
                        blinky.x6 = blinky.x6-1;

                        map[blinky.x7][blinky.y7] = before_blinky_up_x1;
                        map[blinky.x7-1][blinky.y7] = blinky.character;
                        blinky.x7 = blinky.x7-1;

                        map[blinky.x8][blinky.y8] = before_blinky_up_x2;
                        map[blinky.x8-1][blinky.y8] = blinky.character;
                        blinky.x8 = blinky.x8-1;
                    }
    // MOVIMENTA PARA BAIXO 
    if((blinky_posx_menor1 == blinky.x6+1) && (blinky_posx_menor2 == blinky.x7+1) && (blinky_posx_menor3 == blinky.x8+1))
        if((before_blinky_down_x6 != WALL) && (before_blinky_down_x7 != WALL) && (before_blinky_down_x8 != WALL))
            if((before_blinky_down_x6 != PINKY) && (before_blinky_down_x7 != PINKY) && (before_blinky_down_x8 != PINKY))
                if((before_blinky_down_x6 != INKY) && (before_blinky_down_x7 != INKY) && (before_blinky_down_x8 != INKY))
                    if((before_blinky_down_x6 != CLYDE) && (before_blinky_down_x7 != CLYDE) && (before_blinky_down_x8 != CLYDE))
                    {
                        map[blinky.x6][blinky.y6] = before_blinky_down_x6;
                        map[blinky.x6+1][blinky.y6] = blinky.character;
                        blinky.x6 = blinky.x6+1;

                        map[blinky.x7][blinky.y7] = before_blinky_down_x7;
                        map[blinky.x7+1][blinky.y7] = blinky.character;
                        blinky.x7 = blinky.x7+1;

                        map[blinky.x8][blinky.y8] = before_blinky_down_x8;
                        map[blinky.x8+1][blinky.y8] = blinky.character;
                        blinky.x8 = blinky.x8+1;

                        map[blinky.x3][blinky.y3] = before_blinky_down_x6;
                        map[blinky.x3+1][blinky.y3] = blinky.character;
                        blinky.x3 = blinky.x3+1;

                        map[blinky.x4][blinky.y4] = before_blinky_down_x7;
                        map[blinky.x4+1][blinky.y4] = blinky.character;
                        blinky.x4 = blinky.x4+1;

                        map[blinky.x5][blinky.y5] = before_blinky_down_x8;
                        map[blinky.x5+1][blinky.y5] = blinky.character;
                        blinky.x5 = blinky.x5+1;

                        map[blinky.x0][blinky.y0] = before_blinky_down_x6;
                        map[blinky.x0+1][blinky.y0] =  blinky.character;
                        blinky.x0 = blinky.x0+1;

                        map[blinky.x1][blinky.y1] = before_blinky_down_x7;
                        map[blinky.x1+1][blinky.y1] = blinky.character;
                        blinky.x1 = blinky.x1+1;

                        map[blinky.x2][blinky.y2] = before_blinky_down_x8;
                        map[blinky.x2+1][blinky.y2] = blinky.character;
                        blinky.x2 = blinky.x2+1;
                    }
    // VERIFICA SE BLINKY MATOU PACMAN
    if(pacman.power_up == 0)
    {
      if((blinky.x0 == pacman.x0 && blinky.y0==pacman.y0)&&(blinky.x1==pacman.x1 && blinky.y1==pacman.y1)&&(blinky.x2==pacman.x2 && blinky.y2==pacman.y2))
         blinky.kills++;
      else if((blinky.x0 == pacman.x0 && blinky.y0==pacman.y0)&&(blinky.x3==pacman.x3 && blinky.y3==pacman.y3)&&(blinky.x6==pacman.x6 && blinky.y6==pacman.y6))
         blinky.kills++;
      else if((blinky.x2 == pacman.x2 && blinky.y2==pacman.y2)&&(blinky.x5==pacman.x5 && blinky.y5==pacman.y5)&&(blinky.x8==pacman.x8 && blinky.y8==pacman.y8))
         blinky.kills++;
      else if((blinky.x6 == pacman.x6 && blinky.y6==pacman.y6)&&(blinky.x7==pacman.x7 && blinky.y7==pacman.y7)&&(blinky.x8==pacman.x8 && blinky.y8==pacman.y8))
         blinky.kills++;
    }
    else if(pacman.power_up == 1)
    {
      if((blinky.x0 == pacman.x0 && blinky.y0==pacman.y0)&&(blinky.x1==pacman.x1 && blinky.y1==pacman.y1)&&(blinky.x2==pacman.x2 && blinky.y2==pacman.y2))
         blinky.last_move = 'k';
      else if((blinky.x0 == pacman.x0 && blinky.y0==pacman.y0)&&(blinky.x3==pacman.x3 && blinky.y3==pacman.y3)&&(blinky.x6==pacman.x6 && blinky.y6==pacman.y6))
         blinky.last_move = 'k';
      else if((blinky.x2 == pacman.x2 && blinky.y2==pacman.y2)&&(blinky.x5==pacman.x5 && blinky.y5==pacman.y5)&&(blinky.x8==pacman.x8 && blinky.y8==pacman.y8))
         blinky.last_move = 'k';
      else if((blinky.x6 == pacman.x6 && blinky.y6==pacman.y6)&&(blinky.x7==pacman.x7 && blinky.y7==pacman.y7)&&(blinky.x8==pacman.x8 && blinky.y8==pacman.y8))
         blinky.last_move = 'k';
    }
    return blinky;
}

ghost pinky_movement(char **map, ghost pinky, pacman pacman, int key_pressed, char last_move)
{
    // VERIFICA PARA ONDE PACMAN ESTÁ INDO
    int target_up, target_down, target_left, target_right, pacman_x4, pacman_y4;
    if(key_pressed == KEY_LEFT)
    {
        target_left = 1;
        target_right = 0;
        target_down = 0;
        target_up = 0;
        pacman_y4 = (pacman.y4-1)-5;
        pacman_x4 = pacman.x4;
    }       
    else if(key_pressed == KEY_RIGHT)
    {
        target_left = 0;
        target_right = 1;
        target_down = 0;
        target_up = 0;
        pacman_y4 = (pacman.y4+1)+5;
        pacman_x4 = pacman.x4;
    }
    else if(key_pressed == KEY_UP)
    {
        target_left = 0;
        target_right = 0;
        target_down = 0;
        target_up = 1;
        pacman_y4 = pacman.y4;
        pacman_x4 = (pacman.x4-1)-5;
    }
    else if(key_pressed == KEY_DOWN)
    {
        target_left = 0;
        target_right = 0;
        target_down = 1;
        target_up = 0;
        pacman_y4 = pacman.y4;
        pacman_x4 = (pacman.x4+1)+5;
    }
    else
    {
        if(last_move == 'r')
        {
            target_left = 0;
            target_right = 1;
            target_down = 0;
            target_up = 0;
            pacman_y4 = (pacman.y4+1)+5;
            pacman_x4 = pacman.x4;
        }
        else if(last_move == 'l')
        {
            target_left = 1;
            target_right = 0;
            target_down = 0;
            target_up = 0;
            pacman_y4 = (pacman.y4-1)-5;
            pacman_x4 = pacman.x4;
        }
        else if(last_move == 'd')
        {
            target_left = 0;
            target_right = 0;
            target_down = 1;
            target_up = 0;
            pacman_y4 = pacman.y4;
            pacman_x4 = (pacman.x4+1)+5;
        }
        else
        {
            target_left = 0;
            target_right = 0;
            target_down = 0;
            target_up = 1;
            pacman_y4 = pacman.y4;
            pacman_x4 = (pacman.x4-1)-5;
        }
    }
    // VERIFICA O QUE TEM NO LADO ESQUERDO DO FANTASMA
    char before_pinky_left_y0, before_pinky_left_y3, before_pinky_left_y6;
    before_pinky_left_y0 = map[pinky.x0][pinky.y0-1];
    before_pinky_left_y3 = map[pinky.x3][pinky.y3-1];
    before_pinky_left_y6 = map[pinky.x6][pinky.y6-1];
    
    // VERIFICA O QUE TEM NO LADO DIREITO DO FANTASMA
    char before_pinky_right_y2, before_pinky_right_y5, before_pinky_right_y8;
    before_pinky_right_y2 = map[pinky.x2][pinky.y2+1];
    before_pinky_right_y5 = map[pinky.x5][pinky.y5+1];
    before_pinky_right_y8 = map[pinky.x8][pinky.y8+1];

    // VERIFICA O QUE TEM ACIMA DO FANTASMA
    char before_pinky_up_x0, before_pinky_up_x1, before_pinky_up_x2;
    before_pinky_up_x0 = map[pinky.x0-1][pinky.y0];
    before_pinky_up_x1 = map[pinky.x1-1][pinky.y1];
    before_pinky_up_x2 = map[pinky.x2-1][pinky.y2];
    
    // VERIFICA O QUE TEM ABAIXO DO FANTASMA
    char before_pinky_down_x6, before_pinky_down_x7, before_pinky_down_x8;
    before_pinky_down_x6 = map[pinky.x6+1][pinky.y6];
    before_pinky_down_x7 = map[pinky.x7+1][pinky.y7];
    before_pinky_down_x8 = map[pinky.x8+1][pinky.y8];
 
    int small_dist, pinky_posx_menor1, pinky_posx_menor2, pinky_posx_menor3, pinky_posy_menor1, pinky_posy_menor2, pinky_posy_menor3;
    small_dist = calc_dist(pinky.x4,pinky.y4,pacman_x4,pacman_y4);
    pinky_posx_menor1 = pinky.x4;
    pinky_posy_menor1 = pinky.y4;
    // VERIFICA SE IR PARA ESQUERDA(Yn-1) É A MENOR DISTÂNCIA COMPARADA COM O CENTRO DO FANTASMA
    if((calc_dist(pinky.x4,pinky.y4-1,pacman_x4,pacman_y4) < small_dist))
    {
        if((before_pinky_left_y0 != WALL) && (before_pinky_left_y3 != WALL) && (before_pinky_left_y6 != WALL))
        {
            pinky_posy_menor1 = pinky.y0-1;
            pinky_posy_menor2 = pinky.y3-1;
            pinky_posy_menor3 = pinky.y6-1;

            pinky_posx_menor1 = pinky.x0;
            pinky_posx_menor2 = pinky.x3;
            pinky_posx_menor3 = pinky.x6;
        }
    }
    // VERIFICA SE IR PARA DIREITA(Yn+1) É A MENOR DISTÂNCIA COMPARADA COM O CENTRO DO FANTASMA
    else if((calc_dist(pinky.x4,pinky.y4+1,pacman_x4,pacman_y4) < small_dist))
    {
        if((before_pinky_right_y2 != WALL) && (before_pinky_right_y5 != WALL) && (before_pinky_right_y8 != WALL))
        {
            pinky_posy_menor1 = pinky.y2+1;
            pinky_posy_menor2 = pinky.y5+1;
            pinky_posy_menor3 = pinky.y8+1;

            pinky_posx_menor1 = pinky.x2;
            pinky_posx_menor2 = pinky.x5;
            pinky_posx_menor3 = pinky.x8;
        }
    }
    // VERIFICA SE IR PARA CIMA(Xn-1) É A MENOR DISTÂNCIA COMPARADA COM O CENTRO DO FANTASMA
    if((calc_dist(pinky.x4-1,pinky.y4,pacman_x4,pacman_y4) < small_dist))
    {
        if((before_pinky_up_x0 != WALL) && (before_pinky_up_x1 != WALL) && (before_pinky_up_x2 != WALL))
        {
            pinky_posx_menor1 = pinky.x0-1;
            pinky_posx_menor2 = pinky.x1-1;
            pinky_posx_menor3 = pinky.x2-1;

            pinky_posy_menor1 = pinky.y0;
            pinky_posy_menor2 = pinky.y1;
            pinky_posy_menor3 = pinky.y2;
        }
    }
    // VERIFICA SE IR PARA BAIXO(Xn+1) É A MENOR DISTÂNCIA COMPARADA COM O CENTRO DO FANTASMA
    else if((calc_dist(pinky.x4+1,pinky.y4,pacman_x4,pacman_y4) < small_dist))
    {
        if((before_pinky_down_x6 != WALL) && (before_pinky_down_x7 != WALL) && (before_pinky_down_x8 != WALL))
        {
            pinky_posx_menor1 = pinky.x6+1;
            pinky_posx_menor2 = pinky.x7+1;
            pinky_posx_menor3 = pinky.x8+1;

            pinky_posy_menor1 = pinky.y6;
            pinky_posy_menor2 = pinky.y7;
            pinky_posy_menor3 = pinky.y8;
        }
    }
    // BLOCO QUE ESCOLHE MENOR DISTÂNCIA COM BASE NA COLUNA OU LINHA MAIS PRÓXIMA
    if((pinky.x4 == pinky_posx_menor1) && (pinky.y4 == pinky_posy_menor1))
    {
        // CIMA, Xn-1
        if((before_pinky_up_x0 != WALL) && (before_pinky_up_x1 != WALL) && (before_pinky_up_x2 != WALL))
        {
            if(pow((pinky.x4-1)-pacman_x4,2) < pow(pinky.x4-pacman_x4,2))
            {
                pinky_posx_menor1 = pinky.x0-1;
                pinky_posx_menor2 = pinky.x1-1;
                pinky_posx_menor3 = pinky.x2-1;

                pinky_posy_menor1 = pinky.y0;
                pinky_posy_menor2 = pinky.y1;
                pinky_posy_menor3 = pinky.y2;
            }
        }
        // BAIXO, Xn+1
        else if((before_pinky_down_x6!=WALL) && (before_pinky_down_x7 != WALL) && (before_pinky_down_x8 != WALL))
        {
            if(pow((pinky.x4+1)-pacman_x4,2) < pow(pinky.x4-pacman_x4,2))
            {
                pinky_posx_menor1 = pinky.x6+1;
                pinky_posx_menor2 = pinky.x7+1;
                pinky_posx_menor3 = pinky.x8+1;

                pinky_posy_menor1 = pinky.y6;
                pinky_posy_menor2 = pinky.y7;
                pinky_posy_menor3 = pinky.y8;
            }
        }
        // ESQUERDA, Yn-1
        if((before_pinky_left_y0 != WALL) && (before_pinky_left_y3 !=WALL) && (before_pinky_left_y6 != WALL))
        {
            if(pow((pinky.y4-1)-pacman_y4,2) < pow(pinky.y4-pacman_y4,2))
            {
                pinky_posy_menor1 = pinky.y0-1;
                pinky_posy_menor2 = pinky.y3-1;
                pinky_posy_menor3 = pinky.y6-1;

                pinky_posx_menor1 = pinky.x0;
                pinky_posx_menor2 = pinky.x3;
                pinky_posx_menor3 = pinky.x6;
            }
        }
        // DIREITA, Yn+1
        else if((before_pinky_right_y2 != WALL) && (before_pinky_right_y5 != WALL) && (before_pinky_right_y8 != WALL))
        {
            if(pow((pinky.y4+1)-pacman_y4,2) < pow(pinky.y4-pacman_y4,2))
            {
                pinky_posy_menor1 = pinky.y2+1;
                pinky_posy_menor2 = pinky.y5+1;
                pinky_posy_menor3 = pinky.y8+1;

                pinky_posx_menor1 = pinky.x2;
                pinky_posx_menor2 = pinky.x5;
                pinky_posx_menor3 = pinky.x8;
            }
        }
    }
    // MOVIMENTA FANTASMA
    // MOVIMENTA PARA ESQUERDA <
    if((pinky_posy_menor1 == pinky.y0-1) && (pinky_posy_menor2 == pinky.y3-1) && (pinky_posy_menor3 == pinky.y6-1))
        if((before_pinky_left_y0 != WALL) && (before_pinky_left_y3 != WALL) && (before_pinky_left_y6 != WALL))
            if((before_pinky_left_y0 != BLINKY) && (before_pinky_left_y3 != BLINKY) && (before_pinky_left_y6 != BLINKY))
                if((before_pinky_left_y0 != INKY) && (before_pinky_left_y3 != INKY) && (before_pinky_left_y6 != INKY))
                    if((before_pinky_left_y0 != CLYDE) && (before_pinky_left_y3 != CLYDE) && (before_pinky_left_y6 != CLYDE))
                    {
                        map[pinky.x0][pinky.y0] = before_pinky_left_y0;
                        map[pinky.x0][pinky.y0-1] = pinky.character;
                        pinky.y0 = pinky.y0-1;

                        map[pinky.x3][pinky.y3] = before_pinky_left_y3;
                        map[pinky.x3][pinky.y3-1] = pinky.character;
                        pinky.y3 = pinky.y3-1;

                        map[pinky.x6][pinky.y6] = before_pinky_left_y6;
                        map[pinky.x6][pinky.y6-1] = pinky.character;
                        pinky.y6 = pinky.y6-1;        
                        
                        map[pinky.x1][pinky.y1] = before_pinky_left_y0;
                        map[pinky.x1][pinky.y1-1] = pinky.character;
                        pinky.y1 = pinky.y1-1;        
                        
                        map[pinky.x4][pinky.y4] = before_pinky_left_y3;
                        map[pinky.x4][pinky.y4-1] = pinky.character;
                        pinky.y4 = pinky.y4-1;
                        
                        map[pinky.x7][pinky.y7] = before_pinky_left_y6;
                        map[pinky.x7][pinky.y7-1] = pinky.character;
                        pinky.y7 = pinky.y7-1;
                        
                        map[pinky.x2][pinky.y2] = before_pinky_left_y0;
                        map[pinky.x2][pinky.y2-1] = pinky.character;
                        pinky.y2 = pinky.y2-1;
                        
                        map[pinky.x5][pinky.y5] = before_pinky_left_y3;
                        map[pinky.x5][pinky.y5-1] = pinky.character;
                        pinky.y5 = pinky.y5-1;
                        
                        map[pinky.x8][pinky.y8] = before_pinky_left_y6;
                        map[pinky.x8][pinky.y8-1] = pinky.character;
                        pinky.y8 = pinky.y8-1;
                    }
    // MOVIMENTA PARA DIREITA >
    if((pinky_posy_menor1 == pinky.y2+1) && (pinky_posy_menor2 == pinky.y5+1) && (pinky_posy_menor3 == pinky.y8+1))
        if((before_pinky_right_y2 != WALL) && (before_pinky_right_y5 != WALL) && (before_pinky_right_y8 != WALL))
            if((before_pinky_right_y2 != BLINKY) && (before_pinky_right_y5 != BLINKY) && (before_pinky_right_y8 != BLINKY))
                if((before_pinky_right_y2 != INKY) && (before_pinky_right_y5 != INKY) && (before_pinky_right_y8 != INKY))
                    if((before_pinky_right_y2 != CLYDE) && (before_pinky_right_y5 != CLYDE) && (before_pinky_right_y8 != CLYDE))
                    {
                        map[pinky.x2][pinky.y2] = before_pinky_right_y2;
                        map[pinky.x2][pinky.y2+1] = pinky.character;
                        pinky.y2 = pinky.y2+1;

                        map[pinky.x5][pinky.y5] = before_pinky_right_y5;
                        map[pinky.x5][pinky.y5+1] = pinky.character;
                        pinky.y5 = pinky.y5+1;

                        map[pinky.x8][pinky.y8] = before_pinky_right_y8;
                        map[pinky.x8][pinky.y8+1] = pinky.character;
                        pinky.y8 = pinky.y8+1;

                        map[pinky.x1][pinky.y1] = before_pinky_right_y2;
                        map[pinky.x1][pinky.y1+1] = pinky.character;
                        pinky.y1 = pinky.y1+1;

                        map[pinky.x4][pinky.y4] = before_pinky_right_y5;;
                        map[pinky.x4][pinky.y4+1] = pinky.character;
                        pinky.y4 = pinky.y4+1;

                        map[pinky.x7][pinky.y7] = before_pinky_right_y8;
                        map[pinky.x7][pinky.y7+1] = pinky.character;
                        pinky.y7 = pinky.y7+1;

                        map[pinky.x0][pinky.y0] = before_pinky_right_y2;
                        map[pinky.x0][pinky.y0+1] = pinky.character;
                        pinky.y0 = pinky.y0+1;

                        map[pinky.x3][pinky.y3] = before_pinky_right_y5;
                        map[pinky.x3][pinky.y3+1] = pinky.character;
                        pinky.y3 = pinky.y3+1;  

                        map[pinky.x6][pinky.y6] = before_pinky_right_y8;
                        map[pinky.x6][pinky.y6+1] = pinky.character;
                        pinky.y6 = pinky.y6+1;
                    }        
    // MOVIMENTA PARA CIMA ^
    if((pinky_posx_menor1 == pinky.x0-1) && (pinky_posx_menor2 == pinky.x1-1) && (pinky_posx_menor3 == pinky.x2-1))
        if((before_pinky_up_x0 != WALL) && (before_pinky_up_x1 != WALL) && (before_pinky_up_x2 != WALL))
            if((before_pinky_up_x0 != BLINKY) && (before_pinky_up_x1 != BLINKY) && (before_pinky_up_x2 != BLINKY))
                if((before_pinky_up_x0 != INKY) && (before_pinky_up_x1 != INKY) && (before_pinky_up_x2 != INKY))
                    if((before_pinky_up_x0 != CLYDE) && (before_pinky_up_x1 != CLYDE) && (before_pinky_up_x2 != CLYDE))
                    {
                        map[pinky.x0][pinky.y0] = before_pinky_up_x0;
                        map[pinky.x0-1][pinky.y0] = pinky.character;
                        pinky.x0 = pinky.x0-1;

                        map[pinky.x1][pinky.y1] = before_pinky_up_x1;
                        map[pinky.x1-1][pinky.y1] = pinky.character;
                        pinky.x1 = pinky.x1-1;

                        map[pinky.x2][pinky.y2] = before_pinky_up_x2;
                        map[pinky.x2-1][pinky.y2] = pinky.character;
                        pinky.x2 = pinky.x2-1;

                        map[pinky.x3][pinky.y3] = before_pinky_up_x0;
                        map[pinky.x3-1][pinky.y3] = pinky.character;
                        pinky.x3 = pinky.x3-1;

                        map[pinky.x4][pinky.y4] = before_pinky_up_x1;
                        map[pinky.x4-1][pinky.y4] = pinky.character;
                        pinky.x4 = pinky.x4-1;

                        map[pinky.x5][pinky.y5] = before_pinky_up_x2;
                        map[pinky.x5-1][pinky.y5] = pinky.character;
                        pinky.x5 = pinky.x5-1;

                        map[pinky.x6][pinky.y6] = before_pinky_up_x0;
                        map[pinky.x6-1][pinky.y6] = pinky.character;
                        pinky.x6 = pinky.x6-1;

                        map[pinky.x7][pinky.y7] = before_pinky_up_x1;
                        map[pinky.x7-1][pinky.y7] = pinky.character;
                        pinky.x7 = pinky.x7-1;

                        map[pinky.x8][pinky.y8] = before_pinky_up_x2;
                        map[pinky.x8-1][pinky.y8] = pinky.character;
                        pinky.x8 = pinky.x8-1;
                    }
    // MOVIMENTA PARA BAIXO 
    if((pinky_posx_menor1 == pinky.x6+1) && (pinky_posx_menor2 == pinky.x7+1) && (pinky_posx_menor3 == pinky.x8+1))
        if((before_pinky_down_x6 != WALL) && (before_pinky_down_x7 != WALL) && (before_pinky_down_x8 != WALL))
            if((before_pinky_down_x6 != BLINKY) && (before_pinky_down_x7 != BLINKY) && (before_pinky_down_x8 != BLINKY))
                if((before_pinky_down_x6 != INKY) && (before_pinky_down_x7 != INKY) && (before_pinky_down_x8 != INKY))
                    if((before_pinky_down_x6 != CLYDE) && (before_pinky_down_x7 != CLYDE) && (before_pinky_down_x8 != CLYDE))
                    {
                        map[pinky.x6][pinky.y6] = before_pinky_down_x6;
                        map[pinky.x6+1][pinky.y6] = pinky.character;
                        pinky.x6 = pinky.x6+1;

                        map[pinky.x7][pinky.y7] = before_pinky_down_x7;
                        map[pinky.x7+1][pinky.y7] = pinky.character;
                        pinky.x7 = pinky.x7+1;

                        map[pinky.x8][pinky.y8] = before_pinky_down_x8;
                        map[pinky.x8+1][pinky.y8] = pinky.character;
                        pinky.x8 = pinky.x8+1;

                        map[pinky.x3][pinky.y3] = before_pinky_down_x6;
                        map[pinky.x3+1][pinky.y3] = pinky.character;
                        pinky.x3 = pinky.x3+1;

                        map[pinky.x4][pinky.y4] = before_pinky_down_x7;
                        map[pinky.x4+1][pinky.y4] = pinky.character;
                        pinky.x4 = pinky.x4+1;

                        map[pinky.x5][pinky.y5] = before_pinky_down_x8;
                        map[pinky.x5+1][pinky.y5] = pinky.character;
                        pinky.x5 = pinky.x5+1;

                        map[pinky.x0][pinky.y0] = before_pinky_down_x6;
                        map[pinky.x0+1][pinky.y0] =  pinky.character;
                        pinky.x0 = pinky.x0+1;

                        map[pinky.x1][pinky.y1] = before_pinky_down_x7;
                        map[pinky.x1+1][pinky.y1] = pinky.character;
                        pinky.x1 = pinky.x1+1;

                        map[pinky.x2][pinky.y2] = before_pinky_down_x8;
                        map[pinky.x2+1][pinky.y2] = pinky.character;
                        pinky.x2 = pinky.x2+1;
                    }
    // VERIFICA SE PINKY MATOU PACMAN
    if(pacman.power_up == 0)
    {
      if((pinky.x0 == pacman.x0 && pinky.y0==pacman.y0)&&(pinky.x1==pacman.x1 && pinky.y1==pacman.y1)&&(pinky.x2==pacman.x2 && pinky.y2==pacman.y2))
         pinky.kills++;
      else if((pinky.x0 == pacman.x0 && pinky.y0==pacman.y0)&&(pinky.x3==pacman.x3 && pinky.y3==pacman.y3)&&(pinky.x6==pacman.x6 && pinky.y6==pacman.y6))
         pinky.kills++;
      else if((pinky.x2 == pacman.x2 && pinky.y2==pacman.y2)&&(pinky.x5==pacman.x5 && pinky.y5==pacman.y5)&&(pinky.x8==pacman.x8 && pinky.y8==pacman.y8))
         pinky.kills++;
      else if((pinky.x6 == pacman.x6 && pinky.y6==pacman.y6)&&(pinky.x7==pacman.x7 && pinky.y7==pacman.y7)&&(pinky.x8==pacman.x8 && pinky.y8==pacman.y8))
         pinky.kills++;
    }
    else if(pacman.power_up == 1)
    {
      if((pinky.x0 == pacman.x0 && pinky.y0==pacman.y0)&&(pinky.x1==pacman.x1 && pinky.y1==pacman.y1)&&(pinky.x2==pacman.x2 && pinky.y2==pacman.y2))
         pinky.last_move = 'k';
      else if((pinky.x0 == pacman.x0 && pinky.y0==pacman.y0)&&(pinky.x3==pacman.x3 && pinky.y3==pacman.y3)&&(pinky.x6==pacman.x6 && pinky.y6==pacman.y6))
         pinky.last_move = 'k';
      else if((pinky.x2 == pacman.x2 && pinky.y2==pacman.y2)&&(pinky.x5==pacman.x5 && pinky.y5==pacman.y5)&&(pinky.x8==pacman.x8 && pinky.y8==pacman.y8))
         pinky.last_move = 'k';
      else if((pinky.x6 == pacman.x6 && pinky.y6==pacman.y6)&&(pinky.x7==pacman.x7 && pinky.y7==pacman.y7)&&(pinky.x8==pacman.x8 && pinky.y8==pacman.y8))
         pinky.last_move = 'k';
    }
    return pinky;
}

ghost inky_movement(char **map, ghost inky, pacman pacman, ghost blinky)
{
    // SELECIONA O TARGET DO INKY COM BASE NO PACMAN E NO BLINKY
    int target_x = pacman.x4+blinky.x4/2;
    int target_y = pacman.y4+blinky.y4/2;    
    
    // VERIFICA O QUE TEM NO LADO ESQUERDO DO FANTASMA
    char before_inky_left_y0, before_inky_left_y3, before_inky_left_y6;
    before_inky_left_y0 = map[inky.x0][inky.y0-1];
    before_inky_left_y3 = map[inky.x3][inky.y3-1];
    before_inky_left_y6 = map[inky.x6][inky.y6-1];

    // VERIFICA O QUE TEM NO LADO DIREITO
    char before_inky_right_y2, before_inky_right_y5, before_inky_right_y8;
    before_inky_right_y2 = map[inky.x2][inky.y2+1];
    before_inky_right_y5 = map[inky.x5][inky.y5+1];
    before_inky_right_y8 = map[inky.x8][inky.y8+1];

    // VERIFICA O QUE TEM ACIMA DO FANTASMA
    char before_inky_up_x0, before_inky_up_x1, before_inky_up_x2;
    before_inky_up_x0 = map[inky.x0-1][inky.y0];
    before_inky_up_x1 = map[inky.x1-1][inky.y1];
    before_inky_up_x2 = map[inky.x2-1][inky.y2];

    // VERIFICA O QUE TEM ABAIXO DO FANTASMA
    char before_inky_down_x6, before_inky_down_x7, before_inky_down_x8;
    before_inky_down_x6 = map[inky.x6+1][inky.y6];
    before_inky_down_x7 = map[inky.x7+1][inky.y7];
    before_inky_down_x8 = map[inky.x8+1][inky.y8];

    // BLOCO QUE CALCULA O CAMINHO COM A MENOR DISTÂNCIA PARA O TARGET
    int small_dist, inky_posx_menor1, inky_posx_menor2, inky_posx_menor3, inky_posy_menor1, inky_posy_menor2, inky_posy_menor3;
    small_dist = calc_dist(inky.x4,inky.y4,target_x,target_y);
    inky_posx_menor1 = inky.x4;
    inky_posy_menor1 = inky.y4;
    // VERIFICA SE IR PARA ESQUERDA(Yn-1) É A MENOR DISTÂNCIA COMPARADA COM O CENTRO DO FANTASMA
    if((calc_dist(inky.x4,inky.y4-1,target_x,target_y) < small_dist))
    {
        if((before_inky_left_y0 != WALL) && (before_inky_left_y3 != WALL) && (before_inky_left_y6 != WALL))
        {
            inky_posy_menor1 = inky.y0-1;
            inky_posy_menor2 = inky.y3-1;
            inky_posy_menor3 = inky.y6-1;

            inky_posx_menor1 = inky.x0;
            inky_posx_menor2 = inky.x3;
            inky_posx_menor3 = inky.x6;
        }
    }
    // VERIFICA SE IR PARA DIREITA(Yn+1) É A MENOR DISTÂNCIA COMPARADA COM O CENTRO DO FANTASMA
    else if((calc_dist(inky.x4,inky.y4+1,target_x,target_y) < small_dist))
    {
        if((before_inky_right_y2 != WALL) && (before_inky_right_y5 != WALL) && (before_inky_right_y8 != WALL))
        {
            inky_posy_menor1 = inky.y2+1;
            inky_posy_menor2 = inky.y5+1;
            inky_posy_menor3 = inky.y8+1;

            inky_posx_menor1 = inky.x2;
            inky_posx_menor2 = inky.x5;
            inky_posx_menor3 = inky.x8;
        }
    }
    // VERIFICA SE IR PARA CIMA(Xn-1) É A MENOR DISTÂNCIA COMPARADA COM O CENTRO DO FANTASMA
    if((calc_dist(inky.x4-1,inky.y4,target_x,target_y) < small_dist))
    {
        if((before_inky_up_x0 != WALL) && (before_inky_up_x1 != WALL) && (before_inky_up_x2 != WALL))
        {
            inky_posx_menor1 = inky.x0-1;
            inky_posx_menor2 = inky.x1-1;
            inky_posx_menor3 = inky.x2-1;

            inky_posy_menor1 = inky.y0;
            inky_posy_menor2 = inky.y1;
            inky_posy_menor3 = inky.y2;
        }
    }
    // VERIFICA SE IR PARA BAIXO(Xn+1) É A MENOR DISTÂNCIA COMPARADA COM O CENTRO DO FANTASMA
    else if((calc_dist(inky.x4+1,inky.y4,target_x,target_y) < small_dist))
    {
        if((before_inky_down_x6 != WALL) && (before_inky_down_x7 != WALL) && (before_inky_down_x8 != WALL))
        {
            inky_posx_menor1 = inky.x6+1;
            inky_posx_menor2 = inky.x7+1;
            inky_posx_menor3 = inky.x8+1;

            inky_posy_menor1 = inky.y6;
            inky_posy_menor2 = inky.y7;
            inky_posy_menor3 = inky.y8;
        }
    }
   
    // BLOCO QUE ESCOLHE MENOR DISTÂNCIA COM BASE NA COLUNA OU LINHA MAIS PRÓXIMA
    if((inky.x4 == inky_posx_menor1) && (inky.y4 == inky_posy_menor1))
    {
        // CIMA, Xn-1
        if((before_inky_up_x0 != WALL) && (before_inky_up_x1 != WALL) && (before_inky_up_x2 != WALL))
        {
            if(pow((inky.x4-1)-target_x,2) < pow(inky.x4-target_x,2))
            {
                inky_posx_menor1 = inky.x0-1;
                inky_posx_menor2 = inky.x1-1;
                inky_posx_menor3 = inky.x2-1;

                inky_posy_menor1 = inky.y0;
                inky_posy_menor2 = inky.y1;
                inky_posy_menor3 = inky.y2;
            }
        }
        // BAIXO, Xn+1
        else if((before_inky_down_x6!=WALL) && (before_inky_down_x7 != WALL) && (before_inky_down_x8 != WALL))
        {
            if(pow((inky.x4+1)-target_x,2) < pow(inky.x4-target_x,2))
            {
                inky_posx_menor1 = inky.x6+1;
                inky_posx_menor2 = inky.x7+1;
                inky_posx_menor3 = inky.x8+1;

                inky_posy_menor1 = inky.y6;
                inky_posy_menor2 = inky.y7;
                inky_posy_menor3 = inky.y8;
            }
        }
        // ESQUERDA, Yn-1
        if((before_inky_left_y0 != WALL) && (before_inky_left_y3 !=WALL) && (before_inky_left_y6 != WALL))
        {
            if(pow((inky.y4-1)-target_y,2) < pow(inky.y4-target_y,2))
            {
                inky_posy_menor1 = inky.y0-1;
                inky_posy_menor2 = inky.y3-1;
                inky_posy_menor3 = inky.y6-1;

                inky_posx_menor1 = inky.x0;
                inky_posx_menor2 = inky.x3;
                inky_posx_menor3 = inky.x6;
            }
        }
        // DIREITA, Yn+1
        else if((before_inky_right_y2 != WALL) && (before_inky_right_y5 != WALL) && (before_inky_right_y8 != WALL))
        {
            if(pow((inky.y4+1)-target_y,2) < pow(inky.y4-target_y,2))
            {
                inky_posy_menor1 = inky.y2+1;
                inky_posy_menor2 = inky.y5+1;
                inky_posy_menor3 = inky.y8+1;

                inky_posx_menor1 = inky.x2;
                inky_posx_menor2 = inky.x5;
                inky_posx_menor3 = inky.x8;
            }
        }
    }
    // MOVIMENTA FANTASMA
    // MOVIMENTA PARA ESQUERDA <
    if((inky_posy_menor1 == inky.y0-1) && (inky_posy_menor2 == inky.y3-1) && (inky_posy_menor3 == inky.y6-1))
        if((before_inky_left_y0 != WALL) && (before_inky_left_y3 != WALL) && (before_inky_left_y6 != WALL))
            if((before_inky_left_y0 != BLINKY) && (before_inky_left_y3 != BLINKY) && (before_inky_left_y6 != BLINKY))
                if((before_inky_left_y0 != PINKY) && (before_inky_left_y3 != PINKY) && (before_inky_left_y6 != PINKY))
                    if((before_inky_left_y0 != CLYDE) && (before_inky_left_y3 != CLYDE) && (before_inky_left_y6 != CLYDE))
                    {
                        map[inky.x0][inky.y0] = before_inky_left_y0;
                        map[inky.x0][inky.y0-1] = inky.character;
                        inky.y0 = inky.y0-1;

                        map[inky.x3][inky.y3] = before_inky_left_y3;
                        map[inky.x3][inky.y3-1] = inky.character;
                        inky.y3 = inky.y3-1;

                        map[inky.x6][inky.y6] = before_inky_left_y6;
                        map[inky.x6][inky.y6-1] = inky.character;
                        inky.y6 = inky.y6-1;        
                        
                        map[inky.x1][inky.y1] = before_inky_left_y0;
                        map[inky.x1][inky.y1-1] = inky.character;
                        inky.y1 = inky.y1-1;        
                        
                        map[inky.x4][inky.y4] = before_inky_left_y3;
                        map[inky.x4][inky.y4-1] = inky.character;
                        inky.y4 = inky.y4-1;
                        
                        map[inky.x7][inky.y7] = before_inky_left_y6;
                        map[inky.x7][inky.y7-1] = inky.character;
                        inky.y7 = inky.y7-1;
                        
                        map[inky.x2][inky.y2] = before_inky_left_y0;
                        map[inky.x2][inky.y2-1] = inky.character;
                        inky.y2 = inky.y2-1;
                        
                        map[inky.x5][inky.y5] = before_inky_left_y3;
                        map[inky.x5][inky.y5-1] = inky.character;
                        inky.y5 = inky.y5-1;
                        
                        map[inky.x8][inky.y8] = before_inky_left_y6;
                        map[inky.x8][inky.y8-1] = inky.character;
                        inky.y8 = inky.y8-1;
                    }
    // MOVIMENTA PARA DIREITA >
    if((inky_posy_menor1 == inky.y2+1) && (inky_posy_menor2 == inky.y5+1) && (inky_posy_menor3 == inky.y8+1))
        if((before_inky_right_y2 != WALL) && (before_inky_right_y5 != WALL) && (before_inky_right_y8 != WALL))
            if((before_inky_right_y2 != BLINKY) && (before_inky_right_y5 != BLINKY) && (before_inky_right_y8 != BLINKY))
                if((before_inky_right_y2 != PINKY) && (before_inky_right_y5 != PINKY) && (before_inky_right_y8 != PINKY))
                    if((before_inky_right_y2 != CLYDE) && (before_inky_right_y5 != CLYDE) && (before_inky_right_y8 != CLYDE))
                    {
                        map[inky.x2][inky.y2] = before_inky_right_y2;
                        map[inky.x2][inky.y2+1] = inky.character;
                        inky.y2 = inky.y2+1;

                        map[inky.x5][inky.y5] = before_inky_right_y5;
                        map[inky.x5][inky.y5+1] = inky.character;
                        inky.y5 = inky.y5+1;

                        map[inky.x8][inky.y8] = before_inky_right_y8;
                        map[inky.x8][inky.y8+1] = inky.character;
                        inky.y8 = inky.y8+1;

                        map[inky.x1][inky.y1] = before_inky_right_y2;
                        map[inky.x1][inky.y1+1] = inky.character;
                        inky.y1 = inky.y1+1;

                        map[inky.x4][inky.y4] = before_inky_right_y5;;
                        map[inky.x4][inky.y4+1] = inky.character;
                        inky.y4 = inky.y4+1;

                        map[inky.x7][inky.y7] = before_inky_right_y8;
                        map[inky.x7][inky.y7+1] = inky.character;
                        inky.y7 = inky.y7+1;

                        map[inky.x0][inky.y0] = before_inky_right_y2;
                        map[inky.x0][inky.y0+1] = inky.character;
                        inky.y0 = inky.y0+1;

                        map[inky.x3][inky.y3] = before_inky_right_y5;
                        map[inky.x3][inky.y3+1] = inky.character;
                        inky.y3 = inky.y3+1;  

                        map[inky.x6][inky.y6] = before_inky_right_y8;
                        map[inky.x6][inky.y6+1] = inky.character;
                        inky.y6 = inky.y6+1;
                    }        
    // MOVIMENTA PARA CIMA ^
    if((inky_posx_menor1 == inky.x0-1) && (inky_posx_menor2 == inky.x1-1) && (inky_posx_menor3 == inky.x2-1))
        if((before_inky_up_x0 != WALL) && (before_inky_up_x1 != WALL) && (before_inky_up_x2 != WALL))
            if((before_inky_up_x0 != BLINKY) && (before_inky_up_x1 != BLINKY) && (before_inky_up_x2 != BLINKY))
                if((before_inky_up_x0 != PINKY) && (before_inky_up_x1 != PINKY) && (before_inky_up_x2 != PINKY))
                    if((before_inky_up_x0 != CLYDE) && (before_inky_up_x1 != CLYDE) && (before_inky_up_x2 != CLYDE))
                    {
                        map[inky.x0][inky.y0] = before_inky_up_x0;
                        map[inky.x0-1][inky.y0] = inky.character;
                        inky.x0 = inky.x0-1;

                        map[inky.x1][inky.y1] = before_inky_up_x1;
                        map[inky.x1-1][inky.y1] = inky.character;
                        inky.x1 = inky.x1-1;

                        map[inky.x2][inky.y2] = before_inky_up_x2;
                        map[inky.x2-1][inky.y2] = inky.character;
                        inky.x2 = inky.x2-1;

                        map[inky.x3][inky.y3] = before_inky_up_x0;
                        map[inky.x3-1][inky.y3] = inky.character;
                        inky.x3 = inky.x3-1;

                        map[inky.x4][inky.y4] = before_inky_up_x1;
                        map[inky.x4-1][inky.y4] = inky.character;
                        inky.x4 = inky.x4-1;

                        map[inky.x5][inky.y5] = before_inky_up_x2;
                        map[inky.x5-1][inky.y5] = inky.character;
                        inky.x5 = inky.x5-1;

                        map[inky.x6][inky.y6] = before_inky_up_x0;
                        map[inky.x6-1][inky.y6] = inky.character;
                        inky.x6 = inky.x6-1;

                        map[inky.x7][inky.y7] = before_inky_up_x1;
                        map[inky.x7-1][inky.y7] = inky.character;
                        inky.x7 = inky.x7-1;

                        map[inky.x8][inky.y8] = before_inky_up_x2;
                        map[inky.x8-1][inky.y8] = inky.character;
                        inky.x8 = inky.x8-1;
                    }
    // MOVIMENTA PARA BAIXO 
    if((inky_posx_menor1 == inky.x6+1) && (inky_posx_menor2 == inky.x7+1) && (inky_posx_menor3 == inky.x8+1))
        if((before_inky_down_x6 != WALL) && (before_inky_down_x7 != WALL) && (before_inky_down_x8 != WALL))
            if((before_inky_down_x6 != BLINKY) && (before_inky_down_x7 != BLINKY) && (before_inky_down_x8 != BLINKY))
                if((before_inky_down_x6 != PINKY) && (before_inky_down_x7 != PINKY) && (before_inky_down_x8 != PINKY))
                    if((before_inky_down_x6 != CLYDE) && (before_inky_down_x7 != CLYDE) && (before_inky_down_x8 != CLYDE))
                    {
                        map[inky.x6][inky.y6] = before_inky_down_x6;
                        map[inky.x6+1][inky.y6] = inky.character;
                        inky.x6 = inky.x6+1;

                        map[inky.x7][inky.y7] = before_inky_down_x7;
                        map[inky.x7+1][inky.y7] = inky.character;
                        inky.x7 = inky.x7+1;

                        map[inky.x8][inky.y8] = before_inky_down_x8;
                        map[inky.x8+1][inky.y8] = inky.character;
                        inky.x8 = inky.x8+1;

                        map[inky.x3][inky.y3] = before_inky_down_x6;
                        map[inky.x3+1][inky.y3] = inky.character;
                        inky.x3 = inky.x3+1;

                        map[inky.x4][inky.y4] = before_inky_down_x7;
                        map[inky.x4+1][inky.y4] = inky.character;
                        inky.x4 = inky.x4+1;

                        map[inky.x5][inky.y5] = before_inky_down_x8;
                        map[inky.x5+1][inky.y5] = inky.character;
                        inky.x5 = inky.x5+1;

                        map[inky.x0][inky.y0] = before_inky_down_x6;
                        map[inky.x0+1][inky.y0] =  inky.character;
                        inky.x0 = inky.x0+1;

                        map[inky.x1][inky.y1] = before_inky_down_x7;
                        map[inky.x1+1][inky.y1] = inky.character;
                        inky.x1 = inky.x1+1;

                        map[inky.x2][inky.y2] = before_inky_down_x8;
                        map[inky.x2+1][inky.y2] = inky.character;
                        inky.x2 = inky.x2+1;
                    }
    // VERIFICA SE INKY MATOU PACMAN
    if(pacman.power_up == 0)
    {
      if((inky.x0 == pacman.x0 && inky.y0==pacman.y0)&&(inky.x1==pacman.x1 && inky.y1==pacman.y1)&&(inky.x2==pacman.x2 && inky.y2==pacman.y2))
         inky.kills++;
      else if((inky.x0 == pacman.x0 && inky.y0==pacman.y0)&&(inky.x3==pacman.x3 && inky.y3==pacman.y3)&&(inky.x6==pacman.x6 && inky.y6==pacman.y6))
         inky.kills++;
      else if((inky.x2 == pacman.x2 && inky.y2==pacman.y2)&&(inky.x5==pacman.x5 && inky.y5==pacman.y5)&&(inky.x8==pacman.x8 && inky.y8==pacman.y8))
         inky.kills++;
      else if((inky.x6 == pacman.x6 && inky.y6==pacman.y6)&&(inky.x7==pacman.x7 && inky.y7==pacman.y7)&&(inky.x8==pacman.x8 && inky.y8==pacman.y8))
         inky.kills++;
    }
    else if(pacman.power_up == 1)
    {
      if((inky.x0 == pacman.x0 && inky.y0==pacman.y0)&&(inky.x1==pacman.x1 && inky.y1==pacman.y1)&&(inky.x2==pacman.x2 && inky.y2==pacman.y2))
         inky.last_move = 'k';
      else if((inky.x0 == pacman.x0 && inky.y0==pacman.y0)&&(inky.x3==pacman.x3 && inky.y3==pacman.y3)&&(inky.x6==pacman.x6 && inky.y6==pacman.y6))
         inky.last_move = 'k';
      else if((inky.x2 == pacman.x2 && inky.y2==pacman.y2)&&(inky.x5==pacman.x5 && inky.y5==pacman.y5)&&(inky.x8==pacman.x8 && inky.y8==pacman.y8))
         inky.last_move = 'k';
      else if((inky.x6 == pacman.x6 && inky.y6==pacman.y6)&&(inky.x7==pacman.x7 && inky.y7==pacman.y7)&&(inky.x8==pacman.x8 && inky.y8==pacman.y8))
         inky.last_move = 'k';
    }
    return inky;
}

ghost clyde_movement(char **map, ghost clyde, pacman pacman)
{
    // SELECIONA TARGET COM BASE NA POSIÇÃO DO PACMAN
    int target_x,target_y,dist_x, dist_y;
    if(pacman.x4 < clyde.x4)
        dist_x = clyde.x4-pacman.x4;
    else
        dist_x = pacman.x4-clyde.x4;
    if(pacman.y4 < clyde.y4)
        dist_y = clyde.y4-pacman.y4;
    else
        dist_y = pacman.y4-clyde.y4;
    
    if((dist_x || dist_y) < 15)
    {
        target_x = pacman.x4;
        target_y = pacman.y4;
    }
    else
    {
        target_x = 0;
        target_y = 0;
    }
    // VERIFICA O QUE TEM NO LADO ESQUERDO DO FANTASMA 
    char before_clyde_left_y0,before_clyde_left_y3,before_clyde_left_y6;
    before_clyde_left_y0 = map[clyde.x0][clyde.y0-1];    
    before_clyde_left_y3 = map[clyde.x3][clyde.y3-1];    
    before_clyde_left_y6 = map[clyde.x6][clyde.y6-1];

    // VERIFICA O QUE TEM NO LADO DIREITO DO FANTASMA
    char before_clyde_right_y2,before_clyde_right_y5,before_clyde_right_y8;
    before_clyde_right_y2 = map[clyde.x2][clyde.y2+1];
    before_clyde_right_y5 = map[clyde.x5][clyde.y5+1];
    before_clyde_right_y8 = map[clyde.x8][clyde.y8+1];

    // VERIFICA O QUE TEM ACIMA DO FANTASMA
    char before_clyde_up_x0,before_clyde_up_x1,before_clyde_up_x2;
    before_clyde_up_x0 = map[clyde.x0-1][clyde.y0];
    before_clyde_up_x1 = map[clyde.x1-1][clyde.y1];
    before_clyde_up_x2 = map[clyde.x2-1][clyde.y2];

    // VERIFICA O QUE TEM ABAIXO DO FANTASMA
    char before_clyde_down_x6,before_clyde_down_x7,before_clyde_down_x8;
    before_clyde_down_x6 = map[clyde.x6+1][clyde.y6];
    before_clyde_down_x7 = map[clyde.x7+1][clyde.y7];
    before_clyde_down_x8 = map[clyde.x8+1][clyde.y8];

    // BLOCO QUE ESCOLHE MENOR DISTÂNCIA COM BASE NA MENOR POSIÇÃO
    if(target_x != 0 && target_y != 0)
    {
        int small_dist, clyde_posx_menor1, clyde_posx_menor2, clyde_posx_menor3, clyde_posy_menor1, clyde_posy_menor2, clyde_posy_menor3;
        small_dist = calc_dist(clyde.x4,clyde.y4,target_x,target_y);
        clyde_posx_menor1 = clyde.x4;
        clyde_posy_menor1 = clyde.y4;
        // VERIFICA SE IR PARA ESQUERDA(Yn-1) É A MENOR DISTÂNCIA COMPARADA COM O CENTRO DO FANTASMA
        if((calc_dist(clyde.x4,clyde.y4-1,target_x,target_y) < small_dist))
        {
            if((before_clyde_left_y0 != WALL) && (before_clyde_left_y3 != WALL) && (before_clyde_left_y6 != WALL))
            {
                clyde_posy_menor1 = clyde.y0-1;
                clyde_posy_menor2 = clyde.y3-1;
                clyde_posy_menor3 = clyde.y6-1;

                clyde_posx_menor1 = clyde.x0;
                clyde_posx_menor2 = clyde.x3;
                clyde_posx_menor3 = clyde.x6;
            }
        }
        // VERIFICA SE IR PARA DIREITA(Yn+1) É A MENOR DISTÂNCIA COMPARADA COM O CENTRO DO FANTASMA
        else if((calc_dist(clyde.x4,clyde.y4+1,target_x,target_y) < small_dist))
        {
            if((before_clyde_right_y2 != WALL) && (before_clyde_right_y5 != WALL) && (before_clyde_right_y8 != WALL))
            {
                clyde_posy_menor1 = clyde.y2+1;
                clyde_posy_menor2 = clyde.y5+1;
                clyde_posy_menor3 = clyde.y8+1;

                clyde_posx_menor1 = clyde.x2;
                clyde_posx_menor2 = clyde.x5;
                clyde_posx_menor3 = clyde.x8;
            }
        }
        // VERIFICA SE IR PARA CIMA(Xn-1) É A MENOR DISTÂNCIA COMPARADA COM O CENTRO DO FANTASMA
        if((calc_dist(clyde.x4-1,clyde.y4,target_x,target_y) < small_dist))
        {
            if((before_clyde_up_x0 != WALL) && (before_clyde_up_x1 != WALL) && (before_clyde_up_x2 != WALL))
            {
                clyde_posx_menor1 = clyde.x0-1;
                clyde_posx_menor2 = clyde.x1-1;
                clyde_posx_menor3 = clyde.x2-1;

                clyde_posy_menor1 = clyde.y0;
                clyde_posy_menor2 = clyde.y1;
                clyde_posy_menor3 = clyde.y2;
            }
        }
        // VERIFICA SE IR PARA BAIXO(Xn+1) É A MENOR DISTÂNCIA COMPARADA COM O CENTRO DO FANTASMA
        else if((calc_dist(clyde.x4+1,clyde.y4,target_x,target_y) < small_dist))
        {
            if((before_clyde_down_x6 != WALL) && (before_clyde_down_x7 != WALL) && (before_clyde_down_x8 != WALL))
            {
                clyde_posx_menor1 = clyde.x6+1;
                clyde_posx_menor2 = clyde.x7+1;
                clyde_posx_menor3 = clyde.x8+1;

                clyde_posy_menor1 = clyde.y6;
                clyde_posy_menor2 = clyde.y7;
                clyde_posy_menor3 = clyde.y8;
            }
        }
        // BLOCO QUE ESCOLHE MENOR DISTÂNCIA COM BASE NA COLUNA OU LINHA MAIS PRÓXIMA
        if((clyde.x4 == clyde_posx_menor1) && (clyde.y4 == clyde_posy_menor1))
        {
            // CIMA, Xn-1
            if((before_clyde_up_x0 != WALL) && (before_clyde_up_x1 != WALL) && (before_clyde_up_x2 != WALL))
            {
                if(pow((clyde.x4-1)-target_x,2) < pow(clyde.x4-target_x,2))
                {
                    clyde_posx_menor1 = clyde.x0-1;
                    clyde_posx_menor2 = clyde.x1-1;
                    clyde_posx_menor3 = clyde.x2-1;

                    clyde_posy_menor1 = clyde.y0;
                    clyde_posy_menor2 = clyde.y1;
                    clyde_posy_menor3 = clyde.y2;
                }
            }
            // BAIXO, Xn+1
            else if((before_clyde_down_x6 != WALL) && (before_clyde_down_x7 != WALL) && (before_clyde_down_x8 != WALL))
            {
                if(pow((clyde.x4+1)-target_x,2) < pow(clyde.x4-target_x,2))
                {
                    clyde_posx_menor1 = clyde.x6+1;
                    clyde_posx_menor2 = clyde.x7+1;
                    clyde_posx_menor3 = clyde.x8+1;

                    clyde_posy_menor1 = clyde.y6;
                    clyde_posy_menor2 = clyde.y7;
                    clyde_posy_menor3 = clyde.y8;
                }
            }
            // ESQUERDA, Yn-1
            if((before_clyde_left_y0 != WALL) && (before_clyde_left_y3 !=WALL) && (before_clyde_left_y6 != WALL))
            {
                if(pow((clyde.y4-1)-target_y,2) < pow(clyde.y4-target_y,2))
                {
                    clyde_posy_menor1 = clyde.y0-1;
                    clyde_posy_menor2 = clyde.y3-1;
                    clyde_posy_menor3 = clyde.y6-1;

                    clyde_posx_menor1 = clyde.x0;
                    clyde_posx_menor2 = clyde.x3;
                    clyde_posx_menor3 = clyde.x6;
                }
            }
            // DIREITA, Yn+1
            else if((before_clyde_right_y2 != WALL) && (before_clyde_right_y5 != WALL) && (before_clyde_right_y8 != WALL))
            {
                if(pow((clyde.y4+1)-target_y,2) < pow(clyde.y4-target_y,2))
                {
                    clyde_posy_menor1 = clyde.y2+1;
                    clyde_posy_menor2 = clyde.y5+1;
                    clyde_posy_menor3 = clyde.y8+1;

                    clyde_posx_menor1 = clyde.x2;
                    clyde_posx_menor2 = clyde.x5;
                    clyde_posx_menor3 = clyde.x8;
                }
            }
        }
        // MOVIMENTA FANTASMA
        // MOVIMENTA PARA ESQUERDA <
        if((clyde_posy_menor1 == clyde.y0-1) && (clyde_posy_menor2 == clyde.y3-1) && (clyde_posy_menor3 == clyde.y6-1))
            if((before_clyde_left_y0 != WALL) && (before_clyde_left_y3 != WALL) && (before_clyde_left_y6 != WALL))
                if((before_clyde_left_y0 != PINKY) && (before_clyde_left_y3 != PINKY) && (before_clyde_left_y6 != PINKY))
                    if((before_clyde_left_y0 != INKY) && (before_clyde_left_y3 != INKY) && (before_clyde_left_y6 != INKY))
                        if((before_clyde_left_y0 != BLINKY) && (before_clyde_left_y3 != BLINKY) && (before_clyde_left_y6 != BLINKY))
                        {
                            map[clyde.x0][clyde.y0] = before_clyde_left_y0;
                            map[clyde.x0][clyde.y0-1] = clyde.character;
                            clyde.y0 = clyde.y0-1;

                            map[clyde.x3][clyde.y3] = before_clyde_left_y3;
                            map[clyde.x3][clyde.y3-1] = clyde.character;
                            clyde.y3 = clyde.y3-1;

                            map[clyde.x6][clyde.y6] = before_clyde_left_y6;
                            map[clyde.x6][clyde.y6-1] = clyde.character;
                            clyde.y6 = clyde.y6-1;        
                            
                            map[clyde.x1][clyde.y1] = before_clyde_left_y0;
                            map[clyde.x1][clyde.y1-1] = clyde.character;
                            clyde.y1 = clyde.y1-1;        
                            
                            map[clyde.x4][clyde.y4] = before_clyde_left_y3;
                            map[clyde.x4][clyde.y4-1] = clyde.character;
                            clyde.y4 = clyde.y4-1;
                            
                            map[clyde.x7][clyde.y7] = before_clyde_left_y6;
                            map[clyde.x7][clyde.y7-1] = clyde.character;
                            clyde.y7 = clyde.y7-1;
                            
                            map[clyde.x2][clyde.y2] = before_clyde_left_y0;
                            map[clyde.x2][clyde.y2-1] = clyde.character;
                            clyde.y2 = clyde.y2-1;
                            
                            map[clyde.x5][clyde.y5] = before_clyde_left_y3;
                            map[clyde.x5][clyde.y5-1] = clyde.character;
                            clyde.y5 = clyde.y5-1;
                            
                            map[clyde.x8][clyde.y8] = before_clyde_left_y6;
                            map[clyde.x8][clyde.y8-1] = clyde.character;
                            clyde.y8 = clyde.y8-1;
                        }
        // MOVIMENTA PARA DIREITA >
        if((clyde_posy_menor1 == clyde.y2+1) && (clyde_posy_menor2 == clyde.y5+1) && (clyde_posy_menor3 == clyde.y8+1))
            if((before_clyde_right_y2 != WALL) && (before_clyde_right_y5 != WALL) && (before_clyde_right_y8 != WALL))
                if((before_clyde_right_y2 != PINKY) && (before_clyde_right_y5 != PINKY) && (before_clyde_right_y8 != PINKY))
                    if((before_clyde_right_y2 != INKY) && (before_clyde_right_y5 != INKY) && (before_clyde_right_y8 != INKY))
                        if((before_clyde_right_y2 != BLINKY) && (before_clyde_right_y5 != BLINKY) && (before_clyde_right_y8 != BLINKY))
                        {
                            map[clyde.x2][clyde.y2] = before_clyde_right_y2;
                            map[clyde.x2][clyde.y2+1] = clyde.character;
                            clyde.y2 = clyde.y2+1;

                            map[clyde.x5][clyde.y5] = before_clyde_right_y5;
                            map[clyde.x5][clyde.y5+1] = clyde.character;
                            clyde.y5 = clyde.y5+1;

                            map[clyde.x8][clyde.y8] = before_clyde_right_y8;
                            map[clyde.x8][clyde.y8+1] = clyde.character;
                            clyde.y8 = clyde.y8+1;

                            map[clyde.x1][clyde.y1] = before_clyde_right_y2;
                            map[clyde.x1][clyde.y1+1] = clyde.character;
                            clyde.y1 = clyde.y1+1;

                            map[clyde.x4][clyde.y4] = before_clyde_right_y5;;
                            map[clyde.x4][clyde.y4+1] = clyde.character;
                            clyde.y4 = clyde.y4+1;

                            map[clyde.x7][clyde.y7] = before_clyde_right_y8;
                            map[clyde.x7][clyde.y7+1] = clyde.character;
                            clyde.y7 = clyde.y7+1;

                            map[clyde.x0][clyde.y0] = before_clyde_right_y2;
                            map[clyde.x0][clyde.y0+1] = clyde.character;
                            clyde.y0 = clyde.y0+1;

                            map[clyde.x3][clyde.y3] = before_clyde_right_y5;
                            map[clyde.x3][clyde.y3+1] = clyde.character;
                            clyde.y3 = clyde.y3+1;  

                            map[clyde.x6][clyde.y6] = before_clyde_right_y8;
                            map[clyde.x6][clyde.y6+1] = clyde.character;
                            clyde.y6 = clyde.y6+1;
                        }        
        // MOVIMENTA PARA CIMA ^
        if((clyde_posx_menor1 == clyde.x0-1) && (clyde_posx_menor2 == clyde.x1-1) && (clyde_posx_menor3 == clyde.x2-1))
            if((before_clyde_up_x0 != WALL) && (before_clyde_up_x1 != WALL) && (before_clyde_up_x2 != WALL))
                if((before_clyde_up_x0 != PINKY) && (before_clyde_up_x1 != PINKY) && (before_clyde_up_x2 != PINKY))
                    if((before_clyde_up_x0 != INKY) && (before_clyde_up_x1 != INKY) && (before_clyde_up_x2 != INKY))
                        if((before_clyde_up_x0 != BLINKY) && (before_clyde_up_x1 != BLINKY) && (before_clyde_up_x2 != BLINKY))
                        {
                            map[clyde.x0][clyde.y0] = before_clyde_up_x0;
                            map[clyde.x0-1][clyde.y0] = clyde.character;
                            clyde.x0 = clyde.x0-1;

                            map[clyde.x1][clyde.y1] = before_clyde_up_x1;
                            map[clyde.x1-1][clyde.y1] = clyde.character;
                            clyde.x1 = clyde.x1-1;

                            map[clyde.x2][clyde.y2] = before_clyde_up_x2;
                            map[clyde.x2-1][clyde.y2] = clyde.character;
                            clyde.x2 = clyde.x2-1;

                            map[clyde.x3][clyde.y3] = before_clyde_up_x0;
                            map[clyde.x3-1][clyde.y3] = clyde.character;
                            clyde.x3 = clyde.x3-1;

                            map[clyde.x4][clyde.y4] = before_clyde_up_x1;
                            map[clyde.x4-1][clyde.y4] = clyde.character;
                            clyde.x4 = clyde.x4-1;

                            map[clyde.x5][clyde.y5] = before_clyde_up_x2;
                            map[clyde.x5-1][clyde.y5] = clyde.character;
                            clyde.x5 = clyde.x5-1;

                            map[clyde.x6][clyde.y6] = before_clyde_up_x0;
                            map[clyde.x6-1][clyde.y6] = clyde.character;
                            clyde.x6 = clyde.x6-1;

                            map[clyde.x7][clyde.y7] = before_clyde_up_x1;
                            map[clyde.x7-1][clyde.y7] = clyde.character;
                            clyde.x7 = clyde.x7-1;

                            map[clyde.x8][clyde.y8] = before_clyde_up_x2;
                            map[clyde.x8-1][clyde.y8] = clyde.character;
                            clyde.x8 = clyde.x8-1;
                        }
        // MOVIMENTA PARA BAIXO 
        if((clyde_posx_menor1 == clyde.x6+1) && (clyde_posx_menor2 == clyde.x7+1) && (clyde_posx_menor3 == clyde.x8+1))
            if((before_clyde_down_x6 != WALL) && (before_clyde_down_x7 != WALL) && (before_clyde_down_x8 != WALL))
                if((before_clyde_down_x6 != PINKY) && (before_clyde_down_x7 != PINKY) && (before_clyde_down_x8 != PINKY))
                    if((before_clyde_down_x6 != INKY) && (before_clyde_down_x7 != INKY) && (before_clyde_down_x8 != INKY))
                        if((before_clyde_down_x6 != BLINKY) && (before_clyde_down_x7 != BLINKY) && (before_clyde_down_x8 != BLINKY))
                        {
                            map[clyde.x6][clyde.y6] = before_clyde_down_x6;
                            map[clyde.x6+1][clyde.y6] = clyde.character;
                            clyde.x6 = clyde.x6+1;

                            map[clyde.x7][clyde.y7] = before_clyde_down_x7;
                            map[clyde.x7+1][clyde.y7] = clyde.character;
                            clyde.x7 = clyde.x7+1;

                            map[clyde.x8][clyde.y8] = before_clyde_down_x8;
                            map[clyde.x8+1][clyde.y8] = clyde.character;
                            clyde.x8 = clyde.x8+1;

                            map[clyde.x3][clyde.y3] = before_clyde_down_x6;
                            map[clyde.x3+1][clyde.y3] = clyde.character;
                            clyde.x3 = clyde.x3+1;

                            map[clyde.x4][clyde.y4] = before_clyde_down_x7;
                            map[clyde.x4+1][clyde.y4] = clyde.character;
                            clyde.x4 = clyde.x4+1;

                            map[clyde.x5][clyde.y5] = before_clyde_down_x8;
                            map[clyde.x5+1][clyde.y5] = clyde.character;
                            clyde.x5 = clyde.x5+1;

                            map[clyde.x0][clyde.y0] = before_clyde_down_x6;
                            map[clyde.x0+1][clyde.y0] =  clyde.character;
                            clyde.x0 = clyde.x0+1;

                            map[clyde.x1][clyde.y1] = before_clyde_down_x7;
                            map[clyde.x1+1][clyde.y1] = clyde.character;
                            clyde.x1 = clyde.x1+1;

                            map[clyde.x2][clyde.y2] = before_clyde_down_x8;
                            map[clyde.x2+1][clyde.y2] = clyde.character;
                            clyde.x2 = clyde.x2+1;
                        }
    }
    else
    {
        // MOVIMENTA FANTASMA
        // MOVIMENTA PARA ESQUERDA <
        if((before_clyde_left_y0 != WALL) && (before_clyde_left_y3 != WALL) && (before_clyde_left_y6 != WALL))
            if((before_clyde_left_y0 != PINKY) && (before_clyde_left_y3 != PINKY) && (before_clyde_left_y6 != PINKY))
                if((before_clyde_left_y0 != INKY) && (before_clyde_left_y3 != INKY) && (before_clyde_left_y6 != INKY))
                    if((before_clyde_left_y0 != BLINKY) && (before_clyde_left_y3 != BLINKY) && (before_clyde_left_y6 != BLINKY))
                    {
                        map[clyde.x0][clyde.y0] = before_clyde_left_y0;
                        map[clyde.x0][clyde.y0-1] = clyde.character;
                        clyde.y0 = clyde.y0-1;

                        map[clyde.x3][clyde.y3] = before_clyde_left_y3;
                        map[clyde.x3][clyde.y3-1] = clyde.character;
                        clyde.y3 = clyde.y3-1;

                        map[clyde.x6][clyde.y6] = before_clyde_left_y6;
                        map[clyde.x6][clyde.y6-1] = clyde.character;
                        clyde.y6 = clyde.y6-1;        
                        
                        map[clyde.x1][clyde.y1] = before_clyde_left_y0;
                        map[clyde.x1][clyde.y1-1] = clyde.character;
                        clyde.y1 = clyde.y1-1;        
                        
                        map[clyde.x4][clyde.y4] = before_clyde_left_y3;
                        map[clyde.x4][clyde.y4-1] = clyde.character;
                        clyde.y4 = clyde.y4-1;
                        
                        map[clyde.x7][clyde.y7] = before_clyde_left_y6;
                        map[clyde.x7][clyde.y7-1] = clyde.character;
                        clyde.y7 = clyde.y7-1;
                        
                        map[clyde.x2][clyde.y2] = before_clyde_left_y0;
                        map[clyde.x2][clyde.y2-1] = clyde.character;
                        clyde.y2 = clyde.y2-1;
                        
                        map[clyde.x5][clyde.y5] = before_clyde_left_y3;
                        map[clyde.x5][clyde.y5-1] = clyde.character;
                        clyde.y5 = clyde.y5-1;
                        
                        map[clyde.x8][clyde.y8] = before_clyde_left_y6;
                        map[clyde.x8][clyde.y8-1] = clyde.character;
                        clyde.y8 = clyde.y8-1;

                        clyde.last_move = 'l';
                    }
        // MOVIMENTA PARA DIREITA >
        if((before_clyde_right_y2 != WALL) && (before_clyde_right_y5 != WALL) && (before_clyde_right_y8 != WALL))
            if((before_clyde_right_y2 != PINKY) && (before_clyde_right_y5 != PINKY) && (before_clyde_right_y8 != PINKY))
                if((before_clyde_right_y2 != INKY) && (before_clyde_right_y5 != INKY) && (before_clyde_right_y8 != INKY))
                    if((before_clyde_right_y2 != BLINKY) && (before_clyde_right_y5 != BLINKY) && (before_clyde_right_y8 != BLINKY))
                    {
                        map[clyde.x2][clyde.y2] = before_clyde_right_y2;
                        map[clyde.x2][clyde.y2+1] = clyde.character;
                        clyde.y2 = clyde.y2+1;

                        map[clyde.x5][clyde.y5] = before_clyde_right_y5;
                        map[clyde.x5][clyde.y5+1] = clyde.character;
                        clyde.y5 = clyde.y5+1;

                        map[clyde.x8][clyde.y8] = before_clyde_right_y8;
                        map[clyde.x8][clyde.y8+1] = clyde.character;
                        clyde.y8 = clyde.y8+1;

                        map[clyde.x1][clyde.y1] = before_clyde_right_y2;
                        map[clyde.x1][clyde.y1+1] = clyde.character;
                        clyde.y1 = clyde.y1+1;

                        map[clyde.x4][clyde.y4] = before_clyde_right_y5;;
                        map[clyde.x4][clyde.y4+1] = clyde.character;
                        clyde.y4 = clyde.y4+1;

                        map[clyde.x7][clyde.y7] = before_clyde_right_y8;
                        map[clyde.x7][clyde.y7+1] = clyde.character;
                        clyde.y7 = clyde.y7+1;

                        map[clyde.x0][clyde.y0] = before_clyde_right_y2;
                        map[clyde.x0][clyde.y0+1] = clyde.character;
                        clyde.y0 = clyde.y0+1;

                        map[clyde.x3][clyde.y3] = before_clyde_right_y5;
                        map[clyde.x3][clyde.y3+1] = clyde.character;
                        clyde.y3 = clyde.y3+1;  

                        map[clyde.x6][clyde.y6] = before_clyde_right_y8;
                        map[clyde.x6][clyde.y6+1] = clyde.character;
                        clyde.y6 = clyde.y6+1;

                        clyde.last_move = 'r';
                    }        
        // MOVIMENTA PARA CIMA ^
        if((before_clyde_up_x0 != WALL) && (before_clyde_up_x1 != WALL) && (before_clyde_up_x2 != WALL))
            if((before_clyde_up_x0 != PINKY) && (before_clyde_up_x1 != PINKY) && (before_clyde_up_x2 != PINKY))
                if((before_clyde_up_x0 != INKY) && (before_clyde_up_x1 != INKY) && (before_clyde_up_x2 != INKY))
                    if((before_clyde_up_x0 != BLINKY) && (before_clyde_up_x1 != BLINKY) && (before_clyde_up_x2 != BLINKY))
                    {
                        map[clyde.x0][clyde.y0] = before_clyde_up_x0;
                        map[clyde.x0-1][clyde.y0] = clyde.character;
                        clyde.x0 = clyde.x0-1;

                        map[clyde.x1][clyde.y1] = before_clyde_up_x1;
                        map[clyde.x1-1][clyde.y1] = clyde.character;
                        clyde.x1 = clyde.x1-1;

                        map[clyde.x2][clyde.y2] = before_clyde_up_x2;
                        map[clyde.x2-1][clyde.y2] = clyde.character;
                        clyde.x2 = clyde.x2-1;

                        map[clyde.x3][clyde.y3] = before_clyde_up_x0;
                        map[clyde.x3-1][clyde.y3] = clyde.character;
                        clyde.x3 = clyde.x3-1;

                        map[clyde.x4][clyde.y4] = before_clyde_up_x1;
                        map[clyde.x4-1][clyde.y4] = clyde.character;
                        clyde.x4 = clyde.x4-1;

                        map[clyde.x5][clyde.y5] = before_clyde_up_x2;
                        map[clyde.x5-1][clyde.y5] = clyde.character;
                        clyde.x5 = clyde.x5-1;

                        map[clyde.x6][clyde.y6] = before_clyde_up_x0;
                        map[clyde.x6-1][clyde.y6] = clyde.character;
                        clyde.x6 = clyde.x6-1;

                        map[clyde.x7][clyde.y7] = before_clyde_up_x1;
                        map[clyde.x7-1][clyde.y7] = clyde.character;
                        clyde.x7 = clyde.x7-1;

                        map[clyde.x8][clyde.y8] = before_clyde_up_x2;
                        map[clyde.x8-1][clyde.y8] = clyde.character;
                        clyde.x8 = clyde.x8-1;

                        clyde.last_move = 'u';
                    }
        // MOVIMENTA PARA BAIXO 
        if((before_clyde_down_x6 != WALL) && (before_clyde_down_x7 != WALL) && (before_clyde_down_x8 != WALL))
            if((before_clyde_down_x6 != PINKY) && (before_clyde_down_x7 != PINKY) && (before_clyde_down_x8 != PINKY))
                if((before_clyde_down_x6 != INKY) && (before_clyde_down_x7 != INKY) && (before_clyde_down_x8 != INKY))
                    if((before_clyde_down_x6 != BLINKY) && (before_clyde_down_x7 != BLINKY) && (before_clyde_down_x8 != BLINKY))
                    {
                        map[clyde.x6][clyde.y6] = before_clyde_down_x6;
                        map[clyde.x6+1][clyde.y6] = clyde.character;
                        clyde.x6 = clyde.x6+1;

                        map[clyde.x7][clyde.y7] = before_clyde_down_x7;
                        map[clyde.x7+1][clyde.y7] = clyde.character;
                        clyde.x7 = clyde.x7+1;

                        map[clyde.x8][clyde.y8] = before_clyde_down_x8;
                        map[clyde.x8+1][clyde.y8] = clyde.character;
                        clyde.x8 = clyde.x8+1;

                        map[clyde.x3][clyde.y3] = before_clyde_down_x6;
                        map[clyde.x3+1][clyde.y3] = clyde.character;
                        clyde.x3 = clyde.x3+1;

                        map[clyde.x4][clyde.y4] = before_clyde_down_x7;
                        map[clyde.x4+1][clyde.y4] = clyde.character;
                        clyde.x4 = clyde.x4+1;

                        map[clyde.x5][clyde.y5] = before_clyde_down_x8;
                        map[clyde.x5+1][clyde.y5] = clyde.character;
                        clyde.x5 = clyde.x5+1;

                        map[clyde.x0][clyde.y0] = before_clyde_down_x6;
                        map[clyde.x0+1][clyde.y0] =  clyde.character;
                        clyde.x0 = clyde.x0+1;

                        map[clyde.x1][clyde.y1] = before_clyde_down_x7;
                        map[clyde.x1+1][clyde.y1] = clyde.character;
                        clyde.x1 = clyde.x1+1;

                        map[clyde.x2][clyde.y2] = before_clyde_down_x8;
                        map[clyde.x2+1][clyde.y2] = clyde.character;
                        clyde.x2 = clyde.x2+1;

                        clyde.last_move = 'd';
                    }
    }
    // VERIFICA SE CLYDE MATOU PACMAN
    if(pacman.power_up == 0)
    {
      if((clyde.x0 == pacman.x0 && clyde.y0==pacman.y0)&&(clyde.x1==pacman.x1 && clyde.y1==pacman.y1)&&(clyde.x2==pacman.x2 && clyde.y2==pacman.y2))
         clyde.kills++;
      else if((clyde.x0 == pacman.x0 && clyde.y0==pacman.y0)&&(clyde.x3==pacman.x3 && clyde.y3==pacman.y3)&&(clyde.x6==pacman.x6 && clyde.y6==pacman.y6))
         clyde.kills++;
      else if((clyde.x2 == pacman.x2 && clyde.y2==pacman.y2)&&(clyde.x5==pacman.x5 && clyde.y5==pacman.y5)&&(clyde.x8==pacman.x8 && clyde.y8==pacman.y8))
         clyde.kills++;
      else if((clyde.x6 == pacman.x6 && clyde.y6==pacman.y6)&&(clyde.x7==pacman.x7 && clyde.y7==pacman.y7)&&(clyde.x8==pacman.x8 && clyde.y8==pacman.y8))
         clyde.kills++;
    }
    else if(pacman.power_up == 1)
    {
      if((clyde.x0 == pacman.x0 && clyde.y0==pacman.y0)&&(clyde.x1==pacman.x1 && clyde.y1==pacman.y1)&&(clyde.x2==pacman.x2 && clyde.y2==pacman.y2))
         clyde.last_move == 'k';
      else if((clyde.x0 == pacman.x0 && clyde.y0==pacman.y0)&&(clyde.x3==pacman.x3 && clyde.y3==pacman.y3)&&(clyde.x6==pacman.x6 && clyde.y6==pacman.y6))
         clyde.last_move == 'k';
      else if((clyde.x2 == pacman.x2 && clyde.y2==pacman.y2)&&(clyde.x5==pacman.x5 && clyde.y5==pacman.y5)&&(clyde.x8==pacman.x8 && clyde.y8==pacman.y8))
         clyde.last_move == 'k';
      else if((clyde.x6 == pacman.x6 && clyde.y6==pacman.y6)&&(clyde.x7==pacman.x7 && clyde.y7==pacman.y7)&&(clyde.x8==pacman.x8 && clyde.y8==pacman.y8))
         clyde.last_move == 'k';
    }
   return clyde;
}

pacman ini_pacman(char **map,int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,int x5,int y5,int x6,int y6,int x7,int y7,int x8,int y8, int life)
{
    pacman tmp;
    tmp.x0 = x0;
    tmp.x1 = x1;
    tmp.x2 = x2;
    tmp.x3 = x3;
    tmp.x4 = x4;
    tmp.x5 = x5;
    tmp.x6 = x6;
    tmp.x7 = x7;
    tmp.x8 = x8;
    tmp.y0 = y0;
    tmp.y1 = y1;
    tmp.y2 = y2;
    tmp.y3 = y3;
    tmp.y4 = y4;
    tmp.y5 = y5;
    tmp.y6 = y6;
    tmp.y7 = y7;
    tmp.y8 = y8;
    tmp.character = PACMAN;
    tmp.power_up = 0;
    tmp.score = 0;
    tmp.life = life;
    map[x0][y0] = tmp.character;
    map[x1][y1] = tmp.character;
    map[x2][y2] = tmp.character;
    map[x3][y3] = tmp.character;
    map[x4][y4] = tmp.character;
    map[x5][y5] = tmp.character;
    map[x6][y6] = tmp.character;
    map[x7][y7] = tmp.character;
    map[x8][y8] = tmp.character;
    return tmp;
}

pacman mv_pacman_right(char **map, pacman pacman)
{
    if((map[pacman.x2][pacman.y2+1] != WALL) && (map[pacman.x5][pacman.y5+1] != WALL) && (map[pacman.x8][pacman.y8+1] != WALL))
    {
        if((pacman.y2+1 == ESP_FOOD) || (pacman.y5+1 == ESP_FOOD) || (pacman.y8+1 == ESP_FOOD))
        {
            pacman.power_up = 1;
            pacman.score += 2;
            map[pacman.x2][pacman.y2] = ' ';
            map[pacman.x2][pacman.y2+1] = pacman.character;
            pacman.y2 = pacman.y2+1;
            map[pacman.x5][pacman.y5] = ' ';
            map[pacman.x5][pacman.y5+1] = pacman.character;
            pacman.y5 = pacman.y5+1;
            map[pacman.x8][pacman.y8] = ' ';
            map[pacman.x8][pacman.y8+1] = pacman.character;
            pacman.y8 = pacman.y8+1;
            map[pacman.x1][pacman.y1] = ' ';
            map[pacman.x1][pacman.y1+1] = pacman.character;
            pacman.y1 = pacman.y1+1;
            map[pacman.x4][pacman.y4] = ' ';
            map[pacman.x4][pacman.y4+1] = pacman.character;
            pacman.y4 = pacman.y4+1;
            map[pacman.x7][pacman.y7] = ' ';
            map[pacman.x7][pacman.y7+1] = pacman.character;
            pacman.y7 = pacman.y7+1;
            map[pacman.x0][pacman.y0] = ' ';
            map[pacman.x0][pacman.y0+1] = pacman.character;
            pacman.y0 = pacman.y0+1; 
            map[pacman.x3][pacman.y3] = ' ';
            map[pacman.x3][pacman.y3+1] = pacman.character;
            pacman.y3 = pacman.y3+1;        
            map[pacman.x6][pacman.y6] = ' ';
            map[pacman.x6][pacman.y6+1] = pacman.character;
            pacman.y6 = pacman.y6+1;
        }
        else
        {
            pacman.score++;
            map[pacman.x2][pacman.y2] = ' ';
            map[pacman.x2][pacman.y2+1] = pacman.character;
            pacman.y2 = pacman.y2+1;
            map[pacman.x5][pacman.y5] = ' ';
            map[pacman.x5][pacman.y5+1] = pacman.character;
            pacman.y5 = pacman.y5+1;
            map[pacman.x8][pacman.y8] = ' ';
            map[pacman.x8][pacman.y8+1] = pacman.character;
            pacman.y8 = pacman.y8+1;
            map[pacman.x1][pacman.y1] = ' ';
            map[pacman.x1][pacman.y1+1] = pacman.character;
            pacman.y1 = pacman.y1+1;
            map[pacman.x4][pacman.y4] = ' ';
            map[pacman.x4][pacman.y4+1] = pacman.character;
            pacman.y4 = pacman.y4+1;
            map[pacman.x7][pacman.y7] = ' ';
            map[pacman.x7][pacman.y7+1] = pacman.character;
            pacman.y7 = pacman.y7+1;
            map[pacman.x0][pacman.y0] = ' ';
            map[pacman.x0][pacman.y0+1] = pacman.character;
            pacman.y0 = pacman.y0+1; 
            map[pacman.x3][pacman.y3] = ' ';
            map[pacman.x3][pacman.y3+1] = pacman.character;
            pacman.y3 = pacman.y3+1;        
            map[pacman.x6][pacman.y6] = ' ';
            map[pacman.x6][pacman.y6+1] = pacman.character;
            pacman.y6 = pacman.y6+1;
        }
        return pacman;
    }
    else
      return pacman;
}

pacman mv_pacman_left(char **map, pacman pacman)
{
    if((map[pacman.x0][pacman.y0-1] != WALL) && (map[pacman.x3][pacman.y3-1] != WALL) && (map[pacman.x6][pacman.y6-1] != WALL))
    {
        if((map[pacman.x0][pacman.y0-1] == ESP_FOOD) || (map[pacman.x3][pacman.y3-1] == ESP_FOOD) || (map[pacman.x6][pacman.y6-1] == ESP_FOOD))
        {
            pacman.power_up = 1;
            pacman.score +=2;
            map[pacman.x0][pacman.y0] = ' ';
            map[pacman.x0][pacman.y0-1] = pacman.character;
            pacman.y0 = pacman.y0-1;
            map[pacman.x3][pacman.y3] = ' ';
            map[pacman.x3][pacman.y3-1] = pacman.character;
            pacman.y3 = pacman.y3-1;
            map[pacman.x6][pacman.y6] = ' ';
            map[pacman.x6][pacman.y6-1] = pacman.character;
            pacman.y6 = pacman.y6-1;
            map[pacman.x1][pacman.y1] = ' ';
            map[pacman.x1][pacman.y1-1] = pacman.character;
            pacman.y1 = pacman.y1-1;
            map[pacman.x4][pacman.y4] = ' ';
            map[pacman.x4][pacman.y4-1] = pacman.character;
            pacman.y4 = pacman.y4-1;
            map[pacman.x7][pacman.y7] = ' ';
            map[pacman.x7][pacman.y7-1] = pacman.character;
            pacman.y7 = pacman.y7-1;
            map[pacman.x2][pacman.y2] = ' ';
            map[pacman.x2][pacman.y2-1] = pacman.character;
            pacman.y2 = pacman.y2-1;
            map[pacman.x5][pacman.y5] = ' ';
            map[pacman.x5][pacman.y5-1] = pacman.character;
            pacman.y5 = pacman.y5-1;
            map[pacman.x8][pacman.y8] = ' ';
            map[pacman.x8][pacman.y8-1] = pacman.character;
            pacman.y8 = pacman.y8-1;
        }
        else
        {
            pacman.score++;
            map[pacman.x0][pacman.y0] = ' ';
            map[pacman.x0][pacman.y0-1] = pacman.character;
            pacman.y0 = pacman.y0-1;
            map[pacman.x3][pacman.y3] = ' ';
            map[pacman.x3][pacman.y3-1] = pacman.character;
            pacman.y3 = pacman.y3-1;
            map[pacman.x6][pacman.y6] = ' ';
            map[pacman.x6][pacman.y6-1] = pacman.character;
            pacman.y6 = pacman.y6-1;
            map[pacman.x1][pacman.y1] = ' ';
            map[pacman.x1][pacman.y1-1] = pacman.character;
            pacman.y1 = pacman.y1-1;
            map[pacman.x4][pacman.y4] = ' ';
            map[pacman.x4][pacman.y4-1] = pacman.character;
            pacman.y4 = pacman.y4-1;
            map[pacman.x7][pacman.y7] = ' ';
            map[pacman.x7][pacman.y7-1] = pacman.character;
            pacman.y7 = pacman.y7-1;
            map[pacman.x2][pacman.y2] = ' ';
            map[pacman.x2][pacman.y2-1] = pacman.character;
            pacman.y2 = pacman.y2-1;
            map[pacman.x5][pacman.y5] = ' ';
            map[pacman.x5][pacman.y5-1] = pacman.character;
            pacman.y5 = pacman.y5-1;
            map[pacman.x8][pacman.y8] = ' ';
            map[pacman.x8][pacman.y8-1] = pacman.character;
            pacman.y8 = pacman.y8-1;
        }
        return pacman;
    }
    else
        return pacman;
}

pacman mv_pacman_down(char **map, pacman pacman)
{
    if((map[pacman.x6+1][pacman.y6] != WALL) && (map[pacman.x7+1][pacman.y7] != WALL) && (map[pacman.x8+1][pacman.y8] != WALL))
    {
        if((map[pacman.x6+1][pacman.y6] == ESP_FOOD) || (map[pacman.x7+1][pacman.y7] == ESP_FOOD) || (map[pacman.x8+1][pacman.y8] == ESP_FOOD))
        {
            pacman.power_up = 1;
            pacman.score +=2;
            map[pacman.x6][pacman.y6] = ' ';
            map[pacman.x6+1][pacman.y6] = pacman.character;
            pacman.x6 = pacman.x6+1;
            map[pacman.x3][pacman.y3] = ' ';
            map[pacman.x3+1][pacman.y3] = pacman.character;
            pacman.x3 = pacman.x3+1;
            map[pacman.x0][pacman.y0] = ' ';
            map[pacman.x0+1][pacman.y0] = pacman.character;
            pacman.x0 = pacman.x0+1;
            map[pacman.x7][pacman.y7] = ' ';
            map[pacman.x7+1][pacman.y7] = pacman.character;
            pacman.x7 = pacman.x7+1;
            map[pacman.x4][pacman.y4] = ' ';
            map[pacman.x4+1][pacman.y4] = pacman.character;
            pacman.x4 = pacman.x4+1;
            map[pacman.x1][pacman.y1] = ' ';
            map[pacman.x1+1][pacman.y1] = pacman.character;
            pacman.x1 = pacman.x1+1;
            map[pacman.x8][pacman.y8] = ' ';
            map[pacman.x8+1][pacman.y8] = pacman.character;
            pacman.x8 = pacman.x8+1;
            map[pacman.x5][pacman.y5] = ' ';
            map[pacman.x5+1][pacman.y5] = pacman.character;
            pacman.x5 = pacman.x5+1;
            map[pacman.x2][pacman.y2] = ' ';
            map[pacman.x2+1][pacman.y2] = pacman.character;
            pacman.x2 = pacman.x2+1;
        }
        else
        {
            pacman.score++;
            map[pacman.x6][pacman.y6] = ' ';
            map[pacman.x6+1][pacman.y6] = pacman.character;
            pacman.x6 = pacman.x6+1;
            map[pacman.x3][pacman.y3] = ' ';
            map[pacman.x3+1][pacman.y3] = pacman.character;
            pacman.x3 = pacman.x3+1;
            map[pacman.x0][pacman.y0] = ' ';
            map[pacman.x0+1][pacman.y0] = pacman.character;
            pacman.x0 = pacman.x0+1;
            map[pacman.x7][pacman.y7] = ' ';
            map[pacman.x7+1][pacman.y7] = pacman.character;
            pacman.x7 = pacman.x7+1;
            map[pacman.x4][pacman.y4] = ' ';
            map[pacman.x4+1][pacman.y4] = pacman.character;
            pacman.x4 = pacman.x4+1;
            map[pacman.x1][pacman.y1] = ' ';
            map[pacman.x1+1][pacman.y1] = pacman.character;
            pacman.x1 = pacman.x1+1;
            map[pacman.x8][pacman.y8] = ' ';
            map[pacman.x8+1][pacman.y8] = pacman.character;
            pacman.x8 = pacman.x8+1;
            map[pacman.x5][pacman.y5] = ' ';
            map[pacman.x5+1][pacman.y5] = pacman.character;
            pacman.x5 = pacman.x5+1;
            map[pacman.x2][pacman.y2] = ' ';
            map[pacman.x2+1][pacman.y2] = pacman.character;
            pacman.x2 = pacman.x2+1;
        }
        return pacman;
    }
    else
        return pacman;
}

pacman mv_pacman_up(char **map, pacman pacman)
{
    if((map[pacman.x0-1][pacman.y0] != WALL) && (map[pacman.x1-1][pacman.y1] != WALL) && (map[pacman.x2-1][pacman.y2] != WALL))
    {
        if((map[pacman.x6-1][pacman.y6] == ESP_FOOD) || (map[pacman.x3-1][pacman.y3] == ESP_FOOD) || (map[pacman.x0-1][pacman.y0] == ESP_FOOD))
        {
            pacman.power_up = 1;
            pacman.score +=2;
            map[pacman.x0][pacman.y0] = ' ';
            map[pacman.x0-1][pacman.y0] = pacman.character;
            pacman.x0 = pacman.x0-1;
            map[pacman.x1][pacman.y1] = ' ';
            map[pacman.x1-1][pacman.y1] = pacman.character;
            pacman.x1 = pacman.x1-1;
            map[pacman.x2][pacman.y2] = ' ';
            map[pacman.x2-1][pacman.y2] = pacman.character;
            pacman.x2 = pacman.x2-1;
            map[pacman.x3][pacman.y3] = ' ';
            map[pacman.x3-1][pacman.y3] = pacman.character;
            pacman.x3 = pacman.x3-1;
            map[pacman.x4][pacman.y4] = ' ';
            map[pacman.x4-1][pacman.y4] = pacman.character;
            pacman.x4 = pacman.x4-1;
            map[pacman.x5][pacman.y5] = ' ';
            map[pacman.x5-1][pacman.y5] = pacman.character;
            pacman.x5 = pacman.x5-1;
            map[pacman.x6][pacman.y6] = ' ';
            map[pacman.x6-1][pacman.y6] = pacman.character;
            pacman.x6 = pacman.x6-1;
            map[pacman.x7][pacman.y7] = ' ';
            map[pacman.x7-1][pacman.y7] = pacman.character;
            pacman.x7 = pacman.x7-1;        
            map[pacman.x8][pacman.y8] = ' ';
            map[pacman.x8-1][pacman.y8] = pacman.character;
            pacman.x8 = pacman.x8-1;
        }
        else
        {
            pacman.score++;
            map[pacman.x0][pacman.y0] = ' ';
            map[pacman.x0-1][pacman.y0] = pacman.character;
            pacman.x0 = pacman.x0-1;
            map[pacman.x1][pacman.y1] = ' ';
            map[pacman.x1-1][pacman.y1] = pacman.character;
            pacman.x1 = pacman.x1-1;
            map[pacman.x2][pacman.y2] = ' ';
            map[pacman.x2-1][pacman.y2] = pacman.character;
            pacman.x2 = pacman.x2-1;
            map[pacman.x3][pacman.y3] = ' ';
            map[pacman.x3-1][pacman.y3] = pacman.character;
            pacman.x3 = pacman.x3-1;
            map[pacman.x4][pacman.y4] = ' ';
            map[pacman.x4-1][pacman.y4] = pacman.character;
            pacman.x4 = pacman.x4-1;
            map[pacman.x5][pacman.y5] = ' ';
            map[pacman.x5-1][pacman.y5] = pacman.character;
            pacman.x5 = pacman.x5-1;
            map[pacman.x6][pacman.y6] = ' ';
            map[pacman.x6-1][pacman.y6] = pacman.character;
            pacman.x6 = pacman.x6-1;
            map[pacman.x7][pacman.y7] = ' ';
            map[pacman.x7-1][pacman.y7] = pacman.character;
            pacman.x7 = pacman.x7-1;        
            map[pacman.x8][pacman.y8] = ' ';
            map[pacman.x8-1][pacman.y8] = pacman.character;
            pacman.x8 = pacman.x8-1;
        }
        return pacman;
    }
    else
        return pacman;
}