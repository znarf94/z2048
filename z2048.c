#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <games.h>

#include "z2048_sprites.h"

#pragma string name 2048

#define SCREENX 96
#define SCREENY 64

#define clear() printf("%c", 12)

unsigned short game[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void gset(unsigned char move, unsigned char x, unsigned char y, unsigned short value)
{
    switch(move)
    {
        case 11:    // UP
            game[4*y+x] = value;
            break;
        case 10:    // DOWN
            game[4*(3-y)+x] = value;
            break;
        case 9:     // RIGHT
            game[4*x+(3-y)] = value;
            break;
        case 8:     // LEFT
            game[4*x+y] = value;
            break;
    }
}

unsigned short gget(unsigned char move, unsigned char x, unsigned char y)
{
    switch(move)
    {
        case 11:    // UP
            return game[4*y+x];
            break;
        case 10:    // DOWN
            return game[4*(3-y)+x];
            break;
        case 9:     // RIGHT
            return game[4*x+(3-y)];
            break;
        case 8:     // LEFT
            return game[4*x+y];
            break;
    }

    return 0;
}

void disp_game()
{
    unsigned char x, y;

    for(x=0; x<4; x++)
    {
        for(y=0; y<4; y++)
        {
            putsprite(SPR_AND, x*16+1, y*16+1, empty);
            switch(game[4*y+x])
            {
                case 0:
                    break;
                case 1:
                    putsprite(SPR_OR, x*16+1, y*16+1, s2);
                    break;
                case 2:
                    putsprite(SPR_OR, x*16+1, y*16+1, s4);
                    break;
                case 3:
                    putsprite(SPR_OR, x*16+1, y*16+1, s8);
                    break;
                case 4:
                    putsprite(SPR_OR, x*16+1, y*16+1, s16);
                    break;
                case 5:
                    putsprite(SPR_OR, x*16+1, y*16+1, s32);
                    break;
                case 6:
                    putsprite(SPR_OR, x*16+1, y*16+1, s64);
                    break;
                case 7:
                    putsprite(SPR_OR, x*16+1, y*16+1, s128);
                    break;
                case 8:
                    putsprite(SPR_OR, x*16+1, y*16+1, s256);
                    break;
                case 9:
                    putsprite(SPR_OR, x*16+1, y*16+1, s512);
                    break;
                case 10:
                    putsprite(SPR_OR, x*16+1, y*16+1, s1024);
                    break;
                case 11:
                    putsprite(SPR_OR, x*16+1, y*16+1, s2048);
                    break;
                default:
                    printf("%cUNKNOWN !\nx : %d\ny : %d\ng : %d\n", 12, x, y, game[4*y+x]);
                    getkey();
            }
        }
    }
}

unsigned char compute_move(unsigned char m)
{
    char i, j, l, c;
    unsigned char moved = 0;

    i = 0;
    while(i<4) {
        j = 0;
        while(j<3) {
            if(gget(m, i, j) == 0) {
                c = 0;
                for(l=j; l<3; l++) {
                    gset(m, i, l, gget(m, i, l+1));
                    c += gget(m, i, l);
                }
                gset(m, i, 3, 0);
                if(c != 0) {
                    j--;
                    moved = 1;
                }
            }
            j++;
        }
        i++;
    }

    i = 0;
    while(i<4) {
        j = 0;
        while(j<3) {
            if((gget(m, i, j) != 0) && (gget(m, i, j) == gget(m, i, j+1))) {
                moved = 1;
                gset(m, i, j, 1+gget(m, i, j));
                if(j<2) {
                    for(l=j+1; l<3; l++) {
                        gset(m, i, l, gget(m, i, l+1));
                    }
                }
                gset(m, i, 3, 0);
            }
            j++;
        }
        i++;
    }

    return moved;
}

void random_drop()
{
    unsigned char idx[16];
    unsigned char n=0, i, r, v;

    for(i=0; i<16; i++) {
        if(game[i] == 0) {
            idx[n] = i;
            n++
        }
    }

    if(n > 0) {
        r = rand()%n;
        v = (rand()%8 == 0 ? 2 : 1);
        game[idx[r]] = v;
        putsprite(SPR_AND, (idx[r]%4)*16+1, (idx[r]>>2)*16+1, empty);
        putsprite(SPR_OR, (idx[r]%4)*16+1, (idx[r]>>2)*16+1, (v == 1 ? s2 : s4));
    }
}

main()
{
    int k;

    random_drop();
    random_drop();

    disp_game();

    do{
        k = getkey();

        if((k >= 8) && (k <= 11)) {
            if(compute_move(k) != 0) {
                disp_game();
                random_drop();
            }
        }
    }while(k != 13);
}

// vim: set ts=4 sw=4 et:

