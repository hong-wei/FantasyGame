// palyer.h: interface for the player class.
//
// this class provides an board
// types of operation:自己更新 .
//
// author:	Hongwei Zhang
// date:	15.11.2013


//////////////////////////////////////////////////////////////////////
#ifndef PLAYER_H
#define	PLAYER_H

#include <string>
#include"enemy.h"
#include"board.h"

using namespace std;

class inventory
{
public:
    string InvenType;
    int SubStrength;
    int AddAttack;
    int SubAttack;
    int AddDefence;
    int SubDefence;
    int AddHealth;
    int SubHealth;
    int AddStrength;

    void print(){
        cout<< "***The items tpye is = "<<InvenType<<"!"<<endl;
    };
    
};
class player:public enemy  {

public:
    //constructors
    player();
    player(character choose);
    virtual ~player();

    // mothods
    //pick up the inventory and add the attributes
    bool PickUpInventory(inventory &NewInventory,board &CurrentState) ;
    //add the attributes
    void PickUpAddAttributes(inventory &NewInventory);
    //drop the inventory and delete the attributes
    inventory DropInventory(inventory &NewInventory,const int &DropPrintNum);
    //sub the attributes
    void DropSubAttributes(inventory &OldInventory);
    //add the gold number
    inline void GoldAdd(int &GoldAddNum){GoldNumber+=GoldAddNum;};

    //overload
    //overload the attack()
    int Attack();
    //overload the defence()
    void Defence(int &HarmVaule);
    //overload the orcalter
    void OrcAlter(int &steps);
    //print the items lise of the player
    void PlayerListPrint() const;

private:
    
    int GoldNumber ;
    int LifeRingNumber;
    int StrengthRingNumber;
    character PlayerType;
    inventory PlayerWeapon;
    inventory PlayerArmour;
    inventory PlayerShield;
    inventory PlayerRing;
};



#endif

