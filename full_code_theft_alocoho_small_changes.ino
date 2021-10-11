#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
char c = 0;
int i1=2;//left motor
int i2=3;
int i3=4;//right motor
int i4=5;
char o=0;//Variable for storing received data
int x;
int value; // state variable for the LED
int i=1;
int trigPin = 8;//ultrasonic
int echoPin = 11;//ultrasonic
int vibr_Pin =12;//vibration
int smokeA0 = A0;//alocohol
int push=6;//accident push
int count,p,va,v;
int swi=15;//theft analog pin a1
int ir=16;//theft analog pin a2
long duration,distance;//ultrasonic
int analogSensor;//alcohol
long measurement; //vibration
int buzz=13;
long TP_init()
 {
  delay(10);
  long measurement=pulseIn(vibr_Pin, HIGH); 
  return measurement;
}

void forward()
{
      digitalWrite(i2,LOW);
      digitalWrite(i1,HIGH);
      digitalWrite(i3,HIGH);
      digitalWrite(i4,LOW);
}
void left()
{ 
      digitalWrite(i2,LOW);
      digitalWrite(i1,LOW);
      digitalWrite(i3,HIGH);
      digitalWrite(i4,LOW);
}
void right()
{
      digitalWrite(i2,LOW);
      digitalWrite(i1,HIGH);
      digitalWrite(i3,LOW);
      digitalWrite(i4,LOW);
}
void backward()
{
      digitalWrite(i2,HIGH);
      digitalWrite(i1,LOW);
      digitalWrite(i3,LOW);
      digitalWrite(i4,HIGH);
}
void stopcar()
{     
      digitalWrite(i2,LOW);
      digitalWrite(i1,LOW);
      digitalWrite(i3,LOW);
      digitalWrite(i4,LOW);
}   
          
void setup() 
{
  Serial.begin(9600); 
  delay(100);//Sets the data rate in bits per second (baud) for serial data transmission
  pinMode(i1,OUTPUT);//motor
  pinMode(i2,OUTPUT);//motor
  pinMode(i3,OUTPUT);//motor
  pinMode(i4,OUTPUT);//motor
  pinMode(smokeA0, INPUT);//gas
 pinMode(13, OUTPUT);
 pinMode(trigPin, OUTPUT);//ultrasonic
  pinMode(echoPin, INPUT);//ultrasonic
  pinMode(vibr_Pin, INPUT);//vibration sensor
  pinMode(push,INPUT);//pushbutton
  pinMode(swi,INPUT);//switch
  pinMode(ir,INPUT);//ir sensr
}
void theft()
{
  v=digitalRead(swi);
  delay(1000);
  Serial.println("switch is ");
  Serial.println(v);
  while(v==1)
  {
    va=digitalRead(ir);
    delay(1000);
    Serial.println("ir is");
    Serial.println(va);
    if(va==1)
    {
      stopcar();
      digitalWrite(13,HIGH);
      delay(2000);
      digitalWrite(13,LOW);
       mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
       delay(1000);
       mySerial.println("AT+CMGS=\"+919581242287\"\r"); // change to the phone number you using 
       delay(1000);
       mySerial.println("an intruder has entered into ur car");//the content of the message
      delay(200);
      mySerial.println((char)26);//the stopping character
      delay(1000);
    }break;
  }
}
void loop()
{
  analogSensor = analogRead(smokeA0);
  delay(1000);
  Serial.print("alcohol level: ");
  Serial.println(analogSensor);
  if(analogSensor<450)
  {
  Serial.println("Car is okay to start");
  if(Serial.available() > 0)  // Send data only when you receive data:
  { 
    c = Serial.read();      //Read the incoming data and store it into variable data
    Serial.print(c);        //Print Value inside data in Serial monitor
    Serial.print("\n");        //New line 
     if(c=='1')
    {  
      Serial.println("forward");
      forward();
   
  }
  else if(c=='2')//Turn Left
  {
      Serial.println("left");
      left();
  }
  else if(c=='3')//Turn right
  {
      Serial.println("right");
      right();
  }
  else if(c=='4')//Backwards
  {
      Serial.println("back");
      backward();
  }
  else if(c=='5')
  {
      Serial.println("stop");
      stopcar();
  }                          
  }
  delay(1000);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance =(duration/2)/29.1;
  Serial.print("the distance of obj from vehicle is........");
  Serial.print(distance);
  Serial.println("CM");
  delay(100);
  measurement =TP_init();
  delay(500);
  Serial.print("the vibration value is........");
  Serial.println(measurement);
  measure();
  va=digitalRead(swi);
  theft();
}
else
{
  Serial.println("Car doesnot start as the alcohol level is very high");
}}
void measure()
{
  if((distance<=10 || measurement > 3000))
 {
    stopcar();
    Serial.println("car is stopped");
    if(measurement>3000)
    {
    Serial.println("toppled");
    Serial.println("are u okay");
    delay(2000);
    p=digitalRead(push);
    Serial.println(p);
    delay(2000);
  if(p==HIGH)
  {
  Serial.println("okay msg is not sent");
  }

  else if(p==LOW)
  {
  count++;
  while(count==i)
  {
  stopcar();
  Serial.println("Message is being sent");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919581242227\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("TS59ES8965 MET WITH AN ACCIDENT");// The SMS text you want to send
  delay(100);
  Serial.println("Message has ben sent");
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  break;
  }
}}}}       
