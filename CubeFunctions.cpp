#include "CubeFunctions.h"
//#include <BlynkSimpleEsp8266.h>
#include <Arduino.h>

bool registers[16];
bool reg_1[9];
bool reg_2[9];
bool reg_3[9];

void ClearLevels()
{
  for(int i = 0; i < 9; i++)
  {
    reg_1[i] = LOW;
    reg_2[i] = LOW;
    reg_3[i] = LOW;
  }
}

void DropLevels()
{
  for(int i = 0; i < 9; i++) 
  {
    reg_1[i] = reg_2[i];
    reg_2[i] = reg_3[i];
    reg_3[i] = LOW;
  }
}

void SetLed(int _num, int _level, bool _val)
{
  switch(_level)
  {
    case LEVEL_1:
      reg_1[_num] = _val;
      break;
    case LEVEL_2:
      reg_2[_num] = _val;
      break;
    case LEVEL_3:
      reg_3[_num] = _val;
      break;
  }
}


void SetRegisterCol(int _num)
{
  registers[_num] = HIGH;

  registers[LEVEL_1] = reg_1[_num];
  registers[LEVEL_2] = reg_2[_num];
  registers[LEVEL_3] = reg_3[_num];
}

void clearReg() 
{
  for (int i = 0; i<16; i++)
  {
    registers[i] = LOW;
  }
}

void writeReg() 
{
  digitalWrite(STCP_pin, LOW);

  for (int i = 15; i>=0; i--)
  {
    digitalWrite(SHCP_pin, LOW);
    digitalWrite(DS_pin, registers[i]);
    digitalWrite(SHCP_pin, HIGH);
  }
  digitalWrite(STCP_pin, HIGH);

}

void Draw()
{
  for(int i = 0; i < 9; i++)
  {
    clearReg();
    SetRegisterCol(i);
    writeReg();
  }
}
