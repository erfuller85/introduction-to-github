////////////////////////////////
// Header
///////////////////////////////
// Cyber Systems Engineering
// Josué Loor Sánchez, Evan Fuller
// 09/09/2022
// EECE71020-1
// Assingment 4
//////////////////////////////
// Info

// "Preprocessor Directives"
#include <stdio.h>
// Used for NULL
#include <stdlib.h>
// Required for "getch" to get input value
#include <conio.h>
// Required for system("cls")
#include <unistd.h>
// For Sleep()
#include <windows.h>
// Used for rand and srand
#include <time.h>

#define boardsizex 30
#define boardsizey 30

int gameover = 0; //used to end the game under certain conditions
//int boardsizex = 30;
//int boardsizey = 30; 	//size of the board
int snakex; 
int snakey; 	//15 is the starting coordinate (middle of board)
int snakemax = 28;	// Max position for Border() function 
int snakemin = 1;	// Min position for Border() function 
int foodx;	// food postion y coordinate
int foody; // food postion x coordinate
int direction = 3;	// Default direction for snake (right)
int boardwidth = 29;
int boardheight = 29;
int totalTail;
int tailX[30], tailY[30];	// array used for moving the tail
int food;	// used for knowing if there is currently food on the board
int delaytime = 1; 	// delay time constant
int goX = 1;
int goY = 0;
int board[boardsizex][boardsizey];
int snakebody[29*29];
int snakelength = 1;
int nospace = 0;

void FoodLocation(){
    srand(time(NULL));	// allows for a different location of the food for every time the console is loaded
   snakex = boardsizex/2;	// This sets the coordinates of the starting position of the snake, half the widht and height so it starts in the middle of the board
	snakey = boardsizey/2;
    

    
    foodx = 1 + rand()%28;
    foody = 1+ rand()%28;

	if(foodx == 0 && foody == 0) //this means no food on board
		{
			food = 1;		// when there is no food on the board, this allows the following printf statement to print 1 food
		}

    
    }


void Board()
{
    system("cls");

    for(int i = 0; i<boardsizey;i++)
	{
        for(int j = 0; j<boardsizex; j++)
		{
            if(i == 0||j == 0||i == boardsizex-1|| j == boardsizey-1)
			{
                printf("#");						//from 0-30 it will print '#' in both directions
            }
            else if(i == snakex&&j == snakey)
			{
                printf("$");
            } else if(foodx == i && foody == j)
			{
                printf("@");								//When there is no food on the board it will print '@'
            } else
			{
                						// the integer 'nospace' shows when something is being printed
                
				{
                    if(snakebody[1] == snakelength && snakebody[1] == snakelength)
					{
                        printf("*");
                        nospace = 1;
                    }
                
                else //if(nospace == 0){		//when 'nospace' is zero, nothing will be printed
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    

}
// Function using switch to take keyboards output and translate it to 'direction' interger
void UserInput(){

    if(kbhit())		// Checks for keyboard hit
	{	
	
        switch(getch())
		{					// Only takes one input
        	case 'w':
            	direction = 1;
            	goX = 0;
            	goY = 1;
            	break;			// Case switches based on input
        	case 's':
            	direction = 2;
            	goX = 0;
            	goY = -1;
            	break;
        	case 'a':
            	direction = 3;
            	goX = -1;
            	goY = 0;
            	break;
        	case 'd':
            	direction = 4;
            	goX = 1;
            	goY = 0;
            	break;
    }
    }
}

// Function used to check for snakes position and move the snake across the board accordingly
void Boundry()
{
	if (snakex < snakemin)
	{
		snakex = snakemax;
	}
	else if (snakex > snakemax)
	{
		snakex = snakemin;
}
	else if (snakey < snakemin)
	{
		snakey = snakemax;
	}
	else if (snakey > snakemax)
	{
		snakey = snakemin;
	}
}

//fuction that controls snakes tail, snakes direcction, and gomeover conditions
void GameLogic()
{
   // int previousX = tailX[0];		//this logic accounts for the snakes tail to follow itself
   // int previousY = tailY[0];
   // int previous2X, previous2Y;	
   // tailX[0] = snakex;
   // tailY[0] = snakey;
    //for (int i = 1; i < totalTail; i++)
    //{
      //  previous2X = tailX[i];		//previous x tail coordinate is equal to current one
      //  previous2Y = tailY[i];		//previous y tail coordinate is equal to current one
      //  tailX[i] = previousX;		//as it is in the for loop the tail array will contiuosly take the value of the previous tail position, allowing the tail to follow itself
      //  tailY[i] = previousY;
      //  previousX = previous2X;
      //  previousY = previous2Y;
   // }

    switch(direction)
	{
    	sleep(delaytime); // Delay to prevent game running too fast
        case 1:
            snakex--;
            if(snakex == foodx && snakey == foody)
            {
            	snakebody[0]=(snakelength%boardwidth)-1;
			}
			snakelength++;
			snakebody[1] = snakelength;
			nospace = 1;
            break;
        case 2:
            snakex++;
            if(snakex == foodx && snakey == foody)
            {
            	snakebody[0]=(snakelength%boardwidth)-1;
			}
			snakelength++;
			snakebody[1] = snakelength;
			nospace = 1;
            break;
        case 3:
            snakey--;
            if(snakex == foodx && snakey == foody)
            {
            	snakebody[0]=(snakelength%boardwidth)-1;
			}
			snakelength++;
			snakebody[1] = snakelength;
			nospace = 1;
            break;
        case 4:
            snakey++;
            if(snakex == foodx && snakey == foody)
            {
            	snakebody[0]=(snakelength%boardwidth)-1;
			}
			snakelength++;
			snakebody[1] = snakelength;
			nospace = 1;
			
            break;
        default:
            break;
    }
    
    for(int i = 0; i <totalTail; i++)
	{
        if(tailX[i] == snakex&&tailY[i] == snakey)
		{															// if the snake head and the snake tail occupy the smae space the game will end
            gameover = 1;
        }
    }

    if(snakex > boardwidth||snakey>boardheight||snakex<0||snakey<0)	//if the snake head and the border occupy the same space the game will end
	{
        gameover = 1;
    }

    if(snakex == foodx && snakey == foody)
	{
        
        snakelength++;
        					// IF the snake head and food occupy the same space, tail increases, and the food is radomly placed somewhere else
        foodx = 1+rand()%28;
        foody = 1+rand()%28;

       
    }
}

int main()
{
    FoodLocation();

    while(gameover != 1)
	{
        Board();
        GameLogic();
        UserInput();
        //Boundry();
        Sleep(10);
    }
    return 0;
}
