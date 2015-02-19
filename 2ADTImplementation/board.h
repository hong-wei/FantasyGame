// board.h: interface for the board class.
//
// this class provides an board
// types of operation:自己填充 .
//
// author:	Jian Gao
// date:	15.11.2013


//////////////////////////////////////////////////////////////////////

#ifndef BOARD_H
#define BOARD_H


class board
{
public:
    //constructor:
    board();
    board(unsigned int NewX,unsigned int NewY);
    virtual ~board();
    // copy constructor
    board (board &orig);
    // assignment operate
    board &operator=(const board &orig);
    
    //methods
    void BoardInitialization();
    //choosing the charactor begins the game at the starting square.
    inline void SetPlace(unsigned int &x,unsigned int &y,unsigned int &i){
        CurrentState[x][y]=i;
    };
    // set the number to board.
    inline void SetItem(unsigned int &NewItems){CurrentState[x][y]=NewItems;}
    // get the number form the board
    //  inline *unsigned int (unsigned int &x ,unsigned int &y){return;}
    //character moves to the square in the indicated direction
    //(north=up, south=down, east=right, west=left)
    inline void NextPlace( int &NextX, int &NextY){x = NextX; y= NextY;};
    // look function
    //  inline unsigned int BoardLook(){ return CurrentState[x][y];}
   inline unsigned int BoardLook( int &NextX, int &NextY){ return CurrentState[NextX][NextY];}

private:
    unsigned int x;
    unsigned int y;
    unsigned int **CurrentState;// get the information of the current squre.
};

#endif

