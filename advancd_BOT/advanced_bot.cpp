#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

string direction;
string exactDirection = "Default";
string lastDirec;
int shootSuccses = 0;
bool fallShip = false;
int firstShot[1][2];
int count = 0;
int ss = 0;
bool moveMentBot = false;
/// x , y left of ship
void setWAroundF(int y, int x, int size, string direc, char table[10][10])
{

    if(direc == "horizontal")
    {
        if(y != 0 && y != 9)
        {
            table[x][y - 1] = 'W';
            table[x][y + size] = 'W';
        }

        else if(y == 0)
        {
            table[x][y + size] = 'W';
        }

        else if(y == 9)
        {
            table[x][y - 1] = 'W';
        }

        if(x != 0)
        {
            for(int i = y - 1; i <= y + size; i++)
            {
                table[x - 1][i] = 'W';
            }
        }

        if(x != 9)
        {
            for(int i = y - 1; i <= y + size; i++)
            {
                table[x + 1][i] = 'W';
            }
        }
  
    }

    else if(direc == "vertocal")
    {
        if(x != 0 && x != 9)
        {
            table[x - 1][y] = 'W';
            table[x + size][y] = 'W';
        }

        else if(x == 0)
        {
            table[x + size][y] = 'W';
        }

        else if(x == 9)
        {
            table[x - 1][y] = 'W';
        }

        if(y != 9)
        {
            for(int i = x - 1 ; i <= x + size; i++)
            {
                table[i][y + 1] = 'W';
            }

        }
        
        else if(y != 0)
        {
            for(int i = x - 1; i <= x + size; i++)
            {
                table[i][y - 1] = 'W';
            }
        }
    }

}

void win()
{
    cout << "hiiiiiiii";
}

void check()
{
    if(count == 10)
    {
        win();
    }
}

void printMap(char _table[10][10]) {

    // _sleep(20000);
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            cout << _table[i][j] << "  "; 
        }
        cout << endl;
    }
    cout << endl << endl;

    ss++;
    cout << ss;

    cout << endl << endl;
}

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
                lastDirec = "Right";

                if(exactDirection == "Right")
                {                                    
                    if(Y == 9)
                    {
                        if(_table[X][Y - 2] == 'B')
                        {
                            if (_table[X][Y - 3] == 'B')
                            {
                                _table[X][Y] = 'F';
                                _table[X][Y - 1] = 'F';
                                _table[X][Y - 2] = 'F';
                                _table[X][Y - 3] = 'F';
                                setWAroundF(Y - 3,X ,4, "horizontal", _table);
                                fallShip = true;
                                printMap(_table);
                                return;
                            }
                     
                            else
                            {
                                _table[X][Y] = 'F';
                                _table[X][Y - 1] = 'F';
                                _table[X][Y - 2] = 'F';
                                fallShip = true;
                                setWAroundF(Y - 2,X ,3, "horizontal", _table);
                                printMap(_table);         
                                return;
                            }                        
                        }
                    
                        else
                        {
                            _table[X][Y] = 'F';
                            _table[X][Y - 1] = 'F';
                            fallShip = true;
                            setWAroundF(Y - 1, X, 2, "horizontal", _table);
                            printMap(_table);
                            return;
                        }
                    }

                    //table 2 space fall
                    if((_table[X][Y + 1] != 'S' && (_table[X][Y - 2] != 'B')&& Y >= 2)
                        || (Y < 2 && _table[X][Y + 1] != 'S'))
                    {
                        _table[X][Y] = 'F';
                        _table[X][Y - 1] = 'F';
                        printMap(_table);
                        setWAroundF(Y - 1, X, 2, "horizontal", _table);
                        fallShip = true;
                        return;
                    }
                
                    //absoultly have 3 space maby 4 space
                    else if((_table[X][Y + 1] != 'S' && _table[X][Y - 2] == 'B' && Y <= 8) ||
                                (Y == 9 && _table[X][Y - 2] == 'B'))         
                    {
                        //have 4 space
                        if(_table[X][Y - 3] == 'B' && Y >= 3)
                        {
                            _table[X][Y - 3] = 'F';
                            _table[X][Y - 2] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y - 3, X, 4, "horizontal", _table);
                            printMap(_table);
                            fallShip = true;
                        }

                        //have 3 space
                        else
                        {
                            _table[X][Y - 2] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y - 2, X, 3, "horizontal", _table);
                            printMap(_table);
                            fallShip = true;
                        }
                    }

                    //absoultly have 3 space maby 4 space
                    else if(_table[X][Y + 1] == 'S' && Y <= 8)
                    {
                        _table[X][Y + 1] = 'B';

                        if(_table[X][Y - 1] == 'B' && _table[X][Y - 2] == 'B')
                        {
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y - 2] = 'F';
                            fallShip = true;
                            setWAroundF(Y - 2, X, 4, "horizontal", _table);
                            return;
                        }

                        //have 3 space
                        if( (_table[X][Y + 2] != 'S' && _table[X][Y - 2] != 'B' && Y <= 7 && Y >= 2) ||
                                (Y == 1 && _table[X][Y + 2] != 'S'))
                        {
                            _table[X][Y + 1] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y - 1, X, 3, "horizontal", _table);
                            printMap(_table);
                            fallShip = true;
                        }

                        //havev 4 space
                        else if(_table[X][Y + 2] == 'S' && Y <= 7)
                        {
                            _table[X][Y + 2] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y - 1, X, 4, "horizontal", _table);
                            printMap(_table);
                            fallShip =  true;
                        }

                        else if(_table[X][Y - 3] == 'W' && Y >= 2)
                        {
                            _table[X][Y - 2] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y - 2, X, 4, "horizontal", _table);
                            fallShip = true;
                            printMap(_table);
                            return;
                        }

                    }
                }
          
                else if(exactDirection == "Default")
                {
                    if(Y == 9)
                    {
                        if(_table[X][Y - 2] == 'S')
                        {
                            if (_table[X][Y - 3] == 'S')
                            {
                                _table[X][Y] = 'F';
                                _table[X][Y - 1] = 'F';
                                _table[X][Y - 2] = 'F';
                                _table[X][Y - 3] = 'F';
                                fallShip = true;
                                setWAroundF(Y - 3, X, 4, "horizontal", _table);
                                printMap(_table);
                                return;
                            }
                            
                            else
                            {
                                _table[X][Y] = 'F';
                                _table[X][Y - 1] = 'F';
                                _table[X][Y - 2] = 'F';
                                fallShip = true;
                                setWAroundF(Y - 2, X, 3, "horizontal", _table);
                                printMap(_table);
                                return;
                            }                        
                        }
                        else
                        {
                            _table[X][Y] = 'F';
                            _table[X][Y - 1] = 'F';
                            fallShip = true;
                            setWAroundF(Y - 1, X, 2, "horizontal", _table);
                            printMap(_table);
                            return;
                        }
                    }
                    //check ship 2 space
                    if((_table[X][Y + 1] != 'S' && _table[X][Y - 2] != 'S' && (Y <= 8 || Y >= 2)) 
                        
                        || (Y == 1 && _table[X][Y + 1] != 'S') 
                            
                            || (Y == 9 && _table[X][Y - 2] != 'S'))
                    {
                        //ship had 2 spaces but now fall
                        _table[X][Y] = 'F';
                        _table[X][Y - 1] = 'F';
                        setWAroundF(Y - 1, X, 2, "horizontal", _table);
                        printMap(_table);
                        fallShip = true;
                        
                        ///call function to w arount f
                        
                        return;
                    }

                    //absoultly have 3 space
                    else if((_table[X][Y + 1] == 'S' && _table[X][Y + 2] != 'S' && _table[X][Y - 2] != 'S' && (Y <= 7 || Y >= 2))
                            
                            ||(Y == 1 && _table[X][Y + 1] == 'S' && _table[X][Y + 2] != 'S') 
                                
                                || (Y == 9 && _table[X][Y - 2] != 'S'&& _table[X][Y + 1] == 'S'))
                    {
                        _table[X][Y + 1] = 'F';
                        _table[X][Y - 1] = 'F';
                        _table[X][Y] = 'F';
                        setWAroundF(Y - 1, X, 3, "horizontal", _table);
                        printMap(_table);
                        fallShip = true;
                        shootSuccses++;
                        return;
                    }

                    //maby ship have 3 or 4 spaces and change direction
                    else if((_table[X][Y + 1] != 'S' && Y <= 8))
                    {
                        _table[X][Y + 1] = 'W';
                        exactDirection = "Left";
                        fallShip = false;
                        printMap(_table);
                        return;
                    }
                   
                    else if(Y == 9)
                    {
                        exactDirection = "Left";
                        fallShip = false;
                        return;
                    }

                    //have 4 space
                    else if(_table[X][Y + 1] == 'S' && Y >= 1)
                    {
                        //absoultly have 4 apace
                        if(_table[X][Y + 2] == 'S' && Y <= 7)
                        {
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            _table[X][Y + 2] ='F';
                            _table[X][Y + 1] = 'F';
                            setWAroundF(Y - 1, X, 4, "horizontal", _table);
                            printMap(_table);
                            fallShip = true;
                            return ;
                        }

                        //absoultly have 4 spacce but should change direction 
                        else if((_table[X][Y + 2] == 'E' || _table[X][Y + 2] == 'W')  && _table[X][Y - 2] == 'S' && Y <= 7 && Y >= 2)
                        {
                            _table[X][Y + 1] = 'B';
                            _table[X][Y + 2] = 'W';
                            exactDirection = "Left";
                            fallShip = false;      
                            shootSuccses++;
                            printMap(_table);
                            return;                  
                        } 

                    }

                }

            }
            
            if(Y - firstShot[0][1] < 0)
            {
                lastDirec = "Left";

                if(exactDirection == "Left")
                {

                    if(Y == 0)
                    {
                        if(_table[X][Y + 2] == 'B')
                        {
                            if(_table[X][Y + 3] == 'B')
                            {
                                _table[X][Y] = 'F';
                                _table[X][Y + 1] = 'F';
                                _table[X][Y + 2] = 'F';
                                _table[X][Y + 3] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X, 4, "horizontal", _table);
                                printMap(_table);
                                return;
                            }
                            
                            else
                            {
                                _table[X][Y] = 'F';
                                _table[X][Y + 1] = 'F';
                                _table[X][Y + 2] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X, 3, "horizontal", _table);
                                printMap(_table);
                                return;                            
                            }
                        }
                    
                        else
                        {
                            _table[X][Y] = 'F';
                            _table[X][Y + 1] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X, 2, "horizontal", _table);
                            printMap(_table);
                            return;
                        }
                    }

                    //table 2 space fall
                    if((_table[X][Y - 1] != 'S' && _table[X][Y + 2] != 'B' && Y >= 1 && Y <= 7) 
                        || (Y == 0 && _table[X][Y + 2] != 'B') || (Y == 8 && _table[X][Y - 1] != 'S'))
                    {
                        _table[X][Y] = 'F';
                        _table[X][Y + 1] = 'F';
                        setWAroundF(Y, X, 2, "horizontal", _table);
                        printMap(_table);
                        fallShip = true;
                        return;
                    }
                  
                    //absoultly have 3 space maby 4 space
                    else if(_table[X][Y - 1] != 'S' && _table[X][Y + 2] == 'B' && Y >= 1 && Y <= 7)
                    {
                        //have 4 space
                        if(_table[X][Y + 3] == 'B' && Y <= 6)
                        {
                            _table[X][Y + 3] = 'F';
                            _table[X][Y + 2] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X, 4, "horizontal", _table);
                            printMap(_table);
                            return;
                        }

                        //have 3 space
                        else if(Y == 7 || (_table[X][Y + 3] != 'B' && Y <=6))
                        {
                            _table[X][Y + 2] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X, 3, "horizontal", _table);
                            printMap(_table);
                            return;
                        }

                    }

                    //absoultly have 3 space maby 4 space
                    else if((_table[X][Y - 1] == 'S' && Y >= 1) || (Y == 0))
                    {
                        
                        if(Y == 0)
                        {
                            if(_table[X][Y + 3] == 'B')
                            {
                                _table[X][Y] = 'F';
                                _table[X][Y + 1] = 'F';
                                _table[X][Y + 2] = 'F';
                                _table[X][Y + 3] = 'F';
                                setWAroundF(Y, X, 4, "horizontal", _table);
                                printMap(_table);
                                return;
                            }
                           
                            else if(_table[X][Y + 2] == 'B')
                            {
                                _table[X][Y] = 'F';
                                _table[X][Y + 1] = 'F';
                                _table[X][Y + 2] = 'F';                                
                                setWAroundF(Y, X, 3, "horizontal", _table);
                                printMap(_table);
                                return;
                            }

                        }
                    

                        if(Y >= 1)
                            _table[X][Y - 1] = 'B';
                        
                        //have 3 space
                        if(_table[X][Y - 2] != 'S' && _table[X][Y + 2] != 'B' && Y >= 2 && Y <= 7)
                        {
                            _table[X][Y - 1] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y - 1, X, 3, "horizontal", _table);
                            printMap(_table);
                            fallShip = true;
                        }
                        
                        //havev 4 space
                        else if(_table[X][Y - 2] == 'S' && Y >= 2)
                        {
                            _table[X][Y - 2] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y - 2, X, 4, "horizontal", _table);
                            printMap(_table);
                            fallShip =  true;
                        }

                        else if(_table[X][Y + 3] == 'W' && Y <= 6)
                        {
                            _table[X][Y + 2] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y - 1, X, 4, "horizontal", _table);
                            printMap(_table);
                            return;
                        }
                    }
                
                }

                else if(exactDirection == "Default")
                {
                   

                    if(Y == 0)
                    {
                        if(_table[X][Y + 2] == 'S')
                        {
                            if(_table[X][Y + 3] == 'S')
                            {
                                _table[X][Y] = 'F';
                                _table[X][Y + 1] = 'F';
                                _table[X][Y + 2] = 'F';
                                _table[X][Y + 3] = 'F';
                                setWAroundF(Y, X, 4, "horizontal", _table);
                                printMap(_table);
                                fallShip = true;
                                return;
                            }                     
                            
                            else if(_table[X][Y + 3] != 'S')
                            {
                                _table[X][Y] = 'F';
                                _table[X][Y + 1] = 'F';
                                _table[X][Y + 2] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X, 3, "horizontal", _table);
                                printMap(_table);
                                return;                            
                            }
                        }
                                      
                        else if(_table[X][Y + 2] != 'S')
                        {
                            _table[X][Y] = 'F';
                            _table[X][Y + 1] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X, 2, "horizontal", _table);
                            printMap(_table);
                            return;
                        }
                    }

                    //check ship 2 space
                    if(_table[X][Y - 1] != 'S' && _table[X][Y + 2] != 'S' && (Y >= 1 || Y <= 7)
                        || (Y == 0 && _table[X][Y + 2] != 'S') || (Y == 8 && _table[X][Y - 1] != 'S'))
                    {
                        //ship had 2 spaces but now fall
                        _table[X][Y] = 'F';
                        _table[X][Y + 1] = 'F';
                        fallShip = true;
                        setWAroundF(Y, X, 2, "horizontal", _table);
                        printMap(_table);
                        //atack again random
                        return;
                    }

                    //absoultly have 3 space
                    else if(_table[X][Y - 1] == 'S' &&  (_table[X][Y - 2] == 'E' || _table[X][Y - 2] == 'W') && (_table[X][Y + 2] == 'E' || _table[X][Y + 2] == 'W') && Y >= 2 && Y <= 7
                            || (Y == 1 && _table[X][Y - 1] == 'S' && (_table[X][Y + 2] == 'E' ||_table[X][Y + 2] == 'W')))
                    {
                        _table[X][Y - 1] = 'F';
                        _table[X][Y + 1] = 'F';
                        _table[X][Y] = 'F';
                        fallShip = true;
                        shootSuccses++;
                        setWAroundF(Y - 1, X, 3, "horizontal", _table);
                        printMap(_table);
                        return;
                    }

                    //have 4 space
                    else if(_table[X][Y - 1] == 'S' && Y >= 1)
                    {
                        //absoultly have 4 apace
                        if(_table[X][Y - 2] == 'S' && Y >= 2)
                        {
                            _table[X][Y - 2] ='F';
                            _table[X][Y - 1] = 'F';
                            _table[X][Y + 1] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y - 2, X, 4, "horizontal", _table);
                            printMap(_table);
                            fallShip = true;
                            return;
                        }

                        //absoultly have 4 spacce but should change direction 
                        else if((_table[X][Y - 2] == 'E' || _table[X][Y - 2] == 'W') && _table[X][Y + 2] == 'S' && Y >= 2 && Y <= 7)
                        {
                            if(_table[X][Y - 2] == 'W')
                            {
                                if(_table[X][Y + 1] == 'S')
                                {
                                    if(_table[X][Y + 2] == 'S')
                                    {
                                        _table[X][Y] = 'F';
                                        _table[X][Y - 1] = 'F';
                                        _table[X][Y + 1] = 'F';
                                        _table[X][Y + 2] = 'F';
                                        fallShip = true;
                                        setWAroundF(Y - 1, X, 4, "horizontal", _table);
                                        printMap(_table);
                                        shootSuccses++;
                                        return;
                                    }

                                    else
                                    {
                                        _table[X][Y] = 'F';
                                        _table[X][Y - 1] = 'F';
                                        _table[X][Y + 1] = 'F';
                                        fallShip = true;
                                        setWAroundF(Y - 1, X, 3, "horizontal", _table);
                                        printMap(_table);
                                        shootSuccses++;
                                        return;
                                    }

                                }
                       
                                else
                                {
                                    _table[X][Y - 1] = 'F';
                                    _table[X][Y] = 'F';
                                    fallShip = true;      
                                    shootSuccses++;
                                    setWAroundF(Y - 1, X, 2, "horizontal", _table);
                                    printMap(_table); 
                                    return;         
                                }
                            }
                            else
                            {                            
                                _table[X][Y - 1] = 'B';
                                _table[X][Y - 2] = 'W';
                                exactDirection = "Right";            
                                fallShip = false;      
                                shootSuccses++;
                                printMap(_table); 
                                return;    
                            }              
                        } 

                    }  

                    //maby ship have 3 or 4 spaces and change direction
                    else if(((_table[X][Y - 1] != 'S' || _table[X][Y - 1] != 'B') && Y >= 1) || (Y == 0)) 
                    {
                        if(Y >= 1)
                        {   
                            _table[X][Y - 1] = 'W';
                        }
                        exactDirection = "Right";
                        fallShip = false;
                        printMap(_table);
                        return;                    
                    }       
                }                

            }

        }


        else if(Y == firstShot[0][1])
        {
            direction = "vertocal";
            
            if(X - firstShot[0][0] > 0)
            {
                lastDirec = "Down";
                if(exactDirection == "Down")
                {
                    if(X == 9)
                    {
                        if(_table[X - 2][Y] == 'B')
                        {
                            if(_table[X - 3][Y] == 'B')
                            {
                                _table[X][Y] = 'F';
                                _table[X - 1][Y] = 'F';
                                _table[X - 2][Y] = 'F';
                                _table[X - 3][Y] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X - 3, 4, "vertocal", _table);
                                printMap(_table);
                                return;                                
                            }

                            else 
                            {
                                _table[X][Y] = 'F';
                                _table[X - 1][Y] = 'F';
                                _table[X - 2][Y] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X - 2, 3, "vertocal", _table);
                                printMap(_table);
                                return;        
                            }
                        }
                   
                        else 
                        {
                            _table[X][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X - 1, 2, "vertocal", _table);
                            printMap(_table);
                            return;
                        }
                    }

                    //table 2 space fall
                    if((_table[X + 1][Y] != 'S' && _table[X - 2][Y] != 'B' && X <= 8 && X >= 2)
                        || (X == 1 && _table[X + 1][Y] != 'S') || (X == 9 && _table[X - 2][Y] != 'B'))
                    {
                        _table[X][Y] = 'F';
                        _table[X - 1][Y] = 'F';
                        fallShip = true;
                        setWAroundF(Y, X - 1, 2, "vertocal", _table);
                        printMap(_table);  
                        return;
                    }
                
                    //absoultly have 3 space maby 4 space
                    else if(_table[X + 1][Y] != 'S' && _table[X - 2][Y] == 'B' && X >= 2 && X <= 8)
                    {
                        //have 4 space
                        if(_table[X - 3][Y] == 'B' && X >= 3)
                        {
                            _table[X - 3][Y] = 'F';
                            _table[X - 2][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X - 3, 4, "vertocal", _table);
                            printMap(_table);
                            return;
                        }

                        //have 3 space
                        else
                        {
                            _table[X - 2][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X - 2, 3, "vertocal", _table);
                            printMap(_table);
                            return;
                        }

                    }

                    //absoultly have 3 space maby 4 space
                    else if(_table[X + 1][Y] == 'S' && X >= 1 && X <= 8)
                    {
                        _table[X + 1][Y] = 'B';
                        
                        //have 3 space
                        if((_table[X + 2][Y] != 'S' && _table[X - 2][Y] != 'B' && X <= 8 && X >= 2) || 
                            (X == 1) && _table[X + 2][Y] != 'S')
                        {
                            _table[X + 1][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X - 1, 3, "vertocal", _table);
                            printMap(_table);
                            return;
                        }

                        //havev 4 space
                        else if(_table[X + 2][Y] == 'S' && X <= 8)
                        {
                            _table[X + 2][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y, X - 1, 4, "vertocal", _table);
                            printMap(_table);
                            fallShip =  true;
                        }

                        else if(_table[X - 3][Y] == 'W' && _table[X - 2][Y] == 'B' && X >= 3)
                        {
                            _table[X - 2][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X - 2, 4, "vertocal", _table);
                            printMap(_table);
                            return;
                        }
                    }
                }

                else if(exactDirection == "Default")
                {
                    if(X == 9)
                    {
                        if(_table[X - 2][Y] == 'S')
                        {
                            if(_table[X - 3][Y] == 'S')
                            {
                                _table[X][Y] = 'F';
                                _table[X - 1][Y] = 'F';
                                _table[X - 2][Y] = 'F';
                                _table[X - 3][Y] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X - 3, 4, "vertocal", _table);
                                printMap(_table);
                                return;                                
                            }

                            else 
                            {
                                _table[X][Y] = 'F';
                                _table[X - 1][Y] = 'F';
                                _table[X - 2][Y] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X - 2, 3, "vertocal", _table);
                                printMap(_table);
                                return;        
                            }
                        }
                   
                        else 
                        {
                            _table[X][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X - 1, 2, "vertocal", _table);
                            printMap(_table);
                            return;
                        }
                    }
            
                     //check ship 2 space
                    if((_table[X + 1][Y] != 'S' && _table[X - 2][Y] != 'S' && X >= 2 && X <= 8)
                        || ((X == 1) && _table[X + 1][Y] != 'S') 
                        ||((X == 9) && (_table[X - 2][Y] != 'B' || _table[X - 2][Y] != 'S')))
                    {
                        //ship had 2 spaces but now fall
                        _table[X][Y] = 'F';
                        _table[X - 1][Y] = 'F';
                        fallShip = true;
                        setWAroundF(Y, X - 1, 2, "vertocal", _table);
                        printMap(_table);
                        //atack again random
                        return;
                    }

                    //absoultly have 3 space
                    else if((_table[X + 1][Y] == 'S' && _table[X + 2][Y] != 'S' && _table[X - 2][Y] != 'S' && X <= 7 && X >= 2)        
                        || ((X == 8) && _table[X + 1][Y] == 'S' && _table[X - 2][Y] != 'S') 
                            || (X == 1 && _table[X + 1][Y] == 'S' && _table[X + 1][Y] != 'S' ) )
                    {
                        _table[X + 1][Y] = 'F';
                        _table[X - 1][Y] = 'F';
                        _table[X][Y] = 'F';
                        fallShip = true;
                        shootSuccses++;
                        setWAroundF(Y, X - 1, 3, "vertocal", _table);
                        printMap(_table);
                        return;
                    }

                    //maby ship have 3 or 4 spaces and change direction
                    else if(_table[X + 1][Y] != 'S' && X <= 8)
                    {
                        _table[X + 1][Y] = 'W';
                        exactDirection = "Up";
                        fallShip = false;
                        printMap(_table);
                        return;
                    
                    }
    
                    //have 4 space
                    else if(_table[X + 1][Y] == 'S' && X <= 8)
                    {
                        //absoultly have 4 apace
                        if(_table[X + 2][Y] == 'S')
                        {
                            _table[X + 2][Y] ='F';
                            _table[X + 1][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X - 1, 4, "vertocal", _table);
                            printMap(_table);
                            return;
                        }

                        //absoultly have 4 spacce but should change direction 
                        else if(_table[X + 2][Y] != 'S' && _table[X - 2][Y] == 'S')
                        {
                            _table[X + 1][Y] = 'B';
                            _table[X + 2][Y] = 'W';
                            exactDirection = "Up";
                            
                            fallShip = false;      
                            shootSuccses++;
                            printMap(_table);
                            return;                  
                        } 
                    }
                }
            }
            
            else if(X - firstShot[0][0] < 0)
            {
                lastDirec = "Up";
                if(exactDirection == "Up")
                {
                    if(X == 0)
                    {
                        if(_table[X + 2][Y] == 'B')
                        {
                            if(_table[X + 3][Y] == 'B')
                            {
                                _table[X][Y] = 'F';
                                _table[X + 1][Y] = 'F';
                                _table[X + 2][Y] = 'F'; 
                                _table[X + 3][Y] = 'F';                                 
                                fallShip = true;
                                setWAroundF(Y, X, 4, "vertocal", _table);
                                printMap(_table);
                                return;
                            }
                       
                            else
                            {
                                _table[X][Y] = 'F';
                                _table[X + 1][Y] = 'F';
                                _table[X + 2][Y] = 'F'; 
                                fallShip = true;
                                setWAroundF(Y, X, 3, "vertocal", _table);
                                printMap(_table);
                                return;
                            }
                        }
                      
                        else 
                        {
                            _table[X][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X, 2, "vertocal", _table);
                            printMap(_table);
                            return;
                        }
                    }

                    //table 2 space fall
                    if(_table[X - 1][Y] != 'S' && _table[X + 2][Y] != 'B' && X >= 1 && X <= 7 
                    ||(X == 8 && _table[X - 1][Y] != 'S'))
                    {
                        _table[X][Y] = 'F';
                        _table[X + 1][Y] = 'F';
                        fallShip = true;
                        setWAroundF(Y, X, 2, "vertocal", _table);
                        printMap(_table);
                        return;
                    }
                  
                    //absoultly have 3 space maby 4 space
                    else if(_table[X - 1][Y] != 'S' && _table[X + 2][Y] == 'B' && X >= 1 && X <= 7)
                    {
                        //have 4 space
                        if(_table[X + 3][Y] == 'B' && X <= 6)
                        {
                            _table[X + 3][Y] = 'F';
                            _table[X + 2][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y, X, 4, "vertocal", _table);
                            fallShip = true;
                            printMap(_table);
                            return;
                        }

                        //have 3 space
                        else if(_table[X + 2][Y] == 'B' && X <= 7)
                        {
                            _table[X + 2][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y, X, 3, "vertocal", _table);
                            printMap(_table);
                            fallShip = true;
                        }

                    }

                    //absoultly have 3 space maby 4 space
                    else if(_table[X - 1][Y] == 'S' && X >= 1)
                    {
                        _table[X - 1][Y] = 'B';
                        
                        //have 3 space
                        if(_table[X - 2][Y] != 'S' && _table[X + 2][Y] != 'B')
                        {
                            _table[X - 1][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y, X - 1, 3, "vertocal", _table);
                            printMap(_table);
                            fallShip = true;
                            return;
                        }
                        
                        //havev 4 space
                        else if(_table[X - 2][Y] == 'S')
                        {
                            _table[X - 2][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            setWAroundF(Y, X - 2, 4, "vertocal", _table);
                            printMap(_table);
                            fallShip =  true;
                            return;
                        }

                        else if(_table[X + 3][Y] == 'W')
                        {
                            _table[X + 2][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X - 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X - 1, 4, "vertocal", _table);
                            printMap(_table);
                            return;
                        }
                    }
                
                }

                else if(exactDirection == "Default")
                {
                    if(X == 0)
                    {
                        if(_table[X + 2][Y] == 'B')
                        {
                            if(_table[X + 3][Y] == 'B')
                            {
                                _table[X][Y] = 'F';
                                _table[X + 1][Y] = 'F';
                                _table[X + 2][Y] = 'F';
                                _table[X + 3][Y] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X , 4, "vertocal", _table);
                                printMap(_table);
                                return;                                
                            }

                            else
                            {
                                _table[X][Y] = 'F';
                                _table[X + 1][Y] = 'F';
                                _table[X + 2][Y] = 'F';
                                fallShip = true;
                                setWAroundF(Y, X, 3, "vertocal", _table);
                                printMap(_table);
                                return;              
                            }
                        }

                        else 
                        {
                            _table[X][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X, 2, "vertocal", _table);
                            printMap(_table);
                            return;
                        }   
                    }

                    //check ship 2 space
                    if(_table[X - 1][Y] != 'S' && _table[X + 2][Y] != 'S'  && X >= 1 && X <= 7)
                    {
                        //ship had 2 spaces but now fall
                        _table[X][Y] = 'F';
                        _table[X + 1][Y] = 'F';
                        fallShip = true;
                        setWAroundF(Y, X, 2, "vertocal", _table);
                        printMap(_table);
                        //atack again random
                        return;
                    }

                    //absoultly have 3 space
                    else if(_table[X - 1][Y] == 'S' && _table[X - 2][Y] != 'S' && _table[X + 2][Y] != 'S' && X >= 2 && X <= 7)
                    {
                        _table[X - 1][Y] = 'F';
                        _table[X + 1][Y] = 'F';
                        _table[X][Y] = 'F';
                        fallShip = true;
                        shootSuccses++;
                        setWAroundF(Y, X - 1, 3, "vertocal", _table);
                        printMap(_table);
                        return;
                    }

                    //maby ship have 3 or 4 spaces and change direction
                    else if(_table[X - 1][Y] != 'S' && X >= 1)
                    {
                        _table[X - 1][Y] = 'W';
                        exactDirection = "Down";
                        fallShip = false;
                        printMap(_table);
                        return;
                    }

                    //have 4 space
                    else if(_table[X - 1][Y] == 'S' && X >= 1)
                    {
                        //absoultly have 4 apace
                        if(_table[X - 2][Y] == 'S' && X >= 2)
                        {
                            _table[X - 2][Y] ='F';
                            _table[X - 1][Y] = 'F';
                            _table[X + 1][Y] = 'F';
                            _table[X][Y] = 'F';
                            fallShip = true;
                            setWAroundF(Y, X - 2, 4, "vertocal", _table);
                            printMap(_table);
                            return;
                        }

                        //absoultly have 4 spacce but should change direction  
                        else if(_table[X - 2][Y] != 'S'&& _table[X + 2][Y] == 'S' && X >= 2 && X <= 7)
                        {
                            _table[X - 1][Y] = 'B';
                            _table[X- 2][Y] = 'W';
                            exactDirection = "Down";            
                            fallShip = false;      
                            shootSuccses++;
                            printMap(_table);
                            return;                  
                        } 
                    }            
                }
            }
        }
    }

    
    
    
    else if(_table[X][Y] == 'E')
    {
        _table[X][Y] = 'W';
        printMap(_table);


        if(X == firstShot[0][0] && Y - firstShot[0][1] > 0)
        {
            lastDirec = "Right";

            if(Y == 1)
            {
                if(_table[X - 1][0] == 'W')
                {
                    exactDirection = "Down";
                }
                
                else
                {
                    exactDirection = "Up";
                }

                return;
            }

            if(X == 0)
            {
                if(Y == 1)
                {
                    exactDirection = "Down";
                    return;
                }

                else if(_table[X][Y - 2] == 'W')
                {
                    exactDirection = "Down";
                }
             
                else
                {
                    exactDirection = "Left";
                }
             
                return;
            }
   
            else if(X == 9)
            {
                if(Y == 1)
                {
                    exactDirection = "Up";
                    return;
                }

                if(_table[X][Y - 2] == 'W')
                {
                    exactDirection = "Up";
                }
              
                else 
                {
                    exactDirection = "Left";
                    return;
                }

                return;
            }
           
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

                return;
            }
        
            else
            {
                exactDirection = "Left";
            }

            return;
        }
      

        else if(X == firstShot[0][0] && Y - firstShot[0][1] < 0)
        {
            lastDirec = "Left";
      
            if(X == 0)
            {
                if(Y == 8)
                {
                    exactDirection = "Down";
                    return;
                }

                if(_table[X][Y + 2] == 'W')
                {
                    exactDirection = "Down";
                    return;

                }
         
                else 
                {
                    exactDirection = "Right";
                    return;

                }
        
                return;
            }
   
            else if(X == 9)
            {
                if(Y == 8)
                {
                    exactDirection = "Up";
                }

                if(_table[X][Y + 2] == 'W')
                {
                    exactDirection = "Up";
                }
              
                else 
                {
                    exactDirection = "Right";
                }
             
                return;
            }

            if(Y == 8)
            {
                if(_table[X - 1][Y + 1] == 'W')
                {
                    exactDirection = "Down";
                }
                else
                {
                    exactDirection = "Up";
                }
                return;
            }



            if(_table[X][Y + 2] == 'W' && Y <= 7)
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
            return;
        }


        else if(Y == firstShot[0][1] && X - firstShot[0][0] > 0)
        {
            lastDirec = "Down";

            if(Y == 0)
            {
                if(X == 1)
                {
                    exactDirection = "Right";
                }

                if(_table[X - 2][Y] == 'W')
                {
                    exactDirection = "Right";
                }
            
                else 
                {
                    exactDirection = "Up";
                }

                return;
            }


            else if(Y == 9)
            {
                if(X == 1)
                {
                    exactDirection = "Left";
                }

                if(_table[X - 2][Y] == 'W')
                {
                    exactDirection = "Left";
                }
       
                else
                {
                    exactDirection = "Up";
                }
       
                return;
            }


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

            return;
        }

        else if(Y == firstShot[0][1] && X - firstShot[0][0] < 0)
        {
            lastDirec = "Up";

            if(X == 8)
            {
                if(_table[X + 1][Y - 1] == 'W')
                {
                    exactDirection = "Right";
                }
                else 
                {
                    exactDirection = "Left";
                }
                return;
            }

            if(Y == 0)
            {
                if(X == 0)
                {
                    exactDirection = "Right";
                }

                if(_table[X + 1][Y + 1] == 'W')
                {
                    exactDirection = "Down";
                }
                
                else 
                {
                    exactDirection = "Right";
                }
                return;
            }
           
            else if(Y == 9)
            {

                if(X == 8)
                {

                    exactDirection = "Left";
                }

                if(_table[X + 1][Y - 1] == 'W')
                {
                    exactDirection = "Down";
                }
             
                else
                {
                    exactDirection = "Left";
                }
                
                return;
            }


            if(_table[X + 2][Y] == 'W')
            {
                if(_table[X + 1][Y + 1] == 'W')
                {
                    exactDirection = "Left";
                }
     
                else
                {
                    exactDirection= "Right";
                }
                return;
            }

            else
            {
                exactDirection = "Down";
                return;
            }

        }                

        return ;
    
    }



}

void choseDirection(char _table[10][10], int randX, int randY)
{
    
    int x = 0;
    int y = 0;
    int z = 0;

    while(count < 10)
    {
        if(moveMentBot == false)
        {
            cont
        }


        if(fallShip == false && shootSuccses != 0 && exactDirection != "Default")
        {
            z = 1;
            if(exactDirection == "Left")
            {
                if(_table[randX][randY - 1] == 'W')
                {
                    exactDirection = "Default";
                    continue;   
                }

                if(lastDirec == "Up" || lastDirec == "Down")
                {
                    exactDirection = "Default";
                }
     
                attackAgain(_table, randX,randY - 1);
            }

            else if(exactDirection == "Right")
            {
                if(_table[randX][randY + 1] == 'W')
                {
                    exactDirection = "Default";
                    continue;   
                }
            
            
                if(lastDirec == "Up" || lastDirec == "Down")
                {
                    exactDirection = "Default";
                }                
                attackAgain(_table, randX,randY + 1);
            }

            else if(exactDirection == "Up")
            {
                if(_table[randX - 1][randY] == 'W')
                {
                    exactDirection = "Default";
                    continue;   
                }



                if(lastDirec == "Left" || lastDirec == "Right")
                {
                    exactDirection = "Default";
                }  
                attackAgain(_table, randX - 1,randY);
            }
       
            else if(exactDirection == "Down")
            {

                if(_table[randX + 1][randY] == 'W')
                {
                    exactDirection = "Default";
                    continue;   
                }

                if(lastDirec == "Left" || lastDirec == "Right")
                {
                    exactDirection = "Default";
                }  
                attackAgain(_table, randX + 1, randY);
            }
        }
        
        if(fallShip == true)
        {
            shootSuccses = 0;
            fallShip = false;
            exactDirection = "Default";
            count++;
            check();
            return;
        }

        if(fallShip == false && z != 1)
        {
            
            do {
                std::random_device dev;
                std::mt19937 rng(dev());
                std::uniform_int_distribution<int> dist(-1, 1);

                x = dist(rng);
                y = dist(rng);

                // srand(time(0));
                // y = (rand() % 3 ) - 1;
                // x = (rand() % 3 ) - 1;

            } while (abs(x) == abs(y));

            x = x + randX;
            y = y + randY;
            
            if(_table[randX][randY - 1] == 'W' 
               && _table[randX][randY + 1] == 'W')
            {
                if(randX == 0)
                {    
                    x = randX + 1; 
                }
                else if(_table[randX - 1][randY] != 'W')
                {
                    x = randX - 1;
                }
                else
                {
                    x = randX + 1;
                }
            }
            
            else if(_table[randX - 1][randY] == 'W' && _table[randX + 1][randY] == 'W')
            {
                if(randY == 9)
                {
                    y = randY - 1;
                }
                else if(_table[randX][randY + 1] != 'W')
                {
                    y = randY + 1;
                }
                else
                {
                    y = randY - 1;
                }
            }

            if(x < 0 || x > 9 || y < 0 || y > 9)
            {
                continue;
            }
            


            if(_table[x][y] == 'W' || _table[x][y] == 'F')
            {
                continue;
            }
            

            attackAgain(_table, x, y);   
        }    
        
        if(fallShip == true)
        {
            shootSuccses = 0;
            fallShip = false;
            exactDirection = "Default";
            count++;
            check();
            return;
        }
    }

    if(count == 10)
    {
        cout << endl << "WIIIN 110" << endl;
    }
}   

bool checksalam(int x, int y, char _table[10][10])
{
    if(x == 0 && y == 0)
    {
        if(_table[0][1] != 'S' && _table[1][0] != 'S')
        {
            _table[0][0] = 'F';
            _table[0][1] = 'W';
            _table[1][0] = 'W';
            _table[1][1] = 'W';     
            return true;
        }
    }

    else if(x == 0 && y == 9)
    {
        if(_table[0][8] != 'S' && _table[1][9] != 'S')
        {
            _table[0][9] = 'F';            
            _table[0][8] = 'F';
            _table[1][9] = 'F';
            _table[1][8] = 'F';
            return true;
        }
    }

    else if(x == 9 && y == 0)
    {
        if(_table[8][0] != 'S' && _table[9][1] != 'S')
        {
            _table[9][0] = 'F';            
            _table[9][1] = 'F';
            _table[8][1] = 'F';
            _table[8][0] = 'F';

            return true;
        }
    }  

    else if(x == 9 && y == 9)
    {
        if(_table[9][8] != 'S' && _table[8][9] != 'S')
        {
            _table[9][9] = 'F';            
            _table[9][8] = 'F';
            _table[8][9] = 'F';
            _table[8][8] = 'F';
            return true;
        }
    }

    return false;
}

void simpleAttack(char _table[10][10]){   
    

    int numberOfShook = 0;

    while(count < 10)
    {
        if(movement == false)
        {
            continue;
        }
        // std::random_device dev;
        // std::mt19937 rng(dev());
        // std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 9);
        srand(time(0));

        int randX = rand() % 10;
        int randY = rand() % 10;

        if(_table[randX][randY] == 'S')
        {
            movement = true;
            if(checksalam(randX, randY, _table))
            {
                printMap(_table);
                count++;
                fallShip = true;
                check();
                continue;
            }

            firstShot[0][0] = randX;
            firstShot[0][1] = randY;
            
            fallShip = false;

            _table[randX][randY] = 'B';
            shootSuccses++;

            //check space of ship
            if(_table [randX][randY + 1] != 'S' && _table [randX][randY - 1] != 'S' &&
            _table [randX + 1][randY] != 'S' && _table [randX - 1][randY] != 'S' && randX >= 1
            && randX <= 8 && randY >= 1 && randY <= 8)
            
            {
                _table[randX][randY] = 'F';
                fallShip = true;
                count++;    
                setWAroundF(randY, randX, 1, "horizontal", _table);
                printMap(_table);
                check();
                continue;
            }
            
            else
            {
                printMap(_table);
                choseDirection(_table, randX, randY);
            }

            numberOfShook++;
        }
        
        else if(_table[randX][randY] == 'E')
        {
            _table[randX][randY] = 'W';
            movement = false;
        }

        else if(_table[randX][randY] == 'W' || _table[randX][randY] == 'F')
        {
            continue;
        }        
       
        printMap(_table);
    }
    
        cout << endl << "WIIIN 110" << endl;
    
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


    table[0][0] = 'S';
    table[1][6] = 'S';
    table[1][8] = 'S';
    table[1][9] = 'S';
    table[2][1] = 'S';
    table[2][2] = 'S';
    table[2][4] = 'S';
    table[3][9] = 'S';
    table[4][9] = 'S';
    table[5][9] = 'S';
    table[6][9] = 'S';
    table[4][7] = 'S';
    table[4][5] = 'S';
    table[5][5] = 'S';
    table[6][0] = 'S';
    table[6][1] = 'S';
    table[6][2] = 'S';
    table[6][3] = 'S';
    table[9][2] = 'S';
    table[9][3] = 'S';
    table[9][4] = 'S';

    table[4][4] = 'W';
    table[5][4] = 'W';
    table[6][5] = 'W';
    table[5][6] = 'W';
    table[4][6] = 'W';
    table[3][5] = 'W';


    table[2][1] = 'S';
    table[2][2] = 'S';
    table[2][3] = 'S';
    table[2][4] = 'S';

        table[9][9] = 'S';
        table[9][8] = 'S';
        table[9][7] = 'S';
        table[9][6] = 'S';



    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            cout << table[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl << endl;


    simpleAttack(table);
    win();
    return 0;
}

