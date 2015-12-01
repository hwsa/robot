
/* CREDITOS  L298N_Dual_H_Bridge

This program controls 2 separate DC motors using the L298N 
H Bridge Chip. 


          *THE SUBROUTINES WORK AS FOLLOWS*

motorA(mode, speed)
% replace A with B to control motor B %

mode is a number 0 -> 3 that determines what the motor 
will do.
0 = coast/disable the H bridge
1 = turn motor clockwise
2 = turn motor counter clockwise
3 = brake motor

speed is a number 0 -> 100 that represents percentage of
motor speed.
0 = off
50 = 50% of full motor speed
100 = 100% of full motor speed

EXAMPLE
Say you need to have motor A turn clockwise at 33% of its
full speed.  The subroutine call would be the following...

motorA(1, 33);

Created by 
Iain Portalupi http://www.youtube.com/iainportalupi
1/2/2014

Alterado por Equipe Ligados
11/22/2015

This code is in the public domain.
*/

#include <NewPing.h>

#define TRIGGER_PIN1 12

#define ECHO_PIN1 11

#define TRIGGER_PIN2 10

#define ECHO_PIN2 9

#define MAX_DISTANCE 40

#define ENA 3  //enable A on pin 3 (needs to be a pwm pin)
#define ENB 5  //enable B on pin 8 (needs to be a pwm pin)
#define IN1 4  //IN1 on pin 2 controls one side of bridge A
#define IN2 2  //IN2 on pin 4 controls other side of A
#define IN3 6  //IN3 on pin 6 conrtols one side of bridge B
#define IN4 7  //IN4 on pin 7 controls other side of B



//L298n



void setup() {
 
pinMode(13, OUTPUT);
Serial.begin(9600);
delay(5000);
}

void loop() {


pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);

int tcrt0;
int tcrt1;
int tcrt2;
int tcrt3;

tcrt0 = analogRead(A0);
tcrt1 = analogRead(A1);
tcrt2 = analogRead(A2);
tcrt3 = analogRead(A3);

Serial.println("IR111111");
Serial.println(tcrt0);
Serial.println("IR222222");
Serial.println(tcrt1);
Serial.println("IR333333");
Serial.println(tcrt2);
Serial.println("IR444444");
Serial.println(tcrt3);


if ( tcrt0 < 600 || tcrt1 < 600 ) {
      motorA(1, 100);
      motorB(1, 100);
  } else {
            if ( tcrt2 < 600 || tcrt3 < 600 ) {
                  motorA(2, 100);
                  motorB(2, 100);
                  }
                  
  }

  
NewPing sonar(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);
unsigned int uS1 = sonar.ping();
unsigned int XXX1 = uS1 / US_ROUNDTRIP_CM;

pinMode(ECHO_PIN1,OUTPUT);

digitalWrite(ECHO_PIN1,LOW);

pinMode(ECHO_PIN1,INPUT);

Serial.print("Ping1: ");

Serial.print(uS1 / US_ROUNDTRIP_CM);

Serial.println("cm1");

if (XXX1 < 9 and XXX1 != 0  ){
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  motorB(2,80);
  
}else{
  motorB(2,60);
  motorA(1,60);
   }


NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);
unsigned int uS2 = sonar2.ping();
unsigned int XXX2 = uS2 / US_ROUNDTRIP_CM;

pinMode(ECHO_PIN2,OUTPUT);

digitalWrite(ECHO_PIN2,LOW);

pinMode(ECHO_PIN2,INPUT);

Serial.print("Ping2: ");

Serial.print(uS2 / US_ROUNDTRIP_CM);

Serial.println("cm2");

if (XXX2 < 9 and XXX2 != 0  ){
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  motorA(1, 90);
}

else {
  motorB(2,60);
  motorA(1,60);
  }


  
}
// CONTROLAR MOTORES FUNCAO

//******************   Motor A control   *******************
void motorA(int mode, int percent)
{
  
  //change the percentage range of 0 -> 100 into the PWM
  //range of 0 -> 255 using the map function
  int duty = map(percent, 0, 100, 0, 255);
  
  switch(mode)
  {
    case 0:  //disable/coast
      digitalWrite(ENA, LOW);  //set enable low to disable A
      break;
      
    case 1:  //turn clockwise
      //setting IN1 high connects motor lead 1 to +voltage
      digitalWrite(IN1, HIGH);   
      
      //setting IN2 low connects motor lead 2 to ground
      digitalWrite(IN2, LOW);  
      
      //use pwm to control motor speed through enable pin
      analogWrite(ENA, duty);  
      
      break;
      
    case 2:  //turn counter-clockwise
      //setting IN1 low connects motor lead 1 to ground
      digitalWrite(IN1, LOW);   
      
      //setting IN2 high connects motor lead 2 to +voltage
      digitalWrite(IN2, HIGH);  
      
      //use pwm to control motor speed through enable pin
      analogWrite(ENA, duty);  
      
      break;
      
    case 3:  //brake motor
      //setting IN1 low connects motor lead 1 to ground
      digitalWrite(IN1, LOW);   
      
      //setting IN2 high connects motor lead 2 to ground
      digitalWrite(IN2, LOW);  
      
      //use pwm to control motor braking power 
      //through enable pin
      analogWrite(ENA, duty);  
      
      break;
  }
}
//**********************************************************


//******************   Motor B control   *******************
  void motorB(int mode, int percent)
{
  
  //change the percentage range of 0 -> 100 into the PWM
  //range of 0 -> 255 using the map function
  int duty = map(percent, 0, 100, 0, 255);
  
  switch(mode)
  {
    case 0:  //disable/coast
      digitalWrite(ENB, LOW);  //set enable low to disable B
      break;
      
    case 1:  //turn clockwise
      //setting IN3 high connects motor lead 1 to +voltage
      digitalWrite(IN3, HIGH);   
      
      //setting IN4 low connects motor lead 2 to ground
      digitalWrite(IN4, LOW);  
      
      //use pwm to control motor speed through enable pin
      analogWrite(ENB, duty);  
      
      break;
      
    case 2:  //turn counter-clockwise
      //setting IN3 low connects motor lead 1 to ground
      digitalWrite(IN3, LOW);   
      
      //setting IN4 high connects motor lead 2 to +voltage
      digitalWrite(IN4, HIGH);  
      
      //use pwm to control motor speed through enable pin
      analogWrite(ENB, duty);  
      
      break;
      
    case 3:  //brake motor
      //setting IN3 low connects motor lead 1 to ground
      digitalWrite(IN3, LOW);   
      
      //setting IN4 high connects motor lead 2 to ground
      digitalWrite(IN4, LOW);  
      
      //use pwm to control motor braking power 
      //through enable pin
      analogWrite(ENB, duty);  
      
      break;
  }
}
//**********************************************************
