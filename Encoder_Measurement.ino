/* Created by Awan
 * GitHub: https://github.com/awanz
 * Dont Remove This 
 */

#include <math.h>

int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;     //M1 Direction Control
int M2 = 7;     //M1 Direction Control

const byte encoder0pinA = 3;
const byte encoder0pinB = 10;
byte encoder0PinALast;
int duration;
boolean Direction;

const byte encoder0pinA2 = 2;
const byte encoder0pinB2 = 8;
byte encoder0PinALast2;
int duration2;
boolean Direction2;

void stop(void)                    //Stop
{
  digitalWrite(E1,0); 
  digitalWrite(M1,LOW);    
  digitalWrite(E2,0);   
  digitalWrite(M2,LOW);    
}  
void advance(char a,char b)          //Move forward
{
  analogWrite (E1,a);      //PWM Speed Control
  digitalWrite(M1,LOW);    
  analogWrite (E2,b);    
  digitalWrite(M2,LOW);
}  
void back_off (char a,char b)          //Move backward
{
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);   
  analogWrite (E2,b);    
  digitalWrite(M2,HIGH);
}
void turn_R (char a,char b)             //Turn Right
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);    
  analogWrite (E2,b);    
  digitalWrite(M2,HIGH);
}
void turn_L (char a,char b)             //Turn Left
{
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);    
  analogWrite (E2,b);    
  digitalWrite(M2,LOW);
}

void setup(){  
  Serial.begin(57600);                       //Initialize the serial port
  digitalWrite(E1,0); 
  digitalWrite(M1,LOW);    
  digitalWrite(E2,0);   
  digitalWrite(M2,LOW);   
  EncoderInit();                              //Initialize the module
  EncoderInit2();
}

float jarakkanan = 0.0;
float jarakkiri = 0.0;

void loop(){
  //aktifkan ini untuk memajukan robot hanya 5 meter
//  if(jarakkanan >= 5 || jarakkiri >= 5){
//    stop();
//  }else{
//    advance(255,235);
//  }
  advance(255,235);
  Serial.print("Pulse kanan:");
  Serial.println(duration);
  Serial.print("Pulse kiri:");
  Serial.println(duration2);
  
  Serial.print("Jarak Tempuh Kanan:");
  jarakkanan = convertToMeter(duration);
  Serial.print(jarakkanan);
  Serial.println(" Meter");
  jarakkiri = convertToMeter(duration2);
  Serial.print("Jarak Tempuh Kiri:");
  Serial.print(jarakkiri);
  Serial.println(" Meter");
  Serial.println("========");
  Serial.println();
  delay(100);
}

float convertToMeter(int a){
  return a * 0.00523333;
}
void EncoderInit(){
  Direction = true;                            //default -> Forward  
  pinMode(encoder0pinB,INPUT);  
  attachInterrupt(0, wheelSpeed, CHANGE);
}
void EncoderInit2(){
  Direction2 = true;                            //default -> Forward  
  pinMode(encoder0pinB2,INPUT);  
  attachInterrupt(1, wheelSpeed2, CHANGE);
}

 
void wheelSpeed(){
  int Lstate = digitalRead(encoder0pinA);
  if((encoder0PinALast == LOW) && Lstate==HIGH){
    int val = digitalRead(encoder0pinB);
    if(val == LOW && Direction){
      Direction = false;                       //Reverse
    }
    else if(val == HIGH && !Direction){
      Direction = true;                        //Forward
    }
  }
  encoder0PinALast = Lstate;
  if(!Direction)  duration++;
  else  duration--;
}
void wheelSpeed2(){
  int Lstate = digitalRead(encoder0pinA2);
  if((encoder0PinALast2 == LOW) && Lstate==HIGH){
    int val = digitalRead(encoder0pinB2);
    if(val == LOW && Direction2){
      Direction2 = false;                       //Reverse
    }
    else if(val == HIGH && !Direction2){
      Direction2 = true;                        //Forward
    }
  }
  encoder0PinALast2 = Lstate;
  if(!Direction2)  duration2++;
  else  duration2--;
}
