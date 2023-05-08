#include <Ps3Controller.h>

// Pin PWM ke motor driver L298N
const int enA = 12;
const int enB = 33;
const int in1 = 14;
const int in2 = 27;
const int in3 = 26;
const int in4 = 25;

#define pwmSetupChannel
#define pwmWrite
#define motorSpeed 100


void setup() {
  // Setup pin PWM pada ESP32
  pwmSetupChannel(0, 5000, 8, true, enA);
  pwmSetupChannel(1, 5000, 8, true, enB);

  // Setup pin digital pada ESP32
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
 
void loop() {
  // Baca input kecepatan dari sensor atau pengguna
  // Simpan input ke variabel motorSpeed

  // Atur arah putaran motor
  if (motorSpeed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }

  // Set kecepatan motor menggunakan sinyal PWM
  pwmWrite(enA, abs(motorSpeed));
  pwmWrite(enB, abs(motorSpeed));
}
