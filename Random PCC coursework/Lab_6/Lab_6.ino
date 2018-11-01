/* 
This code makes a Tekbot follow a track of black tape.
Authors: Aaron Rito, Chris Hogan
Date: 11/6/14
*/

//motor controls
int EN1 = 10;
int EN2 = 5;
int DIR1 = 11;
int DIR2 = 6;
// sensors and indicator lights
const int sensorPin1 = A0; 
const int sensorPin2 = A1;
int sensorValue1;
int sensorValue2;
int RLED = 2;
int LLED =3;
int GLED =4;


void setup() {
  // initialize pins as I/O's.
  pinMode(EN1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(RLED, OUTPUT);
  pinMode(LLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
    sensorValue1 = analogRead(sensorPin1); 
    sensorValue1 = map(sensorValue1,0,1023,0,255);
    sensorValue2 = analogRead(sensorPin2);  
    sensorValue2 = map(sensorValue2,0,1023,0,255);
    sensorValue1 = constrain(sensorValue1, 0, 255);
    sensorValue2 = constrain(sensorValue2, 0, 255);
   
  
    if (sensorValue1 <= 75 && sensorValue2 <= 75){
    
          forward();    
    }
    else if (sensorValue1 > 75) {  
 
          turnLeft();
    }
    else if (sensorValue2 > 75) {

          turnRight();
   }
 }
 
// this function makes the bot go forward
void forward() {

    digitalWrite (GLED, HIGH);
    analogWrite(EN1, 50);
    digitalWrite(DIR1, HIGH);
    analogWrite(EN2, 50);
    digitalWrite(DIR2, HIGH); 
    digitalWrite (GLED, LOW);
}

// this function turns the bot right...
void turnRight() {
  
    digitalWrite (RLED, HIGH);
    analogWrite(EN1, 100);
    digitalWrite(DIR1, HIGH);
    analogWrite(EN2, 100);
    digitalWrite(DIR2, LOW);   
    delay (10);
    digitalWrite (RLED, LOW);
}
// and this one left....
void turnLeft() {
  
    digitalWrite (LLED, HIGH);
    analogWrite(EN1, 100);
    digitalWrite(DIR1, LOW);
    analogWrite(EN2, 100);
    digitalWrite(DIR2, HIGH);   
    delay (10);
    digitalWrite (LLED, LOW);
}
