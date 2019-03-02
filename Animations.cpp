#include "Animations.h"
#include "CubeFunctions.h"
#include <Arduino.h> 

int counter_Snake = 0;
int snake_pat_1[9] = {0,1,2,5,4,3,6,7,8};
int snake_pat_2[9] = {8,7,6,3,4,5,2,1,0};

int spin_pat[8] = {0,1,2,5,8,7,6,3};
int counter_Spin = 0;

int counter_windmill = 0;

int counter_Flip = 1;

//Loops through in a snakeing pattern
  //Level 1: 012 543 678
  //Level 2: 876 345 210
  //Level 3: 012 543 678
void ani_Snake()
{
  ClearLevels();
  // Level 1
  if(counter_Snake < 9)
  {
    SetLed( snake_pat_1[counter_Snake], LEVEL_1);
    counter_Snake++;
  }
  //Level 2
  else if(counter_Snake < 18)
  {
    SetLed( snake_pat_2[counter_Snake - 9], LEVEL_2);
    counter_Snake++;
  }
  //Level 3
  else
  {
    SetLed( snake_pat_1[counter_Snake - 18], LEVEL_3);
    if(counter_Snake >= 26){ counter_Snake = 0; }
    else { counter_Snake++; }
  }
}

//Center Col stays on while outer Cols spin around center
//cols: 0,1,2,5,8,7,6,3
void ani_Spin()
{
  ClearLevels();
  SetLed(4,LEVEL_1);
  SetLed(4,LEVEL_2);
  SetLed(4,LEVEL_3);

  SetLed(spin_pat[counter_Spin],LEVEL_1);
  SetLed(spin_pat[counter_Spin],LEVEL_2);
  SetLed(spin_pat[counter_Spin],LEVEL_3);
  counter_Spin++;
  if(counter_Spin >= 8) { counter_Spin = 0; }
}

//Random Rain drops
void ani_Rain()
{
  //Push all the levels down
  DropLevels();

  //Pick some new bits
  int i = (int)random(1,5);
  for(int j = 0; j < i; j++)
  {
    int r = (int)random(9);
    SetLed(r, LEVEL_3);
  }
}


// L1: 345 L3: 345
// L1: 012 L3: 678
// L2: 012345678
// L1: 678 L3: 012
void ani_Windmill()
{
  ClearLevels();
  SetLed(3,LEVEL_2);
  SetLed(4,LEVEL_2);
  SetLed(5,LEVEL_2);

  switch(counter_windmill)
  {
    case 0:
      //Pat_1
      SetLed(3,LEVEL_1);
      SetLed(4,LEVEL_1);
      SetLed(5,LEVEL_1);
      
      SetLed(3,LEVEL_3);
      SetLed(4,LEVEL_3);
      SetLed(5,LEVEL_3);
      
      counter_windmill++;
      break;
    case 1:
      //Pat_2
      SetLed(0,LEVEL_1);
      SetLed(1,LEVEL_1);
      SetLed(2,LEVEL_1);
      
      SetLed(6,LEVEL_3);
      SetLed(7,LEVEL_3);
      SetLed(8,LEVEL_3);
      counter_windmill++;
      break;
    case 2:
      //Pat_3
      SetLed(0,LEVEL_2);
      SetLed(1,LEVEL_2);
      SetLed(2,LEVEL_2);
      SetLed(6,LEVEL_2);
      SetLed(7,LEVEL_2);
      SetLed(8,LEVEL_2);
      counter_windmill++;
      break;
    case 3:
      //Pat_4
      SetLed(6,LEVEL_1);
      SetLed(7,LEVEL_1);
      SetLed(8,LEVEL_1);
      
      SetLed(0,LEVEL_3);
      SetLed(1,LEVEL_3);
      SetLed(2,LEVEL_3);
      counter_windmill = 0;
      break;
    defualt:
      counter_windmill = 0;
      break;
  }
}

//Flipping Cube  
  //1 012
  //2 048
  //3 036
  //4 642
  //5 678
  //6 048
  //7 258
  //8 642
void ani_Flip()
{
  ClearLevels();
  switch(counter_Flip)
  {
    case 1:
      for(int lvl = 13; lvl < 16; lvl++)
      {
        SetLed(0,lvl);
        SetLed(1,lvl);
        SetLed(2,lvl);
      }
      break;
    case 2:
      for(int lvl = 13; lvl < 16; lvl++)
      {
        SetLed(0,lvl);
        SetLed(4,lvl);
        SetLed(8,lvl);
      }
      break;
    case 3:
      for(int lvl = 13; lvl < 16; lvl++)
      {
        SetLed(0,lvl);
        SetLed(3,lvl);
        SetLed(6,lvl);
      }
      break;
    case 4:
      for(int lvl = 13; lvl < 16; lvl++)
      {
        SetLed(6,lvl);
        SetLed(4,lvl);
        SetLed(2,lvl);
      }
      break;
    case 5:
      for(int lvl = 13; lvl < 16; lvl++)
      {
        SetLed(6,lvl);
        SetLed(7,lvl);
        SetLed(8,lvl);
      }
      break;
    case 6:
      for(int lvl = 13; lvl < 16; lvl++)
      {
        SetLed(0,lvl);
        SetLed(4,lvl);
        SetLed(8,lvl);
      }
      break;
    case 7:
      for(int lvl = 13; lvl < 16; lvl++)
      {
        SetLed(2,lvl);
        SetLed(5,lvl);
        SetLed(8,lvl);
      }
      break;
    case 8:
      for(int lvl = 13; lvl < 16; lvl++)
      {
        SetLed(6,lvl);
        SetLed(4,lvl);
        SetLed(2,lvl);
      }
      counter_Flip = 0; //will set to 1 on the ++
      break;
  }
  counter_Flip++;
}
