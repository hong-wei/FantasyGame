//.h: interface for the board class.
//
// this class provides an board
// types of operation
//
// author:	hongwei zhang
// date:	15.11.2013

///////////////////////////////////////////////////////////////////
#include <time.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include "stdlib.h"
#include "board.h"
#include "enemy.h"
#include "player.h"
using namespace std;

//rand the 5 kinds of enemies
character RandEnemies(unsigned int&RandNum,int steps);
//rand the 8 kinds of items and 1 empty
inventory RandItems(unsigned int&RandItems); 
// day and night alter every five step:
string DayNightAlter(int steps);
// for player to choose which one he like 
void CharactorChoosePrint();
void CharactorChooseEnter(player & GamePlayer);
// game starting 
void GameProcessPrint(int &CurrentX,int &CurrentY,int &TotalSteps
    ,player &GamePlayer,enemy &EnemyPlayer,inventory &CurrentItem,board &GameBoard);
// when the player drop something ,display the information
void DropPrint();

//user enter the number to choose the character
void BoardNumInput (unsigned int &NewX, unsigned int &NewY);


int main()
{
    srand (time(NULL));
    //the different characters:
    character EnemyEmpty =  {"Empty"  ,0,0,    0,         0,    0,       0};
    
  //   //the items:            type            -Str +Atk -Atk +Def -Def +Hel -Hel +Str
     inventory Empty       = {"Empty"        ,0   ,0,   0,   0,   0,   0,   0,   0} ;
    
    //get the X,Y from the user:
    int CurrentX = 0;//test use
    int CurrentY = 0;//test use
    int TotalSteps = 0;
    bool EnemyUpdataFlag = 0;
    bool PickUpFlag = 0;
    bool DropFlag = 0;
    bool LookFlag = 0;

    enemy EnemyPlayer;
    enemy EnemyIdel;
    player GamePlayer;
    inventory CurrentItem = Empty;
    character CurrentChar = EnemyEmpty;
    unsigned int NewX = 0,NewY = 0;
    // get NewX,NewY for input
    BoardNumInput(NewX, NewY);
    // get the game board
    board GameBoard(NewX,NewY);
    GameBoard.BoardInitialization();
    //show the window for choose the character:
    CharactorChoosePrint();
    // The player choose the character
    CharactorChooseEnter(GamePlayer);
    // start the game:
    cout<<"*******************game start!***********************"<<endl;
    char EnterLetter[100];// keybord numbers
    EnterLetter[0]= 'k'; //idle the keyboard
    do {
        if(EnterLetter[1]== '\0' ){
	         character TestEnemy;
	         TestEnemy = EnemyPlayer.getEnemy();
	         if (EnterLetter[0] == 'a'){
	             EnemyUpdataFlag = 1;
	             int AttackSuccessValue = 0;
	             // the player attack
	             if(TestEnemy.Health > 0){
                     TotalSteps++;
	                 AttackSuccessValue = GamePlayer.Attack();
	                 //cout<< AttackSuccessValue<<"****!!!!"<<endl;
	                 if (AttackSuccessValue == 0){
	                     cerr<<"***You do not attack success!!!"<<endl;
	                 }else{
	                     cout<<"***You attack success!!!"<<endl;
	                 };
	             };
	             // the enemy defence
	             if (AttackSuccessValue != 0){
	                 EnemyPlayer.Defence(AttackSuccessValue);
	                 TestEnemy = EnemyPlayer.getEnemy();
	                 if(TestEnemy.Health > 0 ){
	                     //              cout<<"***You attack success,but the enemy is not dead!!!"
	                     //  <<endl;
	                 }else if (TestEnemy.Health <= 0){
	                     int GoldAddNum = TestEnemy.DefenceValue;
	                     cout<<"***You have defeat the enemy! You Gold add "
	                         << GoldAddNum <<"!!!!" <<endl;
	                     GamePlayer.GoldAdd(GoldAddNum);
	                     //set the squire
	                     if(EnemyUpdataFlag == 1){
	                         EnemyPlayer= EnemyIdel; 
	                     }
	                 }
	             }
	             // the enemy attack the player
	             AttackSuccessValue = 0 ;
	             if(TestEnemy.Health > 0){
	                 AttackSuccessValue = EnemyPlayer.Attack();
	                 if (AttackSuccessValue == 0){
	                     cerr<<"***Enemy do not attack success!!!"<<endl;
	                 };
	                 // the player defence
	                 if(AttackSuccessValue != 0){
	                     GamePlayer.Defence(AttackSuccessValue);
	                 };
	             };
	         }else if(EnterLetter[0] == 'p'){
                 if(PickUpFlag == 0){
                     // up date the current palce
                     unsigned int LookNum = 0;
                     LookNum = GameBoard.BoardLook(CurrentX,CurrentY);
                     CurrentItem = (RandItems(LookNum));
                 }	            
 	             //get the items form the board
 	             PickUpFlag=GamePlayer.PickUpInventory(CurrentItem,GameBoard);
                 if(PickUpFlag == 1){
                      TotalSteps++;
                      CurrentItem = Empty ;
                 }
                    
	        }else if(EnterLetter[0] == 'd'){
	            // up data the current palace
                 if(DropFlag == 0){
                     unsigned int LookNum = 0;
                     LookNum = GameBoard.BoardLook(CurrentX,CurrentY);
                     CurrentItem = (RandItems(LookNum));
                 }
                 DropFlag = 1 ;
	            //drop the items
	            DropPrint();
	            char DropPrintNum[100];
	            cin>>DropPrintNum;
	    		do {
	                if(DropPrintNum[1] ==  '\0' ){
	    		    	if(DropPrintNum[0]=='1'&& CurrentItem.InvenType == "Empty"){
	                	    CurrentItem = GamePlayer.DropInventory(Empty,1);
                            TotalSteps++;
	    		    	    break;
	    		    	}else if(DropPrintNum[0]=='2'&& CurrentItem.InvenType == "Empty"){
	                	    CurrentItem = GamePlayer.DropInventory(Empty,2);
                            TotalSteps++;
	    		    	    break;
	    		    	}else if(DropPrintNum[0]=='3'&& CurrentItem.InvenType == "Empty"){
	                	    CurrentItem = GamePlayer.DropInventory(Empty,3);
                            TotalSteps++;
	    		    	    break;
	    		    	}else if(DropPrintNum[0]=='4'&& CurrentItem.InvenType == "Empty"){
	                	    CurrentItem = GamePlayer.DropInventory(Empty,4);
                            TotalSteps++;
	    		    	    break;
                        }else if(DropPrintNum[0]=='5'&& CurrentItem.InvenType == "Empty"){
	                	    CurrentItem = GamePlayer.DropInventory(Empty,5);
                            TotalSteps++;
	    		    	    break;
	    		    	}else if(DropPrintNum[0]=='6'){
	    		    	    break;
	    		    	}else{
	    		    	    cerr<<"*****\"There is an item,you cannot drop,please enter 1--6:******\" "<<endl<<endl;
	    		    	    DropPrint();
	    		    	    cin>>DropPrintNum;
	    		    	}
	                }else {
	                    cerr<<"*****\"Illegal choice,please enter 1--6:******\" "<<endl<<endl;
	                    DropPrint();
	                    cin>>DropPrintNum;
	                }
	    		} while(1);
	        }else if(EnterLetter[0] == 'l'){
                 LookFlag = 1;
                 TotalSteps++;
                 unsigned int LookNum = 0;
                //  character LookEnemy;
                 LookNum = GameBoard.BoardLook(CurrentX,CurrentY);
	            if(LookNum <6){
                    cout<<"***This squre is Enemy! Here is the information!"<<endl;
	                EnemyPlayer.print();
                    cout<< endl;
                    LookFlag = 1;
 	            }else{
                    cout<<"***This squre is item!  Here is the information!"<<endl;
	                CurrentItem.print();
                    cout<< endl;
	            }
	        }else if(EnterLetter[0] == 'i'){
                 TotalSteps++;
	            GamePlayer.PlayerListPrint();
	            cout<<'i';
	         }else if(EnterLetter[0] == 'x'){
	            return 0;
	         }else if(EnterLetter[0] == 'e'){
	             if((unsigned int )CurrentX+1==NewX){
	                cerr<<"overstep the boundary"<<endl<<endl;
	                cout<<CurrentX<<endl;
	            }else{
	                EnemyUpdataFlag = 0;
	                PickUpFlag = 0 ;
	                DropFlag = 0;
                    LookFlag = 0;
	                CurrentX++;
                    TotalSteps++;
	            }
	        }else if(EnterLetter[0] == 'n'){
	            if(CurrentY==0){
	                cerr<<"overstep the boundary"<<endl<<endl;
	            }else{
	                CurrentY--;
	                EnemyUpdataFlag = 0;
	                PickUpFlag = 0 ;
	                DropFlag = 0;
                    LookFlag = 0;
                    TotalSteps++;
	             }
	                
	         }else if(EnterLetter[0] == 'w'){
	            if(CurrentX==0){
	                cerr<<"overstep the boundary"<<endl<<endl;
	            }else{
	                CurrentX--;
	                EnemyUpdataFlag = 0;
	                PickUpFlag = 0 ;
	                DropFlag = 0;
                    LookFlag = 0;
                    TotalSteps++;
	             }
	            
	        }else if(EnterLetter[0] == 's'){
	             if((unsigned int )CurrentY+1==NewY){
	                cerr<<"overstep the boundary"<<endl<<endl;;
	            }else{
	                CurrentY++;
	                EnemyUpdataFlag = 0;
	                PickUpFlag = 0 ;
	                DropFlag = 0;
                    LookFlag = 0;
                    TotalSteps++;
	             }
	        }else{
	            if(TotalSteps>=1)
	                cerr<<"***Ilegal command，please try again!!!"<<endl<<endl;
	        }
        }else{
            if(TotalSteps>=1)
                cerr<<"***Ilegal command，please try again!!!"<<endl<<endl;
        }
        // get the Enemyplayer
        unsigned int BoardRandNum= 0;
        BoardRandNum = GameBoard.BoardLook(CurrentX,CurrentY);
        CurrentChar = (RandEnemies(BoardRandNum,(TotalSteps+1)));
        if(EnemyUpdataFlag == 1||PickUpFlag == 1 ||DropFlag == 1 || LookFlag == 1){
            EnemyPlayer = EnemyPlayer;
            CurrentItem = CurrentItem;
        }else{
            if(BoardRandNum <6){
        	    EnemyPlayer.setEnemy(CurrentChar);
        	    CurrentItem = Empty;
        	} else{
        	    CurrentItem = (RandItems(BoardRandNum));
        	    EnemyPlayer = EnemyEmpty;
        	}
        }
        // the Orc differenr time different state
        EnemyPlayer.OrcAlter(TotalSteps);
        GamePlayer.OrcAlter(TotalSteps);       
        //put out the game information.
        GameProcessPrint(CurrentX, CurrentY, TotalSteps,GamePlayer,EnemyPlayer,CurrentItem,GameBoard);
        //get to the next place 
        GameBoard.NextPlace(CurrentX,CurrentY);
        cin >> EnterLetter;

    } while (1);
    return 0;
}


string DayNightAlter(int steps){
    string time;
    if ((steps-(steps/10)*10)<5)
        time = "DayTime";
    else
        time = "NightTime";
    return time;
}

void CharactorChoosePrint(){
    cout<<"Please choose the character from following five:"<<endl;
    cout<<"1:Human "<<endl<< "2:Elf "<<endl<< "3:Dwarf "<<endl
        << "4:Hobbit "<<endl<< "5:Orc "<<endl;
    cout<<"Please enter 1--5 :"<<endl;
}

void GameProcessPrint(int &CurrentX,int &CurrentY,int &TotalSteps
    ,player &GamePlayer,enemy &EnemyPlayer,
    inventory &CurrentItem,board &GameBoard){
    cout<<"["<<CurrentX<<"]"<<"["<<CurrentY<<"]"
        <<" is position of the square "<<endl;
    cout<<"It is "<<DayNightAlter((TotalSteps))<<
            " <" <<TotalSteps<<">"<<endl;
    EnemyPlayer.print();
    CurrentItem.print();
    
    GamePlayer.PlayerListPrint();
    cout<<"Please choose the direction N,S,E,W or"<<endl;
    cout<< "Commands: <A>ttack, <P>ickup, <D>rop, <L>ook"; 
    cout<<" <I>nventory or e<X>it:"<<endl;
}

void DropPrint(){
    cout<<"Please choose which items you will drop"<<endl
        <<"1:Weapon" <<endl << "2:Armour "<<endl
        <<"3:Shield" <<endl << "4:Life Ring"<<endl
        <<"5:Strength ring"<<endl << "6:Nothing Drop, Back Game!!"
        <<endl<<"Please enter 1--6 :"<<endl;
}

character RandEnemies(unsigned int &RandNum,int steps){
    // the atributes  Race     Attack AkChance Defence DChance  Health  Stength
    character Human = {"Human" ,30,   2.0/3,  20,     1.0/2,   60,     100};
    character Elf   = {"Elf"   ,40,   1.0/1,  10,     1.0/4,   40,     70 };
    character Dwarf = {"Dwarf" ,30,   2.0/3,  20,     2.0/3,   50,     130};
    character Hobbit= {"Hobbit",25,   1.0/3,  20,     2.0/3,   70,     85 };
    character OrcDay  = {"OrcDay"  ,25,1.0/4, 10,     1.0/4,   50,     130};
    character OrcNight= {"OrcNight",45,1.0/1, 25,     1.0/2,   50,     130};
    character ReturnEnemy; 
    switch(RandNum){
        case 1:
            ReturnEnemy = Human;
            break;
        case 2:
            ReturnEnemy = Elf;
            break;
        case 3:
            ReturnEnemy = Dwarf;
            break;
        case 4:
            ReturnEnemy =  Hobbit;
            break;
        case 5:
            if ((steps-(steps/10)*10)<5)
                ReturnEnemy = OrcDay;
            else
                ReturnEnemy = OrcNight;
            break;
        default:
            break;
    }
    return ReturnEnemy;
}

inventory RandItems(unsigned &RandItems){
      //the items:            type            -Str +Atk -Atk +Def -Def +Hel -Hel +Str
    inventory SwordWeapon = {"SwordWeapon"  ,-10 ,10,  0,   0,   0,   0,   0,   0} ;
    inventory DaggerWeapon= {"DaggerWeapon" ,-5  ,5 ,  0,   0,   0,   0,   0,   0} ;
    inventory LateArmour  = {"LateArmour"   ,-40 ,0,  -5,   10,  0,   0,   0,   0} ;
    inventory LeatherArmour={"LeatherArmour",-20 ,0,   0,   5,   0,   0,   0,   0} ;
    inventory LargeShield = {"LargeShield"  ,-30 ,0,  -5,   10,  0,   0,   0,   0} ;
    inventory SmallShield = {"SmallShield"  ,-10 ,0,   0,   5,   0,   0,   0,   0} ;
    inventory LifeRing    = {"LifeRing"     ,-1  ,0,   0,   0,   0,   10,  0,   0} ;
    inventory StrengthRing= {"StrengthRing" ,-1  ,0,   0,   0,   0,   0, -10,  50} ;
    inventory Empty       = {"Empty"        ,0   ,0,   0,   0,   0,   0,   0,   0} ;
    inventory NewItems;
    switch(RandItems){
        case 6:
            NewItems = SwordWeapon;
            break;
        case 7:
            NewItems = DaggerWeapon;
            break;
        case 8:
            NewItems = LateArmour;
            break;
        case 9:
            NewItems = LeatherArmour;
            break;
        case 10:
            NewItems = LargeShield;
            break;
        case 11:
            NewItems = SmallShield;
            break;
        case 12:
            NewItems = LifeRing;
            break;
        case 13:
            NewItems = StrengthRing;
            break;
        case 14:
            NewItems = Empty;
            break;
        case 15:
            NewItems = Empty;
            break;
        default:
            break;
    }
    return NewItems;
}

void BoardNumInput(unsigned int &NewX, unsigned int &NewY){
    
    char CharX[100],CharY[100];
    int NewXTemp,NewYTemp;
    cout<<"Please enter the number of x and y for the game board:"<<endl;
    while(1){
        cin>>CharX>>CharY;
        NewXTemp = atoi(CharX);
        NewYTemp = atoi(CharY);
        if(NewXTemp>0 && NewYTemp>0){
            NewX=(unsigned int)NewXTemp;
            NewY=(unsigned int)NewYTemp;
            break;
        }else{
             cout<<"Error input,Please enter the number for the x and y "<<endl;
        }
    }
}

void CharactorChooseEnter(player & GamePlayer){
    character Human = {"Human" ,30,   2.0/3,  20,     1.0/2,   60,     100};
    character Elf   = {"Elf"   ,40,   1.0/1,  10,     1.0/4,   40,     70 };
    character Dwarf = {"Dwarf" ,30,   2.0/3,  20,     2.0/3,   50,     130};
    character Hobbit= {"Hobbit",25,   1.0/3,  20,     2.0/3,   70,     85 };
    character OrcDay  = {"OrcDay"  ,25,1.0/4, 10,     1.0/4,   50,     130};
    char ChoiceNumber[100];
    // cin>>ChoiceNumber[0];
    cin>>ChoiceNumber;
    while(1){
        if(ChoiceNumber[1] ==  '\0' ){
            if(ChoiceNumber[0]=='1'){
        	    GamePlayer = Human;
        	    break;
        	}else if(ChoiceNumber[0]=='2'){
        	    GamePlayer = Elf;
        	    break;
        	}else if(ChoiceNumber[0]=='3'){
        	    GamePlayer = Dwarf;
        	    break;
        	}else if(ChoiceNumber[0]=='4'){
        	    GamePlayer = Hobbit;
        	    break;
        	}else if(ChoiceNumber[0]=='5'){
        	    GamePlayer = OrcDay;
        	    break;
        	}else{
        	    cerr<<"*****\"Illegal choice,please try again******\" "<<endl<<endl;
        	    CharactorChoosePrint();
        	    cin>>ChoiceNumber;
        	}
        }else{
            cerr<<"*****\"Illegal choice,please try again******\" "<<endl<<endl;
            CharactorChoosePrint();
            cin>>ChoiceNumber;

        }
        
    }

}