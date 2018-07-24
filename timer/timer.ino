#define AIR_ACTUATOR 4

bool air = false;
long minute = 60;
long hour = minute * 60;
long day = hour * 24;

bool shouldAirBeOn(void){
  long seconds = millis() / 1000;
  //int howOften = 60;
  int howOften = day / 3;
  int forHowLong = 5;
  Serial.print("seconds % howOften: ");
  Serial.println(seconds % howOften);
  return seconds % howOften <= forHowLong;
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

void setup(void) {
  Serial.begin(9600); 
  pinMode(AIR_ACTUATOR, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  airOff();
} 

void loop(void) { 
  if(shouldAirBeOn()) {
    airOn();
  }
  else {
    airOff();
  }
  delay(100); 
} 
