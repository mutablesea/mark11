int motor_voltage_pin=6;
int buttonpin=8;
int buttonold=1;
int buttonnew;
int motor_direction1=4;
int motor_direction2=7;
int buzzer_pin=A1;
int triggerpin1=2;
int triggerpin2=12;
int echopin1=A2;
int echopin2=A3;
int s0=A4,s1=A5,s2=A6,s3=A7,sensorGet=11;
int redPW=0,greenPW=0,bluePW=0;
int whitevalue=0;
int power=10;
unsigned int backtime;
int distance;
int dir=1;
int sec,curr_time,pre_time;
int state=1;
int prostate=0;
int memory=1;

void setup()
{
  pinMode(motor_voltage_pin,OUTPUT);
  pinMode(motor_direction1,OUTPUT);
  pinMode(motor_direction2,OUTPUT);
  pinMode(buzzer_pin,OUTPUT);
  pinMode(triggerpin1,OUTPUT);
  pinMode(triggerpin2,OUTPUT);
  pinMode(echopin1,INPUT);
  pinMode(echopin2,INPUT);
  pinMode(buttonpin,INPUT);
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);

     pinMode(s2,OUTPUT);
      pinMode(sensorGet,INPUT);
        digitalWrite(s0,HIGH);
          digitalWrite(s1,LOW);
          pinMode(power,OUTPUT);
  
     

  Serial.begin(9600);
 }

void loop()
{ 
  buttonnew=digitalRead(buttonpin);
   //Serial.println(buttonnew);
  if (buttonold==0 && buttonnew==1)
  {
    if (prostate==0)
    {   prostate=1;
    }
    else
    {
      prostate=0;
    }
  }
  buttonold=buttonnew;
  
  if (prostate==1)
  {
  
  if (dir==1)
  {
    digitalWrite(triggerpin1,LOW);
    delayMicroseconds(10);
    digitalWrite(triggerpin1,HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerpin1,LOW);
    backtime=pulseIn(echopin1,HIGH);
    distance=34550*backtime/(2000000/4);
  }
  
  if (dir==2)
  {
    
    digitalWrite(triggerpin2,LOW);
    delayMicroseconds(10);
    digitalWrite(triggerpin2,HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerpin2,LOW);
    backtime=pulseIn(echopin2,HIGH);
    distance=34550*backtime/(2000000/4);
    }
    
  if (distance>17)
  {
    analogWrite(buzzer_pin,LOW);
    curr_time=millis();
    if (curr_time-pre_time>=1000/4)
    {
      sec=sec+1;
      pre_time=curr_time;
    }
  }
  analogWrite(power,110);
  digitalWrite(s2,LOW);
   int redPW;
  redPW=pulseIn(sensorGet,LOW);
  delay(20);
  
   digitalWrite(s2,HIGH);

  int greenPW;
  greenPW=pulseIn(sensorGet,LOW);
  delay(20);
   digitalWrite(s2,LOW);

  int bluePW;
  bluePW=pulseIn(sensorGet,LOW);
  delay(20);
  
 Serial.print("red pw= ");
  Serial.print(redPW);
  Serial.print(" green pw= ");
  Serial.print(greenPW);
 Serial.print(" blue pw= ");
 Serial.print(bluePW);
 delay(20);
  Serial.println();
  if (redPW<35 && redPW>8 && greenPW<35 && greenPW>8 && bluePW<35 && bluePW>8)
  {
    Serial.println("white detected");
    analogWrite(buzzer_pin,150);
    delay(10);
    analogWrite(buzzer_pin,LOW);
    delay(10);
    analogWrite(buzzer_pin,150);
    delay(10);
    analogWrite(buzzer_pin,LOW);
    whitevalue=1;
    
  } 
  else
  whitevalue=0;
  Serial.println(whitevalue);



  if (distance<=17)
  {
    
    analogWrite(motor_voltage_pin,0);
    if (memory==1)
    {
      if (state==2)
      {
      digitalWrite(motor_direction1,LOW);
      digitalWrite(motor_direction2,HIGH);
      analogWrite(motor_voltage_pin,150);
      delay(40);
      analogWrite(motor_voltage_pin,0);
      }
      if (state==1)
      {
       digitalWrite(motor_direction1,HIGH);
       digitalWrite(motor_direction2,LOW);
       analogWrite(motor_voltage_pin,150);
       delay(40);
       analogWrite(motor_voltage_pin,0);
      }
    }
    memory=0;
    Serial.println("obstacle");
  }

  
  if (distance<=17)
  {
    
    analogWrite(buzzer_pin,130);
    Serial.println("obstacle");
  }
  

  if ( distance>17 && state==2)
  {
          Serial.println("Going forward");
          digitalWrite(motor_direction1,HIGH);
          digitalWrite(motor_direction2,LOW);
          analogWrite(motor_voltage_pin,150);
          memory=1;
       
  }
  
  if (whitevalue==1 && sec>4 && state==2)
  {
    dir=1;
    state=1;
    sec=0;
    analogWrite(motor_voltage_pin,0);
    analogWrite(buzzer_pin,LOW);
    Serial.println("destination completed");
    whitevalue=0;
    memory=1;
    digitalWrite(power,LOW);
    delay(1000);
  }
  
  if (distance>17 && state==1)
  {
          Serial.println("Going backward");
          digitalWrite(motor_direction1,LOW);
          digitalWrite(motor_direction2,HIGH);
          analogWrite(motor_voltage_pin,150);
          memory=1;       
  }
  
  if (whitevalue==1 && sec>4 && state==1)
  {
    dir=2;
    state=2;
    sec=0;
    analogWrite(motor_voltage_pin,0);
    analogWrite(buzzer_pin,LOW);
    Serial.println("destination completed");
    whitevalue=0;
    memory=1;
    digitalWrite(power,LOW);
    delay(1000);
  }

 //Serial.print("current time= ");
 //Serial.print(sec);
 //Serial.println();
 Serial.print("DISTANCE= ");
 Serial.println(distance);
 Serial.println();

  }
  if (prostate==0)
  {
    analogWrite(motor_voltage_pin,0);
    analogWrite(power,0);
    analogWrite(buzzer_pin,0);
    Serial.println("manually stoped");
    delay(30);
  }
}

  
    

  


  
    

  
