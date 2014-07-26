// This sketch is designed to validate/troubleshoot the moosetimer schematic
// When pushed to the moosetime arduino:
// - All 5 leds should light
// - The speaker should briefly sound
// - pushing the button should also sound the speaker


void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(5,INPUT);
  tone(4,440,500);
}

void loop() {
  digitalWrite(12,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(8,HIGH);
  Serial.println(digitalRead(5));
  if (digitalRead(5) ==  HIGH) {
   tone(4,440,500);
  }
}
