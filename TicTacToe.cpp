#include "TicTacToe.h"

void TicTacToe::play(Player& xPlayer, Player& oPlayer)
{
    w = nullptr;
    xPlayer.setChar('X');
    oPlayer.setChar('O');
    gboard = '.';
    int size = (gboard.size()) * (gboard.size());
    int end=0;
    while(true)
    {
        tryPlay(xPlayer, oPlayer);
        end++;
        if(w) break;
        if(end==size)break;
        tryPlay(oPlayer,xPlayer);
        end++;
        if(w) break;
        if(end==size)break;
    }
   if(w==nullptr)w=&oPlayer;

}


