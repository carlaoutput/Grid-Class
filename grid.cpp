/* 
Carla Pastor 
grid.cpp
*** file pending for review/improvement ***
*/

#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "grid.h" 

Grid::Grid()			// check task: build the grid with mover in only square, facing east
{
   grid = new char* [1];    // may I need to remove * in order to make this less painfull 
   grid[0] = new char [1];
   mover_r = 0;
   mover_c = 0;
   mover_d = EAST;
   path = true;
}

Grid::Grid(int r, int c) // build grid with r rows, c cols,  blocks around edge with random exit
// and random mover position and direction
{
   if(r < 4 || c < 4)
   {
      maxRow = 3;
      maxCol = 3;
   }
   else if(r > 40 || c > 40)
   {
      maxRow = 40;
      maxCol = 40;
   }
   else
   {
      maxRow = r;
      maxCol = c;
   }
   grid = new char* [maxRow];
   for(int i = 0; i < maxRow; i++)
      grid[i] = new char [maxCol];
   
   //populates grid with '#' and '.'
   for(int i = 0; i <  maxRow; i++)
   {
      for(int j = 0; j < maxCol; j++)
      {
         if(i == 0 || i == maxRow-1)
            grid[i][j] = '#';
         else if(j == 0 || j == maxCol-1)
            grid[i][j] = '#';
         else
            grid[i][j] = '.';
      }
   }
   
   path = true;
   srand(time(0));

   int r_n = rand() % maxRow,
   r_exit = rand() % maxRow,
   c_n = rand() % maxCol,
   c_exit = rand() % maxCol,
   direction = rand() % 4,
   edge = rand() % 4;
   
   //exit
   switch(edge)
   {
      case NORTH:
         grid[0][c_exit] = ' ';
         break;
      case SOUTH:
         grid[maxRow-1][c_exit] = ' ';
         break;
      case WEST:
         grid[r_exit][0] = ' ';
         break;
      case EAST:
         grid[r_exit][maxCol-1] = ' ';
         break;
   }
   //mover placement
   mover_r = r_n;
   mover_c = c_n;
   mover_d = direction;
}			

Grid::Grid(int r, int c, int mr, int mc, int d) //make empty grid with r rows, c cols, and mover, at row mr, col mc, and facing direction d
{
   if(r < 0 || c < 0)
   {
      maxRow = 1;
      maxCol = 1;
   }
   else if(r > 40 || c > 40)
   {
      maxRow = 40;
      maxCol = 40;
   }
   else
   {
      maxRow = r;    //inicializado correctamente
      maxCol = c;
   }
   
   grid = new char* [maxRow];
   for(int i = 0; i < maxRow; i++)
      grid[i] = new char [maxCol];

   path = true;
   
   //set up grid
   for(int i = 0; i < maxRow; i++)
      for(int j = 0; j < maxCol; j++)
         grid[i][j] = '.';
   
   if(mr > maxRow)
      mr = maxRow-1;
   else if(mr < 0)
      mr = 0;
   
   if(mc > maxCol)
      mc = maxCol-1;
   else if(mc < 0)
      mc = 0;
      
   mover_r = mr;
   mover_c = mc;
   mover_d = d;
}

bool Grid::Move(int s)	// move forward s spaces, if possible
{
   int temp;
   bool flag = false;
   
   switch(mover_d) {
      
      case NORTH:
         if(s > 0) {
            
            if(mover_r - s >= 0) {
               
               temp = mover_r;
               
               for(int i = 0; i < s; i++)
               {
                  if( FrontIsClear())
                  {
                     flag = true;
                     if(grid[mover_r][mover_c] != '0')
                        grid[mover_r][mover_c] = ' ';
                     mover_r--;
                     
                  } else    flag = false;
               }
               
               if(flag == false)  mover_r = temp;
               
               else return true;
            }
         }
         return false;
         break;
      case SOUTH:
        if(s > 0) {
           
            if(mover_r + s <= maxRow)
            {
               temp = mover_r;
               for(int i = 0; i < s; i++)
               {
                  if( FrontIsClear())  {
                     
                     flag = true;
                     if(grid[mover_r][mover_c] != '0')
                        grid[mover_r][mover_c] = ' ';
                     mover_r++; 
                     
                  } else flag = false;
               }
               
               if(flag == false) mover_r = temp;
               
               else  return true;
            }
         }
         return false;
         break;
      case EAST:
      if(s > 0)
         {
            if(mover_c + s <= maxCol)
            {
               temp = mover_c;
               for(int i = 0; i < s; i++)
               {
                  if( FrontIsClear())
                  {
                     flag = true;
                     if(grid[mover_r][mover_c] != '0')
                        grid[mover_r][mover_c] = ' ';
                     mover_c++;
                     
                  } else flag = false;
               }
               
               if(flag == false)
                  mover_c = temp;
                  
               else  return true;
            }
         }
         return false;
         break;
      case WEST:
      if(s > 0)
         {
            if(mover_c - s >= 0) {
               
               temp = mover_c;
              for(int i = 0; i < s; i++)
              {
                  if( FrontIsClear())
                  {
                     flag = true;
                     if(grid[mover_r][mover_c] != '0')
                        grid[mover_r][mover_c] = ' ';
                     mover_c--; 
                     
                  } else flag = false;
               }
               
               if(flag == false)
                  mover_c = temp;
                  
               else  return true;
            }
         }
         return false;
         break;
   }
} 
   
void Grid::TogglePath()		// toggle whether or not moved path is shown
{
   path = !path;
}
   
void Grid::TurnLeft()		// turn the mover to the left
{
   switch(mover_d)
   {
      case NORTH:
         mover_d = WEST;
         break;
      case WEST:
         mover_d = SOUTH;
         break;
      case SOUTH:
         mover_d = EAST;
         break;
      case EAST:
         mover_d = NORTH;
         break;
   }
}
   
void Grid::PutDown()		// put down an item at the mover's position
{
   grid[mover_r][mover_c] = '0';
}
   
bool Grid::PutDown(int r, int c)  // put down an item at (r,c), if possible
{
   if(r < maxRow && c < maxCol && grid[r][c] != '#')
   {
      grid[r][c] = '0';
      return true;
   }
   return false;
}

bool Grid::PickUp()		// pick up item at current position
{
   if(grid[mover_r][mover_c] == '0')
   {
      grid[mover_r][mover_c] = '.';
      return true;
   }else
      return false;
}
   
bool Grid::PlaceBlock(int r, int c)	// put a block at (r,c), if possible
{
   if(r < maxRow && r > 0 && c < maxCol && c > 0 && grid[r][c] != '#')
   {
      grid[r][c] = '#';
      return true;
   }
   return false;
}

void Grid::Grow(int gr, int gc)	// grow the grid by gr maxRow, gc columns
{
   if(maxRow + gr <= 40)
        maxRow += gr;
    else 
        maxRow = 40;
        
    if(maxCol + gc <= 40)
        maxCol += gc;
    else 
        maxCol = 40;
        
    char **newGrid = new char * [maxRow];
    for(int i = 0; i < maxRow; i++)
        newGrid[i] = new char [maxCol];
        
    for(int i = 0; i < maxRow; i++)
        for(int j = 0; j < maxCol;j++)
            newGrid[i][j] = grid[i][j];
    
    for(int i = 0; i < maxRow; i++)
    {
        for(int j = 0; j < maxCol; j++)
            delete [] &grid[i][j];
            
        delete [] grid[i];
    }
    delete [] grid;
    
    grid = newGrid;
}

void Grid::Display() const	// display the grid on screen
{
   cout << "The Grid:\n";
   
   for(int i = 0; i < maxRow; i++)
   {
      for(int j = 0; j < maxCol; j++)
      {
         if(i == mover_r && j == mover_c)
         {
            if(grid[i][j] == '0')
               cout << '@';
            else
               switch(mover_d)
               {
                  case NORTH:
                     cout << '^';
                     break;
                  case WEST:
                     cout << '<';
                     break;
                  case SOUTH:
                     cout << 'v';
                     break;
                  case EAST:
                     cout << '>';
                     break;
               }
         }
         else if(grid[i][j] == ' ' && path == false)
               cout << '.';
         else if(path == true)
            cout << grid[i][j];
            
         cout << " ";
      }
      cout << endl;
   }
}

// Accessors
bool Grid::FrontIsClear() const	// check to see if space in front of mover is clear
{
   switch(mover_d)
   {
      case NORTH:
         if(grid[mover_r-1][mover_c] != '#')
            return true;
         else
            return false;
         break;
      case WEST:
         if(grid[mover_r][mover_c-1] != '#')
            return true;
         else
            return false;
         break;
      case EAST:
         if(grid[mover_r][mover_c+1] != '#')
            return true;
         else
            return false;
         break;
      case SOUTH:
         if(grid[mover_r+1][mover_c] != '#')
            return true;
         else
            return false;
         break;
   }
}

bool Grid::RightIsClear() const	// check to see if space to right of mover is clear
{
   switch(mover_d)
   {
      case NORTH:
         if(grid[mover_r][mover_c+1] != '#')
            return true;
         else
            return false;
         break;
      case WEST:
         if(grid[mover_r-1][mover_c] != '#')
            return true;
         else
            return false;
         break;
      case EAST:
         if(grid[mover_r+1][mover_c] != '#')
            return true;
         else
            return false;
         break;
      case SOUTH:
         if(grid[mover_r][mover_c-1] != '#')
            return true;
         else
            return false;
         break;
   }
}				
				
int Grid:: GetRow() const		// return row of the mover
{
   return mover_r;     
}
   
int Grid:: GetCol() const		// return column of the mover
{
   return mover_c;
}   
   
int Grid:: GetNumRows() const // return number of rows in the grid
{
   return maxRow;
}
   
int Grid:: GetNumCols() const	// return number of columns in the grid
{
   return maxCol;
}   
