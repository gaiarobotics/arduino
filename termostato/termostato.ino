// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2
#define ACTUATOR 3
#define AIR_ACTUATOR 4
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 

float target = 30;
float current;
float tempBounce = 0.3;
bool  heating = false;
bool air = false;

void heatingOn(void){
  heating = true;
  digitalWrite(ACTUATOR, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Heating ON");
}

void heatingOff(void){
  heating = false;
  digitalWrite(ACTUATOR, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Heating OFF");
}

void airOn(void){
  air = true;
  digitalWrite(AIR_ACTUATOR, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Air ON");
}

void airOff(void){
  air = false;
  digitalWrite(AIR_ACTUATOR, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Air OFF");
}

void sensorDisconnected(void) {
  heatingOff();
  Serial.println("Sensor disconnected");
}

void setup(void) {
  pinMode(ACTUATOR, OUTPUT);
  pinMode(AIR_ACTUATOR, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  // start serial port 
  Serial.begin(9600); 
  Serial.println("Dallas Temperature IC Control Library Demo"); 
   // Start up the library 
   sensors.begin(); 
   heatingOff();
   airOff();
} 

void loop(void) { 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus 
  /********************************************************************/
  //Serial.print(" Requesting temperatures..."); 
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  //Serial.println("DONE"); 
  /********************************************************************/
  Serial.print("Temperature is: "); 
  Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"?
  Serial.print("Target is: ");
  Serial.println(target);
  
  // You can have more than one DS18B20 on the same bus.  
  // 0 refers to the first IC on the wire
   
  float current = sensors.getTempCByIndex(0);
  
  /*
  if(-127 == current) {
    sensorDisconnected();
  }
  else{
    if(heating){
      if(current >= target){
       heatingOff();
     }
    }
    else {
     if(current <= target - tempBounce){
       heatingOn();
     }
    }
  }
  */
  
  if(!heating && -127 < current && current <= target - tempBounce ){
    heatingOn();
  }
  // Failsafe
  if(current >= target){
    heatingOff();
  }
 
  if((millis() / 1000 / 60 ) % 60 == 0) {
    airOn();
  }
  else {
    airOff();
  }
  
  if(heating) {
    Serial.println("Heating status is: ON");
  }
  else {
    Serial.println("Heating status is: OFF");
  }
  
  delay(1000); 
} 
