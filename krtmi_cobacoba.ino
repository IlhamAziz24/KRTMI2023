#include <Ps3Controller.h>
#include <ESP32Servo.h>

Servo srvmtr;

int motor1pin1 = 14;
int motor1pin2 = 27;
int motor2pin1 = 26;
int motor2pin2 = 25;
int motor3pin1 = 4;
int motor3pin2 = 16;
int motor4pin1 = 17;
int motor4pin2 = 5;

// Controller Joystick Values
int leftX;
int leftY;

// Servo Position
int servoPos = 90;

// Servo Pin
#define SERVO_PIN 15

// Callback Function
void notify() {

  // Get Joystick value
  leftX = (Ps3.data.analog.stick.lx);
  leftY = (Ps3.data.analog.stick.ly);
  

  // Check if joystick was moved upward, indicating return to home (90 degrees)
  //if (leftY < -100) {
    //servoPos = 90;
    //srvmtr.write(servoPos);
    //delay(10);
  //} else {

    // See if joystick was moved left or right, and in what direction. If moved, move servo in that direction
    if (leftX < -100) {
      belokkiri();
      Serial.println("kiri");
      
    }
    else if (leftX > 100) {
      belokkanan();
      Serial.println("kanan");
      
    }

    else if (leftY < -100) {
      maju();
      Serial.println("bawah");
      
    }
    else if (leftY > 100) {
      mundur();
      servoPos--;
      srvmtr.write(servoPos);
      Serial.println("atas");
      
    }
    else {
      hop();
    }
//}

  // Print to Serial Monitor
  Serial.print("X value = ");
  Serial.print(leftX);
  Serial.print(" - Y value = ");
  Serial.print(leftY);
  Serial.print(" - Servo Pos = ");
  Serial.println(servoPos);
}

// On Connection function
void onConnect() {
  // Print to Serial Monitor
  Serial.println("Connected.");
}

void setup() {

  Serial.begin(115200);

  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("b8:d6:1a:ab:c0:ee");

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor3pin1, OUTPUT);
  pinMode(motor3pin2, OUTPUT);
  pinMode(motor4pin1, OUTPUT);
  pinMode(motor4pin2, OUTPUT);

  // Attach Servo to pin
  srvmtr.attach(SERVO_PIN);

  // Home at 90 degrees
  srvmtr.write(servoPos);

  // Print to Serial Monitor
  Serial.println("Ready.");
}

void loop() {
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

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);

  digitalWrite(motor3pin1, HIGH);
  digitalWrite(motor3pin2, LOW);

  digitalWrite(motor4pin1, LOW);
  digitalWrite(motor4pin2, HIGH);

}

void belokkanan () {

  digitalWrite(motor1pin1, HIGH); //KANAN
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  digitalWrite(motor3pin1, HIGH);
  digitalWrite(motor3pin2, LOW);

  digitalWrite(motor4pin1, HIGH);
  digitalWrite(motor4pin2, LOW);

}

void belokkiri () {
  digitalWrite(motor1pin1, LOW); //KIRI
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);

  digitalWrite(motor3pin1, LOW);
  digitalWrite(motor3pin2, HIGH);

  digitalWrite(motor4pin1, LOW);
  digitalWrite(motor4pin2, HIGH);
}

void mundur () {

  digitalWrite(motor1pin1, LOW);  //BELAKANG
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  digitalWrite(motor3pin1, LOW);  //BELAKANG
  digitalWrite(motor3pin2, HIGH);

  digitalWrite(motor4pin1, HIGH);
  digitalWrite(motor4pin2, LOW);


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
