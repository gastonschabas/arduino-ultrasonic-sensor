#include <LiquidCrystal.h>

const int triggerPin = 9; 
const int echoPin    = 8; 

const int greenLedPin  = 11;
const int blueLedPin   = 12;
const int redLedPin    = 13;

const int registerSelectPin = 2;
const int enablePin = 3;

const int DB4 = 4;
const int DB5 = 5;
const int DB6 = 6;
const int DB7 = 7;

LiquidCrystal lcd(
  registerSelectPin, 
  enablePin, 
  DB4,
  DB5,
  DB6,
  DB7
);

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  
  lcd.begin(16, 2);
}

void loop() {
  triggerUltraSound();
  
  double distance = calculateDistance();
  
  printDistanceInSerialPort(distance);
  
  setLedColorBasedOnDistance(distance);
  
  // write distance in LCD
  lcd.clear();
  lcd.setCursor(0,0);          
  lcd.print("d: ");
  lcd.print(distance);
  lcd.print("cm");
  
  delay (200);
}

void triggerUltraSound() {
  digitalWrite(triggerPin,LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin,LOW);
}

double calculateDistance() {
  double duration = pulseIn(echoPin, HIGH);
  double distance = duration * 0.0343 / 2;
}

void printDistanceInSerialPort(double distance) {
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void setLedColorBasedOnDistance(double distance) {
  if(distance > 200) {
    setLedToRed();
  } else if(distance > 100) {
    setLedToYellow();
  } else {
    setLedToGreen();
  }
}

void setLedToRed() {
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(blueLedPin, LOW);
  digitalWrite(redLedPin, LOW);
}

void setLedToYellow() {
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(blueLedPin, LOW);
  digitalWrite(redLedPin, HIGH);
}

void setLedToGreen() {
  digitalWrite(greenLedPin, LOW);
  digitalWrite(blueLedPin, LOW);
  digitalWrite(redLedPin, HIGH);
}
