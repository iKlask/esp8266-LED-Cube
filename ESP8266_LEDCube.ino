#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

#include "CubeFunctions.h"
#include "Animations.h"
#include <SimpleTimer.h>

//  Blynk Auth Token
char auth[] = "YOUR BLINK AUTH TOKEN HERE";

//  Timer and id for Animation function
SimpleTimer timer;
int ani_ID = 0;
int shuffle_ID = 10;
int current_ani = 0;

//  Function Pointer to current Animation
void (*ani_func)();

//  Delay in ms between each animation update
int t_delay = 250;

WidgetLCD lcd(V2);
void LCD_Animation(char* _ani)
{
  lcd.clear();
  lcd.print(0, 0, "Animation:");
  lcd.print(0, 1, _ani);
}

void Shuffle_Animations()
{
  //*
  int _rand = current_ani; 
  while(_rand == current_ani)
  {
    _rand = (int)random(2,7);
  }
  current_ani = _rand;
  //*/
  
  switch(current_ani)
  {
    case 2:
      LCD_Animation("Slither");
      
      ani_func = &ani_Snake;
      //current_ani = 2;
      t_delay = 100;
      Blynk.virtualWrite(V1,100);
      break;
    case 3:
      LCD_Animation("Center Spin");
      
      ani_func = &ani_Spin;
      //current_ani = 3;
      t_delay = 150;
      Blynk.virtualWrite(V1,150);
      break;
    case 4:
      LCD_Animation("Rain");
      
      ani_func = &ani_Rain;
      //current_ani = 4;
      t_delay = 200;
      Blynk.virtualWrite(V1,200);
      break;
    case 5:
      LCD_Animation("Flip");
      
      ani_func = &ani_Flip;
      //current_ani = 5;
      t_delay = 450;
      Blynk.virtualWrite(V1,450);
      break;
    case 6:
      LCD_Animation("Windmill");
      
      ani_func = &ani_Windmill;
      //current_ani = 6;
      t_delay = 200;
      Blynk.virtualWrite(V1,200);
      break;
  }

  timer.deleteTimer(ani_ID);
  ani_ID = timer.setInterval(t_delay, ani_func);
  shuffle_ID = timer.setTimeout(10000, Shuffle_Animations);
}


//* === BLYNK functions ===
///App Connect Sync
BLYNK_APP_CONNECTED()
{
  Blynk.syncAll();
  Blynk.virtualWrite(V1, t_delay);
  lcd.clear();
}

///Menu
BLYNK_WRITE(V0)
{
  switch(param.asInt())
  {
    case 1:
      current_ani = 1;
      Shuffle_Animations();
      break;
    case 2:
      LCD_Animation("Slither");
      
      timer.deleteTimer(shuffle_ID); //just in case still random
      ani_func = &ani_Snake;
      current_ani = 2;
      break;
    case 3:
      LCD_Animation("Center Spin");
      
      timer.deleteTimer(shuffle_ID); //just in case still random
      ani_func = &ani_Spin;
      current_ani = 3;
      break;
    case 4:
      LCD_Animation("Rain");
      
      timer.deleteTimer(shuffle_ID); //just in case still random
      ani_func = &ani_Rain;
      current_ani = 4;
      break;
    case 5:
      LCD_Animation("Flip");
      
      timer.deleteTimer(shuffle_ID); //just in case still random
      ani_func = &ani_Flip;
      current_ani = 5;
      break;
    case 6:
      LCD_Animation("Windmill");
    
      timer.deleteTimer(shuffle_ID); //just in case still random
      ani_func = &ani_Windmill;
      current_ani = 6;
      break;
  }
  
  timer.deleteTimer(ani_ID);
  ani_ID = timer.setInterval(t_delay, ani_func);
}
///Animation Speed
BLYNK_WRITE(V1)
{
  t_delay = param.asInt(); // assigning incoming value from pin V1 to a variable

  //Sets the timer to a new delay
  timer.deleteTimer(ani_ID);
  ani_ID = timer.setInterval(t_delay, ani_func);
}
//* ==========================/

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());

  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void WifiSetUp()
{
  //*/====================
  WiFiManager wifiManager;

  //  set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  //  set static ip
  ////wifiManager.setSTAStaticIPConfig(IPAddress(192,168,10,111), IPAddress(192,168,10,90), IPAddress(255,255,255,0));

  //  set minimu quality of signal so it ignores AP's under that quality
  //  defaults to 8%
  ///wifiManager.setMinimumSignalQuality(50);

  wifiManager.setDebugOutput(false);

  //  sets timeout until configuration portal gets turned off
  //  useful to make it all retry or go to sleep, __in seconds__
  wifiManager.setTimeout(120);  //2 min
  wifiManager.setConnectTimeout(120);

  //alternative to force AP mode: wifiManager.startConfigPortal()
  if (!wifiManager.autoConnect("ESPConnect", "ESPpass0")) {
    Serial.println("failed to connect and hit timeout...");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  }
  //================*/
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  randomSeed(analogRead(0));

  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);
  writeReg();

  
  WifiSetUp();

  Blynk.config(auth);
  Blynk.connect();
  //*/


  Serial.println("SETUP DONE");

  
  //* Set starting Animation
  ani_func = &ani_Snake;
  ani_ID = timer.setInterval(t_delay, ani_func);
  //*/

  // or:
  //Shuffle_Animations();
}

void loop()
{
  Blynk.run();
  timer.run();
  
  Draw();
}

