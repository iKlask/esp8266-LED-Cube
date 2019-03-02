#ifndef CubeFunctions_h
#define CubeFunctions_h

#define GPIO0_PIN 0
#define TX_PIN    1
#define GPIO2_PIN 2
#define RX_PIN    3

#define DS_pin    1 //8
#define STCP_pin  2 //9
#define SHCP_pin  0 //10

#define LEVEL_1 14
#define LEVEL_2 15
#define LEVEL_3 13

void SetRegisterCol(int _num);
void clearReg();
void writeReg();

void ClearLevels();
void DropLevels();
void SetLed(int _num, int _level, bool _val = true);
void Draw();

#endif
