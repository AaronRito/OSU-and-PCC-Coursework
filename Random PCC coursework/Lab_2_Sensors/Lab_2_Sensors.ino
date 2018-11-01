/* This program calibrates and displays readings form 2 QRE_1113 sensors, and, it dims 2 LED's corrosponding to the readings on the sensors
Authors: Chris Hogan, Aaron Rito */

const int sensorPin1 = 2; 
const int sensorPin2 = 3;
const int ledPin1 = 9;           
const int ledPin2 = 10;  
const int indicatorLedPin = 13; 
const int buttonPin = 6;   

// Sensor value variables...
int sensorMin1 = 60;  
int sensorMax1 = 3000;     
int sensorValue1 = 0;         
int sensorMin2 = 60;  
int sensorMax2 = 3000;     
int sensorValue2 = 0;         

void setup() {
 
  pinMode(indicatorLedPin, OUTPUT);
  pinMode (ledPin1, OUTPUT);
  pinMode (ledPin2, OUTPUT);
  pinMode (buttonPin, INPUT);
  pinMode (sensorPin1, INPUT);
  pinMode (sensorPin2, INPUT);
  Serial.begin(9600);
}

void loop() {
// while the button is pressed, take calibration readings:
  while (digitalRead(buttonPin) == HIGH) {
   calibrate();
  }
// signal the end of the calibration period
  digitalWrite(indicatorLedPin, LOW);  

// read the sensor:
  int QRE_Value1 = readQD1();
  int QRE_Value2 = readQD2();
  
// apply the calibration to the sensor reading
  sensorValue1 = map(QRE_Value1, sensorMin1, sensorMax1, 0, 255);
  sensorValue2 = map(QRE_Value2, sensorMin2, sensorMax2, 0, 255);
  Serial.print(QRE_Value1);
  Serial.print(" ");
  Serial.println(QRE_Value2); 
// read the sensor:
  int sensorReading1 = readQD1();
  int sensorReading2 = readQD2();
// map the sensor range to a range of two options:
  int range1 = map(sensorReading1, sensorMin1, sensorMax1, 0, 1);
  int range2 = map(sensorReading2, sensorMin2, sensorMax2, 0, 1);

// do something different depending on the range1 value:
  switch (range1) {
  case 0:    // black tape
    Serial.print("Sensor 1 is non-reflective");
    break;
  case 1:    // white paper
    Serial.print("Sensor 1 is reflective");
    break;
  }
  delay(1);
  Serial.print("  ");
  
//and again with range2 
  switch (range2) {
  case 0:    // black tape
    Serial.println("Sensor 2 is non-reflective");
    break;
  case 1:    // white paper
    Serial.println("Sensor 2 is reflective");
    break;
    }
  delay(1);

// in case the sensor value is outside the range seen during calibration
  sensorValue1 = constrain(sensorValue1, 0, 255);
  sensorValue2 = constrain(sensorValue2, 0, 255);

// fade the LED using the calibrated value:
  analogWrite(ledPin1, sensorValue1);
  analogWrite(ledPin2, sensorValue2);
  //set the speed of readings
  delay(100);
}

void calibrate() {
  // turn on the indicator LED to indicate that calibration is happening:
  digitalWrite(indicatorLedPin, HIGH);
  // read the sensors:
  int sensorValue1 = readQD1();
  int sensorValue2 = readQD2();
  Serial.print(sensorValue1);
  Serial.print("  ");
  Serial.println(sensorValue2); 
  delay(100);

  // record the maximum and minimum sensor values
  if (sensorValue1 > sensorMax1) {
    sensorMax1 = sensorValue1;
  }
  if (sensorValue1 < sensorMin1) {
    sensorMin1 = sensorValue1;
  }
  if (sensorValue2 > sensorMax2) {
    sensorMax2 = sensorValue2;
  }
  if (sensorValue2 < sensorMin2) {
    sensorMin2 = sensorValue2;
  }
}

int readQD1(){
  //Returns value from the sensorPin1, lower numbers mean more refleacive, more than 3000 means nothing was reflected.
  pinMode( sensorPin1, OUTPUT );
  digitalWrite( sensorPin1, HIGH );  
  delayMicroseconds(10);
  pinMode( sensorPin1, INPUT );

  long time = micros();

//what does this do??
  while (digitalRead(sensorPin1) == HIGH && micros() - time < 3000); 
  int diff = micros() - time;

  return diff;
}

int readQD2(){
  //Returns value from the sensorPin2
  pinMode( sensorPin2, OUTPUT );
  digitalWrite( sensorPin2, HIGH );  
  delayMicroseconds(10);
  pinMode( sensorPin2, INPUT );

  long time = micros();

  //what is happening here???
  while (digitalRead(sensorPin2) == HIGH && micros() - time < 3000); 
  int diff = micros() - time;

  return diff;
}
