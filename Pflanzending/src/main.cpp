#include <Arduino.h>


// Pins für den Feuchtigkeitssensor
#define POWER_PIN  2
#define SIGNAL_PIN 4
// Pins für Ampel
#define GREEN 3
#define YELLOW 22
#define RED 23


int value = 0; // variable to store the sensor value


// Enum für die Farben der LED Ampel
enum trafficlight_state{
  Green, 
  Yellow,
  Red
};


// Funktion für das ansteuern der Ampel
void set_trafficlight(trafficlight_state state){
  if (state == Green){
    digitalWrite(GREEN, 1);
    digitalWrite(YELLOW, 0);
    digitalWrite(RED, 0);
  }
  else if (state == Yellow){
    digitalWrite(GREEN, 0);
    digitalWrite(YELLOW, 1);
    digitalWrite(RED, 0);
  }
  else{
    digitalWrite(GREEN, 0);
    digitalWrite(YELLOW, 0);
    digitalWrite(RED, 1);
  }
}


// Ampel anhand des Wasserstandes umschalten
void switch_trafficlight(int meassurement){
  if (meassurement < 150)
    set_trafficlight(Red);
  else if (meassurement < 375)
    set_trafficlight(Yellow);
  else 
    set_trafficlight(Green);
}

void setup() {
  Serial.begin(9600);
  pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
  pinMode(GREEN, OUTPUT); // für Grün Ampel
  pinMode(YELLOW, OUTPUT); // für Gelb Ampel
  pinMode(RED, OUTPUT); // für Rot Ampel
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
}

void loop() {
  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF

  switch_trafficlight(value);

  Serial.print("Sensor value: ");
  Serial.println(value);

  delay(1000);
}