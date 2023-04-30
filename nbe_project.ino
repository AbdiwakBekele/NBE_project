#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 8, 7, 6, 5);

const int sensor=1; // Assigning analog pin A1 to variable 'sensor'
float tempc = 0 ;  //variable to store temperature in degree Celsius
float vout = 0;  //temporary variable to hold sensor reading

const int pingPin = 4; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 3; // Echo Pin of Ultrasonic Sensor
long duration, inches, cm;


void setup() {
Serial.begin(9600);
pinMode(9, OUTPUT);

//Ultrasonic
pinMode(pingPin, OUTPUT);
pinMode(echoPin, INPUT);

lcd.begin(16,2);
}

void loop() {

digitalWrite(pingPin, LOW);
delayMicroseconds(2);
digitalWrite(pingPin, HIGH);
delayMicroseconds(10);
digitalWrite(pingPin, LOW);

duration = pulseIn(echoPin, HIGH);
inches = microsecondsToInches(duration);
cm = microsecondsToCentimeters(duration);

if(cm <= 10){
  
vout=analogRead(1);
vout=(vout*500)/1023;
tempc=vout; // Storing value in Degree Celsius

lcd.setCursor(0,0);
lcd.print("T : ");
lcd.print(tempc);
lcd.setCursor(0,1);
lcd.print("Person Detected");
delay(500);

if(tempc >= 37.5){
  lcd.setCursor(0,1);
  lcd.print("WARNING! High T.");
  digitalWrite(9, HIGH);
  delay(500);
}
else{
  digitalWrite(9, LOW);
  lcd.setCursor(0,1);
  //lcd.print("                     ");
}

}
else{
  lcd.setCursor(0,0);
  lcd.print("                      ");
  lcd.setCursor(0,1);
  lcd.print("No Person Detected");
  }


Serial.print(inches);
Serial.print("in, ");
Serial.print(cm);
Serial.print("cm");
Serial.println();


delay(100); //Delay of 1 second for ease of viewing


}



long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}













