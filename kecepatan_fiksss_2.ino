#include <Ps3Controller.h>

// Define motor driver pins
#define enA1 12 //ngarep
#define motor1pin1 14
#define motor1pin2 27
#define enB2 33
#define motor2pin1 26
#define motor2pin2 25

#define enA3 2 //buri
#define motor3pin1 4
#define motor3pin2 16
#define enB4 18
#define motor4pin1 17
#define motor4pin2 5

// Define PWM Parameters
const int motorFreq = 1000;
const int motorResolution = 8;

//----------------Define channels for each motor---------------------//
const int motorAChannel = 3;
const int motorBChannel = 4;
const int motorCChannel = 3;
const int motorDChannel = 4;

//-----------------Variables for Motor PWM values--------------------//
int motorAPWM = 0;
int motorBPWM = 0;
int motorCPWM = 0;
int motorDPWM = 0;

// Variables for motor direction - true=forward
bool motorDir = true;

// Variables for joystick values
int leftX = 0;
int leftY = 0;

// Callback Function
void notify() {

  // Get Joystick value
  leftX = (Ps3.data.analog.stick.lx);
  leftY = (Ps3.data.analog.stick.ly);

  //Determine direction from Y axis position
  if (leftY < 0) {
    // Direction is forward
    motorDir = true;
  } else {
    // Direction is reverse
    motorDir = false;
  }

  // Convert joystick values to positive 0 - 255
  int speedX = (abs(leftX) * 2);
  int speedY = (abs(leftY) * 2);

  // Factor in the X axis value to determine motor speeds (assume Motor A is Left motor going forward)
  if (leftX < -10) {
    // Motor B faster than Motor A
    motorAPWM = speedY - speedX;
    motorBPWM = speedY + speedX;
    motorCPWM = speedY - speedX;
    motorDPWM = speedY + speedX;

  } else if (leftX > 10) {
    // Motor A faster than Motor B
    motorAPWM = speedY + speedX;
    motorBPWM = speedY - speedX;
    motorCPWM = speedY + speedX;
    motorDPWM = speedY - speedX;

  } else {
    // Control is in middle, both motors same speed
    motorAPWM = speedY;
    motorBPWM = speedY;
    motorCPWM = speedY;
    motorDPWM = speedY;
  }

  // Ensure that speed values remain in range of 0 - 255
  motorAPWM = constrain(motorAPWM, 0, 200);
  motorBPWM = constrain(motorBPWM, 0, 200);
  motorCPWM = constrain(motorCPWM, 0, 200);
  motorDPWM = constrain(motorDPWM, 0, 200);

  // Drive the motors
  moveMotorsanalogLEFT(motorAPWM, motorBPWM, motorCPWM, motorDPWM, motorDir);

  // Print to Serial Monitor
  Serial.print("X value = ");
  Serial.print(leftX);
  Serial.print(" - Y value = ");
  Serial.print(leftY);
  Serial.print(" - Motor A = ");
  Serial.print(motorAPWM);
  Serial.print(" - Motor B = ");
  Serial.println(motorBPWM);
}

// On Connection function
void onConnect() {
  // Print to Serial Monitor
  Serial.println("Connected.");
}

// Motor movement function
void moveMotorsanalogLEFT(int mtrAspeed, int mtrBspeed, int mtrCspeed, int mtrDspeed, bool mtrdir) {
  // Set direction pins
  if (!mtrdir) {
    // Move in reverse
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
    digitalWrite(motor3pin1, HIGH);
    digitalWrite(motor3pin2, LOW);
    digitalWrite(motor4pin1, HIGH);
    digitalWrite(motor4pin2, LOW);

  } else {
    // Move Forward
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
    digitalWrite(motor3pin1, LOW);
    digitalWrite(motor3pin2, HIGH);
    digitalWrite(motor4pin1, LOW);
    digitalWrite(motor4pin2, HIGH);

  }
  // Drive motors with PWM
  ledcWrite(motorAChannel, mtrAspeed);
  ledcWrite(motorBChannel, mtrBspeed);
  ledcWrite(motorCChannel, mtrCspeed);
  ledcWrite(motorDChannel, mtrDspeed);
}


if ( Ps3.data.button.up ) {
  Serial.println("Majuuu");
}

if ( Ps3.data.button.right ) {
  Serial.println("Kanannnnn");
}

if ( Ps3.data.button.down ) {
  Serial.println("Mundurrrr");
}

if ( Ps3.data.button.left ) {
  Serial.println("Kiriiiii");
}


void setup() {

  Serial.begin(115200);
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("b8:d6:1a:ab:c0:ee");

  // Set motor controller pins as outputs
  pinMode(enA1, OUTPUT);
  pinMode(enB2, OUTPUT);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(enA3, OUTPUT);
  pinMode(enB4, OUTPUT);
  pinMode(motor3pin1, OUTPUT);
  pinMode(motor3pin2, OUTPUT);
  pinMode(motor4pin1, OUTPUT);
  pinMode(motor4pin2, OUTPUT);

  // Set channel Parameters for each motor
  ledcSetup(motorAChannel, motorFreq, motorResolution);
  ledcSetup(motorBChannel, motorFreq, motorResolution);
  ledcSetup(motorCChannel, motorFreq, motorResolution);
  ledcSetup(motorDChannel, motorFreq, motorResolution);

  // Attach Motor PWM pins to corresponding channels
  ledcAttachPin(enA1, motorAChannel);
  ledcAttachPin(enB2, motorBChannel);
  ledcAttachPin(enA3, motorCChannel);
  ledcAttachPin(enB4, motorDChannel);

  // Print to Serial Monitor
  Serial.println("Ready.");
}

void loop() {
  if (!Ps3.isConnected())
    return;
  delay(500);
}
