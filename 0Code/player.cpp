// player.cpp: implementation of the player class.
// this class provides the inpliment for the player
//
// author:	hongwei zhang
// date:	15.11.2013
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include "enemy.h"
#include "player.h"
#include "board.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
// default constructor
player::player(){
    character Human = {"Human" ,30,2.0/3,20,1.0/2,60,100};
    inventory Empty = {"Empty"        ,0   ,0,   0,   0,   0,   0,   0,   0};

    GoldNumber = 0;
    LifeRingNumber = 0;
    StrengthRingNumber = 0;
    PlayerType = Human;
    PlayerWeapon = Empty;
    PlayerArmour = Empty;
    PlayerShield = Empty;
    PlayerRing = Empty;
};

//generic constructor
player::player(character choose){
    PlayerType = choose;
    inventory Empty = {"Empty"        ,0   ,0,   0,   0,   0,   0,   0,   0};
   
    GoldNumber = 0;
    LifeRingNumber = 0;
    StrengthRingNumber = 0;
    PlayerWeapon = Empty;
    PlayerArmour = Empty;
    PlayerShield = Empty;
    PlayerRing = Empty;
};

//deconstructor
player::~player(){
    //cout << "called palyer desctructor, delete"<<endl;
};

//pick up the item:change the data of the player
bool player::PickUpInventory(inventory &NewInventory,board &CurrentState){
    bool PickFlag = 0;
    // first test the strength,wheather have the enough strength:
    if(PlayerType.Strength+NewInventory.SubStrength >= 0){
	    //the weapon
        if(NewInventory.InvenType=="SwordWeapon" || NewInventory.InvenType=="DaggerWeapon"){
            if(PlayerWeapon.InvenType == "Empty"){
	            //equip the inventory
	            PlayerWeapon = NewInventory;
                //add the attributes
                PickUpAddAttributes(NewInventory);
                //set the palce empty
                unsigned int Num = 14;
                CurrentState.SetItem(Num);
                 PickFlag = 1;
	        }else
	            cerr<<"***note:You have a weapon, cannot pick up another!"<<endl;
	    //the Armour
	    }else if (NewInventory.InvenType=="LateArmour" || NewInventory.InvenType=="LeatherArmour"){
	        if(PlayerArmour.InvenType == "Empty"){
	            PlayerArmour= NewInventory;
                //add the attributes
                PickUpAddAttributes(NewInventory);
                //set the palce empty
                unsigned int Num = 14;
                CurrentState.SetItem(Num);
                PickFlag = 1;
	        }else
	            cerr<<"***note:You have a Armour, cannot pick up another!"<<endl;
	    //the Shield
	    }else if (NewInventory.InvenType=="LargeShield" || NewInventory.InvenType=="SmallShield"){
	        if(PlayerShield.InvenType == "Empty"){
	            PlayerShield = NewInventory;
                //add the attributes
                PickUpAddAttributes(NewInventory);
                unsigned int Num = 14;
                CurrentState.SetItem(Num);
                 PickFlag = 1;
	        }else
	            cerr<<"***note:You have a shield, cannot pick up another!"<<endl;
	    //the ring
	    }else if (NewInventory.InvenType=="LifeRing" ){
	            PlayerRing = NewInventory;
                //add the attributes
                PickUpAddAttributes(NewInventory);
                //the number of the rings:
                ++LifeRingNumber;
                //set the place empty
                unsigned int Num = 14;
                CurrentState.SetItem(Num);
                PickFlag = 1;
 	    }else if (NewInventory.InvenType=="StrengthRing"){
            if( PlayerType.Health-10>0){
                PlayerRing = NewInventory;
                //add the attributes
                PickUpAddAttributes(NewInventory);
                //the number of the rings:
                ++StrengthRingNumber;
                //set the palce empty
                unsigned int Num = 14;
                CurrentState.SetItem(Num);
                PickFlag = 1;
            }
 	    }
    }else{
        cerr<<"****note : The strength is not enough ,you can not pick up the items"<<endl;
        PickFlag = 0;
    }
    return PickFlag ;
};
    

//Drop the old inventory
inventory player::DropInventory(inventory &NewInventory,const int &DropPrintNum){
    inventory Empty       = {"Empty"        ,0   ,0,   0,   0,   0,   0,   0,   0} ;
    inventory PlayerItems = Empty;
    if(NewInventory.InvenType == "Empty"){
        switch (DropPrintNum) {
		    case 1://weapon
                PlayerItems = PlayerWeapon;
	            PlayerWeapon.InvenType =  "Empty";
                DropSubAttributes(PlayerWeapon);
		        break;
		    case 2://Armour
                PlayerItems = PlayerArmour;
	            PlayerArmour.InvenType =  "Empty";
                DropSubAttributes(PlayerArmour);
                break;
		    case 3://Shield
                PlayerItems = PlayerShield;
                PlayerShield.InvenType =  "Empty";
                DropSubAttributes(PlayerShield);
		        break;
		    case 4://life ring
                if(PlayerRing.InvenType== "LifeRing"&& LifeRingNumber > 0){
                    PlayerItems = PlayerRing;
                    DropSubAttributes(PlayerRing);
                    LifeRingNumber--;
                }else{
                    cout<<"***You have no life rings!!!"<<endl;
                };
		        break;
            case 5://strength ring
                if(PlayerRing.InvenType == "StrengthRing" && StrengthRingNumber > 0){
                    PlayerItems = PlayerRing;
                    DropSubAttributes(PlayerRing);
                    StrengthRingNumber--;
                }else{
                    cout<<"***You have no strength rings!!!"<<endl;
                };
                break;
		    default:
		        break;
		}
    }else
        cerr<<"***There is an item ,you can not drop !!!"<<endl;

    return PlayerItems;
}

//pick up fuction,add the attributes:
void player::PickUpAddAttributes(inventory &NewInventory){
    PlayerType.AttackValue+=(NewInventory.AddAttack+NewInventory.SubAttack);
	PlayerType.DefenceValue+=(NewInventory.AddDefence+NewInventory.SubDefence);
    PlayerType.Health+=(NewInventory.AddHealth + NewInventory.SubHealth);
    PlayerType.Strength+=(NewInventory.AddStrength+ NewInventory.SubStrength);
    // cout<<"888888888888888"<<NewInventory.AddStrength<< NewInventory.SubStrength<<(NewInventory.AddStrength + NewInventory.SubStrength)<<endl; //for test

}

//drop fuction ,sub the attributes
void player::DropSubAttributes(inventory &OldInventory){
    PlayerType.AttackValue-=(OldInventory.AddAttack+OldInventory.SubAttack);
	PlayerType.DefenceValue-=(OldInventory.AddDefence+OldInventory.SubDefence);
    PlayerType.Health-=(OldInventory.AddHealth + OldInventory.SubHealth);
    PlayerType.Strength-=(OldInventory.AddStrength+ OldInventory.SubStrength);
    

}


// overload the attack
int player::Attack()
{
    int chance=0;
    int HarmVaule=0;
    //  srand (time(NULL));
    if(PlayerType.CharType == "Human"){//huamn:2/3
        chance = rand() % 3 + 1;
        if(chance > 1)
            HarmVaule = PlayerType.AttackValue;
        else
            HarmVaule = 0;
    }else if(PlayerType.CharType =="Elf"){//Elf:1/1
        chance = 1;
        HarmVaule = PlayerType.AttackValue;
    }else if(PlayerType.CharType =="Dwarf"){//Dwarf:2/3
        chance = rand() % 3 + 1;
        if(chance > 1)
            HarmVaule = PlayerType.AttackValue;
        else
            HarmVaule = 0;
    }else if(PlayerType.CharType =="Hobbit"){//Hobbit:1/3
        chance = rand() % 3+ 1;
        if(chance > 2)
            HarmVaule = PlayerType.AttackValue;
        else
            HarmVaule = 0;
    }else if(PlayerType.CharType =="OrcDay"){//OrcDay:1/4
        chance = rand() % 4 + 1;
        if(chance > 3)
            HarmVaule = PlayerType.AttackValue;
        else
            HarmVaule = 0;
    }else if(PlayerType.CharType =="OrcNight"){//OrcNight:1/1
        HarmVaule = PlayerType.AttackValue;
    }else
        HarmVaule=0;
    return HarmVaule;
}

//overload the defence()
void player::Defence(int &HarmVaule){
    int chance=0;
    if(PlayerType.CharType == "Human"){//huamn:1/2
        chance = rand() % 2 + 1;
        if(chance > 1)
            cout<<"***Player-Human:Successful defences never cause damage!!!"<<endl;
        else{
            cout<<"***Your health lost = "<<HarmVaule<<" !!!"<<endl;
            PlayerType.Health -= HarmVaule;
        }
    }else if(PlayerType.CharType =="Elf"){//Elf:1/4
        chance = rand()%4 +1;
        if(chance > 3){
            cout<<"***Player-Elf:Successful defences always increases health by 1!!!"<<endl;
            PlayerType.Health += 1;
        }else{
            cout<<"***You lost health = "<<HarmVaule<<" !!!"<<endl;
            PlayerType.Health -= HarmVaule;
         }
    }else if(PlayerType.CharType =="Dwarf"){//Dwarf:2/3
        chance = rand() % 3 + 1;
        if(chance > 1){
            cout<<"***Player-Dwarf: Successful defences never cause damage!!!"<<endl;
        }else{
            cout<<"***You lost health= "<<HarmVaule<<" !!!"<<endl;
            PlayerType.Health -= HarmVaule;
        }
    }else if(PlayerType.CharType =="Hobbit"){//Hobbit:2/3
        chance = rand() % 3 + 1;
        if(chance > 1){
            int HobbitDefenceSucess = 0;
            HobbitDefenceSucess = rand() % 5 + 1;            
            cout<<"***Play-Hobbit: Successful defences cause 0-5 damage"
                <<"regardless of attack value!!! = "<< HobbitDefenceSucess<<"!!!"<<endl;
            PlayerType.Health -= HobbitDefenceSucess;
        }else{
            cout<<"***Your health lost = "<<HarmVaule<<" !!!"<<endl;
            PlayerType.Health -= HarmVaule;
        }
    }else if(PlayerType.CharType =="OrcDay"){//OrcDay:1/4
        chance = rand() % 4 + 1;
        if(chance > 3){
            PlayerType.Health -= (HarmVaule/4);
            cout<<"***Player-Orc: During daytime, successful defences cause"
                <<" 1/4 of adjusted damage!!! = "<<(HarmVaule/4)<<"!!!"<<endl;
        }else{
            cout<<"***Your health lost = "<<HarmVaule<<" !!!"<<endl;
            PlayerType.Health -= HarmVaule;
        }
    }else if(PlayerType.CharType =="OrcNight"){//OrcNight:1/2
        chance = rand() % 2 + 1;
        if(chance > 1){
            cout<<"***Play-Orc:During nighttime, successful defences cause "
                <<"increase of health by 1!!!"<<endl;
            PlayerType.Health += 1;
        }else{
            cout<<"***Your health lost = "<<HarmVaule<<" !!!"<<endl;
            PlayerType.Health -= HarmVaule;
         }
    }

    if (PlayerType.Health <= 0)
        throw runtime_error("***********You are dead!!! You fail  the game!!!****************");
}

//overload the Orc Alter 
void player::OrcAlter(int &steps){
    if ((steps-(steps/10)*10) == 0){
        if(PlayerType.CharType == "OrcNight"){
            PlayerType.CharType = "OrcDay";
            PlayerType.AttackValue -= 20;
            PlayerType.AttackChance = 1.0/4;
            PlayerType.DefenceValue -=15;
            PlayerType.DefenceChance= 1.0/4;
        }
    }else if ((steps-(steps/10)*10) == 5){
        if(PlayerType.CharType == "OrcDay"){
            PlayerType.CharType = "OrcNight";
            PlayerType.AttackValue += 20;
            PlayerType.AttackChance = 1.0/1;
            PlayerType.DefenceValue +=15;
            PlayerType.DefenceChance= 1.0/2;
        }
    };
}


// print the player infromation
void player:: PlayerListPrint() const{
    cout<<"***The player is "<<PlayerType.CharType<<"; "<<endl
        <<"****The attributes********************"<<endl
        <<"Attack = "<<PlayerType.AttackValue<<"; "
        <<"Attack Chance = "<<PlayerType.AttackChance<<"; "
        <<"Defence = "<<PlayerType.DefenceValue<<"; "
        <<"Defence Chance = "<<PlayerType.DefenceChance<<"; "
        <<"Health = "<<PlayerType.Health<<"; "
        <<"Strength = "<<PlayerType.Strength<<"; "<<endl
        <<"****The items list********************"<<endl
        <<"Total Gold = "<< GoldNumber<< "; "<<endl
        <<"Weapon = "<<PlayerWeapon.InvenType<<"; "
        <<"Armour = "<<PlayerArmour.InvenType<<"; "
        <<"Shield = "<<PlayerShield.InvenType<<"; "
        <<"The number of LifeRing = "<<LifeRingNumber<<"; "
        <<"The number of StrenghRing = "<< StrengthRingNumber<<"; "
        <<endl<<endl;
}
