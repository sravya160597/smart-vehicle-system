/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include "ESP8266WiFi.h"
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = " f220e369e7ce41398209fe455d7105b7";
WidgetLED led1(V0);
WidgetLED led2(V1);
WidgetLED led3(V2);
WidgetLED led4(V3);
int a,b,c,d;
int sensor1=16;
int sensor2=5;
int sensor3=4;
int sensor4=0;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ramani";
char pass[] = "9848730563";

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(sensor1,INPUT);
  pinMode(sensor2,INPUT);
   pinMode(sensor3,INPUT);
  pinMode(sensor4,INPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  a=digitalRead(sensor1);
  Serial.println(a);
  b=digitalRead(sensor2);
  Serial.println(b);
  c=digitalRead(sensor3);
  Serial.println(c);
  d=digitalRead(sensor4);
  Serial.println(d);
  delay(1000);
  if(a==0)
  {
    led1.on();
    Serial.println("SLOT EMPTY");
  }
  if(a==1)
  {
    led1.off();
    Serial.println("OCCUPIED");
  }
  delay(1000);
  if(b==0)
  {
    led2.on();
    Serial.println("SLOT EMPTY");
  }
  if(b==1)
  {
    led2.off();
    Serial.println("OCCUPIED");
  }
  delay(1000);
  if(c==0)
  {
    led3.on();
    Serial.println("SLOT EMPTY");
  }
  if(c==1)
  {
    led3.off();
    Serial.println("OCCUPIED");
  }
  delay(1000);
  if(d==0)
  {
    led4.on();
    Serial.println("SLOT EMPTY");
  }
  if(d==1)
  {
    led4.off();
    Serial.println("OCCUPIED");
  }
  delay(1000);
}

