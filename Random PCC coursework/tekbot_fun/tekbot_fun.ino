/*
This code makes a Tekbot run default forward, if it's sensors hit an object it will reverse slowly and turn left or right
Authors: Aaron Rito, Chris Hogan
Date: 10/20/14
*/


// Variables for pinouts. This adds clarity and makes it easy to change the pins if needed....
int EN1 = 10;
int EN2 = 5;
int DIR1 = 11;
int DIR2 = 6;
int BUMP1 = 2;
int BUMP2 = 3;
int hitsomethingR= 0;
int hitsomethingL= 0;


void setup() {
  // initialize pins as I/O's.
  pinMode (13, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(DIR2, OUTPUT);
  attachInterrupt(0, hitWallR, CHANGE);
  attachInterrupt(1, hitWallL, CHANGE);
  
}

void loop() {

    if (hitsomethingR == 0 && hitsomethingL == 0) {
       forward();
    }
    else if (hitsomethingR == 1) {
       reverse();
       turnLeft();
       hitsomethingR = 0;
    }
    else if (hitsomethingL == 1) {
        reverse();
        turnRight();
        hitsomethingL =0 ;  
 }
}
// this function makes the bot go forward
void forward() {

    digitalWrite (13, HIGH);
    analogWrite(EN1, 0);
    digitalWrite(DIR1, HIGH);
    analogWrite(EN2, 0);
    digitalWrite(DIR2, HIGH); 
}
// these are the interrupt functions
void hitWallR() {
    
    hitsomethingR = 1;

}
void hitWallL() {
    
    hitsomethingL = 1;

}
// this function makes the bot back up slowly for 2 seconds....
void reverse() {

    digitalWrite (13, LOW);
    analogWrite(EN1, 150);
    digitalWrite(DIR1, LOW);
    analogWrite(EN2, 150);
    digitalWrite(DIR2, LOW);  
    
    delay (2000);
}
// this function turns the bot right...
void turnRight() {
  
    analogWrite(EN1, 0);
    digitalWrite(DIR1, HIGH);
    analogWrite(EN2, 0);
    digitalWrite(DIR2, LOW);   
    delay (250);
}
// and this one left....
void turnLeft() {
  
    analogWrite(EN1, 0);
    digitalWrite(DIR1, LOW);
    analogWrite(EN2, 0);
    digitalWrite(DIR2, HIGH);   
    delay (250);
}
