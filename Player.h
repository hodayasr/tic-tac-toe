#pragma once
#include "Board.h"
#include "BoardIndex.h"

using Coordinate = BoardIndex;

class Player{

public:
    
char myChar;
        
    char getChar() const
    {
        return myChar;
    }
    
    void setChar(char c)
    {
        myChar = c;
    }


    virtual const std::string name() const = 0;
    virtual const Coordinate play(const Board& board) = 0;

};

