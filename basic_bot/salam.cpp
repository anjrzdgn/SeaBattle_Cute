#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;


string direction;
string exactDirection = "Default";
int shootSuccses = 0;
bool fallShip = false;

int firstShot[1][2];

void attackAgain(char _table[10][10], int X, int Y)
{
    
    if(_table[X][Y] == 'S')
    {
        _table[X][Y] = 'B';
        shootSuccses++; 


        if(X == firstShot[0][0])
        {
            direction = "horizontal";
            
            if(Y - firstShot[0][1] > 0)
            {
                if(exactDirection == "Right")
                {
                    //table 2 space fall
                    if(_table[X][Y + 1] != 'S' && _table[X][Y - 2] != 'B')
                    {
                        _table[X][Y] = 'F';
                        _table[X][Y - 1] = 'F';
                        fallShip = true;
                    }
                
                    //absoultly have 3 space maby 4 space
                    else if(_table[X][Y + 1] != 'S' && _table[X][Y - 2] == 'B')
                    {
                        //have 4 space
                        if(_table[X][Y - 3] == 'B')
                        {
                            _table[X][Y - 3] = 'F';
                            _table[X][Y - 2] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                        }

                        //have 3 space
                        else
                        {
                            _table[X][Y - 2] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                        }

                    }

                    //absoultly have 3 space maby 4 space
                    else if(_table[X][Y + 1] == 'S')
                    {
                        _table[X][Y + 1] = 'B';
                        
                        //have 3 space
                        if(_table[X][Y + 2] != 'S' && _table[X][Y - 2] != 'B')
                        {
                            _table[X][Y + 1] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;

                        }
                        //havev 4 space
                        else if(_table[X][Y + 2] == 'S')
                        {
                            _table[X][Y + 2] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip =  true;
                        }

                        else if(_table[X][Y - 3] == 'W')
                        {
                            _table[X][Y - 2] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            return;
                        }
                    }
                }

                else if(exactDirection == "Default")
                {
                    //check ship 2 space
                    if(_table[X][Y + 1] == 'E' && _table[X][Y - 2] == 'E')
                    {
                        //ship had 2 spaces but now fall
                        _table[X][Y] = 'F';
                        _table[X][Y - 1] = 'F';
                        fallShip = true;
                        //atack again random
                        //return;
                    }

                    //absoultly have 3 space
                    else if(_table[X][Y + 1] == 'S' && _table[X][Y + 2] == 'E' && _table[X][Y - 2] == 'E')
                    {
                        _table[X][Y + 1] = 'F';
                        _table[X][Y - 1] = 'F';
                        _table[X][Y] = 'F';
                        fallShip = true;
                        shootSuccses++;
                    }

                    //maby ship have 3 or 4 spaces and change direction
                    else if(_table[X][Y + 1] == 'E')
                    {
                        _table[X][Y + 1] = 'W';
                        exactDirection = "Left";
                        fallShip = false;
                        return;
                    }

                    //have 4 space
                    else if(_table[X][Y + 1] == 'S')
                    {
                        //absoultly have 4 apace
                        if(_table[X][Y + 2] == 'S')
                        {
                            _table[X][Y + 2] ='F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                        }

                        //absoultly have 4 spacce but should change direction 
                        else if(_table[X][Y + 2] == 'E' && _table[X][Y - 2] == 'S')
                        {
                            _table[X][Y + 1] = 'B';
                            _table[X][Y + 2] = 'W';
                            exactDirection = "Left";
                            
                            fallShip = false;      
                            shootSuccses++;
                            
                            return;                  
                        } 

                    }

                }
            }
            
            if(Y - firstShot[0][1] < 0)
            {

                if(exactDirection == "Left")
                {
                    //table 2 space fall
                    if(_table[X][Y - 1] != 'S' && _table[X][Y + 2] != 'B')
                    {
                        _table[X][Y] = 'F';
                        _table[X][Y + 1] = 'F';
                        fallShip = true;
                    }
                  
                    //absoultly have 3 space maby 4 space
                    else if(_table[X][Y - 1] != 'S' && _table[X][Y + 2] == 'B')
                    {
                        //have 4 space
                        if(_table[X][Y + 3] == 'B')
                        {
                            _table[X][Y + 3] = 'F';
                            _table[X][Y + 2] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                        }

                        //have 3 space
                        else
                        {
                            _table[X][Y + 2] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                        }

                    }

                    //absoultly have 3 space maby 4 space
                    else if(_table[X][Y - 1] == 'S')
                    {
                        _table[X][Y - 1] = 'B';
                        
                        //have 3 space
                        if(_table[X][Y - 2] != 'S' && _table[X][Y + 2] != 'B')
                        {
                            _table[X][Y - 1] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;

                        }
                        //havev 4 space
                        else if(_table[X][Y - 2] == 'S')
                        {
                            _table[X][Y - 2] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip =  true;
                        }

                        else if(_table[X][Y + 3] == 'W')
                        {
                            _table[X][Y + 2] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            return;
                        }
                    }
                
                }

                else if(exactDirection == "Default")
                {
                    //check ship 2 space
                    if(_table[X][Y - 1] == 'E' && _table[X][Y + 2] == 'E')
                    {
                        //ship had 2 spaces but now fall
                        _table[X][Y] = 'F';
                        _table[X][Y + 1] = 'F';
                        fallShip = true;
                        //atack again random
                        return;
                    }

                    //absoultly have 3 space
                    else if(_table[X][Y - 1] == 'S' && _table[X][Y - 2] == 'E' && _table[X][Y + 2] == 'E')
                    {
                        _table[X][Y - 1] = 'F';
                        _table[X][Y + 1] = 'F';
                        _table[X][Y] = 'F';
                        fallShip = true;
                        shootSuccses++;
                    }

                    //maby ship have 3 or 4 spaces and change direction
                    else if(_table[X][Y - 1] == 'E')
                    {
                        _table[X][Y - 1] = 'W';
                        exactDirection = "Right";
                        fallShip = false;
                        return;
                    }

                    //have 4 space
                    else if(_table[X][Y - 1] == 'S')
                    {
                        //absoultly have 4 apace
                        if(_table[X][Y - 2] == 'S')
                        {
                            _table[X][Y - 2] ='F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                        }

                        //absoultly have 4 spacce but should change direction 
                        else if(_table[X][Y - 2] == 'E' && _table[X][Y + 2] == 'S')
                        {
                            _table[X][Y - 1] = 'B';
                            _table[X][Y - 2] = 'W';
                            exactDirection = "Right";            
                            fallShip = false;      
                            shootSuccses++;
                            
                            return;                  
                        } 

                    }         
                }                
            }

            else
            {
             //   attackAgain(_table, X, Y - 1);
            }
        }

        else if(Y == firstShot[0][1])
        {
            direction = "vertical";
            
            if(X - firstShot[0][0] > 0)
            {
                if(exactDirection == "Down")
                {
                    //table 2 space fall
                    if(_table[X + 1][Y] != 'S' && _table[X - 2][Y] != 'B')
                    {
                        _table[X][Y] = 'F';
                        _table[X - 1][Y] = 'F';
                        fallShip = true;
                    }
                
                    //absoultly have 3 space maby 4 space
                    else if(_table[X + 1][Y] != 'S' && _table[X - 2][Y] == 'B')
                    {
                        //have 4 space
                        if(_table[X - 3][Y] == 'B')
                        {
                            _table[X - 3][Y] = 'F';
                            _table[X - 2][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                        }

                        //have 3 space
                        else
                        {
                            _table[X][Y - 2] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                        }

                    }

                    //absoultly have 3 space maby 4 space
                    else if(_table[X + 1][Y] == 'S')
                    {
                        _table[X + 1][Y] = 'B';
                        
                        //have 3 space
                        if(_table[X + 2][Y] != 'S' && _table[X - 2][Y] != 'B')
                        {
                            _table[X + 1][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;

                        }
                        //havev 4 space
                        else if(_table[X + 2][Y] == 'S')
                        {
                            _table[X + 2][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip =  true;
                        }

                        else if(_table[X - 3][Y] == 'W')
                        {
                            _table[X - 2][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            return;
                        }
                    }
                }

                else if(exactDirection == "Default")
                {
                     //check ship 2 space
                    if(_table[X + 1][Y] == 'E' && _table[X - 2][Y] == 'E')
                    {
                        //ship had 2 spaces but now fall
                        _table[X][Y] = 'F';
                        _table[X - 1][Y] = 'F';
                        fallShip = true;
                        //atack again random
                        return;
                    }

                    //absoultly have 3 space
                    else if(_table[X + 1][Y] == 'S' && _table[X + 2][Y] == 'E' && _table[X - 2][Y] == 'E')
                    {
                        _table[X + 1][Y] = 'F';
                        _table[X - 1][Y] = 'F';
                        _table[X][Y] = 'F';
                        fallShip = true;
                        shootSuccses++;
                    }

                    //maby ship have 3 or 4 spaces and change direction
                    else if(_table[X][Y + 1] == 'E')
                    {
                        _table[X + 1][Y] = 'W';
                        exactDirection = "UP";
                        fallShip = false;
                        return;
                    }

                    //have 4 space
                    else if(_table[X + 1][Y] == 'S')
                    {
                        //absoultly have 4 apace
                        if(_table[X + 2][Y] == 'S')
                        {
                            _table[X + 2][Y] ='F';
                            _table[X + 1][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                        }

                        //absoultly have 4 spacce but should change direction 
                        else if(_table[X + 2][Y] == 'E' && _table[X - 2][Y] == 'S')
                        {
                            _table[X + 1][Y] = 'B';
                            _table[X + 2][Y] = 'W';
                            exactDirection = "Up";
                            
                            fallShip = false;      
                            shootSuccses++;
                            
                            return;                  
                        } 

                    }
                }
            }
            
            else if(X - firstShot[0][0] < 0)
            {
                if(exactDirection == "Down")
                {
                    //table 2 space fall
                    if(_table[X - 1][Y] != 'S' && _table[X + 2][Y] != 'B')
                    {
                        _table[X][Y] = 'F';
                        _table[X + 1][Y] = 'F';
                        fallShip = true;
                    }
                  
                    //absoultly have 3 space maby 4 space
                    else if(_table[X - 1][Y] != 'S' && _table[X + 2][Y] == 'B')
                    {
                        //have 4 space
                        if(_table[X + 3][Y] == 'B')
                        {
                            _table[X + 3][Y] = 'F';
                            _table[X + 2][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                        }

                        //have 3 space
                        else
                        {
                            _table[X + 2][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                        }

                    }

                    //absoultly have 3 space maby 4 space
                    else if(_table[X - 1][Y] == 'S')
                    {
                        _table[X - 1][Y] = 'B';
                        
                        //have 3 space
                        if(_table[X - 2][Y] != 'S' && _table[X + 2][Y] != 'B')
                        {
                            _table[X - 1][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;

                        }
                        
                        //havev 4 space
                        else if(_table[X - 2][Y] == 'S')
                        {
                            _table[X - 2][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip =  true;
                        }

                        else if(_table[X + 3][Y] == 'W')
                        {
                            _table[X + 2][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            return;
                        }
                    }
                
                }

                else if(exactDirection == "Default")
                {
                   //check ship 2 space
                    if(_table[X - 1][Y] == 'E' && _table[X + 2][Y] == 'E')
                    {
                        //ship had 2 spaces but now fall
                        _table[X][Y] = 'F';
                        _table[X + 1][Y] = 'F';
                        fallShip = true;
                        //atack again random
                        return;
                    }

                    //absoultly have 3 space
                    else if(_table[X - 1][Y] == 'S' && _table[X - 2][Y] == 'E' && _table[X + 2][Y] == 'E')
                    {
                        _table[X - 1][Y] = 'F';
                        _table[X + 1][Y] = 'F';
                        _table[X][Y] = 'F';
                        fallShip = true;
                        shootSuccses++;
                    }

                    //maby ship have 3 or 4 spaces and change direction
                    else if(_table[X - 1][Y] == 'E')
                    {
                        _table[X - 1][Y] = 'W';
                        exactDirection = "Down";
                        fallShip = false;
                        return;
                    }

                    //have 4 space
                    else if(_table[X - 1][Y] == 'S')
                    {
                        //absoultly have 4 apace
                        if(_table[X - 2][Y] == 'S')
                        {
                            _table[X - 2][Y] ='F';
                            _table[X - 1][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                        }

                        //absoultly have 4 spacce but should change direction 
                        else if(_table[X - 2][Y] == 'E' && _table[X + 2][Y] == 'S')
                        {
                            _table[X - 1][Y] = 'B';
                            _table[X- 2][Y] = 'W';
                            exactDirection = "Down";            
                            fallShip = false;      
                            shootSuccses++;
                            
                            return;                  
                        } 

                    }
                     
                }
            }

            else
            {

            }
        }

        else
        {
            direction = "vertical";
        }
    }

    else
    {
        _table[X][Y] = 'W';

        if(X == firstShot[0][0] && Y - firstShot[0][1] > 0)
        {
            if(_table[X][Y - 2] == 'W')
            {
                if(_table[X - 1][Y - 1] == 'W')
                {
                    if(_table[X + 1][Y - 1] != 'W')
                    {
                        exactDirection = "Down";
                    }
                }
                else
                {
                    exactDirection = "Up";
                }
            }
            else
            {
                exactDirection = "Left";
            }
        }

        else if(X == firstShot[0][0] && Y - firstShot[0][1] < 0)
        {
            if(_table[X][Y + 2] == 'W')
            {
                if(_table[X - 1][Y + 1] == 'W')
                {
                    exactDirection = "Down";
                }
      
                else 
                {
                    exactDirection = "Up";
                }
            }
          
            else
            {
                exactDirection = "Right";
            }
        }
     
        else if(Y == firstShot[0][1] && X - firstShot[0][0] > 0)
        {
            if(_table[X - 2][Y] == 'W')
            {
                if(_table[X - 1][Y - 1] == 'W')
                {
                    exactDirection = "Right";
                }
    
                else
                {
                    exactDirection = "Left";
                }
            }
       
            else
            {
                exactDirection = "Up";
            }
        }

        else if(Y == firstShot[0][1] && X - firstShot[0][0] < 0)
        {
            if(_table[X - 2][Y] == 'W')
            {
                if(_table[X - 1][Y - 1] == 'W')
                {
                    exactDirection = "Right";
                }
     
                else
                {
                    exactDirection= "Left";
                }
            }
  
            else
            {
                exactDirection = "Down";
            }

        }        
        
        return ;
    }

}

void choseDirection(char _table[10][10], int randX, int randY)
{
    int x, y;
    while(true)
    {
        if(fallShip == false && shootSuccses != 0)
        {
            if(exactDirection == "Left")
            {
                attackAgain(_table, randX,randY - 1);
            }

            else if(exactDirection == "Right")
            {
                attackAgain(_table, randX,randY + 1);
            }

            else if(exactDirection == "Up")
            {
                attackAgain(_table, randX - 1,randY);
            }
       
            else if(exactDirection == "Down")
            {
                attackAgain(_table, randX + 1, randY);
            }
        }
        
        if(fallShip == true)
        {
            shootSuccses = 0;
            fallShip = false;
            exactDirection = "Default";
            return;
        }

        x = (rand() % 3) - 1;
        y = (rand() % 3) - 1;
        if(x != 0 && y != 0)
        {
            continue;
        }
 
        if(x == 0 && y == 0)
        {
            continue;
        } 
     
        else
        {
            x  = x + randX;
            y = y + randY;

            attackAgain(_table, x, y);   
        }
      
        if(fallShip == true)
        {
            shootSuccses = 0;
            fallShip = false;
            exactDirection = "Default";
            return;
        }
    }
    
}   

void simpleAttack(char _table[10][10])
{
    int xMax;
    int yMax;

    int count = 0;
    int numberOfShook = 0;

    while(true)
    {
        srand(time(0));
        int randX = rand() % 10;
        int randY = rand() % 10;

        if(_table[randX][randY] == 'S')
        {
            firstShot[0][0] = randX;
            firstShot[0][1] = randY;
             
            fallShip = false;

            _table[randX][randY] = 'B';
            shootSuccses++;
            //check space of ship
            if(_table [randX][randY + 1] == 'E' && _table [randX][randY - 1] == 'E' &&
               _table [randX + 1][randY] == 'E' && _table [randX - 1][randY] == 'E')
            {
                fallShip = true;
                count++;    
                //ship is broken
                //next attack
            }

            else
            {
                choseDirection(_table, randX, randY);
            }

            numberOfShook++;
        }
         
        else if(_table[randX][randY] == 'E')
        {
            _table[randX][randY] = 'W';
        }

        else if(_table[randX][randY] == 'W')
        {
            continue;
        }        
    
    }
}

int main()
{

    char table[10][10];

    for(int x = 0; x < 10; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            table[x][y] = 'E';
        }
    }

    table[0][1] = 'S';
    table[0][8] = 'S';
    table[2][1] = 'S';
    table[2][2] = 'S';
    table[2][3] = 'S';
    table[2][4] = 'S';
    table[3][6] = 'S';
    table[3][7] = 'S';
    table[3][8] = 'S';
    table[4][4] = 'S';
    table[5][1] = 'S';
    table[6][1] = 'S';
    table[6][3] = 'S';
    table[6][4] = 'S';
    table[6][5] = 'S';
    table[6][7] = 'S';
    table[7][7] = 'S';
    table[9][3] = 'S';
    table[9][4] = 'S';
    table[9][8] = 'S';


    simpleAttack(table);


    return 0;
}
