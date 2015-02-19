// enemy.cpp: implementation of the enemy class.
// this class provides the inpliment for the enemy
//
// author:	hongwei zhang
// date:	15.11.2013
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <exception>
#include <cstdlib>
#include "enemy.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
// default constructor
enemy::enemy(){
     character EnemyEmpty =  {"Empty"  ,0,0,    0,         0,    0,       0};
     EnemyType = EnemyEmpty;
}

//generic constructor
enemy::enemy(character choose){
    EnemyType = choose;
}

//deconstructor
enemy::~enemy(){
}

//print the infromation
void enemy:: print() const{
    cout<<"***The enenmy is "<<EnemyType.CharType<<"; "<<endl;
    if(EnemyType.CharType != "Empty"){
        cout<<"Attack = "<<EnemyType.AttackValue<<"; "
            <<"Attack Chance = "<<EnemyType.AttackChance<<"; "
            <<"Defence = "<<EnemyType.DefenceValue<<"; "
            <<"Defence Chance = "<<EnemyType.DefenceChance<<"; "
            <<"Health = "<<EnemyType.Health<<"; "
            <<"Strength = "<<EnemyType.Strength<<"; "<<endl;
    };
}

// attack the player
int enemy::Attack()
{
    int chance=0;
    int HarmVaule=0;
    //  srand (time(NULL));
    if(EnemyType.CharType == "Human"){//huamn:2/3
        chance = rand() % 3 + 1;
        if(chance > 1)
            HarmVaule = EnemyType.AttackValue;
        else
            HarmVaule = 0;
    }else if(EnemyType.CharType =="Elf"){//Elf:1/1
        chance = 1;
        HarmVaule = EnemyType.AttackValue;
    }else if(EnemyType.CharType =="Dwarf"){//Dwarf:2/3
        chance = rand() % 3 + 1;
        if(chance > 1)
            HarmVaule = EnemyType.AttackValue;
        else
            HarmVaule = 0;
    }else if(EnemyType.CharType =="Hobbit"){//Hobbit:1/3
        chance = rand() % 3 + 1;
        if(chance > 2)
            HarmVaule = EnemyType.AttackValue;
        else
            HarmVaule = 0;
    }else if(EnemyType.CharType =="OrcDay"){//OrcDay:1/4
        chance = rand() % 4 + 1;
        if(chance > 3)
            HarmVaule = EnemyType.AttackValue;
        else
            HarmVaule = 0;
    }else if(EnemyType.CharType =="OrcNight"){//OrcNight:1/1
        HarmVaule = EnemyType.AttackValue;
    }else
        HarmVaule=0;
    return HarmVaule;
}

//defence
void enemy::Defence(int &HarmVaule)
{
    int chance=0;
        if(EnemyType.CharType == "Human"){//huamn:1/2
            chance = rand() % 2 + 1;
            if(chance > 1)
                cout<<"***Enemy-Human:Successful defences never cause damage!!!"
                    <<endl;
            else{
                EnemyType.Health -= HarmVaule;
            }
        }else if(EnemyType.CharType =="Elf"){//Elf:1/4
            chance = rand()%4 +1;
            if(chance > 3){
                cout<<"***Enemy-Elf:Successful defences always increases health by 1!!!"
                    <<endl;
                EnemyType.Health += 1;
            }else{
                EnemyType.Health -= HarmVaule;
            }
        }else if(EnemyType.CharType =="Dwarf"){//Dwarf:2/3
            chance = rand() % 3 + 1;
            if(chance > 1){
                cout<<"***Enemy-Dwarf: Successful defences never cause damage!!!"<<endl;
            }else{
                 EnemyType.Health -= HarmVaule;
            }
        }else if(EnemyType.CharType =="Hobbit"){//Hobbit:2/3
            chance = rand() % 3 + 1;
            if(chance > 1){
                cout<<"***Enemy-Hobbit: Successful defences cause 0-5 damage"
                    <<"regardless of attack value!!!"<<endl;
                int HobbitDefenceSucess = 0;
                HobbitDefenceSucess = rand() % 5 + 1;
                EnemyType.Health -= HobbitDefenceSucess;
            }else{
                EnemyType.Health -= HarmVaule;
            }
        }else if(EnemyType.CharType =="OrcDay"){//OrcDay:1/4
            chance = rand() % 4 + 1;
            if(chance > 3){
                cout<<"***Enemy-Orc: During daytime, successful defences cause"
                    <<" 1/4 of adjusted damage!!!"<<endl;
                EnemyType.Health -= (HarmVaule/4);
            }else{
                EnemyType.Health -= HarmVaule;
            }
        }else if(EnemyType.CharType =="OrcNight"){//OrcNight:1/2
            chance = rand() % 2 + 1;
            if(chance > 1){
                cout<<"***Enemy-Orc:During nighttime, successful defences cause "
                    <<"increase of health by 1!!!"<<endl;
                EnemyType.Health += 1;
            }else{
                EnemyType.Health -= HarmVaule;
            }
        }
}

void enemy::OrcAlter(int &steps){
    if ((steps-(steps/10)*10) == 0){
        if(EnemyType.CharType == "OrcNight"){
            EnemyType.CharType = "OrcDay";
            EnemyType.AttackValue -= 20;
            EnemyType.AttackChance = 1.0/4;
            EnemyType.DefenceValue -=15;
            EnemyType.DefenceChance= 1.0/4;
        }
    }else if ((steps-(steps/10)*10) == 5){
        if(EnemyType.CharType == "OrcDay"){
            EnemyType.CharType = "OrcNight";
            EnemyType.AttackValue += 20;
            EnemyType.AttackChance = 1.0/1;
            EnemyType.DefenceValue +=15;
            EnemyType.DefenceChance= 1.0/2;
        }
    };
}
