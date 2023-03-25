#include <Ps3Controller.h>
#include <esp32-hal-ledc.h>

//#define enA1 13
//#define enB2 25
//#define enA3 2
//#define enB4 18
int motor1pin1 = 12;
int motor1pin2 = 14;
int motor2pin1 = 27;
int motor2pin2 = 26;
int motor3pin1 = 4;
int motor3pin2 = 16;
int motor4pin1 = 17;
int motor4pin2 = 5;

//--------------------------------------- SERVO ----------------------------------------------

#include <ESP32_Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

int pos1 = 0;
int pos2 = 0;
int pos3 = 0;

int rightX;
int rightY;
int leftX;
int leftY;


//---------------------------------------- PS3 ------------------------------------------------

void notify()
{
  rightX = (Ps3.data.analog.stick.rx);
  rightY = (Ps3.data.analog.stick.ry);
  leftX = (Ps3.data.analog.stick.lx);
  leftY = (Ps3.data.analog.stick.ly);


  //---------------------------------- ANALOG KANAN --------------------------------------------
  if (rightX < -100) {
    Serial.println("analog right kiri");
  }
  
  if (rightX > 100) {
    Serial.println("analog right kanan");
  }

  if (rightY < -100) {
    Serial.println("analog right atas");
  }
  
  if (rightY > 100) {
    Serial.println("analog right bawah");
  }
  

  //---------------------------------- ANALOG KIRI --------------------------------------------
  if (leftX < -100) {
    Serial.println("analog left kiri");
  }
  
  if (leftX > 100) {
    Serial.println("analog left kanan");
  }

  if (leftY < -100) {
    Serial.println("analog left atas");
  }
  
  if (leftY > 100) {
    Serial.println("analog left bawah");
  }



  //---------------------------------- Button R/L --------------------------------------------
  if ( Ps3.data.button.l1 ) {
    servo1.write(70);
    Serial.println(" L1 button");
  }

  if ( Ps3.data.button.r1 ) {
    servo1.write(120);
    Serial.println(" R1 button");
  }

  if ( Ps3.data.button.l2 ) {
    servo2.write(70);
    Serial.println(" L2 button");
  }

  if ( Ps3.data.button.r2 ) {
    servo2.write(120);
    Serial.println(" R2 button");
  }

  //---------------------------------- PAD KIRI --------------------------------------------
  {
    if ( Ps3.data.button.up )
    {
      Serial.println("Majuuu");
      maju();
    }

    else if ( Ps3.data.button.right )
    {
      belokkanan();
      Serial.println("Kanannnnn");
    }
    else if ( Ps3.data.button.down )
    {
      Serial.println("Mundurrrr");
      mundur();
    }
    else if ( Ps3.data.button.left )
    {
      belokkiri();
      Serial.println("Kiriiiii");
    }
    else
    {
      hop();
    }
  }


  //--------------------------------  cross/square/triangle/circle  ---------------------------------------

  if ( Ps3.data.button.cross ) {

    Serial.println(" cross button");
  }

  if ( Ps3.data.button.square ) {

    Serial.println(" square button");
  }

  if ( Ps3.data.button.triangle ) {

    Serial.println(" triangle button");
  }

  if ( Ps3.data.button.circle ) {

    Serial.println(" circle button");
  }

  //---------------------------------- select/start/ps button -------------------------
  if ( Ps3.data.button.select ) {
    Serial.println("select button");
  }
  
  if ( Ps3.data.button.start ) {
    Serial.println("start button");
  }
  
  if ( Ps3.data.button.ps ) {
    Serial.println("Playstation button");
  }
  
}

void onConnect() {
  Serial.println("Connected!.");
}

void setup()
{
  Serial.begin(115200);
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("b8:d6:1a:ab:c0:ee");
  Serial.println("Ready.");

  //pinMode(enA1, OUTPUT);
  //pinMode(enB2, OUTPUT);
  //pinMode(enA3, OUTPUT);
  //pinMode(enB4, OUTPUT);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor3pin1, OUTPUT);
  pinMode(motor3pin2, OUTPUT);
  pinMode(motor4pin1, OUTPUT);
  pinMode(motor4pin2, OUTPUT);

  hop();

  servo1.attach(15);
  servo2.attach(32);
  servo3.attach(33);
  servo1.write(pos1);
  servo2.write(pos2);
  servo3.write(pos3);


}

void loop()
{
  if (!Ps3.isConnected())
    return;

  delay(500);
}

void maju() {
  //analogWrite(enA1, 250);
  //analogWrite(enB2, 250);
  //analogWrite(enA3, 250);
  //analogWrite(enB4, 250);
  digitalWrite(motor1pin1, HIGH); //DEPAN
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  digitalWrite(motor3pin1, HIGH); //DEPAN
  digitalWrite(motor3pin2, LOW);

  digitalWrite(motor4pin1, HIGH);
  digitalWrite(motor4pin2, LOW);

}

void belokkanan () {

  digitalWrite(motor1pin1, LOW); //KANAN
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);

  digitalWrite(motor3pin1, HIGH);
  digitalWrite(motor3pin2, LOW);

  digitalWrite(motor4pin1, LOW);
  digitalWrite(motor4pin2, HIGH);

}

void belokkiri () {
  digitalWrite(motor1pin1, HIGH); //KIRI
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  digitalWrite(motor3pin1, LOW);
  digitalWrite(motor3pin2, HIGH);

  digitalWrite(motor4pin1, HIGH);
  digitalWrite(motor4pin2, LOW);
}

void mundur () {

  digitalWrite(motor1pin1, LOW);  //BELAKANG
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);

  digitalWrite(motor3pin1, LOW);  //BELAKANG
  digitalWrite(motor3pin2, HIGH);

  digitalWrite(motor4pin1, LOW);
  digitalWrite(motor4pin2, HIGH);


}

void hop () {

  //digitalWrite(enA1, 0);
  //digitalWrite(enB2, 0);
  digitalWrite(motor1pin1, LOW); //HENTI
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);

  digitalWrite(motor3pin1, LOW); //HENTI
  digitalWrite(motor3pin2, LOW);

  digitalWrite(motor4pin1, LOW);
  digitalWrite(motor4pin2, LOW);


}
