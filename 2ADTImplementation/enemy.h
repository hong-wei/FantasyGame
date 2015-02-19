// board.h: interface for the board class.
//
// this class provides an board
// types of operation:自己填充 .
//
// author:	Hongwei Zhang
// date:	15.11.2013


//////////////////////////////////////////////////////////////////////
#ifndef ENEMY_H
#define	ENEMY_H

#include <iostream>
#include <string>

using namespace std;


// define type for required data - usually a fully defined class
// will be used. this example is a plain convenience dummy-class
class character
{
public:
    string CharType;
    int AttackValue;
    double AttackChance;
    int DefenceValue;
    double DefenceChance;
    int Health;
    int Strength;
};


class enemy
{
    
public:
    //default constructor
    enemy();
    //general constructor
    enemy(character choose);
    //deconstructor
    virtual ~enemy();
    // attack the player
    int Attack() ;
    // defence for the a ttack
    void Defence(int &HarmVaule);
    // print the members
    void OrcAlter(int &steps);
    void print() const;
    inline character getEnemy(){return EnemyType;};
    inline void setEnemy(character & NewEnemy){EnemyType = NewEnemy;};
private:   
    character EnemyType;

};



#endif

